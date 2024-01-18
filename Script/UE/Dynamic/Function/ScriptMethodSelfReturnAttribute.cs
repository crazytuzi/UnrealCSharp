using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ScriptMethodSelfReturnAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ScriptMethodSelfReturnAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ScriptMethodSelfReturnAttribute()
    {
        this.MetaValue = "true";
    }
    }
}