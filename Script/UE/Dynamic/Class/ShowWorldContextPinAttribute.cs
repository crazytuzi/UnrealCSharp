using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class ShowWorldContextPinAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public ShowWorldContextPinAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}