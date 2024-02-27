using System;

namespace Script.CoreUObject
{
    [AttributeUsage(AttributeTargets.Class | AttributeTargets.Enum | AttributeTargets.Interface)]
    public class PathNameAttribute : Attribute
    {
        public PathNameAttribute(string InPathName) => PathName = InPathName;

        public string PathName { get; }
    }
}