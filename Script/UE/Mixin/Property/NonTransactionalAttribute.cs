using System;

namespace Script.Mixin
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NonTransactionalAttribute : Attribute
    {
    }
}