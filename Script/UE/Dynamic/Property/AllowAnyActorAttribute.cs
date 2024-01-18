using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowAnyActorAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public AllowAnyActorAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public AllowAnyActorAttribute()
    {
        this.MetaValue = "true";
    }
    }
}