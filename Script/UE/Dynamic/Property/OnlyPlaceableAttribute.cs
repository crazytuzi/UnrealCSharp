using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class OnlyPlaceableAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public OnlyPlaceableAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}