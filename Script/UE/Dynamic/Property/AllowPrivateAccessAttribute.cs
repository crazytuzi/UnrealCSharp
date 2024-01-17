using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowPrivateAccessAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public AllowPrivateAccessAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}