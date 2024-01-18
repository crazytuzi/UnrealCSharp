using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CompactNodeTitleAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public CompactNodeTitleAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public CompactNodeTitleAttribute()
    {
        this.MetaValue = "true";
    }
    }
}