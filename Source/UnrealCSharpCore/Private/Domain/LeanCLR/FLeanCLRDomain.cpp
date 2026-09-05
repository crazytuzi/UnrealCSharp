#include "Domain/LeanCLR/FLeanCLRDomain.h"
#if WITH_LEANCLR
#include "HAL/FileManager.h"
#include "Misc/Paths.h"
#include "Domain/LeanCLR/FLeanCLRFunctionLibrary.h"
#include "Domain/Script/FScriptLog.h"
#include "Domain/LeanCLR/FLeanCLRLog.h"
#include "Common/FUnrealCSharpFunctionLibrary.h"
#include "Reflection/FReflectionRegistry.h"
#include "Reflection/FClassReflection.h"
#include "Binding/FBinding.h"
#include "Binding/Class/FBindingClass.h"
#include "Binding/Function/FBindingMethod.h"
#include "CoreMacro/Macro.h"
#include "CoreMacro/BindingMacro.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "CoreMacro/FunctionMacro.h"
THIRD_PARTY_INCLUDES_START
#include "vm/runtime.h"
#include "vm/assembly.h"
#include "vm/class.h"
#include "vm/method.h"
#include "vm/object.h"
#include "vm/reflection.h"
#include "vm/rt_exception.h"
#include "vm/pinvoke.h"
#include "metadata/module_def.h"
#include "alloc/general_allocation.h"
#include "core/rt_result.h"
THIRD_PARTY_INCLUDES_END

TMap<const leanclr::metadata::RtMethodInfo*, TPair<int32, int32>> FLeanCLRDomain::MethodSlotSizes;

TMap<const leanclr::metadata::RtMethodInfo*, FLeanCLRDomain::FPInvokeSignature> FLeanCLRDomain::PInvokeSignatures;

void FLeanCLRDomain::Initialize()
{
	if (bIsInitialized)
	{
		return;
	}

	if (leanclr::vm::Settings::get_file_loader() == nullptr)
	{
		leanclr::vm::Settings::set_file_loader(&FileLoader);

		if (leanclr::vm::Runtime::initialize().is_err())
		{
			leanclr::vm::Settings::set_file_loader(nullptr);

			return;
		}

		RegisterBinding();
	}

	auto InteropAssembly = leanclr::vm::Assembly::load_by_name(TCHAR_TO_UTF8(*INTEROP_NAME));

	if (InteropAssembly.is_err() || InteropAssembly.unwrap() == nullptr)
	{
		return;
	}

	InteropModule = InteropAssembly.unwrap()->mod;

	RegisterInterop();

	if (const auto InitializeLeanCLR = Class_Get_Method_From_Name(InteropModule,
	                                                              COMBINE_FULL_NAME(
		                                                              NAMESPACE_INTEROP, CLASS_LOG_BRIDGE),
	                                                              FUNCTION_LOG_BRIDGE_INITIALIZE_LEANCLR))
	{
		Bridge_Invoke(InitializeLeanCLR);
	}

	if (!InitializeAssembly(FUnrealCSharpFunctionLibrary::GetFullAssemblyPublishPath()))
	{
		UnloadAssembly();

		return;
	}

	bIsInitialized = true;
}

void FLeanCLRDomain::Deinitialize()
{
	if (!bIsInitialized)
	{
		return;
	}

	bIsInitialized = false;

	UnloadAssembly();
}

