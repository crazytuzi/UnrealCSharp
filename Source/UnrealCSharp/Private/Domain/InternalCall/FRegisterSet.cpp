#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Container/FSetHelper.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Bridge/FTypeBridge.h"
#include "Async/Async.h"

struct FRegisterSet
{
	static void RegisterImplementation(MonoObject* InMonoObject)
	{
		FCSharpBind::Bind<FSetHelper>(InMonoObject, FTypeBridge::GetGenericArgument(InMonoObject));
	}

	static void UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
		{
			(void)FCSharpEnvironment::GetEnvironment().RemoveContainerReference<FSetHelper>(InGarbageCollectionHandle);
		});
	}

	static void EmptyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                const int32 InExpectedNumElements)
	{
		if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
			InGarbageCollectionHandle))
		{
			SetHelper->Empty(InExpectedNumElements);
		}
	}

	static int32 NumImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
			InGarbageCollectionHandle))
		{
			return SetHelper->Num();
		}

		return 0;
	}

	static bool IsEmptyImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
			InGarbageCollectionHandle))
		{
			return SetHelper->IsEmpty();
		}

		return false;
	}

	static int32 GetMaxIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
	{
		if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
			InGarbageCollectionHandle))
		{
			return SetHelper->GetMaxIndex();
		}

		return 0;
	}

	static void AddImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                              MonoObject* InValue)
	{
		if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
			InGarbageCollectionHandle))
		{
			if (SetHelper->GetElementPropertyDescriptor()->IsPrimitiveProperty())
			{
				SetHelper->Add(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
			}
			else
			{
				SetHelper->Add(InValue);
			}
		}
	}

	static int32 RemoveImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                  MonoObject* InValue)
	{
		if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
			InGarbageCollectionHandle))
		{
			if (SetHelper->GetElementPropertyDescriptor()->IsPrimitiveProperty())
			{
				return SetHelper->Remove(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
			}
			else
			{
				return SetHelper->Remove(InValue);
			}
		}

		return 0;
	}

	static bool ContainsImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                   MonoObject* InValue)
	{
		if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
			InGarbageCollectionHandle))
		{
			if (SetHelper->GetElementPropertyDescriptor()->IsPrimitiveProperty())
			{
				return SetHelper->Contains(FCSharpEnvironment::GetEnvironment().GetDomain()->Object_Unbox(InValue));
			}
			else
			{
				return SetHelper->Contains(InValue);
			}
		}

		return false;
	}

	static bool IsValidIndexImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                       const int32 InIndex)
	{
		if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
			InGarbageCollectionHandle))
		{
			return SetHelper->IsValidIndex(InIndex);
		}

		return false;
	}

	static MonoObject* GetEnumeratorImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
	                                               const int32 InIndex)
	{
		MonoObject* ReturnValue{};

		if (const auto SetHelper = FCSharpEnvironment::GetEnvironment().GetContainer<FSetHelper>(
			InGarbageCollectionHandle))
		{
			const auto Value = SetHelper->GetEnumerator(InIndex);

			SetHelper->GetElementPropertyDescriptor()->Get(Value, reinterpret_cast<void**>(&ReturnValue));
		}

		return ReturnValue;
	}

	FRegisterSet()
	{
		FClassBuilder(TEXT("TSet"), NAMESPACE_LIBRARY)
			.Function("Register", RegisterImplementation)
			.Function("UnRegister", UnRegisterImplementation)
			.Function("Empty", EmptyImplementation)
			.Function("Num", NumImplementation)
			.Function("IsEmpty", IsEmptyImplementation)
			.Function("GetMaxIndex", GetMaxIndexImplementation)
			.Function("Add", AddImplementation)
			.Function("Remove", RemoveImplementation)
			.Function("Contains", ContainsImplementation)
			.Function("IsValidIndex", IsValidIndexImplementation)
			.Function("GetEnumerator", GetEnumeratorImplementation)
			.Register();
	}
};

static FRegisterSet RegisterSet;
