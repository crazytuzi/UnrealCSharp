using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ScriptNoExportAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ScriptNoExportAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ScriptNoExportAttribute()
    {
        this.MetaValue = "true";
    }
    }
}