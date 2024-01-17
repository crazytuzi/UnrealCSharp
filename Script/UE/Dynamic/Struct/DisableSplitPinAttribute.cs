using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DisableSplitPinAttribute : UStructAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DisableSplitPinAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}