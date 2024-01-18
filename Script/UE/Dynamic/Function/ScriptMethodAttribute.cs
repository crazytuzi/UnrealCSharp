using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ScriptMethodAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ScriptMethodAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ScriptMethodAttribute()
    {
        this.MetaValue = "true";
    }
    }
}