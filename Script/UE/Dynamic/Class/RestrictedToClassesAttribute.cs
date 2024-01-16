using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class RestrictedToClassesAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public RestrictedToClassesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}