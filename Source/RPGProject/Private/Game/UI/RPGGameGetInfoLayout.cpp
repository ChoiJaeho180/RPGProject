// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/UI/RPGGameGetInfoLayout.h"
#include "Game/UI/RPGameFadeTextBlock.h"

void URPGGameGetInfoLayout::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<FString> TextInfo = { "GetInfoText_0","GetInfoText_1", "GetInfoText_2",
								"GetInfoText_3", "GetInfoText_4", "GetInfoText_5"};

	for (int i = 0; i < TextInfo.Num(); i++)
	{
		_TextBlocks.Add(Cast<URPGameFadeTextBlock>(GetWidgetFromName(*TextInfo[i])));
	}
}

void URPGGameGetInfoLayout::UpdateFadeText()
{
	for (int i = 0; i < _TextBlocks.Num(); i++)
	{
		if (_TextBlocks[i]->GetbActive() == false) continue;
		_TextBlocks[i]->Update();
	}
}

void URPGGameGetInfoLayout::SetGetInfoText(int New, bool bGold)
{
	for (int i = _TextBlocks.Num() - 1; i >= 0 ; i--)
	{
		if (_TextBlocks[i]->GetbActive() == false) continue;
		if (i == _TextBlocks.Num() - 1) continue;

		_TextBlocks[i + 1]->SetOpacity(_TextBlocks[i]->GetRenderOpacity());
		_TextBlocks[i + 1]->SetLogText(_TextBlocks[i]->GetLogText());
		_TextBlocks[i + 1]->SetbActive(_TextBlocks[i]->GetbActive());
	}
	_TextBlocks[0]->SetOpacity(1);
	_TextBlocks[0]->SetbActive(true);
	FString Text = bGold == true ? L"골드" : L"경험치";
	Text.Append(" ( ");
	Text.Append(FString::FromInt(New));
	Text.Append(L" ) 를 획득하였습니다. ");
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Text);
	_TextBlocks[0]->SetLogText(FText::FromString(Text));
}
