using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class BlueprintProtectedAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public BlueprintProtectedAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public BlueprintProtectedAttribute()
    {
        this.MetaValue = "true";
    }
    }
}