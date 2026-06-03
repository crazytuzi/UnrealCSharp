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
				if (const auto Element = NodeStack.Pop();
					NodeSet.Contains(Element))
				{
					// @TODO
				}
				else
				{
					if (NodeArray[NodeMap[Element]].IsCompleted())
					{
						continue;
					}

					auto bIsCompleted = true;

					for (const auto& [Dependency, bIsSoftReference] : NodeArray[NodeMap[Element]].Dependencies)
					{
						if (bIsSoftReference)
						{
							continue;
						}

						const auto Type = FDependency::GetType(Dependency);

						if (!NodeMap.Contains(Type))
						{
							continue;
						}

						if (NodeArray[NodeMap[Type]].IsPending())
						{
							bIsCompleted = false;
						}
						else if (NodeArray[NodeMap[Type]].IsInitial())
						{
							NodeStack.Push(Type);

							bIsCompleted = false;
						}
					}

					if (bIsCompleted)
					{
						NodeArray[NodeMap[Element]].Generator();

						NodeArray[NodeMap[Element]].Completed();
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
				if (NodeArray[NodeMap[OutNode]].IsCompleted())
				{
					continue;
				}

				auto bIsPending = false;

				auto bIsCompleted = true;

				for (const auto& [Dependency, bIsSoftReference] : NodeArray[NodeMap[OutNode]].Dependencies)
				{
					if (!bIsSoftReference)
					{
						const auto Type = FDependency::GetType(Dependency);

						if (!NodeMap.Contains(Type))
						{
							continue;
						}

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

					NodeArray[NodeMap[OutNode]].Completed();
				}
				else
				{
					// @TODO
				}
			}
		}
	}
}
