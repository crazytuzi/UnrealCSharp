using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ChildCanTickAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ChildCanTickAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}