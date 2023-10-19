using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DuplicateTransientAttribute : Attribute
    {
    }
}