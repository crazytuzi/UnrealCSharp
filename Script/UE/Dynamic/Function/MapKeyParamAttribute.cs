using System;
using Script.Common;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class MapKeyParamAttribute : Attribute
    {
        public string MetaValue { get; set; }

        public MapKeyParamAttribute(string MetaValue)
        {
            this.MetaValue = MetaValue;
        }

        public MapKeyParamAttribute()
        {
            this.MetaValue = "true";
        }
    }
}