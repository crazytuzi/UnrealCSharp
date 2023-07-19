using System;
 namespace Script.Mixin 
{     
[AttributeUsage(AttributeTargets.Property)]     
public class SkipSerializationAttribute  : Attribute    
{    
} 
}