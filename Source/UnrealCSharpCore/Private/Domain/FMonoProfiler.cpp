#include "Domain/FMonoProfiler.h"
#if UE_TRACE_ENABLED
#include "mono/metadata/class.h"

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

				mono_profiler_set_method_exception_leave_callback(ProfilerHandle, Method_Exception_Leave);

				mono_profiler_set_method_tail_call_callback(ProfilerHandle, Method_Tail_Call);

				mono_profiler_set_call_instrumentation_filter_callback(ProfilerHandle, Call_Instrumentation_Filter);
			}
		}
	}
}

void FMonoProfiler::Method_Enter(MonoProfiler* InMonoProfiler, MonoMethod* InMonoMethod,
                                 MonoProfilerCallContext* InMonoProfilerCallContext)
{
	const auto MethodClass = mono_method_get_class(InMonoMethod);

	const auto MethodNamespace = FString(mono_class_get_namespace(MethodClass));

	const auto ClassName = FString(mono_class_get_name(MethodClass));

	const auto MethodName = FString(mono_method_get_name(InMonoMethod));

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

void FMonoProfiler::Method_Exception_Leave(MonoProfiler* InMonoProfiler, MonoMethod* InMonoMethod,
                                           MonoObject* InException)
{
	FCpuProfilerTrace::OutputEndEvent();
}

void FMonoProfiler::Method_Tail_Call(MonoProfiler* InMonoProfiler, MonoMethod* InMonoMethod,
                                     MonoMethod* InTargetMonoMethod)
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
		MONO_PROFILER_CALL_INSTRUMENTATION_LEAVE_CONTEXT |
		MONO_PROFILER_CALL_INSTRUMENTATION_EXCEPTION_LEAVE |
		MONO_PROFILER_CALL_INSTRUMENTATION_TAIL_CALL
	);
}
#endif
