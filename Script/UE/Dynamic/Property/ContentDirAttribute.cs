using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ContentDirAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public ContentDirAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}