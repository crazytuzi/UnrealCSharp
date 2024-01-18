using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NoResetToDefaultAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public NoResetToDefaultAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public NoResetToDefaultAttribute()
    {
        this.MetaValue = "true";
    }
    }
}