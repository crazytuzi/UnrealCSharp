#pragma once

#define BINDING_REMOVE_PREFIX_CLASS(Class) Class.RightChop(1)

#define BINDING_CLASS_IMPLEMENTATION(A) FString::Printf(TEXT("%sImplementation"), *A)

#define BINDING_COMBINE_FUNCTION(A, B) FString::Printf(TEXT("%s_%sImplementation"), *A, *B)

#define BINDING_PROPERTY_SET FString(TEXT("Set"))

#define BINDING_PROPERTY_GET FString(TEXT("Get"))
