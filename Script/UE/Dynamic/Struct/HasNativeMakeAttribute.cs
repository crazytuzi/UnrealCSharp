using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class HasNativeMakeAttribute : UStructAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public HasNativeMakeAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}