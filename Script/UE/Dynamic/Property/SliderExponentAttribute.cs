using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class SliderExponentAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public SliderExponentAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public SliderExponentAttribute()
    {
        this.MetaValue = "true";
    }
    }
}