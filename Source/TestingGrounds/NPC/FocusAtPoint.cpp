// Fill out your copyright notice in the Description page of Project Settings.

#include "FocusAtPoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"



EBTNodeResult::Type UFocusAtPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto BlackboardComponent = OwnerComp.GetBlackboardComponent();
	BlackboardComponent->SetValueAsObject(FocalPointKey.SelectedKeyName, UGameplayStatics::GetPlayerPawn(this, 0));
	auto FocalPoint = Cast<AActor>(BlackboardComponent->GetValueAsObject(FocalPointKey.SelectedKeyName));
	OwnerComp.GetAIOwner()->SetFocus(FocalPoint);

	return EBTNodeResult::Succeeded;
}