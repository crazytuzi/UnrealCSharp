using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MakeEditWidgetAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public MakeEditWidgetAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}