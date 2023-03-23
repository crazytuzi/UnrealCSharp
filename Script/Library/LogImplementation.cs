using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class LogImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Log_LogImplementation(char[] InBuffer, uint InReadOffset);
    }
}