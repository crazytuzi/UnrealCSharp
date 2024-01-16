using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class LongPackageNameAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public LongPackageNameAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}