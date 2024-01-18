using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class UnitsAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public UnitsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public UnitsAttribute()
    {
        this.MetaValue = "true";
    }
    }
}