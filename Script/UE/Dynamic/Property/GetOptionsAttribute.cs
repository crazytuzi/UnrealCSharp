using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class GetOptionsAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public GetOptionsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public GetOptionsAttribute()
    {
        this.MetaValue = "true";
    }
    }
}