using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NeedsLatentFixupAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public NeedsLatentFixupAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}