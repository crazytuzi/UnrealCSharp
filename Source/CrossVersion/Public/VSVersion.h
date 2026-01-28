#pragma once

#ifdef _MSC_VER
#define VS2022 _MSC_VER >= 1930 && _MSC_VER < 1950

#define VS2026 _MSC_VER >= 1950
#else
#define VS2022 0

#define VS2026 0
#endif
