#pragma once

#if UE_TRACE_ENABLED
#include "mono/metadata/profiler.h"

class FMonoProfiler
{
public:
	static void Register();

private:
	static void Method_Enter(MonoProfiler* InMonoProfiler, MonoMethod* InMonoMethod,
	                         MonoProfilerCallContext* InMonoProfilerCallContext);

	static void Method_Leave(MonoProfiler* InMonoProfiler, MonoMethod* InMonoMethod,
	                         MonoProfilerCallContext* InMonoProfilerCallContext);

	static MonoProfilerCallInstrumentationFlags Call_Instrumentation_Filter(MonoProfiler* InMonoProfiler,
	                                                                        MonoMethod* InMonoMethod);

private:
	static MonoProfilerHandle ProfilerHandle;
};
#endif
