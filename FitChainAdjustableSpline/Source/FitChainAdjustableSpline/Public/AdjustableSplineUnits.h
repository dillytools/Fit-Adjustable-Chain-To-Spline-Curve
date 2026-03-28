// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once
#include "ControlRigSplineTypes.h"
#include "Units/RigUnit.h"
#include "Units/Highlevel/RigUnit_HighlevelBase.h"
#include "Units/Highlevel/Hierarchy/RigUnit_FitChainToCurve.h"
#include "AdjustableSplineUnits.generated.h"

/**
 * Fits a given chain to a spline curve. Chain will update to reflect pose changes that are applied additively at runtime.
 * Additionally provides rotational control matching the features of the Distribute Rotation node.
 */
USTRUCT(meta=(DisplayName="Fit Adjustable Chain on Spline Curve", Category="Splines", Keywords="Fit,Resample,Spline"))
struct FRigUnit_FitAdjustableChainToSplineCurve : public FRigUnit_HighlevelBaseMutable
{
	GENERATED_BODY()

	FRigUnit_FitAdjustableChainToSplineCurve()
	{
		Alignment = EControlRigCurveAlignment::Stretched;
		Minimum = 0.f;
		Maximum = 1.f;
		SamplingPrecision = 12;
		PrimaryAxis = FVector(1.f, 0.f, 0.f);
		SecondaryAxis = FVector(0.f, 0.f, 0.f);
		PoleVectorPosition = FVector::ZeroVector;
		RotationEaseType = ERigVMAnimEasingType::Linear;
		Weight = 1.f;
		bUpdateChainLength = true;
		bPropagateToChildren = true;
		DebugSettings = FRigUnit_FitChainToCurve_DebugSettings();
	}

	RIGVM_METHOD()
	virtual void Execute() override;

	/** 
	 * The items to align
	 */
	UPROPERTY(meta = (Input))
	TArray<FRigElementKey> Items;

	/** 
	 * The curve to align to
	 */
	UPROPERTY(meta = (Input))
	FControlRigSpline Spline;

	/** 
	 * Specifies how to align the chain on the curve
	 */
	UPROPERTY(meta = (Input, Constant))
	EControlRigCurveAlignment Alignment;

	/** 
	 * The minimum U value to use on the curve
	 */
	UPROPERTY(meta = (Input, Constant))
	float Minimum;

	/** 
	 * The maximum U value to use on the curve
	 */
	UPROPERTY(meta = (Input, Constant))
	float Maximum;

	/**
	 * The number of samples to use on the curve. Clamped at 64.
	 */
	UPROPERTY(meta = (Input, Constant))
	int32 SamplingPrecision;

	/**
	 * The major axis being aligned - along the bone
	 */
	UPROPERTY(meta = (Input))
	FVector PrimaryAxis;

	/**
	 * The minor axis being aligned - towards the pole vector.
	 * You can use (0.0, 0.0, 0.0) to disable it.
	 */
	UPROPERTY(meta = (Input))
	FVector SecondaryAxis;

	/**
	 * The the position of the pole vector used for aligning the secondary axis.
	 * Only has an effect if the secondary axis is set.
	 */
	UPROPERTY(meta = (Input))
	FVector PoleVectorPosition;

	/** 
	 * The list of rotations to be applied along the curve
	 */
	UPROPERTY(meta = (Input))
	TArray<FRigUnit_FitChainToCurve_Rotation> Rotations;

	/**
	 * The easing to use between to rotations.
	 */
	UPROPERTY(meta = (Input, Constant))
	ERigVMAnimEasingType RotationEaseType;

	/**
	 * The weight of the solver - how much the rotation should be applied
	 */
	UPROPERTY(meta = (Input))
	float Weight;

	/**
	 * If set to true the length of the bone chain will update continuously,
	 * allowing for bone transform changes to be made at runtime while
	 * maintaining proper spline behavior.
	 */
	UPROPERTY(meta = (Input, Constant))
	bool bUpdateChainLength;

	/**
	 * If set to true all of the global transforms of the children
	 * of this bone will be recalculated based on their local transforms.
	 * Note: This is computationally more expensive than turning it off.
	 */
	UPROPERTY(meta = (Input, Constant))
	bool bPropagateToChildren;

	UPROPERTY(meta = (Input, DetailsOnly))
	FRigUnit_FitChainToCurve_DebugSettings DebugSettings;

	UPROPERTY(transient)
	FRigUnit_FitChainToCurve_WorkData WorkData;
};