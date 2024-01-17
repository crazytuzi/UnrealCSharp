using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ScriptConstantHostAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ScriptConstantHostAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}