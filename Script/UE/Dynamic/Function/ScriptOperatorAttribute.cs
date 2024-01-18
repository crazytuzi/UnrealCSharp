using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ScriptOperatorAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ScriptOperatorAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ScriptOperatorAttribute()
    {
        this.MetaValue = "true";
    }
    }
}