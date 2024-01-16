using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DeterminesOutputTypeAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DeterminesOutputTypeAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}