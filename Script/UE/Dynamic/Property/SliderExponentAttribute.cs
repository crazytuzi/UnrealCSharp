using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class SliderExponentAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public SliderExponentAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}