using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DeltaAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DeltaAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}