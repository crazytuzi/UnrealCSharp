using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowPrivateAccessAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public AllowPrivateAccessAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public AllowPrivateAccessAttribute()
    {
        this.MetaValue = "true";
    }
    }
}