#define SCRIPT_DOMAIN_INVOKE(Return, Fn, ...) Bridge_Invoke<Return>(Fn, __VA_ARGS__)
#define SCRIPT_DOMAIN_CUSTOM_UNBOX_VALUE
#define SCRIPT_DOMAIN_CUSTOM_FREE
#define SCRIPT_DOMAIN_CUSTOM_INVOKE
#define SCRIPT_DOMAIN_CUSTOM_GET_CLASSES_WITH_ATTRIBUTE
#define SCRIPT_DOMAIN_CUSTOM_REGISTER_LOG
#define SCRIPT_DOMAIN_CUSTOM_REGISTER_BINDING
#define SCRIPT_DOMAIN_CUSTOM_REGISTER_SYNCHRONIZATION_CONTEXT_TICK
#define SCRIPT_DOMAIN_TYPE FLeanCLRDomain
#include "Domain/Script/FScriptDomainImpl.inl"
#undef SCRIPT_DOMAIN_TYPE
#undef SCRIPT_DOMAIN_CUSTOM_REGISTER_SYNCHRONIZATION_CONTEXT_TICK
#undef SCRIPT_DOMAIN_CUSTOM_REGISTER_BINDING
#undef SCRIPT_DOMAIN_CUSTOM_REGISTER_LOG
#undef SCRIPT_DOMAIN_CUSTOM_GET_CLASSES_WITH_ATTRIBUTE
#undef SCRIPT_DOMAIN_CUSTOM_INVOKE
#undef SCRIPT_DOMAIN_CUSTOM_FREE
#undef SCRIPT_DOMAIN_CUSTOM_UNBOX_VALUE

void* FLeanCLRDomain::UnboxValue(const IManagedHandle InManagedHandle)
{
	static uint64 Result{};

	Result = 0;

	if (const auto Object = static_cast<const leanclr::vm::RtObject*>(
			Object_Get_From_Handle(HandleDataGetObjectPointerFn, InManagedHandle));
		Object != nullptr && Object->klass != nullptr && Object->klass->by_val != nullptr)
	{
		FMemory::Memcpy(&Result, leanclr::vm::Object::get_box_value_type_data_ptr(Object),
		                Type_Get_Boxed_Primitive_Size(leanclr::vm::Class::get_element_type(Object->klass)));
	}

	return &Result;
}

void FLeanCLRDomain::Free(const IManagedHandle InManagedHandle)
{
	if (IManagedHandleIsValid(InManagedHandle))
	{
		if (HandleDataFreeFn != nullptr)
		{
			MethodInvokePaths.Remove(InManagedHandle);

			Bridge_Invoke(HandleDataFreeFn, InManagedHandle);
		}
	}
}

IManagedHandle FLeanCLRDomain::Invoke(const IManagedHandle InManagedHandle, const IManagedHandle InManagedMethod,
                                      const int32 InParamCount, void** InParams)
{
	if (IManagedHandleIsValid(InManagedMethod) || MethodBridgeInvokeFn == nullptr)
	{
		if (MethodBridgeInvokeFn != nullptr)
		{
			if (HandleDataGetObjectPointerFn != nullptr)
			{
				const auto Path = MethodInvokePaths.Find(InManagedMethod);

				TPair<const leanclr::metadata::RtMethodInfo*, bool> Entry;

				if (Path != nullptr)
				{
					Entry = *Path;
				}
				else
				{
					Entry.Key = Method_Get_From_Handle(HandleDataGetObjectPointerFn, InManagedMethod);

					Entry.Value = Method_Is_ReferenceType_Constructor(Entry.Key);

					MethodInvokePaths.Add(InManagedMethod, Entry);
				}

				if (Entry.Value)
				{
					Object_Constructor(HandleDataGetObjectPointerFn, Entry.Key, InManagedHandle);

					return InvalidManagedHandle;
				}
			}

			return Bridge_Invoke<IManagedHandle>(MethodBridgeInvokeFn, InManagedHandle,
			                                     InManagedMethod, InParamCount, InParams);
		}
	}

	return InvalidManagedHandle;
}

