using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ExpandEnumAsExecsAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ExpandEnumAsExecsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}