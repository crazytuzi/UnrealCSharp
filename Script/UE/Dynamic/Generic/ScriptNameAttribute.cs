using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Property)]
    public class ScriptNameAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ScriptNameAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}