using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CallableWithoutWorldContextAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public CallableWithoutWorldContextAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}