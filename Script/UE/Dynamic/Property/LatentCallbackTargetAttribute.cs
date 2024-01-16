using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class LatentCallbackTargetAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public LatentCallbackTargetAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}