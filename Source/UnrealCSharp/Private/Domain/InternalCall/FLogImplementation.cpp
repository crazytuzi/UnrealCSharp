#include "Domain/InternalCall/FLogImplementation.h"
#include "Binding/Class/FBindingClassBuilder.h"
#include "Log/UnrealCSharpLog.h"
#include "Macro/NamespaceMacro.h"

struct FRegisterLog
{
	FRegisterLog()
	{
		FBindingClassBuilder(TEXT("Log"), NAMESPACE_LIBRARY)
			.Function("Log", static_cast<void*>(FLogImplementation::Log_LogImplementation))
			.Register();
	}
};

static FRegisterLog RegisterLog;

/**
* https://github.com/mono-ue/UnrealEngine/blob/monoue/Engine/Plugins/MonoUE/Source/MonoRuntime/Private/MonoLogTextWriter.cpp#L14
*/
void FLogImplementation::Log_LogImplementation(const UTF16CHAR* InBuffer, const unsigned int InReadOffset)
{
#if !NO_LOGGING
	if (UE_LOG_ACTIVE(LogUnrealCSharp, Log))
	{
		GLog->Serialize(StringCast<TCHAR>(InBuffer + 2 * sizeof(void*)).Get() + InReadOffset, ELogVerbosity::Log,
		                LogUnrealCSharp.GetCategoryName());
	}
#endif
}
