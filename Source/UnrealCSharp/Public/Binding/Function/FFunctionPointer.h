#pragma once

struct FFunctionPointer
{
	explicit FFunctionPointer(void (*InFunction)(BINDING_FUNCTION_SIGNATURE))
	{
		Value.Function = InFunction;
	}

	union
	{
		void (*Function)(BINDING_FUNCTION_SIGNATURE);

		void* Pointer;
	} Value;
};
