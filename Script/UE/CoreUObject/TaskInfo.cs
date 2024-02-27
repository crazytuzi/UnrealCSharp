#nullable enable
using System.Threading;

namespace Script.CoreUObject;

public struct TaskInfo
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