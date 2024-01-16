using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class PinShownByDefaultAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public PinShownByDefaultAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}