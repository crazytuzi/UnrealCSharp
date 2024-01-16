using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class FilePathFilterAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public FilePathFilterAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}