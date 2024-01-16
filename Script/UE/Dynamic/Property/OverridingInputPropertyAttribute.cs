using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class OverridingInputPropertyAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public OverridingInputPropertyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}