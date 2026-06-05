using System;
using System.IO;
using System.Runtime.InteropServices;

namespace Interop
{
    public static class AssemblyLoader
    {
        private static UnrealAssemblyLoadContext? Context;

        internal static System.Runtime.Loader.AssemblyLoadContext? CurrentContext => Context;

        [UnmanagedCallersOnly]
        public static unsafe nint LoadFromStream(byte* InData, int InLength, char* InInPublishDirectory)
        {
            if (InData != null && InLength > 0)
            {
                Context ??= new UnrealAssemblyLoadContext(InInPublishDirectory is not null
                    ? new string(InInPublishDirectory)
                    : string.Empty);

                using var Stream = new UnmanagedMemoryStream(InData, InLength);

                return HandleData.AllocImplementation(Context.LoadFromStream(Stream));
            }

            return 0;
        }

        [UnmanagedCallersOnly]
        public static void Unload()
        {
            if (Context != null)
            {
                HandleData.Clear();

                TypeBridge.Clear();

                MethodBridge.Clear();

                var ContextWeakReference = new WeakReference(Context);

                try
                {
                    Context.Unload();
                }
                finally
                {
                    Context = null;
                }

                const int TimeLimit = 2000;

                var Stopwatch = System.Diagnostics.Stopwatch.StartNew();

                while (ContextWeakReference.IsAlive)
                {
                    GC.Collect();

                    GC.WaitForPendingFinalizers();

                    GC.Collect(GC.MaxGeneration, GCCollectionMode.Forced, blocking: true, compacting: true);

                    if (!ContextWeakReference.IsAlive)
                    {
                        break;
                    }

                    if (Stopwatch.ElapsedMilliseconds >= TimeLimit)
                    {
                        break;
                    }
                }
            }
        }
    }
}