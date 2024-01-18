using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Property)]
    public class DeprecationMessageAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DeprecationMessageAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}