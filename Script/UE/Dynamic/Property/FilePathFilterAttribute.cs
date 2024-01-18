using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class FilePathFilterAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public FilePathFilterAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}