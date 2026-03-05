#include "Dynamic/FDynamicDependencyGraph.h"
#include "CoreMacro/Macro.h"

FDynamicDependencyGraph& FDynamicDependencyGraph::Get()
{
	static FDynamicDependencyGraph Instance;

	return Instance;
}

void FDynamicDependencyGraph::AddNode(const FNode& InNode)
{
	NodeArray.Emplace(InNode);

	NodeMap.Emplace(InNode.Name, NodeArray.Num() - 1);
}

bool FDynamicDependencyGraph::IsCompleted(const FString& InName)
{
	static auto A = ACTOR_PREFIX;

	static auto U = OBJECT_PREFIX;

	static auto F = STRUCT_PREFIX;

	if (auto FoundNode = NodeMap.Find(InName))
	{
		return NodeArray[*FoundNode].IsCompleted();
	}
	else if (FoundNode = NodeMap.Find(A + InName); FoundNode != nullptr)
	{
		return NodeArray[*FoundNode].IsCompleted();
	}
	else if (FoundNode = NodeMap.Find(U + InName); FoundNode != nullptr)
	{
		return NodeArray[*FoundNode].IsCompleted();
	}
	else if (FoundNode = NodeMap.Find(F + InName); FoundNode != nullptr)
	{
		return NodeArray[*FoundNode].IsCompleted();
	}

	return true;
}

void FDynamicDependencyGraph::Completed(const FString& InName)
{
	if (const auto FoundNode = NodeMap.Find(InName))
	{
		NodeArray[*FoundNode].Completed();
	}
}

void FDynamicDependencyGraph::OnCompleted(const FString& InName, const TFunction<void()>& InOnCompleted)
{
	static auto A = ACTOR_PREFIX;

	static auto U = OBJECT_PREFIX;

	static auto F = STRUCT_PREFIX;

	if (auto FoundNode = NodeMap.Find(InName))
	{
		NodeArray[*FoundNode].OnCompleted.Add(InOnCompleted);
	}
	else if (FoundNode = NodeMap.Find(A + InName); FoundNode != nullptr)
	{
		NodeArray[*FoundNode].OnCompleted.Add(InOnCompleted);
	}
	else if (FoundNode = NodeMap.Find(U + InName); FoundNode != nullptr)
	{
		NodeArray[*FoundNode].OnCompleted.Add(InOnCompleted);
	}
	else if (FoundNode = NodeMap.Find(F + InName); FoundNode != nullptr)
	{
		NodeArray[*FoundNode].OnCompleted.Add(InOnCompleted);
	}
}

void FDynamicDependencyGraph::Generator()
{
	for (const auto& Node : NodeArray)
	{
		if (Node.IsCompleted())
		{
			// @TODO
		}
		else
		{
			TArray<FString> NodeStack{Node.Name};

			TQueue<FString> NodeQueue;

			TSet<FString> NodeSet;

			while (!NodeStack.IsEmpty())
			{
				if (const auto& Element = NodeStack.Pop();
					NodeSet.Contains(Element))
				{
					// @TODO
				}
				else
				{
					auto bIsCompleted = true;

					for (const auto& [Dependency, bIsSoftReference] : NodeArray[NodeMap[Element]].Dependencies)
					{
						if (NodeArray[NodeMap[Element]].IsPending())
						{
							if (!bIsSoftReference)
							{
								bIsCompleted = false;
							}
						}
						else if (NodeArray[NodeMap[Element]].IsInitial())
						{
							if (!bIsSoftReference)
							{
								NodeArray[NodeMap[Element]].Pending();

								NodeStack.Push(Dependency);

								bIsCompleted = false;
							}
						}
					}

					if (bIsCompleted)
					{
						NodeArray[NodeMap[Element]].Generator();
					}
					else
					{
						NodeArray[NodeMap[Element]].Pending();

						NodeQueue.Enqueue(Element);

						NodeSet.Add(Element);
					}
				}
			}

			FString OutNode;

			while (NodeQueue.Dequeue(OutNode))
			{
				auto bIsPending = false;

				auto bIsCompleted = true;

				for (const auto& [Dependency, bIsSoftReference] : NodeArray[NodeMap[OutNode]].Dependencies)
				{
					if (!bIsSoftReference)
					{
						auto Type = FDependency::GetType(Dependency);

						if (NodeArray[NodeMap[Type]].IsInitial())
						{
							bIsCompleted = false;

							break;
						}

						if (NodeArray[NodeMap[Type]].IsPending())
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
					NodeArray[NodeMap[OutNode]].Generator();
				}
				else
				{
					// @TODO
				}
			}
		}
	}
}
