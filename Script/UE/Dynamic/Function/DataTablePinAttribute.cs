using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class DataTablePinAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DataTablePinAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DataTablePinAttribute()
    {
        this.MetaValue = "true";
    }
    }
}