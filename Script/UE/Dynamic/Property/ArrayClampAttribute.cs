using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ArrayClampAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ArrayClampAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ArrayClampAttribute()
    {
        this.MetaValue = "true";
    }
    }
}