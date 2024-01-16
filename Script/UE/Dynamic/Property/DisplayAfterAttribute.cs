using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisplayAfterAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DisplayAfterAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}