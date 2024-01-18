using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class HiddenByDefaultAttribute : UStructAttribute
    {
    public string MetaValue { get; set; }
    public HiddenByDefaultAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public HiddenByDefaultAttribute()
    {
        this.MetaValue = "true";
    }
    }
}