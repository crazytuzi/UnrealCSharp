using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DeprecatedNodeAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DeprecatedNodeAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}