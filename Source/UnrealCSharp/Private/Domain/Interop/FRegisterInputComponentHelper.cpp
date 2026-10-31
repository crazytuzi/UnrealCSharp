#include "Domain/Interop/FRegisterInputComponentHelper.h"
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/DynamicBlueprintBinding.h"
#include "Environment/FCSharpEnvironment.h"

IManagedHandle FRegisterInputComponentHelper::GetDynamicBindingObject(const IManagedHandle InThisClass,
                                                                      const IManagedHandle InBindingClass)
{
	const auto ThisClass = FCSharpEnvironment::GetEnvironment().GetObject<UBlueprintGeneratedClass>(InThisClass);

	const auto BindingClass = FCSharpEnvironment::GetEnvironment().GetObject<UClass>(InBindingClass);

	if (ThisClass != nullptr && BindingClass != nullptr)
	{
		auto DynamicBindingObject = UBlueprintGeneratedClass::GetDynamicBindingObject(ThisClass, BindingClass);

		if (DynamicBindingObject == nullptr)
		{
			DynamicBindingObject = NewObject<UDynamicBlueprintBinding>(GetTransientPackage(), BindingClass);

			ThisClass->DynamicBindingObjects.Add(DynamicBindingObject);
		}

		return FCSharpEnvironment::GetEnvironment().Bind(DynamicBindingObject);
	}

	return InvalidManagedHandle;
}

void FRegisterInputComponentHelper::BindFunction(UClass* InClass, const FName* InFunctionName,
                                                 const TFunction<void(UFunction* InFunction)>& InProperty)
{
	if (InClass == nullptr || InFunctionName == nullptr)
	{
		return;
	}

	if (InClass->FindFunctionByName(*InFunctionName) != nullptr)
	{
		return;
	}

	const auto Function = NewObject<UFunction>(InClass, *InFunctionName, EObjectFlags::RF_Transient);

	Function->FunctionFlags = FUNC_BlueprintEvent;

	InProperty(Function);

	Function->Bind();

	Function->StaticLink(true);

	InClass->AddFunctionToFunctionMap(Function, *InFunctionName);

	Function->Next = InClass->Children;

	InClass->Children = Function;

	FCSharpEnvironment::GetEnvironment().GetBind()->Bind(FCSharpEnvironment::GetEnvironment().GetRegistry<
		                                                     FClassRegistry>()->GetClassDescriptor(InClass),
	                                                     InClass,
	                                                     Function
	);
}
