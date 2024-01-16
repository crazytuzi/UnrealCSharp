using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Property)]
    public class ToolTipAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ToolTipAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}