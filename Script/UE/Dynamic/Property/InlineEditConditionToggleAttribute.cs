using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class InlineEditConditionToggleAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public InlineEditConditionToggleAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}