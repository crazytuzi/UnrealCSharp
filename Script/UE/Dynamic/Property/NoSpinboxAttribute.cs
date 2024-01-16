using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NoSpinboxAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public NoSpinboxAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}