using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class InvalidEnumValuesAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public InvalidEnumValuesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public InvalidEnumValuesAttribute()
    {
        this.MetaValue = "true";
    }
    }
}