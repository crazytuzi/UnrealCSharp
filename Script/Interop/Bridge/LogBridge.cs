using System;
using System.IO;
using System.Runtime.CompilerServices;
using System.Runtime.InteropServices;
using System.Text;

namespace Interop;

public sealed class LogBridge : TextWriter
{
    private static unsafe delegate* unmanaged[Cdecl]<byte*, int, byte, void> LogFn;

    private static TextWriter? ConsoleOut;

    private static TextWriter? ConsoleError;

    private readonly bool bIsError;

    private readonly StringBuilder Buffer = new();

    private LogBridge(bool InIsError) => bIsError = InIsError;

    public override Encoding Encoding => Encoding.UTF8;

    private static bool bIsLeanCLR;

    [DllImport("UnrealCSharp", CallingConvention = CallingConvention.Cdecl)]
    private static unsafe extern void LogLeanCLR(byte* InBuffer, int InSize, byte InIsError);

    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static unsafe void SetLog(nint InLogFn)
    {
        LogFn = (delegate* unmanaged[Cdecl]<byte*, int, byte, void>)InLogFn;
    }

    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static void Initialize()
    {
        ConsoleOut = Console.Out;

        ConsoleError = Console.Error;

        RedirectConsole();
    }

    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static void InitializeLeanCLR()
    {
        bIsLeanCLR = true;

        RedirectConsole();
    }

    [UnmanagedCallersOnly(CallConvs = [typeof(CallConvCdecl)])]
    public static void Deinitialize()
    {
        if (ConsoleOut is not null)
        {
            Console.SetOut(ConsoleOut);

            ConsoleOut = null;
        }

        if (ConsoleError is not null)
        {
            Console.SetError(ConsoleError);

            ConsoleError = null;
        }

        unsafe
        {
            LogFn = null;
        }
    }

    private static void RedirectConsole()
    {
        Console.SetOut(new LogBridge(InIsError: false));

        Console.SetError(new LogBridge(InIsError: true));
    }

    public override void Write(char value)
    {
        if (value == '\n')
        {
            if (bIsError)
            {
                Buffer.Append(value);
            }
            else
            {
                Flush();
            }
        }
        else if (value != '\r')
        {
            Buffer.Append(value);
        }
    }

    public override void Write(string? value)
    {
        if (value != null)
        {
            foreach (var character in value)
            {
                Write(character);
            }
        }
    }

    public override void WriteLine(string? value)
    {
        Write(value);

        Flush();
    }

    public override void WriteLine()
    {
        Flush();
    }

    protected override void Dispose(bool disposing)
    {
        if (disposing)
        {
            if (Buffer.Length > 0)
            {
                Flush();
            }
        }

        base.Dispose(disposing);
    }

    public override void Flush()
    {
        if (Buffer.Length > 0)
        {
            Flush(Buffer.ToString().AsSpan(), bIsError);

            Buffer.Clear();
        }
    }

    private static unsafe void Flush(ReadOnlySpan<char> InBuffer, bool InIsError)
    {
        var MaxByteCount = Encoding.UTF8.GetMaxByteCount(InBuffer.Length) + 1;

        var UTF8 = MaxByteCount <= 512
            ? stackalloc byte[MaxByteCount]
            : new byte[MaxByteCount];

        var Size = Encoding.UTF8.GetBytes(InBuffer, UTF8);

        UTF8[Size] = 0;

        var IsError = (byte)(InIsError ? 1 : 0);

        fixed (byte* Ptr = UTF8)
        {
            if (LogFn != null)
            {
                LogFn(Ptr, Size, IsError);
            }
            else if (bIsLeanCLR)
            {
                LogLeanCLR(Ptr, Size, IsError);
            }
        }
    }
}