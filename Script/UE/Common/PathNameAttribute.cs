using System;

namespace Script.Common
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Enum | AttributeTargets.Interface)]
    public class PathNameAttribute : Attribute
    {
        public PathNameAttribute(string InPathName) => PathName = InPathName;

        public string PathName { get; set; }
    }
}