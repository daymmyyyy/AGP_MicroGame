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

public:
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, Category = "Platform")
	UStaticMeshComponent* PlatformMesh;

	UPROPERTY(VisibleAnywhere, Category = "Platform")
	UBoxComponent* TriggerBox;

	UPROPERTY()
	bool bIsPlatformVisible;

	UPROPERTY()
	bool bPlayerStillOnPlatform;

	UPROPERTY()
	FTimerHandle DisappearTimer;

	UPROPERTY()
	FTimerHandle FlickerTimer;

	int32 FlickerCount;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void DisappearPlatform();
	void StartFlicker();
	void Flicker();
};
