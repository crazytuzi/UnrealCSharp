using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ValidEnumValuesAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ValidEnumValuesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ValidEnumValuesAttribute()
    {
        this.MetaValue = "true";
    }
    }
}