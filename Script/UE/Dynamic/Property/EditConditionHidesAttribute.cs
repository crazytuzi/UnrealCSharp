using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class EditConditionHidesAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public EditConditionHidesAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}