TArray<FClassReflection*> FLeanCLRDomain::GetClassesWithAttribute(const FClassReflection* InClass,
                                                                  const IManagedHandle InManagedHandle)
{
	TArray<FClassReflection*> Result;

	if (InClass != nullptr && IManagedHandleIsValid(InManagedHandle) &&
		HandleDataGetObjectPointerFn != nullptr && HandleDataAllocFn != nullptr)
	{
		if (const auto UtilsClass = FReflectionRegistry::Get().GetUtilsClass())
		{
			if (const auto GetTypesWithAttributeMethod = GetMethod(UtilsClass->GetManagedClass(),
			                                                       FUNCTION_UTILS_GET_TYPES_WITH_ATTRIBUTE, 3);
				IManagedHandleIsValid(GetTypesWithAttributeMethod))
			{
				const auto Assembly = static_cast<leanclr::metadata::RtAssembly*>(IManagedHandleToObject(
					InManagedHandle));

				if (const auto AssemblyHandle = Assembly_Alloc_Handle(HandleDataAllocFn, Assembly);
					IManagedHandleIsValid(AssemblyHandle))
				{
					int32 OutLength{};

					auto ManagedClass = InClass->GetManagedClass();

					auto ManagedHandle = AssemblyHandle;

					void* InParams[3] = {
						&ManagedClass,
						&ManagedHandle,
						&OutLength
					};

					if (const auto Types = Invoke(InvalidManagedHandle, GetTypesWithAttributeMethod, 3, InParams);
						IManagedHandleIsValid(Types))
					{
						for (auto Index = 0; Index < OutLength; ++Index)
						{
							if (const auto Element = ArrayGet(Types, Index);
								IManagedHandleIsValid(Element))
							{
								Result.Add(FReflectionRegistry::Get().GetClass(
									GetNamespace(Element),
									GetName(Element)));

								Free(Element);
							}
						}

						Free(Types);
					}

					Free(AssemblyHandle);
				}

				Free(GetTypesWithAttributeMethod);
			}
		}
	}

	return Result;
}

const leanclr::metadata::RtMethodInfo* FLeanCLRDomain::Class_Get_Method_From_Name(
	leanclr::metadata::RtModuleDef* InManagedModule, const FString& InClassName, const FString& InMethodName)
{
	if (InManagedModule != nullptr)
	{
		const FTCHARToUTF8 ClassName(*InClassName);

		const FTCHARToUTF8 MethodName(*InMethodName);

		if (const auto ClassResult = InManagedModule->get_class_by_nested_full_name(ClassName.Get(), false, false);
			ClassResult.is_ok())
		{
			if (const auto Class = ClassResult.unwrap();
				leanclr::vm::Class::initialize_all(Class).is_ok())
			{
				return leanclr::vm::Method::find_matched_method_in_class_by_name(Class, MethodName.Get());
			}
		}
	}

	return nullptr;
}

bool FLeanCLRDomain::Runtime_Invoke(const leanclr::metadata::RtMethodInfo* InManagedMethod,
                                    const leanclr::interp::RtStackObject* InParams, const int32 InParamCount,
                                    leanclr::interp::RtStackObject& OutReturn)
{
	if (InManagedMethod != nullptr)
	{
		const auto [ArgumentSlots, ReturnSlots] = Method_Get_Slot_Sizes(InManagedMethod);

		TArray<leanclr::interp::RtStackObject, TInlineAllocator<8>> ArgumentBuffer;

		ArgumentBuffer.SetNumUninitialized(ArgumentSlots);

		TArray<leanclr::interp::RtStackObject, TInlineAllocator<8>> ReturnBuffer;

		ReturnBuffer.SetNumZeroed(ReturnSlots);

		const auto Count = InParams != nullptr ? FMath::Max(0, FMath::Min(InParamCount, ArgumentSlots)) : 0;

		if (Count > 0)
		{
			FMemory::Memcpy(ArgumentBuffer.GetData(), InParams,
			                static_cast<SIZE_T>(Count) * sizeof(leanclr::interp::RtStackObject));
		}

		if (Count < ArgumentSlots)
		{
			FMemory::Memzero(ArgumentBuffer.GetData() + Count,
			                 static_cast<SIZE_T>(ArgumentSlots - Count) * sizeof(leanclr::interp::RtStackObject));
		}


		if (leanclr::vm::RtException* Exception{};
			Runtime_Invoke(InManagedMethod, ArgumentBuffer.GetData(), ReturnBuffer.GetData(), &Exception))
		{
			OutReturn = ReturnBuffer[0];

			return true;
		}
		else
		{
			Unhandled_Exception(Exception);
		}
	}

	return false;
}

