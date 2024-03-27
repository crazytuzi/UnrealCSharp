using System;
using Script.CoreUObject;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class ReplicatedAttribute : Attribute
    {
        public ReplicatedAttribute(ELifetimeCondition InLifetimeCondition = ELifetimeCondition.COND_None)
        {
            LifetimeCondition = InLifetimeCondition;
        }

        private ELifetimeCondition LifetimeCondition { get; set; }
    }
}