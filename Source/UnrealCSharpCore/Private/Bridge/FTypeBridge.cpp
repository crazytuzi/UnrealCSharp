#include "Bridge/FTypeBridge.h"
#include "CoreMacro/ClassMacro.h"
#include "CoreMacro/FunctionMacro.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Domain/FMonoDomain.h"
#include "Template/TGetArrayLength.h"

FString FTypeBridge::GetPathName(MonoReflectionType* InReflectionType)
{
	const auto UtilsMonoClass = FMonoDomain::Class_From_Name(
		COMBINE_NAMESPACE(NAMESPACE_ROOT, NAMESPACE_COMMON), CLASS_UTILS);

	auto InParams = static_cast<void*>(InReflectionType);

	const auto GetPathNameMonoMethod = FMonoDomain::Class_Get_Method_From_Name(
		UtilsMonoClass, FUNCTION_UTILS_GET_PATH_NAME, TGetArrayLength(InParams));

	const auto PathNameMonoObject = FMonoDomain::Runtime_Invoke(
		GetPathNameMonoMethod, nullptr, &InParams);

	const auto PathNameMonoString = FMonoDomain::Object_To_String(
		PathNameMonoObject, nullptr);

	return UTF8_TO_TCHAR(FMonoDomain::String_To_UTF8(PathNameMonoString));
}
