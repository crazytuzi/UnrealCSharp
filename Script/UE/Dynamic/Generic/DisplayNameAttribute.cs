using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Property)]
    public class DisplayNameAttribute : Attribute
    {
        public string MetaValue { get; set; }
        public DisplayNameAttribute(string MetaValue)
        {
        this.MetaValue = MetaValue;
        }
    }
}