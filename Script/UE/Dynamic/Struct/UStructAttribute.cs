using System;
using Script.Common;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class UStructAttribute : IsOverrideAttribute
    {
    }
}