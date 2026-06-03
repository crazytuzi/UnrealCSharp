using System;
using System.Runtime.InteropServices;

namespace Interop
{
    public static unsafe class StringBridge
    {
        [UnmanagedCallersOnly]
        public static nint NewString(byte* InText)
        {
            if (InText != null)
            {
                return HandleData.AllocImplementation(Marshal.PtrToStringUTF8((nint)InText)!);
            }

            return 0;
        }

        [UnmanagedCallersOnly]
        public static int GetString(nint InHandle, char* InBuffer, int InSize)
        {
            if (InBuffer != null && InSize > 0)
            {
                if (HandleData.GetObject(InHandle) is string String)
                {
                    var Length = String.Length;

                    if (Length < InSize)
                    {
                        fixed (char* Ptr = String)
                        {
                            Buffer.MemoryCopy(Ptr, InBuffer, (InSize - 1) * sizeof(char), Length * sizeof(char));
                        }

                        InBuffer[Length] = '\0';

                        return Length;
                    }
                }
            }

            return -1;
        }
    }
}