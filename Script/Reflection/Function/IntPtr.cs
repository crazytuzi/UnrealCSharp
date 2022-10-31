namespace Script.Reflection.Function
{
    public class IntPtr
    {
        private unsafe IntPtr(void* InValue) => Value = new System.IntPtr(InValue);

        public unsafe void* ToPointer() => Value.ToPointer();

        private readonly System.IntPtr Value;
    }
}