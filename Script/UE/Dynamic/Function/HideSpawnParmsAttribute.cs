using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class HideSpawnParmsAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public HideSpawnParmsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}