using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class RelativeToGameDirAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public RelativeToGameDirAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}