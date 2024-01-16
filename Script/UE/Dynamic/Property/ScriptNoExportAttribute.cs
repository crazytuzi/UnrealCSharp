using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ScriptNoExportAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ScriptNoExportAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}