using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class UIMaxAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public UIMaxAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}