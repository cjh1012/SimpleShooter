// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
    //	AIMODULE_API virtual void SetFocus(AActor* NewFocus, EAIFocusPriority::Type InPriority = EAIFocusPriority::Gameplay);

    if (AIBehavior != nullptr) {
        RunBehaviorTree(AIBehavior);
    }

}
// Called every frame
void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
/*
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);     //플레이어 폰을 가리키는 포인터를 반환  GetPlayerPawn(WorldContextObject, PlayerIndex)
    
    if(LineOfSightTo(PlayerPawn)){
        SetFocus(PlayerPawn);
        MoveToActor(PlayerPawn, AcceptanceRadius);
    }
    else {
        ClearFocus(EAIFocusPriority::Gameplay);
        StopMovement();
    }
*/



}

