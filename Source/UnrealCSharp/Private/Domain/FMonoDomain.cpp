#include "Domain/FMonoDomain.h"
#include "Domain/InternalCall/FMonoInternalCall.h"
#include "Domain/InternalCall/FPropertyImplementation.h"
#include "Domain/InternalCall/FFunctionImplementation.h"
#include "Log/FMonoLog.h"
#include "Macro/NamespaceMacro.h"
#include "Macro/ClassMacro.h"
#include "Macro/FunctionMacro.h"
#include "mono/jit/jit.h"
#include "mono/metadata/assembly.h"
#include "mono/utils/mono-logger.h"

FMonoDomain::FMonoDomain(const FMonoDomainInitializeParams& Params):
	Domain(nullptr),
	Assembly(nullptr),
	Image(nullptr)
{
	Initialize(Params);
}

FMonoDomain::~FMonoDomain()
{
	Deinitialize();
}

void FMonoDomain::Initialize(const FMonoDomainInitializeParams& Params)
{
	Domain = mono_jit_init(TCHAR_TO_ANSI(*Params.Domain));

	Assembly = mono_domain_assembly_open(Domain, TCHAR_TO_ANSI(*Params.Assembly));

	Image = mono_assembly_get_image(Assembly);

	RegisterMonoTrace();

	RegisterReflectionPropertyImplementation();

	RegisterReflectionFunctionImplementation();

	RegisterLog();
}

void FMonoDomain::Deinitialize()
{
	if (Image != nullptr)
	{
		mono_image_close(Image);

		Image = nullptr;
	}

	if (Assembly != nullptr)
	{
		mono_assembly_name_free(mono_assembly_get_name(Assembly));

		Assembly = nullptr;
	}

	if (Domain != nullptr)
	{
		mono_jit_cleanup(Domain);

		Domain = nullptr;
	}
}

MonoObject* FMonoDomain::Object_New(MonoClass* InMonoClass, const bool bInit) const
{
	if (Domain != nullptr && InMonoClass != nullptr)
	{
		if (const auto NewMonoObject = mono_object_new(Domain, InMonoClass))
		{
			if (bInit)
			{
				mono_runtime_object_init(NewMonoObject);
			}

			return NewMonoObject;
		}
	}

	return nullptr;
}

MonoClass* FMonoDomain::Class_From_Name(const FString& InNameSpace, const FString& InMonoClassName) const
{
	return Image != nullptr
		       ? mono_class_from_name(Image, TCHAR_TO_ANSI(*InNameSpace), TCHAR_TO_ANSI(*InMonoClassName))
		       : nullptr;
}

MonoMethod* FMonoDomain::Class_Get_Method_From_Name(MonoClass* InMonoClass, const FString& InFunctionName,
                                                    const int32 InParamCount) const
{
	return InMonoClass != nullptr
		       ? mono_class_get_method_from_name(InMonoClass, TCHAR_TO_ANSI(*InFunctionName), InParamCount)
		       : nullptr;
}

MonoObject* FMonoDomain::Runtime_Invoke(MonoMethod* InFunction, void* InMonoObject, void** InParams, MonoObject** InExc)
{
	return InFunction != nullptr ? mono_runtime_invoke(InFunction, InMonoObject, InParams, InExc) : nullptr;
}

void* FMonoDomain::Object_Unbox(MonoObject* InMonoObject)
{
	return InMonoObject != nullptr ? mono_object_unbox(InMonoObject) : nullptr;
}

void FMonoDomain::RegisterMonoTrace()
{
	mono_trace_set_log_handler(FMonoLog::MonoLog, nullptr);

	mono_trace_set_print_handler(FMonoLog::MonoPrintf);

	mono_trace_set_printerr_handler(FMonoLog::MonoPrintf);
}

void FMonoDomain::RegisterReflectionPropertyImplementation()
{
	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(UInt16)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(UInt32)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Int8)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Int16)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Int)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Int64)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Bool)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Float)

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Object)

	// @TODO

	// REGISTER_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Array)

	// @TODO

	REGISTER_PROPERTY_PROPERTY_IMPLEMENTATION_INTERNAL_CALL(Double)

	// @TODO
}

void FMonoDomain::RegisterReflectionFunctionImplementation()
{
	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_FUNCTION), CLASS_FUNCTION_IMPLEMENTATION) +
				COMBINE_FUNCTION(FUNCTION_CALL_REFLECTION_FUNCTION_IMPLEMENTATION))),
		static_cast<void*>(FFunctionImplementation::CallReflectionFunctionImplementation));
}

void FMonoDomain::RegisterLog()
{
	FMonoInternalCall::RegisterInternalCall(
		TCHAR_TO_ANSI(
			*(COMBINE_CLASS(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_LOG), CLASS_LOG) + COMBINE_FUNCTION(
				FUNCTION_LOG_IMPLEMENTATION))),
		static_cast<void*>(FMonoLog::LogImplementation));

	if (Domain != nullptr)
	{
		if (const auto FoundClass = Class_From_Name(COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_LOG), CLASS_LOG))
		{
			if (const auto FoundMethod = Class_Get_Method_From_Name(FoundClass, FUNCTION_SET_OUT, 0))
			{
				Runtime_Invoke(FoundMethod, nullptr, nullptr, nullptr);
			}
		}
	}
}
