using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ArrayTypeDependentParamsAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ArrayTypeDependentParamsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}