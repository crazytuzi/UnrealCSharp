using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NeedsLatentFixupAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public NeedsLatentFixupAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public NeedsLatentFixupAttribute()
    {
        this.MetaValue = "true";
    }
    }
}