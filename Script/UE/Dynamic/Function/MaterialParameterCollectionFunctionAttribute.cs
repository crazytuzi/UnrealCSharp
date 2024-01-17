using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class MaterialParameterCollectionFunctionAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public MaterialParameterCollectionFunctionAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}