bool FLeanCLRDomain::Runtime_Invoke(const leanclr::metadata::RtMethodInfo* InManagedMethod,
                                    const leanclr::interp::RtStackObject* InParams,
                                    leanclr::interp::RtStackObject* OutReturn,
                                    leanclr::vm::RtException** InExc)
{
	if (const auto Result = leanclr::vm::Runtime::invoke_stackobject_arguments_with_run_cctor(
			InManagedMethod, InParams, OutReturn);
		Result.is_ok())
	{
		return true;
	}

	*InExc = leanclr::vm::Exception::get_and_clear_current_exception();

	return false;
}

void FLeanCLRDomain::Unhandled_Exception(leanclr::vm::RtException* InException)
{
	if (InException != nullptr)
	{
		leanclr::utils::Utf8StringBuilder Builder;

		leanclr::vm::Exception::format_exception(InException, Builder);

		FLeanCLRLog::ErrorWriter(Builder.get_const_chars());
	}
}

const leanclr::metadata::RtMethodInfo* FLeanCLRDomain::Method_Get_From_Handle(
	const leanclr::metadata::RtMethodInfo* InManagedBridge, const IManagedHandle InManagedMethod)
{
	if (const auto MethodObject = Object_Get_From_Handle(InManagedBridge, InManagedMethod))
	{
		auto MethodResult = leanclr::vm::Reflection::get_method_info_from_handle_arg(MethodObject);

		return MethodResult.is_ok() ? MethodResult.unwrap() : nullptr;
	}

	return nullptr;
}

bool FLeanCLRDomain::Method_Is_ReferenceType_Constructor(const leanclr::metadata::RtMethodInfo* InManagedMethod)
{
	return InManagedMethod != nullptr &&
		leanclr::vm::Method::is_ctor(InManagedMethod) &&
		leanclr::vm::Method::is_instance(InManagedMethod) &&
		!leanclr::vm::Class::is_value_type(InManagedMethod->parent) &&
		leanclr::vm::Method::get_param_count_exclude_this(InManagedMethod) == 0;
}

const TPair<int32, int32>& FLeanCLRDomain::Method_Get_Slot_Sizes(const leanclr::metadata::RtMethodInfo* InManagedMethod)
{
	if (const auto FoundSlotSize = MethodSlotSizes.Find(InManagedMethod))
	{
		return *FoundSlotSize;
	}

	return MethodSlotSizes.Add(InManagedMethod, {
		                           FMath::Max(
			                           1, static_cast<int32>(leanclr::vm::Method::get_total_arg_stack_object_size(
				                           InManagedMethod))),
		                           FMath::Max(
			                           1, static_cast<int32>(leanclr::vm::Method::get_return_value_stack_object_size(
				                           InManagedMethod)))
	                           });
}

void FLeanCLRDomain::Object_Constructor(const leanclr::metadata::RtMethodInfo* InManagedBridge,
                                        const leanclr::metadata::RtMethodInfo* InManagedConstructor,
                                        const IManagedHandle InManagedHandle)
{
	if (InManagedConstructor != nullptr)
	{
		if (const auto Object = static_cast<leanclr::vm::RtObject*>(Object_Get_From_Handle(
			InManagedBridge, InManagedHandle)))
		{
			leanclr::vm::RtObject* Exception{};

			const auto Result = leanclr::vm::Reflection::invoke_method(
				InManagedConstructor, Object, nullptr, &Exception);

			if (Exception != nullptr)
			{
				Unhandled_Exception(reinterpret_cast<leanclr::vm::RtException*>(Exception));
			}
			else if (Result.is_err())
			{
				Unhandled_Exception(leanclr::vm::Exception::get_and_clear_current_exception());
			}
		}
	}
}

void* FLeanCLRDomain::Object_Get_From_Handle(const leanclr::metadata::RtMethodInfo* InManagedBridge,
                                             const IManagedHandle InManagedHandle)
{
	return InManagedBridge != nullptr && IManagedHandleIsValid(InManagedHandle)
		       ? Bridge_Invoke<void*>(InManagedBridge, InManagedHandle)
		       : nullptr;
}

