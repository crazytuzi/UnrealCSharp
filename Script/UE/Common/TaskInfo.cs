#nullable enable
using System;
using System.Threading;

namespace Script.Common;

public struct TaskInfo
{
    public SendOrPostCallback CallBack;

    public Object? State;

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