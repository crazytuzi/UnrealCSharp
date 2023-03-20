#include "Registry/FMultiRegistry.h"

FMultiRegistry::FMultiRegistry()
{
	Initialize();
}

FMultiRegistry::~FMultiRegistry()
{
	Deinitialize();
}

void FMultiRegistry::Initialize()
{
}

void FMultiRegistry::Deinitialize()
{
	GarbageCollectionHandle2SubclassOfAddress.Empty();

	SubclassOfAddress2GarbageCollectionHandle.Empty();

	GarbageCollectionHandle2WeakObjectPtrAddress.Empty();;

	WeakObjectPtrAddress2GarbageCollectionHandle.Empty();;

	GarbageCollectionHandle2LazyObjectPtrAddress.Empty();;

	LazyObjectPtrAddress2GarbageCollectionHandle.Empty();;

	GarbageCollectionHandle2SoftObjectPtrAddress.Empty();;

	SoftObjectPtrAddress2GarbageCollectionHandle.Empty();;

	GarbageCollectionHandle2ScriptInterfaceAddress.Empty();;

	ScriptInterfaceAddress2GarbageCollectionHandle.Empty();;

	GarbageCollectionHandle2SoftClassPtrAddress.Empty();

	SoftClassPtrAddress2GarbageCollectionHandle.Empty();
}
