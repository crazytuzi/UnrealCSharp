using System;
using Script.Common;
using Script.Library;
using IntPtr = System.IntPtr;

namespace Script.Reflection.Delegate
{
    public static class DelegateUtils
    {
        public static void Delegate_Register(FDelegateBase InMonoObject) =>
            DelegateImplementation.Delegate_RegisterImplementation(InMonoObject);

        public static void Delegate_UnRegister(IntPtr InMonoObject) =>
            DelegateImplementation.Delegate_UnRegisterImplementation(InMonoObject);

        public static void Delegate_Bind<T>(IntPtr InMonoObject, T InDelegate) where T : System.Delegate =>
            DelegateImplementation.Delegate_BindImplementation(InMonoObject, InDelegate);

        public static Boolean Delegate_IsBound(IntPtr InMonoObject) =>
            DelegateImplementation.Delegate_IsBoundImplementation(InMonoObject);

        public static void Delegate_UnBind(IntPtr InMonoObject) =>
            DelegateImplementation.Delegate_UnBindImplementation(InMonoObject);

        public static void Delegate_Clear(IntPtr InMonoObject) =>
            DelegateImplementation.Delegate_ClearImplementation(InMonoObject);

        public static void Delegate_Execute<T>(IntPtr InMonoObject, out T ReturnValue, out ObjectList OutValue,
            params Object[] InValue) =>
            DelegateImplementation.Delegate_ExecuteImplementation(InMonoObject, out ReturnValue, out OutValue, InValue);
    }
}