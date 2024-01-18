using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisplayThumbnailAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DisplayThumbnailAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DisplayThumbnailAttribute()
    {
        this.MetaValue = "true";
    }
    }
}