#include "Reflection/Function/FCSharpFunctionRegister.h"
#include "Reflection/Function/CSharpFunction.h"

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
TSet<FCSharpFunctionRegister*> FCSharpFunctionRegister::Registers;
#endif

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
FCSharpFunctionRegister::FCSharpFunctionRegister(UFunction* InFunction,
                                                 UFunction* InOriginalFunction,
                                                 const EFunctionFlags InOriginalFunctionFlags,
                                                 const FNativeFuncPtr InOriginalNativeFuncPtr,
                                                 const FCSharpFunctionOwnerClassInfo& InOwnerClassInfo) :
	Function(InFunction),
	OriginalFunction(InOriginalFunction),
	OriginalFunctionFlags(InOriginalFunctionFlags),
	OriginalNativeFuncPtr(InOriginalNativeFuncPtr),
	OwnerClassInfo(InOwnerClassInfo)
#else
FCSharpFunctionRegister::FCSharpFunctionRegister(UFunction* InFunction,
                                                 UFunction* InOriginalFunction,
                                                 const EFunctionFlags InOriginalFunctionFlags,
                                                 const FNativeFuncPtr InOriginalNativeFuncPtr) :
	Function(InFunction),
	OriginalFunction(InOriginalFunction),
	OriginalFunctionFlags(InOriginalFunctionFlags),
	OriginalNativeFuncPtr(InOriginalNativeFuncPtr)
#endif
{
#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	AddRegister();
#endif
}

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
FCSharpFunctionRegister::FCSharpFunctionRegister(FCSharpFunctionRegister&& InOther) :
	Function(InOther.Function),
	OriginalFunction(InOther.OriginalFunction),
	OriginalFunctionFlags(InOther.OriginalFunctionFlags),
	OriginalNativeFuncPtr(InOther.OriginalNativeFuncPtr),
	OwnerClassInfo(InOther.OwnerClassInfo)
#else
FCSharpFunctionRegister::FCSharpFunctionRegister(FCSharpFunctionRegister&& InOther) :
	Function(InOther.Function),
	OriginalFunction(InOther.OriginalFunction),
	OriginalFunctionFlags(InOther.OriginalFunctionFlags),
	OriginalNativeFuncPtr(InOther.OriginalNativeFuncPtr)
#endif
{
#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	InOther.RemoveRegister();

	AddRegister();
#endif

	InOther.Function.Reset();

	InOther.OriginalFunction.Reset();

	InOther.OriginalFunctionFlags = FUNC_None;

	InOther.OriginalNativeFuncPtr = nullptr;

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	InOther.OwnerClassInfo = FCSharpFunctionOwnerClassInfo{};
#endif
}

FCSharpFunctionRegister::~FCSharpFunctionRegister()
{
#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	RemoveRegister();
#endif

	const auto InOriginalFunction = OriginalFunction.Get(true);

	const auto InCallCSharpFunction = Function.Get(true);

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
	SuspendDummyOwnerClass();
#endif

	if (InOriginalFunction != nullptr && InCallCSharpFunction != nullptr)
	{
		UFunction* FunctionRemove;

		if (InOriginalFunction->GetOuter() == InCallCSharpFunction->GetOuter())
		{
			InCallCSharpFunction->FunctionFlags = OriginalFunctionFlags;

			InCallCSharpFunction->SetNativeFunc(OriginalNativeFuncPtr);

			FunctionRemove = InOriginalFunction;
		}
		else
		{
			FunctionRemove = InCallCSharpFunction;
		}

		if (const auto Class = Cast<UClass>(FunctionRemove->GetOuter()))
		{
			Class->RemoveFunctionFromFunctionMap(FunctionRemove);
		}

		FunctionRemove->Rename(
			*MakeUniqueObjectName(
				GetTransientPackage(),
				FunctionRemove->GetClass(),
				*FString::Printf(TEXT(
					"TRASH_%s"
				),
				                 *FunctionRemove->GetName()
				)).ToString(),
			GetTransientPackage(),
			REN_DontCreateRedirectors | REN_NonTransactional | REN_DoNotDirty);

		if (FunctionRemove->IsRooted())
		{
			FunctionRemove->RemoveFromRoot();
		}
		else
		{
			FunctionRemove->MarkAsGarbage();
		}
	}

	OriginalFunction = nullptr;
}

const TWeakObjectPtr<UFunction>& FCSharpFunctionRegister::GetOriginalFunction() const
{
	return OriginalFunction;
}

EFunctionFlags FCSharpFunctionRegister::GetOriginalFunctionFlags() const
{
	return OriginalFunctionFlags;
}

#if WITH_OVERRIDE_BLUEPRINT_NATIVE_EVENT
void FCSharpFunctionRegister::IteratorRegister(const TFunctionRef<void(const FCSharpFunctionRegister&)>& InFunction)
{
	for (const auto Register : Registers)
	{
		InFunction(*Register);
	}
}

UClass* FCSharpFunctionRegister::GetOriginalOwnerClass() const
{
	return OwnerClassInfo.OriginalOwnerClass;
}

void FCSharpFunctionRegister::SuspendDummyOwnerClass() const
{
	if (OwnerClassInfo.OriginalOwnerClass != nullptr && OwnerClassInfo.DummyOwnerClass != nullptr)
	{
		if (const auto InFunction = Function.Get();
			InFunction != nullptr && InFunction->GetNativeFunc() == &UCSharpFunction::execCallCSharp)
		{
			if (const auto OriginalOwnerClass = GetOriginalOwnerClass();
				InFunction->GetOuter() != OriginalOwnerClass)
			{
				InFunction->Rename(nullptr, OriginalOwnerClass,
				                   REN_DontCreateRedirectors | REN_NonTransactional | REN_DoNotDirty);
			}
		}
	}
}

void FCSharpFunctionRegister::ResumeDummyOwnerClass() const
{
	if (OwnerClassInfo.OriginalOwnerClass != nullptr && OwnerClassInfo.DummyOwnerClass != nullptr)
	{
		if (const auto InFunction = Function.Get())
		{
			if (const auto DummyOwnerClass = OwnerClassInfo.DummyOwnerClass;
				InFunction->GetOuter() != DummyOwnerClass)
			{
				InFunction->Rename(nullptr, DummyOwnerClass,
				                   REN_DontCreateRedirectors | REN_NonTransactional | REN_DoNotDirty);
			}
		}
	}
}

void FCSharpFunctionRegister::AddRegister()
{
	if (OwnerClassInfo.OriginalOwnerClass != nullptr && OwnerClassInfo.DummyOwnerClass != nullptr)
	{
		Registers.Add(this);
	}
}

void FCSharpFunctionRegister::RemoveRegister() const
{
	Registers.Remove(this);
}
#endif
