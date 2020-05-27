/*
	By Rama for You
	
	UMG的实现文件
*/
#include "JoyColorWheel.h"
#include "VictoryUMGPrivatePCH.h"

 
//LOCTEXT
#define LOCTEXT_NAMESPACE "UMG"
 
/////////////////////////////////////////////////////
// UJoyColorWheel

#if WITH_EDITOR
/*
const FSlateBrush* UJoyColorWheel::GetEditorIcon()
{
	return FUMGStyle::Get().GetBrush("Widget.Image");
}
*/ 
 
const FText UJoyColorWheel::GetPaletteCategory()
{
	return LOCTEXT("Victory UMG", "Victory UMG");
}

#endif

UJoyColorWheel::UJoyColorWheel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, JoyColor(FLinearColor::Red)
{   
	// 利用初始化方法设置默认值
}

// 重构UMG
TSharedRef<SWidget> UJoyColorWheel::RebuildWidget()
{
	// 重构UMG需要的参数
	FColorPickerArgs Args;
	
	//设置初始颜色
	Args.InitialColorOverride = JoyColor; 
	
	Args.bUseAlpha = true;
	Args.bOnlyRefreshOnOk = false;
	Args.bOnlyRefreshOnMouseUp = false;
	
	//设置需要的委托
	Args.OnColorCommitted 			= FOnLinearColorValueChanged::CreateUObject(	this, &UJoyColorWheel::ColorUpdated);
	Args.OnColorPickerCancelled 	= FOnColorPickerCancelled::CreateUObject(		this, &UJoyColorWheel::ColorPickCancelled);
	
	//真正创建Slate的地方
	 
	ColorPicker = SNew(SJoyColorPicker)
		.TargetColorAttribute(Args.InitialColorOverride)
		.TargetFColors(Args.ColorArray ? *Args.ColorArray : TArray<FColor*>())
		.TargetLinearColors(Args.LinearColorArray ? *Args.LinearColorArray : TArray<FLinearColor*>())
		.TargetColorChannels(Args.ColorChannelsArray ? *Args.ColorChannelsArray : TArray<FColorChannels>())
		.UseAlpha(Args.bUseAlpha)
		.ExpandAdvancedSection(Args.bExpandAdvancedSection)
		.OnlyRefreshOnMouseUp(Args.bOnlyRefreshOnMouseUp && !Args.bIsModal)
		.OnlyRefreshOnOk(Args.bOnlyRefreshOnOk || Args.bIsModal)
		.OnColorCommitted(Args.OnColorCommitted)
		.PreColorCommitted(Args.PreColorCommitted)
		.OnColorPickerCancelled(Args.OnColorPickerCancelled)
		.OnInteractivePickBegin(Args.OnInteractivePickBegin)
		.OnInteractivePickEnd(Args.OnInteractivePickEnd)
		.DisplayGamma(Args.DisplayGamma);
	
	// 是否需要跳过动画
	if(bSkipAnimationOnConstruction)
	{  
		SetColor(JoyColor, true); //Skip
	}
	
	return ColorPicker.ToSharedRef();
}
// 释放资源
void UJoyColorWheel::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	ColorPicker.Reset();
}

#if WITH_EDITOR
// 当在UMG编辑器中调节JoyColor属性时会自动刷新UMG中的颜色
void UJoyColorWheel::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;
  
	// 将ColorPicker的颜色更新为 JoyColor 属性设置的颜色
	if (PropertyName == TEXT("JoyColor"))
	{  
		if(ColorPicker.IsValid())
		{
			ColorPicker->SetColorRGB(JoyColor);
		}
	}	
} 
#endif

//~~~~~~~~~~~~~~~~~~
//			蓝图暴露函数的实现
//~~~~~~~~~~~~~~~~~~
FLinearColor UJoyColorWheel::GetColor() 
{
	return JoyColor;
} 
void UJoyColorWheel::SetColor(FLinearColor NewColor, bool SkipAnimation )
{ 
	if(!ColorPicker.IsValid()) return;
	 
	// 是否跳过动画
	if(SkipAnimation)
	{
		ColorPicker->InstantColor = NewColor; 
		ColorPicker->Animation_SkipToFinalForOneTick = true;		//See SJoyColorPicker.h
	}
	else
	{
		// 设置颜色
		ColorPicker->SetColorRGB(NewColor);
	}
}

//~~~~~~~~~~~~~~~~~~~~
//	   Color Picker 内部函数的实现
//~~~~~~~~~~~~~~~~~~~~
void UJoyColorWheel::ColorUpdated(FLinearColor NewValue)
{
	JoyColor = NewValue; 
	 
	if(OnColorChanged.IsBound())
	{
		OnColorChanged.Broadcast(JoyColor);
	}
} 
void UJoyColorWheel::ColorPickCancelled(FLinearColor NewValue)
{
	//Color Picking 
}




/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
