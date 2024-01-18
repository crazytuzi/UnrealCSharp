using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowPreserveRatioAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public AllowPreserveRatioAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public AllowPreserveRatioAttribute()
    {
        this.MetaValue = "true";
    }
    }
}