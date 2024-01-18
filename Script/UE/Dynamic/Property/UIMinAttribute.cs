using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class UIMinAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public UIMinAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}