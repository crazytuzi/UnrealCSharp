#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CSharpBlueprintFunctionLibrary.generated.h"

UCLASS()
class UNREALCSHARPBLUEPRINTFUNCTION_API UCSharpBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, CustomThunk, Category = "UnrealCSharp",
		meta = (BlueprintInternalUseOnly = "true", Variadic))
	static void CallCSharpFunction(UObject* Target, FName FunctionName, int32 ParamCount, int32 SignatureHash);

	UFUNCTION(BlueprintCallable, CustomThunk, Category = "UnrealCSharp",
		meta = (BlueprintInternalUseOnly = "true", Variadic))
	static void GetCSharpProperty(UObject* Target, FName PropertyName, int32 ParamCount, int32 SignatureHash);

	UFUNCTION(BlueprintCallable, CustomThunk, Category = "UnrealCSharp",
		meta = (BlueprintInternalUseOnly = "true", Variadic))
	static void SetCSharpProperty(UObject* Target, FName PropertyName, int32 ParamCount, int32 SignatureHash);

	UFUNCTION(BlueprintPure, Category = "UnrealCSharp", meta = (BlueprintInternalUseOnly = "true"))
	static UObject* GetCSharpDelegateProxy(UObject* Target, FName FunctionName, int32 ParamCount, int32 SignatureHash);

	DECLARE_FUNCTION(execCallCSharpFunction);

	DECLARE_FUNCTION(execGetCSharpProperty);

	DECLARE_FUNCTION(execSetCSharpProperty);

public:
	static UFunction* GetCallFunction();

	static UFunction* GetGetPropertyFunction();

	static UFunction* GetSetPropertyFunction();

	static UFunction* GetDelegateProxyFunction();
};
