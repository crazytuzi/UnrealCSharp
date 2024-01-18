using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ClampMinAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ClampMinAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}