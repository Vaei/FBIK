// Copyright (c) Jared Taylor

#include "AnimGraphNode_FBIK.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"

/////////////////////////////////////////////////////
// UAnimGraphNode_FBIK 

#define LOCTEXT_NAMESPACE "AnimGraphNode_FBIK"

UAnimGraphNode_FBIK::UAnimGraphNode_FBIK(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

FText UAnimGraphNode_FBIK::GetControllerDescription() const
{
	return LOCTEXT("FBIK", "Full-Body IK");
}

FText UAnimGraphNode_FBIK::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return GetControllerDescription();
}

FLinearColor UAnimGraphNode_FBIK::GetNodeTitleColor() const
{
	return FLinearColor(0.1f, 0.3f, 1.f);
}

#undef LOCTEXT_NAMESPACE
