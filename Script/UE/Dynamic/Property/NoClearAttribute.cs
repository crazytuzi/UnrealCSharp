using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NoClearAttribute : Attribute
    {
    }
}