using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class LatentCallbackTargetAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public LatentCallbackTargetAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}