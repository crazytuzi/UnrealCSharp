using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class HideInDetailPanelAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public HideInDetailPanelAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}