using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ScriptMethodSelfReturnAttribute : Attribute
    {
        private string Value { get; set; } = "true";
    }
}