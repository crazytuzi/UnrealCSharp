using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisplayPriorityAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DisplayPriorityAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}