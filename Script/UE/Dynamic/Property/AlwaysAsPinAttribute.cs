using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AlwaysAsPinAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public AlwaysAsPinAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}