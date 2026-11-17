namespace Script.Library
{
    public static unsafe partial class TFieldPathImplementation
    {
        private static unsafe partial void __TFieldPath_Register1Implementation(nint InManagedObject);

        public static void TFieldPath_Register1Implementation(nint InManagedObject)
        {
            __TFieldPath_Register1Implementation(InManagedObject);
        }

        private static unsafe partial void __TFieldPath_Register2Implementation(nint InManagedObject, nint InManagedField);

        public static void TFieldPath_Register2Implementation(nint InManagedObject, nint InManagedField)
        {
            __TFieldPath_Register2Implementation(InManagedObject, InManagedField);
        }

        private static unsafe partial byte __TFieldPath_IdenticalImplementation(nint InA, nint InB);

        public static bool TFieldPath_IdenticalImplementation(nint InA, nint InB)
        {
            return __TFieldPath_IdenticalImplementation(InA, InB) != 0;
        }

        private static unsafe partial void __TFieldPath_UnRegisterImplementation(nint InManagedHandle);

        public static void TFieldPath_UnRegisterImplementation(nint InManagedHandle)
        {
            __TFieldPath_UnRegisterImplementation(InManagedHandle);
        }

        private static unsafe partial byte __TFieldPath_IsValidImplementation(nint InManagedHandle);

        public static bool TFieldPath_IsValidImplementation(nint InManagedHandle)
        {
            return __TFieldPath_IsValidImplementation(InManagedHandle) != 0;
        }

        private static unsafe partial nint __TFieldPath_GetImplementation(nint InManagedHandle);

        public static nint TFieldPath_GetImplementation(nint InManagedHandle)
        {
            return __TFieldPath_GetImplementation(InManagedHandle);
        }

        private static unsafe partial void __TFieldPath_SetImplementation(nint InManagedHandle, nint InManagedField);

        public static void TFieldPath_SetImplementation(nint InManagedHandle, nint InManagedField)
        {
            __TFieldPath_SetImplementation(InManagedHandle, InManagedField);
        }

        private static unsafe partial void __TFieldPath_ResetImplementation(nint InManagedHandle);

        public static void TFieldPath_ResetImplementation(nint InManagedHandle)
        {
            __TFieldPath_ResetImplementation(InManagedHandle);
        }
    }
}