IManagedHandle FLeanCLRDomain::Handle_Alloc_From_Object(const leanclr::metadata::RtMethodInfo* InManagedBridge,
                                                        leanclr::vm::RtObject* InManagedObject)
{
	return InManagedBridge != nullptr && InManagedObject != nullptr
		       ? Bridge_Invoke<IManagedHandle>(InManagedBridge, InManagedObject, 0)
		       : InvalidManagedHandle;
}

IManagedHandle FLeanCLRDomain::Assembly_Alloc_Handle(const leanclr::metadata::RtMethodInfo* InManagedBridge,
                                                     leanclr::metadata::RtAssembly* InManagedAssembly)
{
	if (InManagedBridge != nullptr)
	{
		if (InManagedAssembly != nullptr)
		{
			if (auto AssemblyResult = leanclr::vm::Reflection::get_assembly_reflection_object(InManagedAssembly);
				AssemblyResult.is_ok())
			{
				return Handle_Alloc_From_Object(InManagedBridge, AssemblyResult.unwrap());
			}
		}
	}

	return InvalidManagedHandle;
}

int32 FLeanCLRDomain::Type_Get_Boxed_Primitive_Size(const leanclr::metadata::RtElementType InElementType)
{
	switch (InElementType)
	{
	case leanclr::metadata::RtElementType::Boolean:
	case leanclr::metadata::RtElementType::I1:
	case leanclr::metadata::RtElementType::U1:
		return 1;
	case leanclr::metadata::RtElementType::I2:
	case leanclr::metadata::RtElementType::U2:
		return 2;
	case leanclr::metadata::RtElementType::I4:
	case leanclr::metadata::RtElementType::U4:
	case leanclr::metadata::RtElementType::R4:
		return 4;
	case leanclr::metadata::RtElementType::I8:
	case leanclr::metadata::RtElementType::U8:
	case leanclr::metadata::RtElementType::R8:
		return 8;
	default:
		return 0;
	}
}

leanclr::interp::RtStackObject FLeanCLRDomain::Stack_Object_From(const IManagedHandle InManagedHandle)
{
	leanclr::interp::RtStackObject Object;

	Object.i64 = InManagedHandle.Value;

	return Object;
}

leanclr::interp::RtStackObject FLeanCLRDomain::Stack_Object_From(const int32 InValue)
{
	leanclr::interp::RtStackObject Object;

	Object.i32 = InValue;

	return Object;
}

leanclr::interp::RtStackObject FLeanCLRDomain::Stack_Object_From(const int64 InValue)
{
	leanclr::interp::RtStackObject Object;

	Object.i64 = InValue;

	return Object;
}

leanclr::interp::RtStackObject FLeanCLRDomain::Stack_Object_From(const float InValue)
{
	leanclr::interp::RtStackObject Object;

	Object.f32 = InValue;

	return Object;
}

leanclr::interp::RtStackObject FLeanCLRDomain::Stack_Object_From(const void* InPointer)
{
	leanclr::interp::RtStackObject Object;

	Object.cptr = InPointer;

	return Object;
}

leanclr::interp::RtStackObject FLeanCLRDomain::Stack_Object_From(leanclr::vm::RtObject* InManagedObject)
{
	leanclr::interp::RtStackObject Object;

	Object.obj = InManagedObject;

	return Object;
}

