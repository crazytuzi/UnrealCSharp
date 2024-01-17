using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class HiddenByDefaultAttribute : UStructAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public HiddenByDefaultAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}