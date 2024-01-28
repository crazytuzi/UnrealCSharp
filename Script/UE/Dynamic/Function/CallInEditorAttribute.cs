using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CallInEditorAttribute : Attribute
    {
        public CallInEditorAttribute()
        {
            Value = "true";
        }

        public CallInEditorAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}