#pragma once

#include "CoreMinimal.h"

class FClassReflection;
class FMethodReflection;
class FPropertyReflection;
class FReflection;

enum class ECSharpBlueprintMemberKind : uint8
{
	Function,
	PropertyGet,
	PropertySet
};

/** 一个可供蓝图访问的 C# 成员（Override 类上的 [UFunction] 方法或 [UProperty] 属性）。 */
struct UNREALCSHARPBLUEPRINTFUNCTION_API FCSharpBlueprintMemberInfo
{
	ECSharpBlueprintMemberKind Kind = ECSharpBlueprintMemberKind::Function;

	/** 声明该成员的 C# Override 类 */
	FClassReflection* ClassReflection = nullptr;

	/** ClassReflection 对应的 UClass */
	UClass* OwnerClass = nullptr;

	FMethodReflection* Method = nullptr;

	FPropertyReflection* Property = nullptr;

	bool IsValid() const;

	const FReflection* GetReflection() const;

	FString GetMemberName() const;

	int32 GetParamCount() const;
};

/**
 * C# 成员的查找与签名构建。
 * 签名 UFunction 只用于参数封送，Outer 为 Transient 包，不挂到任何 UClass，蓝图资产不会引用它。
 */
class UNREALCSHARPBLUEPRINTFUNCTION_API FCSharpBlueprintMemberLibrary
{
public:
	static bool IsScriptDomainReady();

	static bool IsRuntimeActive();

public:
	static bool IsBlueprintCallable(const FMethodReflection* InMethod);

	static bool IsBlueprintPure(const FMethodReflection* InMethod);

	static bool IsBlueprintReadable(const FPropertyReflection* InProperty);

	static bool IsBlueprintWritable(const FPropertyReflection* InProperty);

public:
	static FClassReflection* GetOverrideClassReflection(UClass* InClass);

	static UClass* FindOwnerClass(const FClassReflection* InClassReflection);

	static void ForEachOverrideClass(const TFunctionRef<void(FClassReflection*)>& InFunction);

	static void ForEachBlueprintMember(FClassReflection* InClassReflection, UClass* InOwnerClass,
	                                   const TFunctionRef<void(const FCSharpBlueprintMemberInfo&)>& InFunction);

	/** 从 InClass 沿父类链查找成员 */
	static bool Resolve(UClass* InClass, ECSharpBlueprintMemberKind InKind, const FName& InName, int32 InParamCount,
	                    FCSharpBlueprintMemberInfo& OutInfo);

	/** 只在 InClassReflection 自身查找成员 */
	static bool ResolveDeclared(FClassReflection* InClassReflection, UClass* InOwnerClass,
	                            ECSharpBlueprintMemberKind InKind, const FName& InName, int32 InParamCount,
	                            FCSharpBlueprintMemberInfo& OutInfo);

public:
	static FString GetDisplayName(const FCSharpBlueprintMemberInfo& InInfo);

	static FString GetCategory(const FCSharpBlueprintMemberInfo& InInfo);

	static FString GetToolTip(const FCSharpBlueprintMemberInfo& InInfo);

public:
	static UFunction* BuildSignature(const FCSharpBlueprintMemberInfo& InInfo, const FName& InBaseName);

	static void DestroySignature(UFunction* InFunction);

	/** 由签名 UFunction 的参数名/类型/方向计算，编辑器编译期与运行期用同一算法 */
	static uint32 ComputeSignatureHash(const UFunction* InFunction);

	/** 为属性访问合成 get_X / set_X 的方法反射，调用方持有 */
	static TUniquePtr<FMethodReflection> MakeAccessorMethod(const FCSharpBlueprintMemberInfo& InInfo);
};
