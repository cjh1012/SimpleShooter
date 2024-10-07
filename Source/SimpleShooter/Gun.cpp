// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket")); 	//부착할 위치
	
	APawn* OwnerPawn = Cast<APawn>(GetOwner());	
	if(OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn-> GetController();
	if(OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;
	OwnerController -> GetPlayerViewPoint(Location, Rotation); 

	FVector End= Location + Rotation.Vector() * MaxRange; //Vector.Rotation() => Rotation의 방향 벡터를 부여  끝점을 계산하는 방법

	//DrawDebugCamera(GetWorld(), Location, Rotation, 90, 2, FColor::Red, true);	//카메라 위치 확인용
	
	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1);
	if(bSuccess){
		
		FVector ShotDirection =	-Rotation.Vector();		//총격을 입었을 때 총격이 가해지는 방향
		DrawDebugPoint(GetWorld(), Hit.Location, 20, FColor::Red, true);
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr) {
			//ToDo: DamageEvent
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);	 //nullptr인 이유 = 화상대미지와 같은 피격 외 대미지가 필요할 시 새로운 대미지타입을 만들 때 사용됨. 여기서는 피격대미지만 존재하므로 사용X
			HitActor -> TakeDamage(Damage, DamageEvent, OwnerController, this);	//피격된 액터 체력 감소(대미지량, 대미지이벤트, 피격유발컨트롤러, 데미지원인)
		}
		
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

