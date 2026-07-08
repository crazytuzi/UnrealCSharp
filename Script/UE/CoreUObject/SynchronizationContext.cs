#nullable enable
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Threading;

namespace Script.CoreUObject;

public class SynchronizationContext : System.Threading.SynchronizationContext
{
    private static SynchronizationContext? Context;

    public static void Initialize()
    {
        Context = new SynchronizationContext();

        SetSynchronizationContext(Context);
    }

    public static void Deinitialize()
    {
        SetSynchronizationContext(null);

        Context = null;
    }

    [UnmanagedCallersOnly(CallConvs = [typeof(System.Runtime.CompilerServices.CallConvCdecl)])]
    public static void Tick(float DeltaTime)
    {
        Context?.Process();
    }

    private SynchronizationContext() => ThreadId = Thread.CurrentThread.ManagedThreadId;

    List<TaskInfo> TaskList = new();

    List<TaskInfo> PendingTaskList = new();

    private void Process()
    {
        lock (TaskList)
        {
            PendingTaskList.AddRange(TaskList);

            TaskList.Clear();
        }

        foreach (var Task in PendingTaskList)
        {
            Task.Invoke();
        }

        PendingTaskList.Clear();
    }

    public override void Post(SendOrPostCallback InCallback, object? InState)
    {
        lock (TaskList)
        {
            TaskList.Add(new TaskInfo
            {
                CallBack = InCallback,

                State = InState
            });
        }
    }

    public override void Send(SendOrPostCallback InCallback, object? InState)
    {
        if (Thread.CurrentThread.ManagedThreadId == ThreadId)
        {
            InCallback(InState);

            return;
        }

        using var ResetEvent = new ManualResetEvent(false);

        lock (TaskList)
        {
            TaskList.Add(new TaskInfo
            {
                CallBack = InCallback,

                State = InState,

                WaitHandle = ResetEvent
            });
        }
    }

    private int ThreadId;
}