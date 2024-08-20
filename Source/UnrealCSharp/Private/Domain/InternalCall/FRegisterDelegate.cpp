#include "Registry/FCSharpBind.h"
#include "Binding/Class/FClassBuilder.h"
#include "Environment/FCSharpEnvironment.h"
#include "Reflection/Delegate/FDelegateHelper.h"
#include "CoreMacro/NamespaceMacro.h"
#include "Async/Async.h"

#define EXECUTE_IMPLEMENTATION(PropertyType, Type) \
		static Type PropertyType##Execute1Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle) \
		{ \
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(InGarbageCollectionHandle)) \
			{ \
				return DelegateHelper->Execute1<Type>(); \
			} \
			return {}; \
		} \
		static Type PropertyType##Execute3Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle, uint8* InBuffer) \
		{ \
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(InGarbageCollectionHandle)) \
			{ \
				return DelegateHelper->Execute3<Type>(InBuffer); \
			} \
			return {}; \
		} \
		static Type PropertyType##Execute7Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle, MonoObject** OutValue, uint8* InBuffer) \
		{ \
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(InGarbageCollectionHandle)) \
			{ \
				return DelegateHelper->Execute7<Type>(OutValue, InBuffer); \
			} \
			return {}; \
		}

namespace
{
	struct FRegisterDelegate
	{
		static void RegisterImplementation(MonoObject* InMonoObject)
		{
			FCSharpBind::Bind<FDelegateHelper>(InMonoObject);
		}

		static void UnRegisterImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			AsyncTask(ENamedThreads::GameThread, [InGarbageCollectionHandle]
			{
				(void)FCSharpEnvironment::GetEnvironment().RemoveDelegateReference<FDelegateHelper>(
					InGarbageCollectionHandle);
			});
		}

		static void BindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                               const FGarbageCollectionHandle InObject, MonoObject* InDelegate)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				if (const auto FoundObject = FCSharpEnvironment::GetEnvironment().GetObject(InObject))
				{
					DelegateHelper->Bind(FoundObject, FCSharpEnvironment::GetEnvironment().GetDomain()->
					                     Delegate_Get_Method(InDelegate));
				}
			}
		}

		static bool IsBoundImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				return DelegateHelper->IsBound();
			}

			return false;
		}

		static void UnBindImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->UnBind();
			}
		}

		static void ClearImplementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Clear();
			}
		}

		EXECUTE_IMPLEMENTATION(Byte, uint8)

		EXECUTE_IMPLEMENTATION(UInt16, uint16)

		EXECUTE_IMPLEMENTATION(UInt32, uint32)

		EXECUTE_IMPLEMENTATION(UInt64, uint64)

		EXECUTE_IMPLEMENTATION(SByte, int8)

		EXECUTE_IMPLEMENTATION(Int16, int16)

		EXECUTE_IMPLEMENTATION(Int32, int)

		EXECUTE_IMPLEMENTATION(Int64, int64)

		EXECUTE_IMPLEMENTATION(Boolean, bool)

		EXECUTE_IMPLEMENTATION(Single, float)

		static void GenericExecute0Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				return DelegateHelper->Execute0<MonoObject*>();
			}
		}

		static void GenericExecute2Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                          uint8* InBuffer)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute2<MonoObject*>(InBuffer);
			}
		}

		static void GenericExecute4Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                          MonoObject** OutValue)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute4<MonoObject*>(OutValue);
			}
		}

		static void GenericExecute6Implementation(const FGarbageCollectionHandle InGarbageCollectionHandle,
		                                          MonoObject** OutValue, uint8* InBuffer)
		{
			if (const auto DelegateHelper = FCSharpEnvironment::GetEnvironment().GetDelegate<FDelegateHelper>(
				InGarbageCollectionHandle))
			{
				DelegateHelper->Execute6<MonoObject*>(OutValue, InBuffer);
			}
		}

		EXECUTE_IMPLEMENTATION(Generic, MonoObject*)

		EXECUTE_IMPLEMENTATION(Double, double)

		FRegisterDelegate()
		{
			FClassBuilder(TEXT("FDelegate"), NAMESPACE_LIBRARY, true)
				.Function("Register", RegisterImplementation)
				.Function("UnRegister", UnRegisterImplementation)
				.Function("Bind", BindImplementation)
				.Function("IsBound", IsBoundImplementation)
				.Function("UnBind", UnBindImplementation)
				.Function("Clear", ClearImplementation)
				.Function("ByteExecute1", ByteExecute1Implementation)
				.Function("ByteExecute3", ByteExecute3Implementation)
				.Function("ByteExecute7", ByteExecute7Implementation)
				.Function("UInt16Execute1", UInt16Execute1Implementation)
				.Function("UInt16Execute3", UInt16Execute3Implementation)
				.Function("UInt16Execute7", UInt16Execute7Implementation)
				.Function("UInt32Execute1", UInt32Execute1Implementation)
				.Function("UInt32Execute3", UInt32Execute3Implementation)
				.Function("UInt32Execute7", UInt32Execute7Implementation)
				.Function("UInt64Execute1", UInt64Execute1Implementation)
				.Function("UInt64Execute3", UInt64Execute3Implementation)
				.Function("UInt64Execute7", UInt64Execute7Implementation)
				.Function("SByteExecute1", SByteExecute1Implementation)
				.Function("SByteExecute3", SByteExecute3Implementation)
				.Function("SByteExecute7", SByteExecute7Implementation)
				.Function("Int16Execute1", Int16Execute1Implementation)
				.Function("Int16Execute3", Int16Execute3Implementation)
				.Function("Int16Execute7", Int16Execute7Implementation)
				.Function("Int32Execute1", Int32Execute1Implementation)
				.Function("Int32Execute3", Int32Execute3Implementation)
				.Function("Int32Execute7", Int32Execute7Implementation)
				.Function("Int64Execute1", Int64Execute1Implementation)
				.Function("Int64Execute3", Int64Execute3Implementation)
				.Function("Int64Execute7", Int64Execute7Implementation)
				.Function("BooleanExecute1", BooleanExecute1Implementation)
				.Function("BooleanExecute3", BooleanExecute3Implementation)
				.Function("BooleanExecute7", BooleanExecute7Implementation)
				.Function("SingleExecute1", SingleExecute1Implementation)
				.Function("SingleExecute3", SingleExecute3Implementation)
				.Function("SingleExecute7", SingleExecute7Implementation)
				.Function("GenericExecute0", GenericExecute0Implementation)
				.Function("GenericExecute1", GenericExecute1Implementation)
				.Function("GenericExecute2", GenericExecute2Implementation)
				.Function("GenericExecute3", GenericExecute3Implementation)
				.Function("GenericExecute4", GenericExecute4Implementation)
				.Function("GenericExecute6", GenericExecute6Implementation)
				.Function("GenericExecute7", GenericExecute7Implementation)
				.Function("DoubleExecute1", DoubleExecute1Implementation)
				.Function("DoubleExecute3", DoubleExecute3Implementation)
				.Function("DoubleExecute7", DoubleExecute7Implementation);
		}
	};

	FRegisterDelegate RegisterDelegate;
}
