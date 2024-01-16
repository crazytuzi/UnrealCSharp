using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DebugTreeLeafAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DebugTreeLeafAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}