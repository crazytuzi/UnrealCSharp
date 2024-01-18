using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DeprecatedPropertyAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DeprecatedPropertyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DeprecatedPropertyAttribute()
    {
        this.MetaValue = "true";
    }
    }
}