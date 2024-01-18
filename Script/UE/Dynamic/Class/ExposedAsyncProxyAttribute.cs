using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ExposedAsyncProxyAttribute : UClassAttribute
    {
    public string MetaValue { get; set; }
    public ExposedAsyncProxyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ExposedAsyncProxyAttribute()
    {
        this.MetaValue = "true";
    }
    }
}