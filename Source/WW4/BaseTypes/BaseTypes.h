#pragma once

#include "CoreMinimal.h"
#include "BaseTypes.generated.h"

UENUM(BlueprintType)
enum class EFaction: uint8
{
	EF_RedTeam	UMETA(DisplayName = "RedTeam"),
	ET_BlueTeam	UMETA(DisplayName = "BlueTeam"),

	ET_Max	UMETA(DisplayName = "DefaultMax"),
};

UENUM(BlueprintType)
enum class EContructItemType : uint8
{
	ECT_Building	UMETA(DisplayName = "Building"),
	ECT_Infantry	UMETA(DisplayName = "Infantry"),
	ECT_Vehicle		UMETA(DisplayName = "Vehicle"),

	ECT_Max	UMETA(DisplayName = "DefaultMax"),
};

USTRUCT(BlueprintType)
struct WW4_API FItemProductionInfoBase : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EContructItemType ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemPrice;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ItemProductTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;
};
