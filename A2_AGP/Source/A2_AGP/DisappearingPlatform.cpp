
#include "DisappearingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/Character.h" // To identify player character

ADisappearingPlatform::ADisappearingPlatform()
{
    PrimaryActorTick.bCanEverTick = false;

    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    SetRootComponent(PlatformMesh);

    static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (CubeMesh.Succeeded())
    {
        PlatformMesh->SetStaticMesh(CubeMesh.Object);
    }

    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    TriggerBox->SetupAttachment(PlatformMesh);
    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ADisappearingPlatform::OnOverlapBegin);
    TriggerBox->OnComponentEndOverlap.AddDynamic(this, &ADisappearingPlatform::OnOverlapEnd);

    bPlayerOnPlatform = false;
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

void ADisappearingPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
    bool bFromSweep, const FHitResult& SweepResult)
{
    if (!bPlayerOnPlatform && OtherActor && OtherActor->IsA<ACharacter>())
    {
        bPlayerOnPlatform = true;
        StartStayTimer();
    }
}

void ADisappearingPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor && OtherActor->IsA<ACharacter>())
    {
        bPlayerOnPlatform = false;
        GetWorldTimerManager().ClearTimer(StayTimerHandle);
    }
}

void ADisappearingPlatform::StartStayTimer()
{
    // Wait 2 seconds before starting flicker
    GetWorldTimerManager().ClearTimer(StayTimerHandle);
    GetWorldTimerManager().SetTimer(StayTimerHandle, this, &ADisappearingPlatform::StartFlicker, 2.f, false);
}

void ADisappearingPlatform::StartFlicker()
{
    FlickerCount = 0;

    GetWorldTimerManager().SetTimer(FlickerTimerHandle, this, &ADisappearingPlatform::Flicker, 0.1f, true);
}

void ADisappearingPlatform::Flicker()
{
    if (FlickerCount >= 6)
    {
        GetWorldTimerManager().ClearTimer(FlickerTimerHandle);
        DisappearPlatform();

        // Set timer to reset platform after 3 seconds
        GetWorldTimerManager().SetTimer(DisappearTimerHandle, this, &ADisappearingPlatform::ResetPlatform, 2.f, false);
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
}

void ADisappearingPlatform::ResetPlatform()
{
    PlatformMesh->SetVisibility(true, true);
    PlatformMesh->SetHiddenInGame(false);
    PlatformMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

    // Reset state so it can happen again
    bPlayerOnPlatform = false;
    FlickerCount = 0;
}
