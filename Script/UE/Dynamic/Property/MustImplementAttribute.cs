using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MustImplementAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public MustImplementAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public MustImplementAttribute()
    {
        this.MetaValue = "true";
    }
    }
}