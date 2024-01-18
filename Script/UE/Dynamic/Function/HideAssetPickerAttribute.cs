using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class HideAssetPickerAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public HideAssetPickerAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public HideAssetPickerAttribute()
    {
        this.MetaValue = "true";
    }
    }
}