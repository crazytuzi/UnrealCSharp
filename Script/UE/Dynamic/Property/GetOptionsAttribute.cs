using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class GetOptionsAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public GetOptionsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}