#include "DisappearingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

// Constructor
ADisappearingPlatform::ADisappearingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	// Platform mesh
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
	SetRootComponent(PlatformMesh);

	// Trigger box
	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(PlatformMesh);
	TriggerBox->SetBoxExtent(FVector(100.f, 100.f, 50.f));
	TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

	// Bind overlap events
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADisappearingPlatform::OnOverlapBegin);
	TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADisappearingPlatform::OnOverlapEnd);
}

void ADisappearingPlatform::BeginPlay()
{
	Super::BeginPlay();
}

void ADisappearingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADisappearingPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// Start the disappear timer
	GetWorldTimerManager().SetTimer(DisappearTimer, this, &ADisappearingPlatform::Disappear, 2.0f, false);
}

void ADisappearingPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Start the reappear timer
	GetWorldTimerManager().SetTimer(ReappearTimer, this, &ADisappearingPlatform::Reappear, 1.0f, false);
}

void ADisappearingPlatform::Disappear()
{
	if (PlatformMesh)
	{
		PlatformMesh->SetVisibility(false);
		PlatformMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

void ADisappearingPlatform::Reappear()
{
	if (PlatformMesh)
	{
		PlatformMesh->SetVisibility(true);
		PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}
