#pragma once

#include "CoreMinimal.h"

template <class T>
class TFieldIteratorExt
{
private:
	/** The object being searched for the specified field */
	const UStruct* Struct;
	/** The current location in the list of fields being iterated */
	typename T::BaseFieldClass* Field;
	/** The index of the current interface being iterated */
	int32 InterfaceIndex;
	/** Whether to include the super class or not */
	const bool bIncludeSuper;
	/** Whether to include deprecated fields or not */
	const bool bIncludeDeprecated;
	/** Whether to include interface fields or not */
	const bool bIncludeInterface;

public:
	TFieldIteratorExt(const UStruct* InStruct, EFieldIterationFlags InIterationFlags = EFieldIterationFlags::Default)
		: Struct            ( InStruct )
		, Field             ( InStruct ? GetChildFieldsFromStruct<typename T::BaseFieldClass>(InStruct) : NULL )
		, InterfaceIndex    ( -1 )
		, bIncludeSuper     ( EnumHasAnyFlags(InIterationFlags, EFieldIterationFlags::IncludeSuper) )
		, bIncludeDeprecated( EnumHasAnyFlags(InIterationFlags, EFieldIterationFlags::IncludeDeprecated) )
		, bIncludeInterface ( EnumHasAnyFlags(InIterationFlags, EFieldIterationFlags::IncludeInterfaces) && InStruct && InStruct->IsA(UClass::StaticClass()) )
	{
		IterateToNext();
	}

	/** Legacy version taking the flags as 3 separate values */
	TFieldIteratorExt(const UStruct*                               InStruct,
	               EFieldIteratorFlags::SuperClassFlags         InSuperClassFlags,
	               EFieldIteratorFlags::DeprecatedPropertyFlags InDeprecatedFieldFlags = EFieldIteratorFlags::IncludeDeprecated,
	               EFieldIteratorFlags::InterfaceClassFlags     InInterfaceFieldFlags  = EFieldIteratorFlags::ExcludeInterfaces)
		: TFieldIteratorExt(InStruct, (EFieldIterationFlags)(InSuperClassFlags | InDeprecatedFieldFlags | InInterfaceFieldFlags))
	{
	}

	/** conversion to "bool" returning true if the iterator is valid. */
	FORCEINLINE explicit operator bool() const
	{ 
		return Field != NULL; 
	}
	/** inverse of the "bool" operator */
	FORCEINLINE bool operator !() const 
	{
		return !(bool)*this;
	}

	inline friend bool operator==(const TFieldIteratorExt<T>& Lhs, const TFieldIteratorExt<T>& Rhs) { return Lhs.Field == Rhs.Field; }
	inline friend bool operator!=(const TFieldIteratorExt<T>& Lhs, const TFieldIteratorExt<T>& Rhs) { return Lhs.Field != Rhs.Field; }

	inline void operator++()
	{
		checkSlow(Field);
		Field = Field->Next;
		IterateToNext();
	}
	inline T* operator*()
	{
		checkSlow(Field);
		return (T*)Field;
	}
	inline const T* operator*() const
	{
		checkSlow(Field);
		return (const T*)Field;
	}
	inline T* operator->()
	{
		checkSlow(Field);
		return (T*)Field;
	}
	inline const UStruct* GetStruct()
	{
		return Struct;
	}
protected:
	inline void IterateToNext()
	{
		typename T::BaseFieldClass* CurrentField  = Field;
		const UStruct* CurrentStruct = Struct;

		while (CurrentStruct)
		{
			while (CurrentField)
			{
				typename T::FieldTypeClass* FieldClass = CurrentField->GetClass();

				if (FieldClass->HasAllCastFlags(T::StaticClassCastFlags()) &&
					(
						   bIncludeDeprecated
						|| !FieldClass->HasAllCastFlags(CASTCLASS_FProperty)
						|| !((FProperty*)CurrentField)->HasAllPropertyFlags(CPF_Deprecated)
					)
				)
				{
					Struct = CurrentStruct;
					Field  = CurrentField;
					return;
				}

				CurrentField = CurrentField->Next;
			}

			if (bIncludeInterface)
			{
				// We shouldn't be able to get here for non-classes
				UClass* CurrentClass = (UClass*)CurrentStruct;
				TArray<UClass*> InterfaceClasses = GetAllInterfaceClasses(CurrentClass);
				++InterfaceIndex;
				if (InterfaceIndex < InterfaceClasses.Num())
				{
					UClass* InterfaceClass = InterfaceClasses[InterfaceIndex];
					CurrentField = InterfaceClass ? GetChildFieldsFromStruct<typename T::BaseFieldClass>(InterfaceClass) : nullptr;
					continue;
				}
			}

			if (bIncludeSuper)
			{
				CurrentStruct = CurrentStruct->GetInheritanceSuper();
				if (CurrentStruct)
				{
					CurrentField   = GetChildFieldsFromStruct<typename T::BaseFieldClass>(CurrentStruct);
					InterfaceIndex = -1;
					continue;
				}
			}

			break;
		}

		Struct = CurrentStruct;
		Field  = CurrentField;
	}

	static TArray<UClass*> GetAllInterfaceClasses(const UClass* InClass)
	{
		TArray<UClass*> InterfaceClasses;

		if (InClass != nullptr)
		{
			for (const FImplementedInterface& ImplementedInterface : InClass->Interfaces)
			{
				if (ImplementedInterface.Class != nullptr)
				{
					UClass* CurrentClass = ImplementedInterface.Class;

					while (CurrentClass &&
						CurrentClass->HasAnyClassFlags(CLASS_Interface) &&
						!InterfaceClasses.Contains(CurrentClass))
					{
						InterfaceClasses.Add(CurrentClass);

						CurrentClass = CurrentClass->GetSuperClass();
					}
				}
			}
		}

		return InterfaceClasses;
	}
};
