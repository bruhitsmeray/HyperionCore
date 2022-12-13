// Fill out your copyright notice in the Description page of Project Settings.


#include "HyperionCharacter.h"

#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AHyperionCharacter::AHyperionCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanCrouch = true;
	GetCharacterMovement()->GetNavAgentPropertiesRef().bCanJump = true;
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
	GetCharacterMovement()->MaxWalkSpeedCrouched = BaseCrouchSpeed;
	GetCapsuleComponent()->SetCapsuleHalfHeight(90.0f);

	JumpMaxCount = 2;
	JumpMaxHoldTime = 0.1f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;
	Camera->SetWorldLocation(FVector(0, 0, 70));

	FlashSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("FlashSpringArm"));
	FlashSpringArm->SetupAttachment(Camera);
	FlashSpringArm->TargetArmLength = 0.0f;
	FlashSpringArm->bEnableCameraRotationLag = true;
	FlashSpringArm->CameraRotationLagSpeed = 12.0f;

	HUDSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("HUDSpringArm"));
	HUDSpringArm->SetupAttachment(Camera);
	HUDSpringArm->TargetArmLength = 0.0f;
	HUDSpringArm->bEnableCameraLag = true;
	HUDSpringArm->CameraLagSpeed = 20.0f;
	HUDSpringArm->CameraLagMaxDistance = 1.0f;

	InnerLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("InnerLight"));
	InnerLight->SetupAttachment(FlashSpringArm);
	InnerLight->AttenuationRadius = 2500.0f;
	InnerLight->InnerConeAngle = 16.0f;
	InnerLight->OuterConeAngle = 24.0f;
	InnerLight->SetVisibility(false);

	OuterLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("OuterLight"));
	OuterLight->SetupAttachment(FlashSpringArm);
	OuterLight->Intensity = 2500.0f;
	OuterLight->AttenuationRadius = 2500.0f;
	OuterLight->InnerConeAngle = 32.0f;
	OuterLight->OuterConeAngle = 48.0f;
	OuterLight->SetVisibility(false);

	HUDWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HUDWidget"));
	HUDWidget->SetupAttachment(HUDSpringArm);
	HUDWidget->SetRelativeLocation(FVector(120, 0, 0));
	HUDWidget->SetWidgetSpace(EWidgetSpace::Screen);
	HUDWidget->SetDrawSize(FVector2D(1920, 1080));

	PhysicsHandle = CreateDefaultSubobject<UPhysicsHandleComponent>(TEXT("PhysicsHandle"));
}

// Called when the game starts or when spawned
void AHyperionCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AHyperionCharacter::FBeginGrab()
{
	UWorld* World = GetWorld();
	if(IsValid(World))
	{
		FVector CamLoc;
		FRotator CamRot;
		FHitResult HitResult;

		GetController()->GetPlayerViewPoint(CamLoc, CamRot);

		FVector Start = CamLoc;
		FVector End = (CamRot.Vector() * GrabDistance) + Start;

		FCollisionQueryParams TraceParams;
		bool bHit = World->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility, TraceParams);

		if(bHit)
		{
			Log("Warning", "The line trace hit an object.");
			if(IsValid(HitResult.GetComponent()) && HitResult.GetComponent()->IsSimulatingPhysics())
			{
				HitComponent = HitResult.GetComponent();
				PhysicsHandle->GrabComponentAtLocation(HitComponent, "None", HitComponent->GetComponentLocation());
				HitComponent->SetAngularDamping(PhysicsHandle->AngularDamping);
				bIsHolding = true;
			} else {
				bIsHolding = false;
				Log("Warning", "The component that was hit is not available or does not simulate physics.");
			}
		} else {
			bIsHolding = false;
			Log("Warning", "No hit registered.");
		}
	} else {
		Log("Warning", "World is not available.");
	}
}

void AHyperionCharacter::FGrabLocation()
{
	PhysicsHandle->SetTargetLocation(Camera->GetComponentLocation() + (Camera->GetForwardVector() * GrabDistance));
	if(bIsHolding && IsValid(HitComponent))
	{
		HitComponent->SetWorldRotation(GetControlRotation(), false, nullptr);
	}
}

void AHyperionCharacter::FStopGrab()
{
	if(IsValid(HitComponent))
	{
		HitComponent->SetAngularDamping(0.0f);
		PhysicsHandle->ReleaseComponent();
		bIsHolding = false;
	}
}

bool AHyperionCharacter::IsMoving()
{
	if((InputComponent->GetAxisValue(MoveForward) > 0 || InputComponent->GetAxisValue(MoveForward) < 0)
		|| (InputComponent->GetAxisValue(MoveSide) > 0 || InputComponent->GetAxisValue(MoveSide) < 0))
	{
		return true;
	}
	return false;
}

void AHyperionCharacter::FVerticalMove(float Value)
{
	if(Value != 0.0f)
	{
		AddMovementInput(GetActorForwardVector(), Value);
		IsWalkingV = true;
	} else {
		IsWalkingV = false;
	}
}

void AHyperionCharacter::FHorizontalMove(float Value)
{
	if(Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value);
		IsWalkingH = true;
	} else {
		IsWalkingH = false;
	}
}

void AHyperionCharacter::FVerticalLook(float Axis)
{
	AddControllerPitchInput(Axis * Sensitivity);
	FGrabLocation();
}

void AHyperionCharacter::FVerticalLookOnController(float Axis)
{
	AddControllerPitchInput(Axis * SensitivityY * GetWorld()->GetDeltaSeconds());
	FGrabLocation();
}

void AHyperionCharacter::FHorizontalLook(float Axis)
{
	AddControllerYawInput(Axis * Sensitivity);
	FGrabLocation();
}

void AHyperionCharacter::FHorizontalLookOnController(float Axis)
{
	AddControllerYawInput(Axis * SensitivityZ * GetWorld()->GetDeltaSeconds());
	FGrabLocation();
}

void AHyperionCharacter::BeginSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed * BaseWalkSpeedMultiplier;
}

void AHyperionCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
}

// Called every frame
void AHyperionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

// Called to bind functionality to input
void AHyperionCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(MoveForward, this, &AHyperionCharacter::FVerticalMove);
	PlayerInputComponent->BindAxis(MoveSide, this, &AHyperionCharacter::FHorizontalMove);
	PlayerInputComponent->BindAxis(VerticalLook, this, &AHyperionCharacter::FVerticalLook);
	PlayerInputComponent->BindAxis(VerticalLookOnController, this, &AHyperionCharacter::FVerticalLookOnController);
	PlayerInputComponent->BindAxis(HorizontalLook, this, &AHyperionCharacter::FHorizontalLook);
	PlayerInputComponent->BindAxis(HorizontalLookOnController, this, &AHyperionCharacter::FHorizontalLookOnController);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AHyperionCharacter::BeginSprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AHyperionCharacter::StopSprint);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AHyperionCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AHyperionCharacter::StopJumping);

	PlayerInputComponent->BindAction("Use", IE_Pressed, this, &AHyperionCharacter::FBeginGrab);
	PlayerInputComponent->BindAction("Use", IE_Released, this, &AHyperionCharacter::FStopGrab);
}
