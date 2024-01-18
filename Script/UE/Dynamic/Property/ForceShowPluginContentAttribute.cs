using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ForceShowPluginContentAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ForceShowPluginContentAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ForceShowPluginContentAttribute()
    {
        this.MetaValue = "true";
    }
    }
}