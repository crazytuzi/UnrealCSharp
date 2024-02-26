using System;
using Script.CoreUObject;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class UFunctionAttribute : OverrideAttribute
    {
    }
}