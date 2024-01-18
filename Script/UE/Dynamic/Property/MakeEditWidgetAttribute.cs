using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MakeEditWidgetAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public MakeEditWidgetAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public MakeEditWidgetAttribute()
    {
        this.MetaValue = "true";
    }
    }
}