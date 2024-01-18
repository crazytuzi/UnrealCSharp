using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class DontUseGenericSpawnObjectAttribute : UClassAttribute
    {
    public string MetaValue { get; set; }
    public DontUseGenericSpawnObjectAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DontUseGenericSpawnObjectAttribute()
    {
        this.MetaValue = "true";
    }
    }
}