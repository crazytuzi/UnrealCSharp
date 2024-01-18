using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class HasNativeMakeAttribute : UStructAttribute
    {
    public string MetaValue { get; set; }
    public HasNativeMakeAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public HasNativeMakeAttribute()
    {
        this.MetaValue = "true";
    }
    }
}