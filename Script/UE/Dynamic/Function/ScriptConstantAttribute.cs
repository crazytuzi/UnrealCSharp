using System;
using Script.Common;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class ScriptConstantAttribute : Attribute
    {
        public string MetaValue { get; set; }

        public ScriptConstantAttribute(string MetaValue)
        {
            this.MetaValue = MetaValue;
        }

        public ScriptConstantAttribute()
        {
            this.MetaValue = "true";
        }
    }
}