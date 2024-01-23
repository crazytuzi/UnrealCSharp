using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Enum)]
    public class UseEnumValuesAsMaskValuesInEditorAttribute : Attribute
    {
        public UseEnumValuesAsMaskValuesInEditorAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}