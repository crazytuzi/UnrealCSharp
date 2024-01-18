using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AssetBundlesAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public AssetBundlesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public AssetBundlesAttribute()
    {
        this.MetaValue = "true";
    }
    }
}