using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class IsBlueprintBaseAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public IsBlueprintBaseAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}