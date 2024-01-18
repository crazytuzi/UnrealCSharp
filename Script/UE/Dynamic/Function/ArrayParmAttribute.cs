using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ArrayParmAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ArrayParmAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ArrayParmAttribute()
    {
        this.MetaValue = "true";
    }
    }
}