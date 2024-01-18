using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NoSpinboxAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public NoSpinboxAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public NoSpinboxAttribute()
    {
        this.MetaValue = "true";
    }
    }
}