using System.IO;
using System.Reflection;
using System.Runtime.Loader;

namespace Interop
{
    internal sealed class UnrealAssemblyLoadContext(string InPublishDirectory)
        : AssemblyLoadContext(name: "UnrealAssemblyLoadContext", isCollectible: true)
    {
        protected override Assembly? Load(AssemblyName InAssemblyName)
        {
            if (InAssemblyName.Name != null)
            {
                if (InAssemblyName.Name == "Interop")
                {
                    return GetLoadContext(typeof(AssemblyLoader).Assembly)
                               ?.LoadFromAssemblyName(InAssemblyName)
                           ?? Default.LoadFromAssemblyName(InAssemblyName);
                }

                var AssemblyPath = Path.Combine(InPublishDirectory, InAssemblyName.Name + ".dll");

                if (File.Exists(AssemblyPath))
                {
                    return LoadFromStream(AssemblyPath);
                }
            }

            return null;
        }

        private Assembly LoadFromStream(string InAssemblyPath)
        {
            var PdbPath = Path.ChangeExtension(InAssemblyPath, ".pdb");

            var PdbBytes = File.Exists(PdbPath) ? File.ReadAllBytes(PdbPath) : null;

            using var AssemblyStream = new MemoryStream(File.ReadAllBytes(InAssemblyPath));

            using var PdbStream = PdbBytes is not null ? new MemoryStream(PdbBytes) : null;

            return LoadFromStream(AssemblyStream, PdbStream);
        }
    }
}