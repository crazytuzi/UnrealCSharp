using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class UnsafeDuringActorConstructionAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public UnsafeDuringActorConstructionAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}