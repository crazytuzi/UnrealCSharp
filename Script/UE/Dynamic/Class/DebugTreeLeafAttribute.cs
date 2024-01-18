using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DebugTreeLeafAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DebugTreeLeafAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    
    }
}