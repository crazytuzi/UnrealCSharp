// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

namespace System.ServiceProcess.Tests
{
    public enum PipeMessageByteCode
    {
        Start,
        Continue,
        Pause,
        Stop,
        OnCustomCommand,
        ExceptionThrown,
        Connected
    };
}
