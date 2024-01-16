using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class SetParamAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public SetParamAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}