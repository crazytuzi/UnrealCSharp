using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MaxLengthAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public MaxLengthAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}