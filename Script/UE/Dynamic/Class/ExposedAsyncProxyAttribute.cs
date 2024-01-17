using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ExposedAsyncProxyAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ExposedAsyncProxyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}