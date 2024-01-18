using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class KeywordsAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public KeywordsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public KeywordsAttribute()
    {
        this.MetaValue = "true";
    }
    }
}