using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ConfigHierarchyEditableAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ConfigHierarchyEditableAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}