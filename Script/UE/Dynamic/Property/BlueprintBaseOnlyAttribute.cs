using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class BlueprintBaseOnlyAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public BlueprintBaseOnlyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}