using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ForceUnitsAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ForceUnitsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ForceUnitsAttribute()
    {
        this.MetaValue = "true";
    }
    }
}