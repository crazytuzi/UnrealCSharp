using System;
using Script.Common;

namespace Script.Mixin
{
    [AttributeUsage(AttributeTargets.Method)]
    public class UFunctionAttribute : IsOverrideAttribute
    {
    }
}