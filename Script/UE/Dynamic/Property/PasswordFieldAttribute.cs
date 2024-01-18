using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class PasswordFieldAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public PasswordFieldAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public PasswordFieldAttribute()
    {
        this.MetaValue = "true";
    }
    }
}