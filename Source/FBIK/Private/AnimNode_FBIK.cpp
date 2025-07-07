// Copyright (c) Jared Taylor

#include "AnimNode_FBIK.h"
#include "AnimationRuntime.h"
#include "Animation/AnimInstanceProxy.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AnimNode_FBIK)

FAnimNode_FBIK::FAnimNode_FBIK() {}

void FAnimNode_FBIK::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	Super::Initialize_AnyThread(Context);
	WorkData.bNeedsInit = true;
}

bool FAnimNode_FBIK::IsValidToEvaluate(const USkeleton* Skeleton, const FBoneContainer& RequiredBones)
{
	return RootBone.IsValidToEvaluate(RequiredBones);
}

void FAnimNode_FBIK::InitializeBoneReferences(const FBoneContainer& RequiredBones)
{
	RootBone.Initialize(RequiredBones);
	for (FBoneReference& Ref : ExcludedBones) Ref.Initialize(RequiredBones);
}

FHashBuilder FAnimNode_FBIK::BuildHash() const
{
	FHashBuilder Hash;
	for (const FPBIKEffector& Eff : Effectors) Hash << Eff.Bone;
	for (const FPBIKBoneSetting& Set : BoneSettings) Hash << Set.Bone;
	return Hash;
}

int32 FAnimNode_FBIK::GetParentSolverIndex(const FCompactPoseBoneIndex& Index, const TArray<FCompactPoseBoneIndex>& PoseBoneIndices, const FBoneContainer& BoneContainer) const
{
	const FCompactPoseBoneIndex Parent = BoneContainer.GetParentBoneIndex(Index);
	if (!Parent.IsValid()) return -1;
	for (int32 i = 0; i < SolverBoneToPoseIndex.Num(); ++i)
	{
		if (SolverBoneToPoseIndex[i] == Parent) return i;
	}
	return -1;
}

void FAnimNode_FBIK::InitializeSolverIfNeeded(const FBoneContainer& BoneContainer, FCSPose<FCompactPose>& CSPose)
{
	const uint32 Hash = BuildHash().GetHash();
	WorkData.bNeedsInit |= WorkData.HashInitializedWith != Hash;
	if (!WorkData.bNeedsInit) return;

	WorkData.Solver.Reset();
	SolverBoneToPoseIndex.Reset();
	EffectorSolverIndices.Reset();

	TArray<FCompactPoseBoneIndex> BoneIndices;
	for (const FBoneIndexType& BoneIndex : BoneContainer.GetBoneIndicesArray())
	{
		FCompactPoseBoneIndex Index(BoneIndex);
		const int32 SkeletonIndex = BoneContainer.GetSkeletonIndex(Index);
		if (!BoneContainer.GetReferenceSkeleton().IsValidIndex(SkeletonIndex))
		{
			// Ignore bones that are not in the reference skeleton
			continue;
		}
		FName BoneName = BoneContainer.GetReferenceSkeleton().GetBoneName(SkeletonIndex);

		if (ExcludedBones.ContainsByPredicate([&](const FBoneReference& Ref){ return Ref.BoneName == BoneName; }))
		{
			continue;
		}
		
		const int32 ParentIdx = GetParentSolverIndex(Index, BoneIndices, BoneContainer);
		FTransform InitXf = CSPose.GetComponentSpaceTransform(Index);
		const bool bIsRoot = (BoneName == RootBone.BoneName);
		const int32 SolverIdx = WorkData.Solver.AddBone(BoneName, ParentIdx, InitXf.GetLocation(), InitXf.GetRotation(), bIsRoot);
		if (SolverBoneToPoseIndex.Num() <= SolverIdx)
		{
			SolverBoneToPoseIndex.SetNumUninitialized(SolverIdx + 1);
		}
		SolverBoneToPoseIndex[SolverIdx] = Index;
		BoneIndices.Add(Index);
	}

	for (const FPBIKEffector& Eff : Effectors)
		EffectorSolverIndices.Add(WorkData.Solver.AddEffector(Eff.Bone));

	WorkData.Solver.Initialize();
	WorkData.bNeedsInit = false;
	WorkData.HashInitializedWith = Hash;
}

void FAnimNode_FBIK::EvaluateSkeletalControl_AnyThread(FComponentSpacePoseContext& Output, TArray<FBoneTransform>& OutBoneTransforms)
{
	FCSPose<FCompactPose>& CSPose = Output.Pose;
	InitializeSolverIfNeeded(Output.AnimInstanceProxy->GetRequiredBones(), CSPose);
	if (!WorkData.Solver.IsReadyToSimulate()) return;

	for (int32 i = 0; i < SolverBoneToPoseIndex.Num(); ++i)
	{
		WorkData.Solver.SetBoneTransform(i, CSPose.GetComponentSpaceTransform(SolverBoneToPoseIndex[i]));
	}

	for (int32 BSI = 0; BSI < BoneSettings.Num(); ++BSI)
	{
		const int32 Idx = WorkData.Solver.GetBoneIndex(BoneSettings[BSI].Bone);
		if (Idx == INDEX_NONE) continue;
		if (PBIK::FBoneSettings* BSettings = WorkData.Solver.GetBoneSettings(Idx))
			BoneSettings[BSI].CopyToCoreStruct(*BSettings);
	}

	for (int32 E = 0; E < Effectors.Num(); ++E)
	{
		if (EffectorSolverIndices[E] == -1) continue;
		const FPBIKEffector& Eff = Effectors[E];
		PBIK::FEffectorSettings S;
		S.PositionAlpha = Eff.PositionAlpha;
		S.RotationAlpha = Eff.RotationAlpha;
		S.StrengthAlpha = Eff.StrengthAlpha;
		S.ChainDepth = Eff.ChainDepth;
		S.PullChainAlpha = Eff.PullChainAlpha;
		S.PinRotation = Eff.PinRotation;
		WorkData.Solver.SetEffectorGoal(EffectorSolverIndices[E], Eff.Transform.GetLocation(), Eff.Transform.GetRotation(), S);
	}

	WorkData.Solver.Solve(Settings);
	for (int32 i = 0; i < SolverBoneToPoseIndex.Num(); ++i)
	{
		FTransform NewTransform;
		WorkData.Solver.GetBoneGlobalTransform(i, NewTransform);
		OutBoneTransforms.Add(FBoneTransform(SolverBoneToPoseIndex[i], NewTransform));
	}
}
