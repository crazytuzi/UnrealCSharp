#pragma once

enum
{
	EX_CallCSharp = EX_Max - 1
};

class FCSharpInvoker
{
public:
	DECLARE_FUNCTION(execCallCSharp);
};
