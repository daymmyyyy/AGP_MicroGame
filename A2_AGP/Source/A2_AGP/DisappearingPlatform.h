#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DisappearingPlatform.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class A2_AGP_API ADisappearingPlatform : public AActor
{
	GENERATED_BODY()

public:
	ADisappearingPlatform();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerBox;

	UPROPERTY()
	AActor* PlayerActor;

	UPROPERTY()
	bool bIsPlatformVisible = true;

	UPROPERTY()
	FTimerHandle DelayBeforeFlickerTimer;

	UPROPERTY()
	FTimerHandle FlickerTimer;

	int32 FlickerCount = 0;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void BeginFlicker();
	void Flicker();
	void DisappearPlatform();
	void ResetPlatform();
};
