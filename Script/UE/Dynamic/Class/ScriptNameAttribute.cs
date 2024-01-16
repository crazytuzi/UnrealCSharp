using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method | AttributeTargets.Property)]
    public class ScriptNameAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ScriptNameAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}