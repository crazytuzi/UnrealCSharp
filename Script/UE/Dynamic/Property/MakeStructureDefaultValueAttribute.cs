using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class MakeStructureDefaultValueAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public MakeStructureDefaultValueAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}