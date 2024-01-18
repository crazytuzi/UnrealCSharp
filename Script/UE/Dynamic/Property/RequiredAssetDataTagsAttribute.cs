using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class RequiredAssetDataTagsAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public RequiredAssetDataTagsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public RequiredAssetDataTagsAttribute()
    {
        this.MetaValue = "true";
    }
    }
}