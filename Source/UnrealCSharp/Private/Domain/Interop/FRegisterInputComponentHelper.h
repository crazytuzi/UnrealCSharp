#pragma once

#include "CoreMinimal.h"
#include "Templates/Function.h"
#include "Domain/Script/IManagedHandle.h"

class UClass;
class UFunction;

struct FRegisterInputComponentHelper
{
	static IManagedHandle GetDynamicBindingObject(const IManagedHandle InThisClass,
	                                              const IManagedHandle InBindingClass);

	static void BindFunction(UClass* InClass, const FName* InFunctionName,
	                         const TFunction<void(UFunction* InFunction)>& InProperty);
};
