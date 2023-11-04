using System;
using Script.Common;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class UFunctionAttribute : IsOverrideAttribute
    {
    }
}