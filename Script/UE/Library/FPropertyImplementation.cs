using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class FPropertyImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte FProperty_GetObjectBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetObjectBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ushort FProperty_GetObjectUInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetObjectUInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, ushort InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint FProperty_GetObjectUInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetObjectUInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, uint InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong FProperty_GetObjectUInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetObjectUInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, ulong InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern sbyte FProperty_GetObjectSBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetObjectSBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, sbyte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short FProperty_GetObjectInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetObjectInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, short InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int FProperty_GetObjectInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetObjectInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, int InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long FProperty_GetObjectInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetObjectInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, long InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FProperty_GetObjectBooleanPropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetObjectBooleanPropertyImplementation(nint InMonoObject,
            uint InPropertyHash, bool InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float FProperty_GetObjectSinglePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetObjectSinglePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, float InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FProperty_GetObjectCompoundPropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetObjectCompoundPropertyImplementation(nint InMonoObject,
            uint InPropertyHash, nint InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double FProperty_GetObjectDoublePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetObjectDoublePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, double InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte FProperty_GetStructBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetStructBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ushort FProperty_GetStructUInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetStructUInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, ushort InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint FProperty_GetStructUInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetStructUInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, uint InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong FProperty_GetStructUInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetStructUInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, ulong InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern sbyte FProperty_GetStructSBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetStructSBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, sbyte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short FProperty_GetStructInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetStructInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, short InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int FProperty_GetStructInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetStructInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, int InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long FProperty_GetStructInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetStructInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, long InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool FProperty_GetStructBooleanPropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetStructBooleanPropertyImplementation(nint InMonoObject,
            uint InPropertyHash, bool InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float FProperty_GetStructSinglePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetStructSinglePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, float InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object FProperty_GetStructCompoundPropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetStructCompoundPropertyImplementation(nint InMonoObject,
            uint InPropertyHash, nint InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double FProperty_GetStructDoublePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void FProperty_SetStructDoublePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, double InValue);
    }
}