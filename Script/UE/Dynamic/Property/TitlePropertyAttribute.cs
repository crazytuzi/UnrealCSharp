using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class TitlePropertyAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public TitlePropertyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}