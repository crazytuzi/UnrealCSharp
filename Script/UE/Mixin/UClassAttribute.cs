using System;
using Script.Common;

namespace Script.Mixin
{
    [AttributeUsage(AttributeTargets.Class)]
    public class UClassAttribute : IsOverrideAttribute
    {
    }
}