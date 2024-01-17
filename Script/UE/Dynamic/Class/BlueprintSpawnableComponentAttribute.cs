using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class BlueprintSpawnableComponentAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public BlueprintSpawnableComponentAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}