using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DontUseGenericSpawnObjectAttribute : UClassAttribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public DontUseGenericSpawnObjectAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}