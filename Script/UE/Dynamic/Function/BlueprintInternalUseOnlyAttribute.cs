using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class BlueprintInternalUseOnlyAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public BlueprintInternalUseOnlyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public BlueprintInternalUseOnlyAttribute()
    {
        this.MetaValue = "true";
    }
    }
}