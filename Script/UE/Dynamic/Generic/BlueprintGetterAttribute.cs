using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Property)]
    public class BlueprintGetterAttribute : Attribute
    {
        public BlueprintGetterAttribute(string InValue = "")
        {
        }
    }
}