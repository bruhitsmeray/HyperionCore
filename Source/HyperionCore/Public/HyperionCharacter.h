// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Konsole.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "HyperionCharacter.generated.h"

UCLASS()
class HYPERIONCORE_API AHyperionCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHyperionCharacter();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Preferences")
		bool EnableLoggingThroughKonsolePlugin = false;
	
	void Log(FString Code, FString Message)
	{
		if(EnableLoggingThroughKonsolePlugin)
		{
			UKonsole::PrintToConsole(GetName(), Code, Message);
		}
	};
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components")
		UCameraComponent* Camera;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components|Interaction")
		UPhysicsHandleComponent* PhysicsHandle;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category="Components|Flashlight")
		USpringArmComponent* FlashSpringArm;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere,Category="Components|HUD")
		USpringArmComponent* HUDSpringArm;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components|Flashlight")
		USpotLightComponent* InnerLight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components|Flashlight")
		USpotLightComponent* OuterLight;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components|Interaction")
		UPrimitiveComponent* HitComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Components|HUD")
		UWidgetComponent* HUDWidget;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	bool bIsHolding = false;

	UFUNCTION(BlueprintCallable, Category="Character|Interface")
		void SetDrawSizeByScreenResolution(FVector2D Resolution);
	
	bool IsWalkingV;
	bool IsWalkingH;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Bindings|Camera")
		FName VerticalLook = "MouseY";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Bindings|Camera")
		FName VerticalLookOnController = "LookRate";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Bindings|Camera")
		FName HorizontalLook = "MouseX";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Bindings|Camera")
		FName HorizontalLookOnController = "TurnRate";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Bindings|Movement")
		FName MoveForward = "Vertical";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Bindings|Movement")
		FName MoveSide = "Horizontal";
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Bindings")
		FName Grapple = "Grapple";

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Interaction")
		float GrabDistance = 256.0f;
		float OutlineRange = GrabDistance;

		float ObjectRotation = 0.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Interaction")
		float OutlineRadius = 128.0f;
	
	UFUNCTION(BlueprintCallable, Category = "Character|Interaction")
		void FBeginGrab();
	UFUNCTION(BlueprintCallable, Category="Character|Interaction")
		void FGrabLocation();
	UFUNCTION(BlueprintCallable, Category="Character|Interaction")
		void FStopGrab();
	UFUNCTION(BlueprintCallable, Category="Character|Interaction")
		void ToggleGrab();
	UFUNCTION(BlueprintCallable, Category="Character|Interaction")
		void FRotateObject(float Axis);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Character|Sensitivity|Mouse")
		float Sensitivity = 0.25f;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Character|Sensitivity|Gamepad")
		float SensitivityZ = 25.0f;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Character|Sensitivity|Gamepad")
		float SensitivityY = 45.0f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Preferences")
		bool bToggleUse = true;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Preferences|Gameplay")
		bool bUseSmoothCrouch = true;

	UFUNCTION(BlueprintPure, Category = "Character|Sensitivity|Mouse")
		float GetMouseSens() const
		{
			UKonsole::PrintToConsole(GetName(), "Warning", FString::Printf(TEXT("Sensitivity: %f"), Sensitivity));
			return Sensitivity;	
		}
	UFUNCTION(BlueprintPure, Category = "Character|Sensitivity|Gamepad")
		float GetSensZ() const
		{
			UKonsole::PrintToConsole(GetName(), "Warning", FString::Printf(TEXT("Z Sensitivity: %f"), SensitivityZ));
			return SensitivityZ;
		}
	UFUNCTION(BlueprintPure, Category = "Character|Sensitivity|Gamepad")
		float GetSensY() const
		{
			UKonsole::PrintToConsole(GetName(), "Warning", FString::Printf(TEXT("X Sensitivity: %f"), SensitivityY));
			return SensitivityY;
		}

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Character|Camera")
		float BaseFoV = 90.0f;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Character|Speeds")
		float BaseWalkSpeed = 250.0f;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Character|Speeds")
		float BaseWalkSpeedMultiplier = 2.2f;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Character|Speeds")
		float BaseCrouchSpeed = 75.0f;

	bool IsMoving();

	UFUNCTION(BlueprintCallable, Category = "Character|Movement")
		void FVerticalMove(float Value);
	UFUNCTION(BlueprintCallable, Category = "Character|Movement")
		void FHorizontalMove(float Value);
	UFUNCTION(BlueprintCallable, Category = "Character|Camera")
		void FVerticalLook(float Axis);
	UFUNCTION(BlueprintCallable, Category = "Character|Camera")
		void FVerticalLookOnController(float Axis);
	UFUNCTION(BlueprintCallable, Category = "Character|Camera")
		void FHorizontalLook(float Axis);
	UFUNCTION(BlueprintCallable, Category = "Character|Camera")
		void FHorizontalLookOnController(float Axis);
	
	UFUNCTION(BlueprintCallable, Category="Character|Movement")
		void BeginSprint();
	UFUNCTION(BlueprintCallable, Category="Character|Movement")
		void StopSprint();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Preferences")
		bool bAllowFlash = true;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Status")
		bool bIsCrouching = false;
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, Category = "Status")
		bool bIsFlashOn = false;
};
