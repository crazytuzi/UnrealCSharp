using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class UnsafeDuringActorConstructionAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public UnsafeDuringActorConstructionAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public UnsafeDuringActorConstructionAttribute()
    {
        this.MetaValue = "true";
    }
    }
}