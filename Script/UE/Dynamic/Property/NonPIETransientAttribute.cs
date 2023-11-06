using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NonPIETransientAttribute : Attribute
    {
    }
}