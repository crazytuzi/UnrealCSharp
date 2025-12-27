#include "Domain/FMonoProfiler.h"
#if UE_TRACE_ENABLED
#include "Domain/FMonoDomain.h"

MonoProfilerHandle FMonoProfiler::ProfilerHandle = nullptr;

void FMonoProfiler::Register()
{
	if (FString Channels; FParse::Value(FCommandLine::Get(), TEXT("-trace="), Channels, false))
	{
		if (Channels.ToLower().Contains(TEXT("CSharp")))
		{
			if (ProfilerHandle = mono_profiler_create(nullptr);
				ProfilerHandle != nullptr)
			{
				mono_profiler_set_method_enter_callback(ProfilerHandle, Method_Enter);

				mono_profiler_set_method_leave_callback(ProfilerHandle, Method_Leave);

				mono_profiler_set_call_instrumentation_filter_callback(ProfilerHandle, Call_Instrumentation_Filter);
			}
		}
	}
}

void FMonoProfiler::Method_Enter(MonoProfiler* InMonoProfiler, MonoMethod* InMonoMethod,
                                 MonoProfilerCallContext* InMonoProfilerCallContext)
{
	const auto MethodClass = FMonoDomain::Method_Get_Class(InMonoMethod);

	const auto MethodNamespace = FString(FMonoDomain::Class_Get_Namespace(MethodClass));

	const auto ClassName = FString(FMonoDomain::Class_Get_Name(MethodClass));

	const auto MethodName = FString(FMonoDomain::Method_Get_Name(InMonoMethod));

	const auto EventName = FString::Printf(TEXT(
		"[C#] %s.%s.%s"
	),
	                                       *MethodNamespace, *ClassName, *MethodName);

	FCpuProfilerTrace::OutputBeginDynamicEvent(*EventName);
}

void FMonoProfiler::Method_Leave(MonoProfiler* InMonoProfiler, MonoMethod* InMonoMethod,
                                 MonoProfilerCallContext* InMonoProfilerCallContext)
{
	FCpuProfilerTrace::OutputEndEvent();
}

MonoProfilerCallInstrumentationFlags FMonoProfiler::Call_Instrumentation_Filter(MonoProfiler* InMonoProfiler,
	MonoMethod* InMonoMethod)
{
	return (MonoProfilerCallInstrumentationFlags)(
		MONO_PROFILER_CALL_INSTRUMENTATION_ENTER |
		MONO_PROFILER_CALL_INSTRUMENTATION_LEAVE |
		MONO_PROFILER_CALL_INSTRUMENTATION_ENTER_CONTEXT |
		MONO_PROFILER_CALL_INSTRUMENTATION_LEAVE_CONTEXT
	);
}
#endif
