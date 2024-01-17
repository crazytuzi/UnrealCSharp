using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MultiLineAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public MultiLineAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public MultiLineAttribute()
    {
        this.MetaValue = "true";
    }
    }
}