using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class HideAlphaChannelAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public HideAlphaChannelAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}