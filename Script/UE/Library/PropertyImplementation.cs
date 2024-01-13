using System.Runtime.CompilerServices;

namespace Script.Library
{
    public static class PropertyImplementation
    {
        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte Property_GetObjectBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ushort Property_GetObjectUInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, ushort InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint Property_GetObjectUInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, uint InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong Property_GetObjectUInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectUInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, ulong InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern sbyte Property_GetObjectSBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectSBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, sbyte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short Property_GetObjectInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, short InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Property_GetObjectInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, int InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long Property_GetObjectInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, long InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Property_GetObjectBooleanPropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectBooleanPropertyImplementation(nint InMonoObject,
            uint InPropertyHash, bool InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float Property_GetObjectSinglePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectSinglePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, float InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Property_GetObjectCompoundPropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectCompoundPropertyImplementation(nint InMonoObject,
            uint InPropertyHash, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double Property_GetObjectDoublePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetObjectDoublePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, double InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern byte Property_GetStructBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, byte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ushort Property_GetStructUInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, ushort InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern uint Property_GetStructUInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, uint InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern ulong Property_GetStructUInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructUInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, ulong InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern sbyte Property_GetStructSBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructSBytePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, sbyte InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern short Property_GetStructInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInt16PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, short InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern int Property_GetStructInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInt32PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, int InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern long Property_GetStructInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructInt64PropertyImplementation(nint InMonoObject,
            uint InPropertyHash, long InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern bool Property_GetStructBooleanPropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructBooleanPropertyImplementation(nint InMonoObject,
            uint InPropertyHash, bool InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern float Property_GetStructSinglePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructSinglePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, float InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern object Property_GetStructCompoundPropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructCompoundPropertyImplementation(nint InMonoObject,
            uint InPropertyHash, object InValue);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern double Property_GetStructDoublePropertyImplementation(nint InMonoObject,
            uint InPropertyHash);

        [MethodImpl(MethodImplOptions.InternalCall)]
        public static extern void Property_SetStructDoublePropertyImplementation(nint InMonoObject,
            uint InPropertyHash, double InValue);
    }
}