using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CompactNodeTitleAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public CompactNodeTitleAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}