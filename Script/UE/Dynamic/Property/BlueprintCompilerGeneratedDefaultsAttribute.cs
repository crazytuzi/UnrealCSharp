using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class BlueprintCompilerGeneratedDefaultsAttribute : Attribute
    {
    public string MetaValue { get; set; }
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