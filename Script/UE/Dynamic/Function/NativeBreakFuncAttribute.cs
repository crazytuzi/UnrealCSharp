using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class NativeBreakFuncAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public NativeBreakFuncAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public NativeBreakFuncAttribute()
    {
        this.MetaValue = "true";
    }
    }
}