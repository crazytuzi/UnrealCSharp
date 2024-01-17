using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class NativeMakeFuncAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public NativeMakeFuncAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}