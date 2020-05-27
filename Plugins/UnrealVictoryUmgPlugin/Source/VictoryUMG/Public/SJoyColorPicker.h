/*
	By Rama for You
	上面这条是作者要求的，必须留着，所以不能删，但是插件的代码可以自由更改和发布
*/

#pragma once

//UE4中 ColorPicker 这个类需要APPFRAMEWORK这个模块，我们已经在配置文件的Public中添加了

// 这里定义了SColorPicker的子类，后续我们会在Widget中使用，主要提供了更改ColorPicker颜色的操作变量和函数

//#include "Widgets/SCompoundWidget.h"
#include "Widgets/Colors/SColorPicker.h"
//#include "../../Plugins/UnrealVictoryUmgPlugin/Source/VictoryUMG/Public/SJoyColorPicker.h"
  
class SJoyColorPicker
	: public SColorPicker
{ 
	typedef SColorPicker Super;
	
public: 
	FORCEINLINE void SetColorRGB(const FLinearColor& NewColor)
	{
		//接下来这个方法在SColorPicker中是protected，但是我们需要在UMG中使用（protected无法完成调用）。
		// 所以我们重新封装了一个public方法，方便改变调用 
		
		SetNewTargetColorRGB( NewColor, true ); //强制更新，应该是设置ColorPickjer的颜色
	}
	

// 动画设置
public:
 
	FLinearColor InstantColor;
	bool Animation_SkipToFinalForOneTick = false; 
	virtual void Tick( const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime ) override
	{ 
		//Skip to final, then resume normal animation behavior
		if(Animation_SkipToFinalForOneTick)
		{  
			Animation_SkipToFinalForOneTick = false;
			Super::Tick(AllottedGeometry, InCurrentTime, 10000); //<~~~ 所有需要的变量，比如 CurrentTime 都是私有的 :)
			SetNewTargetColorRGB(InstantColor,true);
			return;
			//~~~~
		}
		
		//Animate normally!
		Super::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	}
};
