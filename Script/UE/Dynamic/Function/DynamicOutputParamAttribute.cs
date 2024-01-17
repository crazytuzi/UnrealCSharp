using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DynamicOutputParamAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DynamicOutputParamAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}