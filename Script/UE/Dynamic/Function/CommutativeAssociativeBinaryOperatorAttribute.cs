using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CommutativeAssociativeBinaryOperatorAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public CommutativeAssociativeBinaryOperatorAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}