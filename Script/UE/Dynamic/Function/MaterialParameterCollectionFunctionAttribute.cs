using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class MaterialParameterCollectionFunctionAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public MaterialParameterCollectionFunctionAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public MaterialParameterCollectionFunctionAttribute()
    {
        this.MetaValue = "true";
    }
    }
}