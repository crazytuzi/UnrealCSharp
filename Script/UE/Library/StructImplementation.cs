using System.Runtime.CompilerServices;
using Script.CoreUObject;

namespace Script.Library
{
    public static partial class UStructImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern UScriptStruct UStruct_StaticStructImplementation(string InStructName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UStruct_RegisterImplementation(object InMonoObject, string InStructName);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool UStruct_IdenticalImplementation(nint InScriptStruct, nint InA, nint InB);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void UStruct_UnRegisterImplementation(nint InMonoObject);
    }
}