using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class IgnoreForMemberInitializationTestAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public IgnoreForMemberInitializationTestAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public IgnoreForMemberInitializationTestAttribute()
    {
        this.MetaValue = "true";
    }
    }
}