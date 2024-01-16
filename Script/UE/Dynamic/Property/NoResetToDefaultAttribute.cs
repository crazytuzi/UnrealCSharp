using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NoResetToDefaultAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public NoResetToDefaultAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}