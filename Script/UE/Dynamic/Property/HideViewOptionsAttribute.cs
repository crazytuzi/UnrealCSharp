using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class HideViewOptionsAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public HideViewOptionsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}