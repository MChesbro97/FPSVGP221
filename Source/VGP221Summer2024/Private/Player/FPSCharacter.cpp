// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FPSCharacter.h"
#include "Projectile/SeedProjectile.h"
#include "Projectile/WaterProjectile.h"
#include "Projectile/FPSProjectile.h"
#include "VGP221Summer2024/FPSGameMode.h"
#include "HUD/FPSHUD.h"
#include "GUI/FPSUserWidget.h" 

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Similar Unity Instantiate but only for constructors
	if (!FPSCameraComponent) {
		FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
		FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));
		FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
		FPSCameraComponent->bUsePawnControlRotation = true;
	}

	if (!FPSMesh) {
		FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
		FPSMesh->SetupAttachment(FPSCameraComponent);
		FPSMesh->bCastDynamicShadow = false;
		FPSMesh->CastShadow = false;
	}

	GetMesh()->SetOwnerNoSee(true);

	UE_LOG(LogTemp, Warning, TEXT("Character Constructor Is Being Called"));
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRightNotTheSameAsInput);

	// Look
	PlayerInputComponent->BindAxis("LookHorizontal", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookVertical", this, &AFPSCharacter::AddControllerPitchInput);

	// Jump
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::EndJump);

	// Fire
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AFPSCharacter::Fire);

	// Switch projectile types
	PlayerInputComponent->BindAction("SetWaterProjectile", IE_Pressed, this, &AFPSCharacter::SetWaterProjectile);
	PlayerInputComponent->BindAction("SetSeedProjectile", IE_Pressed, this, &AFPSCharacter::SetSeedProjectile);
	PlayerInputComponent->BindAction("SetDefaultProjectile", IE_Pressed, this, &AFPSCharacter::SetDefaultProjectile);
}

void AFPSCharacter::MoveForward(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);

	// Forward Vector from actor also works. Based on documentation
	//GetActorForwardVector();
}

void AFPSCharacter::MoveRightNotTheSameAsInput(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;

	// In blueprint we used Jump() so we can also use it here based on the documentation
	//Jump();
}

void AFPSCharacter::EndJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	if (!DefaultProjectileClass) return;

	if (DefaultProjectileClass == ASeedProjectile::StaticClass())
	{
		if (Seeds > 0)
		{
			DecreaseSeeds(1);
		}
		else
		{
			return;
			UE_LOG(LogTemp, Warning, TEXT("Out of seeds"));
			//DefaultProjectileClass = AFPSProjectile::StaticClass();
			//UE_LOG(LogTemp, Warning, TEXT("Out of seeds, switching to default projectile."));
		}
	}

	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

	FRotator MuzzleRotation = CameraRotation;
	//MuzzleRotation.Pitch += 10.0f;

	// Unity Instantiate
	// 1. Get World we to spawn in
	// 2. Spawn Actor with parameters to setup
	UWorld* World = GetWorld();
	if (!World) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(DefaultProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
	if (!Projectile) return;


	FVector LaunchDirection = MuzzleRotation.Vector();
	Projectile->FireInDirection(LaunchDirection);
}

float AFPSCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	AFPSHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AFPSHUD>();
	if (HUD) {
		Health -= DamageAmount;
		float HealthPercent = Health / MaxHealth;

		HUD->gameWidgetContainer->SetHealthBar(HealthPercent);
	}

	return FinalDamage;
}

void AFPSCharacter::SetProjectileClass(TSubclassOf<AFPSProjectile> NewProjectileClass)
{
	if (NewProjectileClass)
	{
		DefaultProjectileClass = NewProjectileClass;
		UE_LOG(LogTemp, Warning, TEXT("Projectile class has been set to: %s"), *NewProjectileClass->GetName());
	}
}

void AFPSCharacter::SetWaterProjectile()
{
	SetProjectileClass(AWaterProjectile::StaticClass());
	UE_LOG(LogTemp, Warning, TEXT("Projectile set to Water"));
}

void AFPSCharacter::SetSeedProjectile()
{
	SetProjectileClass(ASeedProjectile::StaticClass());
	UE_LOG(LogTemp, Warning, TEXT("Projectile set to Seeds"));
}

void AFPSCharacter::SetDefaultProjectile()
{
	SetProjectileClass(AFPSProjectile::StaticClass());
	UE_LOG(LogTemp, Warning, TEXT("Projectile set to Default"));
}


void AFPSCharacter::IncreaseSeeds(int Amount)
{
	Seeds += Amount;

	AFPSHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AFPSHUD>();
	if (HUD && HUD->gameWidgetContainer)
	{
		HUD->gameWidgetContainer->IncreaseSeedsText(Amount);
	}

	UE_LOG(LogTemp, Log, TEXT("Seeds increased by %d, total seeds: %d"), Amount, Seeds);
}

void AFPSCharacter::DecreaseSeeds(int Amount)
{
	Seeds = FMath::Max(0, Seeds - Amount); 

	AFPSHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD<AFPSHUD>();
	if (HUD && HUD->gameWidgetContainer)
	{
		HUD->gameWidgetContainer->DecreaseSeedsText(Amount);  
	}

	UE_LOG(LogTemp, Log, TEXT("Seeds decreased by %d, total seeds: %d"), Amount, Seeds);
}

int AFPSCharacter::GetPlayerSeedCount() const
{
	return Seeds;
}


