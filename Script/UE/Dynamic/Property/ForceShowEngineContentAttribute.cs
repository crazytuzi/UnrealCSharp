using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ForceShowEngineContentAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ForceShowEngineContentAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ForceShowEngineContentAttribute()
    {
        this.MetaValue = "true";
    }
    }
}