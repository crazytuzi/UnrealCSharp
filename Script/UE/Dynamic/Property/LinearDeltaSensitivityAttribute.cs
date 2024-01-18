using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class LinearDeltaSensitivityAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public LinearDeltaSensitivityAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public LinearDeltaSensitivityAttribute()
    {
        this.MetaValue = "true";
    }
    }
}