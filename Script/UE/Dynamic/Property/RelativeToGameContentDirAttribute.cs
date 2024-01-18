using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class RelativeToGameContentDirAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public RelativeToGameContentDirAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}