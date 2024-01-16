using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisallowedAssetDataTagsAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DisallowedAssetDataTagsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}