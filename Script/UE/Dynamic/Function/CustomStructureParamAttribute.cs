using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CustomStructureParamAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public CustomStructureParamAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}