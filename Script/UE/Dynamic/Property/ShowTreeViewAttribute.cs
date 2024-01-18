using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ShowTreeViewAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ShowTreeViewAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ShowTreeViewAttribute()
    {
        this.MetaValue = "true";
    }
    }
}