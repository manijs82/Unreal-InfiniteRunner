// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Probability.generated.h"

class ASpawnable;

/**
 * 
 */
UCLASS()
class SMALLGAME_API UProbability : public UObject
{
	GENERATED_BODY()

public:
	template<typename T>
	static T GetWeightedRandomElement(TArray<T> array, TArray<float> probabilities);
};

template <typename T>
T UProbability::GetWeightedRandomElement(TArray<T> array, TArray<float> probabilities)
{
	if(probabilities.Num() != array.Num()) return array[0];

	float weight = FMath::RandRange(0.f, 1.f);

	float currentProbability = probabilities[0];
	for (int i = 0; i < probabilities.Num(); i++)
	{
		if(i == probabilities.Num() - 1) return array[i];
		if(weight <= currentProbability)
			return array[i];
		
		currentProbability += probabilities[i + 1];
	}
	
	return array[0];
}
