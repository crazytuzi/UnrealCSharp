using System;

namespace Script.CoreUObject
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Method)]
    public class OverrideAttribute : Attribute
    {
    }
}