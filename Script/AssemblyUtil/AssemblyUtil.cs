using System.Reflection;
using System.Runtime.Loader;

namespace Script
{
    public static class AssemblyUtil
    {
        static AssemblyLoadContext? ALC;

        public static void Initialize()
        {
            ALC ??= new AssemblyLoadContext("MonoCSharp", true);
        }

        public static void Deinitialize()
        {
            if (ALC != null)
            {
                ALC.Unload();

                ALC = null;
            }
        }

        public static Assembly? Load(string InPath)
        {
            using var sr = new StreamReader(InPath);

            return ALC.LoadFromStream(sr.BaseStream);
        }
    }
}