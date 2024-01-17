using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowAnyActorAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public AllowAnyActorAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}