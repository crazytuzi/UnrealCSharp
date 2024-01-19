using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class AllowAnyActorAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}