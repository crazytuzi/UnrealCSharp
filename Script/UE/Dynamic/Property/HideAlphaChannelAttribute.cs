using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class HideAlphaChannelAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public HideAlphaChannelAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public HideAlphaChannelAttribute()
    {
        this.MetaValue = "true";
    }
    }
}