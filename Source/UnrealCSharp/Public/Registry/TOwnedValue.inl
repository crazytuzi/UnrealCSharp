#pragma once

template <typename Derived>
struct TOwnedValue
{
	explicit TOwnedValue(const bool InNeedFree) :
		bNeedFree(InNeedFree)
	{
	}

	void Free()
	{
		if (bNeedFree)
		{
			static_cast<Derived*>(this)->FreeImplementation();

			bNeedFree = false;
		}
	}

	bool bNeedFree;
};
