#pragma once

#define BINDING_CLASS_IMPLEMENTATION(A) A + FString(TEXT("Implementation"))

#define BINDING_COMBINE_FUNCTION(A, B) A + FString(TEXT("_")) + B + FString(TEXT("Implementation"))

#define BINDING_PROPERTY_SET FString(TEXT("Set"))

#define BINDING_PROPERTY_GET FString(TEXT("Get"))

#define BINDING_BASE_STRUCTURE(T) FString(TEXT("F")) + TBaseStructure<T>::Get()->GetName()
