using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NonTransactionalAttribute : Attribute
    {
    }
}