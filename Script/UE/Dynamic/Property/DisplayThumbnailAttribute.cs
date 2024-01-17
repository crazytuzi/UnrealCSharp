using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisplayThumbnailAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DisplayThumbnailAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}