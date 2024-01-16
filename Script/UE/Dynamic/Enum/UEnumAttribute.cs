using System;
using Script.Common;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Enum)]
    public class UEnumAttribute : IsOverrideAttribute
    {
    }
}