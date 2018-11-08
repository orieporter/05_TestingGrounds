// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "Public/PatrolComponent.h"




EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get Patrol Points
	auto BlackboardComp = OwnerComp.GetBlackboardComponent();
	auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
	auto PatrollingPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto PatrolComponent = PatrollingPawn->FindComponentByClass<UPatrolComponent>();
	auto PatrolPoints = PatrolComponent->GetPatrolPoints();

	if (!ensure(PatrolComponent)) { return EBTNodeResult::Failed; }
	// Warn if no patrol points
	if (PatrolPoints.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("A patrolling pawn has no patrol points."))
			return EBTNodeResult::Failed;
	}

	// Set Next Patrol Point
	BlackboardComp->SetValueAsObject(NextWaypointKey.SelectedKeyName, PatrolPoints[Index]);
	
	// Cycle Index
	Index++;
	Index = Index % PatrolPoints.Num();
	BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, Index);

	return EBTNodeResult::Succeeded;
}
