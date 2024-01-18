using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class EditConditionHidesAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public EditConditionHidesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public EditConditionHidesAttribute()
    {
        this.MetaValue = "true";
    }
    }
}