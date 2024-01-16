using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class AutoCreateRefTermAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public AutoCreateRefTermAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}