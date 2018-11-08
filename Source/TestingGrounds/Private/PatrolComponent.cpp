// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/PatrolComponent.h"

TArray<AActor*> UPatrolComponent::GetPatrolPoints()
{
	return PatrolPoints;
}

