#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CSharpBlueprintFunctionLibrary.generated.h"

/**
 * 蓝图访问 C# Override 类成员的运行时入口。
 * 只能由 UK2Node_CallCSharpFunction / UK2Node_CSharpPropertyAccess 生成的字节码调用：
 * 固定参数之后，编译器按 C# 签名顺序追加变参（输入参数、ref 参数、返回值），由 CustomThunk 逐项读取。
 */
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

	DECLARE_FUNCTION(execCallCSharpFunction);

	DECLARE_FUNCTION(execGetCSharpProperty);

	DECLARE_FUNCTION(execSetCSharpProperty);

public:
	static UFunction* GetCallFunction();

	static UFunction* GetGetPropertyFunction();

	static UFunction* GetSetPropertyFunction();
};
