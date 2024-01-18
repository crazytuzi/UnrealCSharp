using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisallowedClassesAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DisallowedClassesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DisallowedClassesAttribute()
    {
        this.MetaValue = "true";
    }
    }
}