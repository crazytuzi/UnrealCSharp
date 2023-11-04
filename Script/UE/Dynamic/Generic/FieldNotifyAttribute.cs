using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method | AttributeTargets.Property)]
    public class FieldNotifyAttribute : Attribute
    {
    }
}