using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class EditFixedOrderAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public EditFixedOrderAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}