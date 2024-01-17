using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class NativeBreakFuncAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public NativeBreakFuncAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}