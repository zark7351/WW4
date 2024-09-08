#pragma once

#include "CoreMinimal.h"
#include "BaseTypes.generated.h"

UENUM(BlueprintType)
enum class EFaction: uint8
{
	EF_None	UMETA(DisplayName = "NoneFaction"),
	EF_Red	UMETA(DisplayName = "RedFaction"),
	ET_Blue	UMETA(DisplayName = "BlueFaction"),

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
	TArray<int32> PrerequisiteItemsID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ItemPrice;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ItemProductTime = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<int32> Grid;

	friend inline bool operator==(const FItemProductionInfoBase& A, const FItemProductionInfoBase& B)
	{
		return A.ItemType == B.ItemType && A.ItemID == B.ItemID;
	}

	friend inline uint32 GetTypeHash(const FItemProductionInfoBase& Key)
	{
		return HashCombine(GetTypeHash(Key.ItemType), GetTypeHash(Key.ItemID));
	}
};
