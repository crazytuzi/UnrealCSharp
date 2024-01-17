using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class PinHiddenByDefaultAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public PinHiddenByDefaultAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}