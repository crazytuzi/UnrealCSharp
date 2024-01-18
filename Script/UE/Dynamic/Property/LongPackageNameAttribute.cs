using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class LongPackageNameAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public LongPackageNameAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public LongPackageNameAttribute()
    {
        this.MetaValue = "true";
    }
    }
}