#pragma once

class FDynamicDependencyGraph
{
public:
	struct FDependency
	{
		FString Name;

		bool bIsSoftReference;
	};

	enum class EState
	{
		Initial,
		Pending,
		Completed
	};

	struct FNode
	{
		FNode(const FString& InName, const TFunction<void()>& InGeneratorImplementation):
			Name(InName),
			State(EState::Initial),
			GeneratorImplementation(InGeneratorImplementation)
		{
		}

		bool IsInitial() const
		{
			return State == EState::Initial;
		}

		bool IsPending() const
		{
			return State == EState::Pending;
		}

		bool IsCompleted() const
		{
			return State == EState::Completed;
		}

		void Pending()
		{
			State = EState::Pending;
		}

		void Completed()
		{
			State = EState::Completed;
		}

		void Dependency(const FDependency& InDependency)
		{
			Dependencies.Add(InDependency);
		}

		void Generator()
		{
			GeneratorImplementation();

			for (const auto& Item : OnCompleted)
			{
				Item();
			}
		}

		FString Name;

		EState State;

		TArray<FDependency> Dependencies;

		TFunction<void()> GeneratorImplementation;

		TArray<TFunction<void()>> OnCompleted;
	};

public:
	static FDynamicDependencyGraph& Get();

public:
	void AddNode(const FNode& InNode);

	bool IsCompleted(const FString& InName);

	void Completed(const FString& InName);

	void OnCompleted(const FString& InName, const TFunction<void()>& InOnCompleted);

	void Generator();

private:
	TSortedMap<FString, FNode> Nodes;
};
