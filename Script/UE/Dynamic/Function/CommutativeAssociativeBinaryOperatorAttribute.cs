using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class CommutativeAssociativeBinaryOperatorAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public CommutativeAssociativeBinaryOperatorAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public CommutativeAssociativeBinaryOperatorAttribute()
    {
        this.MetaValue = "true";
    }
    }
}