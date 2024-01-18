using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ClampMaxAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ClampMaxAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}