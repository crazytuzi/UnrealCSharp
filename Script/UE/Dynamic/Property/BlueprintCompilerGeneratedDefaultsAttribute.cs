using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class BlueprintCompilerGeneratedDefaultsAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public BlueprintCompilerGeneratedDefaultsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public BlueprintCompilerGeneratedDefaultsAttribute()
    {
        this.MetaValue = "true";
    }
    }
}