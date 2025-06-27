#include "Dynamic/DynamicBlueprintExtension.h"
#if WITH_EDITOR
#include "KismetCompiler.h"
#endif

#if WITH_EDITOR
void UDynamicBlueprintExtension::HandleGenerateFunctionGraphs(FKismetCompilerContext* CompilerContext)
{
	CompilerContext->bIsFullCompile = false;
}
#endif
