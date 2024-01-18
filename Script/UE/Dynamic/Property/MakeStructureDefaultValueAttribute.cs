using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MakeStructureDefaultValueAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public MakeStructureDefaultValueAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public MakeStructureDefaultValueAttribute()
    {
        this.MetaValue = "true";
    }
    }
}