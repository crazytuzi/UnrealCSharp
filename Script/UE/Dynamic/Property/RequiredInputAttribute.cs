using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class RequiredInputAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public RequiredInputAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}