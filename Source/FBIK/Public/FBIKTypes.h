// Copyright (c) Jared Taylor

#pragma once

#include "CoreMinimal.h"
#include "Animation/BoneReference.h"
#include "FBIKTypes.generated.h"

struct FPBIKBoneSetting;
struct FPBIKEffector;

/** Target effectors for solving. */
USTRUCT(BlueprintType)
struct FFBIKEffectors
{
	GENERATED_BODY()

	/** Target effectors for solving. */
	UPROPERTY(EditAnywhere, Category=Solver)
	TArray<FPBIKEffector> Effectors;
};

/** Settings for each bone. */
USTRUCT(BlueprintType)
struct FFBIKBoneSettings
{
	GENERATED_BODY()

	/** Settings for each bone. */
	UPROPERTY(EditAnywhere, Category=Solver)
	TArray<FPBIKBoneSetting> BoneSettings;
};

/** Bones that should not move. */
USTRUCT(BlueprintType)
struct FFBIKExcludedBones
{
	GENERATED_BODY()

	/** Bones that should not move. */
	UPROPERTY(EditAnywhere, Category=Solver)
	TArray<FBoneReference> ExcludedBones;
};