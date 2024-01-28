using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ExposeOnSpawnAttribute : Attribute
    {
        public ExposeOnSpawnAttribute()
        {
            Value = "true";
        }

        public ExposeOnSpawnAttribute(string InValue)
        {
            Value = InValue;
        }

        private string Value { get; set; }
    }
}