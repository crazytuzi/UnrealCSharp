using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ForceShowPluginContentAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ForceShowPluginContentAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}