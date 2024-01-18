using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class OnlyPlaceableAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public OnlyPlaceableAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public OnlyPlaceableAttribute()
    {
        this.MetaValue = "true";
    }
    }
}