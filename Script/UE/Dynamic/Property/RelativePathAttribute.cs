using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class RelativePathAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public RelativePathAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public RelativePathAttribute()
    {
        this.MetaValue = "true";
    }
    }
}