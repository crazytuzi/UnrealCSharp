using System;

namespace Script.Mixin
{
    [AttributeUsage(AttributeTargets.Method)]
    public class UnreliableAttribute : Attribute
    {
    }
}