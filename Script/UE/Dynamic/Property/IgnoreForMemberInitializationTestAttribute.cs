using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class IgnoreForMemberInitializationTestAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public IgnoreForMemberInitializationTestAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}