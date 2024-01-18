using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MetaClassAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public MetaClassAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}