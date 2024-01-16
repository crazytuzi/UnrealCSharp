using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ForceShowEngineContentAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ForceShowEngineContentAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}