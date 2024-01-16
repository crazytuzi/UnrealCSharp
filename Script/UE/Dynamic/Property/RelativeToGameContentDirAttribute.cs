using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class RelativeToGameContentDirAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public RelativeToGameContentDirAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}