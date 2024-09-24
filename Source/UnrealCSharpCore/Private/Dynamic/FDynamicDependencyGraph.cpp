#include "Dynamic/FDynamicDependencyGraph.h"
#include "CoreMacro/Macro.h"

FDynamicDependencyGraph& FDynamicDependencyGraph::Get()
{
	static FDynamicDependencyGraph Instance;

	return Instance;
}

void FDynamicDependencyGraph::AddNode(const FNode& InNode)
{
	Nodes.Emplace(InNode.Name, InNode);
}

bool FDynamicDependencyGraph::IsCompleted(const FString& InName)
{
	static auto A = ACTOR_PREFIX;

	static auto U = OBJECT_PREFIX;

	static auto F = STRUCT_PREFIX;

	if (auto FoundNode = Nodes.Find(InName))
	{
		return FoundNode->IsCompleted();
	}
	else if (FoundNode = Nodes.Find(A + InName); FoundNode != nullptr)
	{
		return FoundNode->IsCompleted();
	}
	else if (FoundNode = Nodes.Find(U + InName); FoundNode != nullptr)
	{
		return FoundNode->IsCompleted();
	}
	else if (FoundNode = Nodes.Find(F + InName); FoundNode != nullptr)
	{
		return FoundNode->IsCompleted();
	}

	return true;
}

void FDynamicDependencyGraph::Completed(const FString& InName)
{
	if (const auto FoundNode = Nodes.Find(InName))
	{
		FoundNode->Completed();
	}
}

void FDynamicDependencyGraph::OnCompleted(const FString& InName, const TFunction<void()>& InOnCompleted)
{
	static auto A = ACTOR_PREFIX;

	static auto U = OBJECT_PREFIX;

	static auto F = STRUCT_PREFIX;

	if (auto FoundNode = Nodes.Find(InName))
	{
		FoundNode->OnCompleted.Add(InOnCompleted);
	}
	else if (FoundNode = Nodes.Find(A + InName); FoundNode != nullptr)
	{
		FoundNode->OnCompleted.Add(InOnCompleted);
	}
	else if (FoundNode = Nodes.Find(U + InName); FoundNode != nullptr)
	{
		FoundNode->OnCompleted.Add(InOnCompleted);
	}
	else if (FoundNode = Nodes.Find(F + InName); FoundNode != nullptr)
	{
		FoundNode->OnCompleted.Add(InOnCompleted);
	}
}

void FDynamicDependencyGraph::Generator()
{
	for (auto& [Name, PLACEHOLDER] : Nodes)
	{
		if (Nodes[Name].IsCompleted())
		{
			// @TODO
		}
		else
		{
			TArray<FString> NodeStack{Name};

			TQueue<FString> NodeQueue;

			TSet<FString> NodeSet;

			while (!NodeStack.IsEmpty())
			{
				if (const auto& Node = NodeStack.Pop();
					NodeSet.Contains(Node))
				{
					// @TODO
				}
				else
				{
					auto bIsCompleted = true;

					for (const auto& [Dependency, bIsSoftReference] : Nodes[Node].Dependencies)
					{
						if (Nodes[Dependency].IsPending())
						{
							if (!bIsSoftReference)
							{
								bIsCompleted = false;
							}
						}
						else if (Nodes[Dependency].IsInitial())
						{
							if (!bIsSoftReference)
							{
								Nodes[Dependency].Pending();

								NodeStack.Push(Dependency);

								bIsCompleted = false;
							}
						}
					}

					if (bIsCompleted)
					{
						Nodes[Node].Generator();
					}
					else
					{
						Nodes[Node].Pending();

						NodeQueue.Enqueue(Node);

						NodeSet.Add(Node);
					}
				}
			}

			FString OutNode;

			while (NodeQueue.Dequeue(OutNode))
			{
				auto bIsPending = false;

				auto bIsCompleted = true;

				for (const auto& [Dependency, bIsSoftReference] : Nodes[OutNode].Dependencies)
				{
					if (!bIsSoftReference)
					{
						if (Nodes[Dependency].IsInitial())
						{
							bIsCompleted = false;

							break;
						}

						if (Nodes[Dependency].IsPending())
						{
							bIsPending = true;

							break;
						}
					}
				}

				if (bIsPending)
				{
					NodeQueue.Enqueue(OutNode);

					continue;
				}

				if (bIsCompleted)
				{
					Nodes[OutNode].Generator();
				}
				else
				{
					// @TODO
				}
			}
		}
	}
}
