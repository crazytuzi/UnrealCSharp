using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Property)]
    public class DocumentationPolicyAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DocumentationPolicyAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}