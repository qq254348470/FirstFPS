/*
	JoyColorWheel by Rama
*/
#pragma once

//~~~~~~~~~~~~ UMG ~~~~~~~~~~~~~~~~
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  
//UE4 Color Picker
#include "SJoyColorPicker.h"
  
#include "JoyColorWheel.generated.h"

// 更改颜色的委托
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJoyColorChangedEvent, const FLinearColor&, NewColor);

UCLASS()
class VICTORYUMG_API  UJoyColorWheel : public UWidget
{
	GENERATED_UCLASS_BODY()

//Color Picker物体
protected:
	TSharedPtr<SJoyColorPicker> ColorPicker;
	
//~~~~~~~~~~~~~~
// C++代码暴露给蓝图的函数和属性
//~~~~~~~~~~~~~~
public:

	/** 作者原来为EditDefaultsOnly，我擅作主张改成了EditAnywhere，这样可以在UMG中随时调节颜色。不需要的话可以改回来 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Joy Color Wheel")
	FLinearColor JoyColor;

    /** 初次创建时是否立即跳到JoyColor指定的颜色 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Joy Color Wheel")
	bool bSkipAnimationOnConstruction = false;
	
	
	/** 当ColorPicker颜色改变时需要调用的委托，必须得有BlueprintAssignable，否则蓝图属性中不显示 */
	UPROPERTY(BlueprintAssignable, Category="Widget Event", meta=(DisplayName="OnColorChanged (Joy Color Wheel)"))
	FOnJoyColorChangedEvent OnColorChanged;
	
	/** 获取当前颜色的方法 */
	UFUNCTION(BlueprintPure, Category="Joy Color Wheel")
	FLinearColor GetColor();
 
	/** 设置 Color Picker 的颜色 */
	UFUNCTION(BlueprintCallable, Category="Joy Color Wheel")
	void SetColor(FLinearColor NewColor, bool SkipAnimation = false );
	 
//~~~~~~~~~~~~~~~~~~
// Color Picker 内部使用的方法
//~~~~~~~~~~~~~~~~~~
public:	
	void ColorUpdated(FLinearColor NewValue);
	void ColorPickCancelled(FLinearColor NewValue);
	
//~~~~~~~~~~~~~~
// UMG 组件
//~~~~~~~~~~~~~~
public:

	// UVisual 接口   :( 具体时干啥的还没来得及研究，字面意思是释放Slate资源
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// UVisual 接口结束

protected:
	// UWidget 接口 :( 具体时干啥的还没来得及研究，字面意思是重构Widget
	virtual TSharedRef<SWidget> RebuildWidget() override;
	// UWidget 接口结束
  
#if WITH_EDITOR
	// UWidget 接口
	//virtual const FSlateBrush* GetEditorIcon() override;
	virtual const FText GetPaletteCategory() override;

	
	// UObject 接口，主要用于调整属性时，ColorPicker会更新
	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	
#endif

};
