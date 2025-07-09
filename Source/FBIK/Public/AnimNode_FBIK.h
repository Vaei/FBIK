// Copyright (c) Jared Taylor

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "BoneIndices.h"
#include "BoneContainer.h"
#include "BonePose.h"
#include "FBIKTypes.h"
#include "BoneControllers/AnimNode_SkeletalControlBase.h"
#include "PBIK_Shared.h"
#include "RigUnit_PBIK.h"
#include "Core/PBIKSolver.h"
#include "Misc/HashBuilder.h"
#include "AnimNode_FBIK.generated.h"

/*
 * Based on a Position Based solver at core, this node can solve multi chains within a root using multi effectors
 */
USTRUCT(BlueprintInternalUseOnly)
struct FBIK_API FAnimNode_FBIK : public FAnimNode_SkeletalControlBase
{
	GENERATED_USTRUCT_BODY()

	/** The root of the solver. Bones above this will be ignored. */
	UPROPERTY(EditAnywhere, Category=Solver, meta=(PinHiddenByDefault))
	FBoneReference RootBone;

	/** Target effectors for solving. */
	UPROPERTY(EditAnywhere, Category=Solver, meta=(PinHiddenByDefault))
	FFBIKEffectors Effectors;

	/** Settings for each bone. */
	UPROPERTY(EditAnywhere, Category=Solver, meta=(PinHiddenByDefault))
	FFBIKBoneSettings BoneSettings;

	/** Bones that should not move. */
	UPROPERTY(EditAnywhere, Category=Solver, meta=(PinHiddenByDefault))
	FFBIKExcludedBones ExcludedBones;

	/** Global solver settings. */
	UPROPERTY(EditAnywhere, Category=Solver, meta=(PinHiddenByDefault))
	FPBIKSolverSettings Settings;

	FAnimNode_FBIK();

	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;
	virtual void EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms) override;
	virtual bool IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones) override;
	virtual void InitializeBoneReferences(const FBoneContainer& RequiredBones) override;

private:
	FPBIKWorkData WorkData;
	TArray<FCompactPoseBoneIndex> SolverBoneToPoseIndex;
	TArray<int32> EffectorSolverIndices;

	FHashBuilder BuildHash(const FBoneContainer& BoneContainer) const;
	void InitializeSolverIfNeeded(const FBoneContainer& BoneContainer, FCSPose<FCompactPose>& CSPose);
	int32 GetParentSolverIndex(const FCompactPoseBoneIndex& Index, const TArray<FCompactPoseBoneIndex>& PoseBoneIndices, const FBoneContainer& BoneContainer) const;
};
