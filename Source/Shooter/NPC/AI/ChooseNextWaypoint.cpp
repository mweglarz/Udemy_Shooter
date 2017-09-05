// Fill out your copyright notice in the Description page of Project Settings.


#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRouteComponent.h"


EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) {

	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	int32 Index = BlackboardComponent->GetValueAsInt(IndexKey.SelectedKeyName);

	UPatrolRouteComponent* RouteComponent = OwnerComp.GetAIOwner()->GetPawn()->FindComponentByClass<UPatrolRouteComponent>();

	if (!ensure(RouteComponent)) return EBTNodeResult::Failed;

	TArray<AActor*> Waypoints = RouteComponent->GetPatrolPoints();
	if (!(Waypoints.Num() > 0 && Index < Waypoints.Num())) return EBTNodeResult::Failed;

	BlackboardComponent->SetValueAsObject(WaypointKey.SelectedKeyName, Waypoints[Index]);

	int32 NewIndex = ++Index % Waypoints.Num();
	BlackboardComponent->SetValueAsInt(IndexKey.SelectedKeyName, NewIndex);

	return EBTNodeResult::Succeeded;
}
