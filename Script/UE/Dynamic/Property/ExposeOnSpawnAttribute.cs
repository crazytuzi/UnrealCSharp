using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ExposeOnSpawnAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ExposeOnSpawnAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ExposeOnSpawnAttribute()
    {
        this.MetaValue = "true";
    }
    }
}