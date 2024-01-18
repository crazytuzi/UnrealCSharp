using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class HasNativeBreakAttribute : UStructAttribute
    {
    public string MetaValue { get; set; }
    public HasNativeBreakAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public HasNativeBreakAttribute()
    {
        this.MetaValue = "true";
    }
    }
}