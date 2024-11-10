#pragma once

#include "ContentBrowserItemData.h"

class FDynamicFolderItemDataPayload final : public IContentBrowserItemDataPayload
{
public:
	explicit FDynamicFolderItemDataPayload(const FName& InInternalPath):
		InternalPath(InInternalPath)
	{
	}

	const FName& GetInternalPath() const
	{
		return InternalPath;
	}

private:
	FName InternalPath;
};
