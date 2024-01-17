using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class LatentInfoAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public LatentInfoAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}