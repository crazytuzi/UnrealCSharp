using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class HideViewOptionsAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public HideViewOptionsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public HideViewOptionsAttribute()
    {
        this.MetaValue = "true";
    }
    }
}