#pragma once

#include "Reflection/FMethodReflection.h"

struct FDelegateWrapper
{
	TWeakObjectPtr<UObject> Object;

	FMethodReflection* Method;
};

static bool operator==(const FDelegateWrapper& A, const FDelegateWrapper& B)
{
	return A.Object == B.Object && A.Method == B.Method;
}
