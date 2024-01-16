using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NoEditInlineAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public NoEditInlineAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}