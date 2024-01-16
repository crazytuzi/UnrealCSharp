using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class NotBlueprintThreadSafeAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public NotBlueprintThreadSafeAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}