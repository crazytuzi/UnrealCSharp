using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ArrayClampAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ArrayClampAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}