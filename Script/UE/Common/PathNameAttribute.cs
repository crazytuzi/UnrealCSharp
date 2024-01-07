using System;

namespace Script.Common
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Enum | AttributeTargets.Interface)]
    public class PathNameAttribute : Attribute
    {
        public PathNameAttribute(String InPathName) => PathName = InPathName;

        public String PathName { get; set; }
    }
}