using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NeverAsPinAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public NeverAsPinAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}