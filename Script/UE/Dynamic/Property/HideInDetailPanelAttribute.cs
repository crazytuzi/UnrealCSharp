using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class HideInDetailPanelAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public HideInDetailPanelAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public HideInDetailPanelAttribute()
    {
        this.MetaValue = "true";
    }
    }
}