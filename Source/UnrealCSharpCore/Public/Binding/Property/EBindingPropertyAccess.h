#pragma once

enum class EBindingPropertyAccess
{
	None = 0b00,
	OnlyRead = 0b01,
	OnlyWrite = 0b10,
	ReadAndWrite = OnlyRead | OnlyWrite
};
