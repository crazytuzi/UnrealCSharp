#pragma once

template <typename T>
struct TIsTScriptInterface
{
	enum { Value = false };
};

template <typename T>
struct TIsTScriptInterface<TScriptInterface<T>>
{
	enum { Value = true };
};
