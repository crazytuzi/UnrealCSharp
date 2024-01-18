using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class EditFixedOrderAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public EditFixedOrderAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public EditFixedOrderAttribute()
    {
        this.MetaValue = "true";
    }
    }
}