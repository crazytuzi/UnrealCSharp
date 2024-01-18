using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class UntrackedAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public UntrackedAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public UntrackedAttribute()
    {
        this.MetaValue = "true";
    }
    }
}