using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ScriptMethodAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ScriptMethodAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}