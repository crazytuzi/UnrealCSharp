using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CallableWithoutWorldContextAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public CallableWithoutWorldContextAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public CallableWithoutWorldContextAttribute()
    {
        this.MetaValue = "true";
    }
    }
}