using Script.Library;
using Script.Reflection.Property;
using Interop;

namespace Script.CoreUObject
{
    public class TFieldPath<T> where T : FField
    {
        public TFieldPath() =>
            TFieldPathImplementation.TFieldPath_Register1Implementation(HandleData.Alloc(this, true));

        public TFieldPath(T InObject) => TFieldPathImplementation.TFieldPath_Register2Implementation(
            HandleData.Alloc(this, true), HandleData.GetHandle(InObject));

        ~TFieldPath() => TFieldPathImplementation.TFieldPath_UnRegisterImplementation(HandleData.GetHandle(this));

        public bool IsValid() => TFieldPathImplementation.TFieldPath_IsValidImplementation(HandleData.GetHandle(this));

        public T Get() =>
            (T)HandleData.GetObject(TFieldPathImplementation.TFieldPath_GetImplementation(HandleData.GetHandle(this)));

        public void Set(T InObject) => TFieldPathImplementation.TFieldPath_SetImplementation(
            HandleData.GetHandle(this), HandleData.GetHandle(InObject));

        public void Reset() => TFieldPathImplementation.TFieldPath_ResetImplementation(HandleData.GetHandle(this));
    }
}