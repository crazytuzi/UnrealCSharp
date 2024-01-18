using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class EditConditionAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public EditConditionAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public EditConditionAttribute()
    {
        this.MetaValue = "true";
    }
    }
}