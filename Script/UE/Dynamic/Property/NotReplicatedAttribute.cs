using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class NotReplicatedAttribute : Attribute
    {
    }
}