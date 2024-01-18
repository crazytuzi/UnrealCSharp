using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class AutoCreateRefTermAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public AutoCreateRefTermAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public AutoCreateRefTermAttribute()
    {
        this.MetaValue = "true";
    }
    }
}