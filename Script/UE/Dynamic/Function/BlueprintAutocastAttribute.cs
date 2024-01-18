using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class BlueprintAutocastAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public BlueprintAutocastAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public BlueprintAutocastAttribute()
    {
        this.MetaValue = "true";
    }
    }
}