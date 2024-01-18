using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowedClassesAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public AllowedClassesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public AllowedClassesAttribute()
    {
        this.MetaValue = "true";
    }
    }
}