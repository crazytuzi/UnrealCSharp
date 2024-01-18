using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DevelopmentOnlyAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DevelopmentOnlyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DevelopmentOnlyAttribute()
    {
        this.MetaValue = "true";
    }
    }
}