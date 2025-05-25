#include "DisappearingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"

ADisappearingPlatform::ADisappearingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	// Platform mesh
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		PlatformMesh->SetStaticMesh(CubeMesh.Object);
	}

	// Trigger box
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(PlatformMesh);
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADisappearingPlatform::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADisappearingPlatform::OnOverlapEnd);

	bIsPlatformVisible = true;
}

void ADisappearingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (PlatformMesh && TriggerBox)
	{
		FVector Origin, BoxExtent;
		PlatformMesh->GetLocalBounds(Origin, BoxExtent);
		TriggerBox->SetBoxExtent(BoxExtent);
		TriggerBox->SetRelativeLocation(FVector(0, 0, BoxExtent.Z));
	}
}

void ADisappearingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADisappearingPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsPlatformVisible)
	{
		bPlayerStillOnPlatform = true;
		StartFlicker();
	}
}

void ADisappearingPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bPlayerStillOnPlatform = false;

	// Cancel flicker completely
	GetWorldTimerManager().ClearTimer(FlickerTimer);
	FlickerCount = 0;

	PlatformMesh->SetVisibility(true);
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	bIsPlatformVisible = true;
}


void ADisappearingPlatform::StartFlicker()
{
	FlickerCount = 0;
	GetWorldTimerManager().SetTimer(FlickerTimer, this, &ADisappearingPlatform::Flicker, 0.2f, true);
}

void ADisappearingPlatform::Flicker()
{
	if (FlickerCount >= 6) // After 3 flickers
	{
		GetWorldTimerManager().ClearTimer(FlickerTimer);

		if (bPlayerStillOnPlatform)
		{
			DisappearPlatform();
		}
		else
		{
			PlatformMesh->SetVisibility(true); // Ensure it's visible
		}
		return;
	}

	bool bVisibleNow = (FlickerCount % 2 == 0);
	PlatformMesh->SetVisibility(bVisibleNow);
	FlickerCount++;
}


void ADisappearingPlatform::DisappearPlatform()
{
	PlatformMesh->SetVisibility(false);
	PlatformMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bIsPlatformVisible = false;
}
