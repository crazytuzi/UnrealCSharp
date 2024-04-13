using System;
using Script.CoreUObject;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ReplicatedUsingAttribute : Attribute
    {
        public ReplicatedUsingAttribute(string InRepCallbackName,
            ELifetimeCondition InLifetimeCondition = ELifetimeCondition.COND_None)
        {
            RepCallbackName = InRepCallbackName;

            LifetimeCondition = InLifetimeCondition;
        }

        private string RepCallbackName { get; set; }

        private ELifetimeCondition LifetimeCondition { get; set; }
    }
}