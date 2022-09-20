// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FCommonType.h"
#include "FDataTableTool.generated.h"

#define DATATABLE_Signed(AttrName)\
public:\
	static  F##AttrName##* Get##AttrName##(FName RowName);\
private:\
	static UDataTable *##AttrName##DT;


//DataTable'/Game/DataTables/FloodManagerDT.FloodManagerDT'
#define DATATABLE_Path(AttrName) "DataTable'/Game/DataTables/"#AttrName"DT."#AttrName"DT'"

#define DATATABLE_Impl(AttrName)\
UDataTable *FDTTool::##AttrName##DT = NULL;\
F##AttrName## *FDTTool::Get##AttrName##(FName RowName)\
{\
	if (!IsValid(##AttrName##DT))\
	{\
		##AttrName##DT = LoadObject<UDataTable>(NULL, TEXT(DATATABLE_Path(AttrName)));\
		check(##AttrName##DT);\
	}\
	F##AttrName## *Attr = ##AttrName##DT->FindRow<F##AttrName##>(RowName, FString("None"));\
	return Attr;\
}


class FDTTool
{
	DATATABLE_Signed(ButtonAttr)
	DATATABLE_Signed(FloodManagerAttr)
};

/**
 * 
 */
UCLASS()
class FLOODMANAGER_API UFDataTableTool : public UObject
{
	GENERATED_BODY()
};
