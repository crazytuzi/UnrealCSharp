using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class FixedIncrementAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public FixedIncrementAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}