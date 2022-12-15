// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HyperionHealthComp.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HYPERIONCORE_API UHyperionHealthComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHyperionHealthComp();
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Settings")
	bool bAllowDamage = true;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UFUNCTION()
	void TakeDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Character|Vitals")
	int MaxHealth;
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Character|Vitals")
	int CurrentHealth;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure, Category="Character|Health")
	int GetHealth() const;
	UFUNCTION(Exec, BlueprintCallable, Category="Character|Health")
	void SetHealth(int Value);
};
