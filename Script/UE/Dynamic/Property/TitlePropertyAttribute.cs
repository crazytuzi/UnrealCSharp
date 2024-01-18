using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class TitlePropertyAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public TitlePropertyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public TitlePropertyAttribute()
    {
        this.MetaValue = "true";
    }
    }
}