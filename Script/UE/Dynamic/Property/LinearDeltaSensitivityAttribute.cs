using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class LinearDeltaSensitivityAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public LinearDeltaSensitivityAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}