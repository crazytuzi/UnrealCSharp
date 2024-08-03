#pragma once

#include "mono/metadata/object-forward.h"

struct FDelegateWrapper
{
	TWeakObjectPtr<UObject> Object;

	MonoMethod* Method;
};

static bool operator==(const FDelegateWrapper& A, const FDelegateWrapper& B)
{
	return A.Object == B.Object && A.Method == B.Method;
}
