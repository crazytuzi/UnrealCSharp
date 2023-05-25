using System;
using Script.Common;

namespace Script.Mixin
{
    [AttributeUsage(AttributeTargets.Enum)]
    public class UEnumAttribute : IsOverrideAttribute
    {
    }
}