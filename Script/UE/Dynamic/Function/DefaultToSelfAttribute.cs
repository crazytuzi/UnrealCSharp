using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DefaultToSelfAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DefaultToSelfAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}