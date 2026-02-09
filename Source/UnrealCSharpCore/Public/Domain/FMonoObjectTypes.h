#pragma once

#include "mono/metadata/details/object-types.h"

typedef uint32_t       guint32;

typedef uint64_t       guint64;

typedef guint64 mono_64bitaligned_t;

typedef uint32_t mono_array_size_t;

typedef int32_t mono_array_lower_bound_t;

typedef struct {
	mono_array_size_t length;
	mono_array_lower_bound_t lower_bound;
} MonoArrayBounds;

struct _MonoArray {
	MonoObject obj;
	/* bounds is NULL for szarrays */
	MonoArrayBounds *bounds;
	/* total number of elements of the array */
	mono_array_size_t max_length;
	/* we use mono_64bitaligned_t to ensure proper alignment on platforms that need it */
	mono_64bitaligned_t vector [MONO_ZERO_LEN_ARRAY];
};

struct _MonoReflectionMethod
{
	MonoObject object;
	MonoMethod* method;
	MonoString* name;
	MonoReflectionType* reftype;
};

struct _MonoReflectionField {
	MonoObject object;
	MonoClass *klass;
	MonoClassField *field;
	MonoString *name;
	MonoReflectionType *type;
	guint32 attrs;
};

struct _MonoReflectionProperty {
	MonoObject object;
	MonoClass *klass;
	MonoProperty *property;
};
