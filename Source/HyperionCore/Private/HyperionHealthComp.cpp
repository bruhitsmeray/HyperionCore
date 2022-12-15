// Fill out your copyright notice in the Description page of Project Settings.


#include "HyperionHealthComp.h"

// Sets default values for this component's properties
UHyperionHealthComp::UHyperionHealthComp() {
	PrimaryComponentTick.bCanEverTick = true;
	MaxHealth = 100.0f;
}


// Called when the game starts
void UHyperionHealthComp::BeginPlay() {
	Super::BeginPlay();
	AActor* Owner = GetOwner();
	if(IsValid(Owner)) {
		Owner->OnTakeAnyDamage.AddDynamic(this, &UHyperionHealthComp::TakeDamage);
	}

	CurrentHealth = MaxHealth;
}

void UHyperionHealthComp::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser) {
	if(bAllowDamage) {
		CurrentHealth = FMath::Clamp(float(CurrentHealth) - Damage, 0.0f, float(MaxHealth));	
	}
}


// Called every frame
void UHyperionHealthComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(CurrentHealth <= 0) {
		GetOwner()->Destroy();
	}
}

int UHyperionHealthComp::GetHealth() const {
	return CurrentHealth;
}

void UHyperionHealthComp::SetHealth(int Value) {
	if(Value > MaxHealth) {
		CurrentHealth = MaxHealth;
	} else if(Value < 0) {
		CurrentHealth = 0;
	}
	CurrentHealth = Value;
}

