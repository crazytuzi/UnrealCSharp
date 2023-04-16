using System.Reflection;
using System.Runtime.Loader;

namespace Util;

public static class AssemblyUtil
{
    static AssemblyLoadContext? Alc;

    public static void InitAssemblyLoadContext()
    {
        if (Alc == null)
        {
            Alc = new AssemblyLoadContext("MonoCSharp", true);
        }
    }

    public static void UninitAssemblyLoadContext()
    {
        if (Alc != null)
        {
            Alc.Unload();
            
            Alc = null;
            
        }
    }
    public static Assembly? LoadLibrary(string path)
    {
        using StreamReader sr = new StreamReader(path);

        Assembly asm = Alc.LoadFromStream(sr.BaseStream);
        
        if (asm == null)
            return null;
        return asm;
    }


}