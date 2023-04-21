using System.Threading;

namespace Script;

class UnrealCSharpSyncContext : SynchronizationContext
{
    static UnrealCSharpSyncContext? Context;
    public static void InitSyncContext()
    {
        Context = new UnrealCSharpSyncContext();
        SetSynchronizationContext(Context);
    }

    public static void FiniSyncContext()
    {
        Context?.Destory();
        SetSynchronizationContext(null);
        Context = null;
    }
    public static void GlobalTick()
    {
        Context?.Tick();
    }

    UnrealCSharpSyncContext()
    {
        ThreadId = Thread.CurrentThread.ManagedThreadId;
    }

    void Destory()
    {
    }

    List<TaskInfo> TaskList = new List<TaskInfo>();
    List<TaskInfo> TempList = new List<TaskInfo>();
    private int ThreadId;
    public void Tick()
    {
        lock(TaskList)
        {
            TempList.AddRange(TaskList);
            TaskList.Clear();
        }
        foreach(var task in TempList)
        {
            task.Invoke();
        }
        TempList.Clear();
    }
    public override void Post(SendOrPostCallback d, object? state)
    {
        lock (TaskList)
        {
            TaskList.Add(new TaskInfo
            {
                CallBack = d,
                State = state
            });
        }
    }

    public override void Send(SendOrPostCallback d, object? state)
    {
        if (Thread.CurrentThread.ManagedThreadId == ThreadId)
        {
            d(state);
            return;
        }
        using (var waitHandle = new ManualResetEvent(false))
        {
            lock (TaskList)
            {
                TaskList.Add(new TaskInfo
                {
                    CallBack = d,
                    State = state,
                    WaitHandle = waitHandle
                });
            }
        }
    }

}

struct TaskInfo
{
    public SendOrPostCallback CallBack;
    public object? State;
    public ManualResetEvent? WaitHandle;

    public void Invoke()
    {
        try
        {
            CallBack?.Invoke(State);
        } 
        finally
        {
            WaitHandle?.Set();
        }
    }

}