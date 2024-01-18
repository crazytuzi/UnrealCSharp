using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class BlueprintInternalUseOnlyAttribute : Attribute
    {
    public string MetaValue { get; set; }
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