using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ScriptConstantHostAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ScriptConstantHostAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ScriptConstantHostAttribute()
    {
        this.MetaValue = "true";
    }
    }
}