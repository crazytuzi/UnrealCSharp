using System;

namespace Script.Engine
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Enum)]
    public class PathNameAttribute : Attribute
    {
        public PathNameAttribute(string InPathName) => PathName = InPathName;

        public string PathName { get; set; }
    }
}