using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ShowOnlyInnerPropertiesAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ShowOnlyInnerPropertiesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ShowOnlyInnerPropertiesAttribute()
    {
        this.MetaValue = "true";
    }
    }
}