using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class RelativeToGameDirAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public RelativeToGameDirAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}