leanclr::RtErr FLeanCLRDomain::PInvoke_Classify(const leanclr::metadata::RtMethodInfo* InManagedMethod,
                                                FPInvokeSignature& OutSignature)
{
	auto EntryResult = leanclr::vm::PInvokes::get_pinvoke_by_method(InManagedMethod);

	if (EntryResult.is_err())
	{
		return leanclr::RtErr::ExecutionEngine;
	}

	const auto Entry = EntryResult.unwrap();

	if (Entry == nullptr || Entry->func == nullptr)
	{
		return leanclr::RtErr::ExecutionEngine;
	}

	auto ReturnReduceResult = leanclr::interp::InterpDefs::get_reduce_type_and_size_by_typesig(
		InManagedMethod->return_type);

	if (ReturnReduceResult.is_err())
	{
		return leanclr::RtErr::NotImplemented;
	}

	const auto ReturnReduceType = ReturnReduceResult.unwrap().reduce_type;

	switch (ReturnReduceType)
	{
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::Void:
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::I1:
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::U1:
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::I2:
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::U2:
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::I4:
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::I8:
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::I:
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::Ref:
		break;
	default:
		return leanclr::RtErr::NotImplemented;
	}

	const auto ParameterCount = InManagedMethod->parameter_count;

	if (ParameterCount > MaxPInvokeArguments)
	{
		return leanclr::RtErr::NotImplemented;
	}

	for (auto Index = 0; Index < ParameterCount; ++Index)
	{
		const auto [ArgumentReduceType, ArgumentStackObjectSize] = InManagedMethod->arg_descs[Index];

		if (ArgumentStackObjectSize != 1)
		{
			return leanclr::RtErr::NotImplemented;
		}

		if (ArgumentReduceType == leanclr::metadata::RtArgOrLocOrFieldReduceType::R4 ||
			ArgumentReduceType == leanclr::metadata::RtArgOrLocOrFieldReduceType::R8)
		{
			return leanclr::RtErr::NotImplemented;
		}
	}

	OutSignature.Function = reinterpret_cast<UPTRINT>(Entry->func);

	OutSignature.ParamCount = ParameterCount;

	OutSignature.ReturnType = ReturnReduceType;

	return leanclr::RtErr::None;
}

leanclr::RtResultVoid FLeanCLRDomain::PInvoke_Dispatch(leanclr::metadata::RtManagedMethodPointer,
                                                       const leanclr::metadata::RtMethodInfo* InManagedMethod,
                                                       const leanclr::interp::RtStackObject* InParams,
                                                       leanclr::interp::RtStackObject* OutReturn) noexcept
{
	auto Signature = PInvokeSignatures.Find(InManagedMethod);

	if (Signature == nullptr)
	{
		FPInvokeSignature Classified;

		Classified.Error = PInvoke_Classify(InManagedMethod, Classified);

		Signature = &PInvokeSignatures.Add(InManagedMethod, Classified);
	}

	if (Signature->Error != leanclr::RtErr::None)
	{
		return Signature->Error;
	}

	const auto Function = Signature->Function;

	const auto ReturnType = Signature->ReturnType;

	const auto ParameterCount = Signature->ParamCount;

	void* Arguments[MaxPInvokeArguments];

	for (auto Index = 0; Index < ParameterCount; ++Index)
	{
		Arguments[Index] = reinterpret_cast<void*>(InParams[Index].u64);
	}

	PTRINT ReturnValue;

	switch (ParameterCount)
	{
	case 0:
		ReturnValue = reinterpret_cast<PTRINT(*)()>(Function)();
		break;
	case 1:
		ReturnValue = reinterpret_cast<PTRINT(*)(void*)>(Function)(
			Arguments[0]);
		break;
	case 2:
		ReturnValue = reinterpret_cast<PTRINT(*)(void*, void*)>(Function)(
			Arguments[0], Arguments[1]);
		break;
	case 3:
		ReturnValue = reinterpret_cast<PTRINT(*)(void*, void*, void*)>(Function)(
			Arguments[0], Arguments[1], Arguments[2]);
		break;
	case 4:
		ReturnValue = reinterpret_cast<PTRINT(*)(void*, void*, void*, void*)>(Function)(
			Arguments[0], Arguments[1], Arguments[2], Arguments[3]);
		break;
	case 5:
		ReturnValue = reinterpret_cast<PTRINT(*)(void*, void*, void*, void*, void*)>(Function)(
			Arguments[0], Arguments[1], Arguments[2], Arguments[3], Arguments[4]);
		break;
	case 6:
		ReturnValue = reinterpret_cast<PTRINT(*)(void*, void*, void*, void*, void*, void*)>(Function)(
			Arguments[0], Arguments[1], Arguments[2], Arguments[3], Arguments[4], Arguments[5]);
		break;
	case 7:
		ReturnValue = reinterpret_cast<PTRINT(*)(void*, void*, void*, void*, void*, void*, void*)>(Function)(
			Arguments[0], Arguments[1], Arguments[2], Arguments[3], Arguments[4], Arguments[5], Arguments[6]);
		break;
	case 8:
		ReturnValue = reinterpret_cast<PTRINT(*)(void*, void*, void*, void*, void*, void*, void*, void*)>(Function)(
			Arguments[0], Arguments[1], Arguments[2], Arguments[3], Arguments[4], Arguments[5], Arguments[6],
			Arguments[7]);
		break;
	default:
		return leanclr::RtErr::NotImplemented;
	}

	OutReturn->u64 = 0;

	switch (ReturnType)
	{
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::Void:
		break;
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::I1:
		OutReturn->i32 = static_cast<int32>(static_cast<int8>(ReturnValue));
		break;
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::U1:
		OutReturn->i32 = static_cast<int32>(static_cast<uint8>(ReturnValue));
		break;
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::I2:
		OutReturn->i32 = static_cast<int32>(static_cast<int16>(ReturnValue));
		break;
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::U2:
		OutReturn->i32 = static_cast<int32>(static_cast<uint16>(ReturnValue));
		break;
	case leanclr::metadata::RtArgOrLocOrFieldReduceType::I4:
		OutReturn->i32 = static_cast<int32>(ReturnValue);
		break;
	default:
		OutReturn->u64 = static_cast<uint64>(ReturnValue);
		break;
	}

	return leanclr::Unit{};
}

