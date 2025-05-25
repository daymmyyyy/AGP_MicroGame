#include "DisappearingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "Engine/World.h"

ADisappearingPlatform::ADisappearingPlatform()
{
	PrimaryActorTick.bCanEverTick = false;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(PlatformMesh);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADisappearingPlatform::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADisappearingPlatform::OnOverlapEnd);
}

void ADisappearingPlatform::BeginPlay()
{
	Super::BeginPlay();

	FVector Origin, Extent;
	PlatformMesh->GetLocalBounds(Origin, Extent);
	TriggerBox->SetBoxExtent(Extent);
	TriggerBox->SetRelativeLocation(FVector(0, 0, Extent.Z));
}

void ADisappearingPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsPlatformVisible || PlayerActor)
		return;

	PlayerActor = OtherActor;

	// Start 2-second delay before flickering
	GetWorldTimerManager().ClearTimer(DelayBeforeFlickerTimer);
	GetWorldTimerManager().SetTimer(DelayBeforeFlickerTimer, this, &ADisappearingPlatform::BeginFlicker, 2.0f, false);
}

void ADisappearingPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == PlayerActor)
	{
		PlayerActor = nullptr;

		GetWorldTimerManager().ClearTimer(DelayBeforeFlickerTimer);
		GetWorldTimerManager().ClearTimer(FlickerTimer);

		ResetPlatform();
	}
}

void ADisappearingPlatform::BeginFlicker()
{
	if (!PlayerActor || !TriggerBox->IsOverlappingActor(PlayerActor))
	{
		ResetPlatform();
		return;
	}

	FlickerCount = 0;
	GetWorldTimerManager().SetTimer(FlickerTimer, this, &ADisappearingPlatform::Flicker, 0.2f, true);
}

void ADisappearingPlatform::Flicker()
{
	// Player jumped off during flicker
	if (!PlayerActor || !TriggerBox->IsOverlappingActor(PlayerActor))
	{
		GetWorldTimerManager().ClearTimer(FlickerTimer);
		ResetPlatform();
		return;
	}

	if (FlickerCount >= 6) // 3 flickers
	{
		GetWorldTimerManager().ClearTimer(FlickerTimer);
		DisappearPlatform();
		return;
	}

	bool bVisible = (FlickerCount % 2 == 0);
	PlatformMesh->SetVisibility(bVisible, true);
	PlatformMesh->SetHiddenInGame(!bVisible);
	FlickerCount++;
}

void ADisappearingPlatform::DisappearPlatform()
{
	PlatformMesh->SetVisibility(false, true);
	PlatformMesh->SetHiddenInGame(true);
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bIsPlatformVisible = false;
}

void ADisappearingPlatform::ResetPlatform()
{
	PlatformMesh->SetVisibility(true, true);
	PlatformMesh->SetHiddenInGame(false);
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	bIsPlatformVisible = true;
}
