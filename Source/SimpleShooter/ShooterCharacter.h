// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun; 		//전방선언 컴파일링 시간 단축, 에러 수정용

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)	//BlueprintPure  blueprintCallable을 오버라이드 하는 함수. 블루프린트에서 호출 가능함
	bool IsDead() const;		//BlueprintPure는 const 함수와 함께 사용되어야 함. 

	// 블루프린트에서 pure 노드에는 실행 핀이 존재하지 않음 => 해당 함수를 호출하는 대상에게 어떠한 영향을 끼치지 않으며 결과를 산출하는 역할만 수행함.
	// BlueprintPure는 호출 대상의 그 어떠한 상태도 바꾸지 않음. 결과를 산출하는 역할만 수행 => 블루프린트에서 호출 시 실행핀이 존재하지 않음

private:
	void MoveForward(float AxisValue);
	void LookUp(float AxisValue); void LookRight(float AxisValue);
	void MoveRight(float AxisValue);
	
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	void Shoot();

	UPROPERTY(EditAnywhere)
	float RotationRate = 10.0;

	UPROPERTY(EditDefaultsOnly)			//런타임 중 총타입이 변경되지 않도록 선언0
	TSubclassOf<AGun> GunClass;			//블루프린트에서 선택할 수 있는 클래스를 제한

	UPROPERTY()
	AGun* Gun;							//블루프린트에서 GunClass를 통해 생성된 인스턴스가 저장될 변수

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;
};