bool FLeanCLRDomain::FileLoader(const char* InAssemblyName, const char* InExtension, leanclr::vm::FileData& OutFileData)
{
	const auto AssemblyName = FString(UTF8_TO_TCHAR(InAssemblyName));

	const auto Extension = FString(UTF8_TO_TCHAR(InExtension));

	for (const auto& Directory : {
		     FLeanCLRFunctionLibrary::GetLibDirectory(), FUnrealCSharpFunctionLibrary::GetFullPublishDirectory()
	     })
	{
		const auto FileName = FString::Printf(TEXT(
			"%s/%s.%s"
		),
		                                      *Directory,
		                                      *AssemblyName,
		                                      *Extension
		);

		if (const auto FileReader{IFileManager::Get().CreateFileReader(*FileName, FILEREAD_Silent)})
		{
			if (const auto TotalSize = FileReader->TotalSize();
				TotalSize > 0)
			{
				if (const auto Buffer = leanclr::alloc::GeneralAllocation::malloc(static_cast<SIZE_T>(TotalSize)))
				{
					FileReader->Serialize(Buffer, TotalSize);

					if (FileReader->Close())
					{
						OutFileData.data = static_cast<const uint8*>(Buffer);

						OutFileData.length = static_cast<SIZE_T>(TotalSize);

						OutFileData.shared = false;

						return true;
					}

					leanclr::alloc::GeneralAllocation::free(Buffer);
				}
			}
		}
	}

	return false;
}

bool FLeanCLRDomain::InitializeAssembly(const TArray<FString>& InAssemblies)
{
	LoadAssembly(InAssemblies);

	UEModule = nullptr;

	if (const auto UEAssembly = leanclr::vm::Assembly::find_by_name(
		TCHAR_TO_UTF8(*FUnrealCSharpFunctionLibrary::GetUEName())))
	{
		UEModule = UEAssembly->mod;
	}

	if (UEModule == nullptr)
	{
		return false;
	}

#define RESOLVE_LEANCLR_UE_METHOD(Name, FnType, ClassFullNameMacro, MethodNameMacro, ParamCount) \
	Name##Fn = Class_Get_Method_From_Name(UEModule, ClassFullNameMacro, MethodNameMacro);

	UTILS_BRIDGE_METHODS(RESOLVE_LEANCLR_UE_METHOD)

#undef RESOLVE_LEANCLR_UE_METHOD

	FReflectionRegistry::Get().Initialize();

	return true;
}

