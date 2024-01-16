using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class PasswordFieldAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public PasswordFieldAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}