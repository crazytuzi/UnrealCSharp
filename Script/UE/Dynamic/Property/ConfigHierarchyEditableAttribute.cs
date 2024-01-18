using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ConfigHierarchyEditableAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ConfigHierarchyEditableAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public ConfigHierarchyEditableAttribute()
    {
        this.MetaValue = "true";
    }
    }
}