using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NoElementDuplicateAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public NoElementDuplicateAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}