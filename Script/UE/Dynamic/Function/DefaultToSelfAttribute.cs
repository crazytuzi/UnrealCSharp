using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DefaultToSelfAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DefaultToSelfAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DefaultToSelfAttribute()
    {
        this.MetaValue = "true";
    }
    }
}