void FLeanCLRDomain::LoadAssembly(const TArray<FString>& InAssemblies)
{
	Assemblies.Empty();

	for (const auto& AssemblyPath : InAssemblies)
	{
		const auto AssemblyName = FPaths::GetBaseFilename(AssemblyPath);

		if (AssemblyName != INTEROP_NAME)
		{
			if (auto AssemblyResult = leanclr::vm::Assembly::load_by_name(TCHAR_TO_UTF8(*AssemblyName));
				AssemblyResult.is_ok())
			{
				Assemblies.Add(IManagedHandleFromObject(AssemblyResult.unwrap()));
			}
		}
	}
}

void FLeanCLRDomain::UnloadAssembly()
{
	FReflectionRegistry::Get().Deinitialize();

	if (AssemblyLoaderUnloadFn != nullptr)
	{
		Bridge_Invoke(AssemblyLoaderUnloadFn);
	}

	Assemblies.Empty();

	UEModule = nullptr;

	InteropModule = nullptr;

#define LEANCLR_METHOD_CLEAR(Name, FnType, ClassNameMacro, MethodNameMacro, ParamCount) Name##Fn = nullptr;

	COMMON_BRIDGE_METHODS(LEANCLR_METHOD_CLEAR)

	LEANCLR_INTEROP_BRIDGE_METHODS(LEANCLR_METHOD_CLEAR)

	UTILS_BRIDGE_METHODS(LEANCLR_METHOD_CLEAR)

#undef LEANCLR_METHOD_CLEAR

	MethodInvokePaths.Empty();
}

void FLeanCLRDomain::RegisterInterop()
{
	if (InteropModule == nullptr)
	{
		return;
	}

#define RESOLVE_LEANCLR_METHOD(Name, FnType, ClassNameMacro, MethodNameMacro, ParamCount) \
	{ \
		const auto FullName = COMBINE_FULL_NAME(NAMESPACE_INTEROP, ClassNameMacro); \
		Name##Fn = Class_Get_Method_From_Name(InteropModule, FullName, MethodNameMacro); \
	}

	COMMON_BRIDGE_METHODS(RESOLVE_LEANCLR_METHOD)

	LEANCLR_INTEROP_BRIDGE_METHODS(RESOLVE_LEANCLR_METHOD)

#undef RESOLVE_LEANCLR_METHOD
}

void FLeanCLRDomain::RegisterBinding() const
{
	static TArray<TArray<ANSICHAR>> PInvokeNames;

	auto RegisterPInvoke = [](const FString& InName, const void* InFunc)
	{
		const auto MethodName = StringCast<UTF8CHAR>(*InName);

		const auto Length = MethodName.Length() + 1;

		auto& Name = PInvokeNames.AddDefaulted_GetRef();

		Name.SetNumUninitialized(Length);

		FMemory::Memcpy(Name.GetData(), MethodName.Get(), Length);

		leanclr::vm::PInvokes::register_pinvoke(
			reinterpret_cast<const char*>(Name.GetData()),
			reinterpret_cast<leanclr::vm::PInvokeFunction>(reinterpret_cast<PTRINT>(const_cast<void*>(InFunc))),
			&PInvoke_Dispatch);
	};

	for (const auto& Class : FBinding::Get().Register().GetClasses())
	{
		for (const auto& Method : Class->GetMethods())
		{
			RegisterPInvoke(Method.GetMethod(), Method.GetFunction());
		}
	}

	RegisterPInvoke(
		COMBINE_FULL_NAME(NAMESPACE_INTEROP, CLASS_LOG_BRIDGE)
		+ BINDING_COMBINE_FUNCTION(FUNCTION_LOG_BRIDGE_LOG_LEANCLR),
		reinterpret_cast<const void*>(&FScriptLog::Log));
}
#endif
