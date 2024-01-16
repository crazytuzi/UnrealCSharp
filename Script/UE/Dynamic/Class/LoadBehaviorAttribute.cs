using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Property)]
    public class LoadBehaviorAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public LoadBehaviorAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}