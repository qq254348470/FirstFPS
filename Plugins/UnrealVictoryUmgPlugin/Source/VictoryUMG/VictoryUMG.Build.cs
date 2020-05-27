/*
	By Rama for You
	
	上面这条是作者要求的，必须留着，所以不能删，但是插件的代码可以自由更改和发布
*/

// 这是插件的模块依赖配置文件

using UnrealBuildTool;

public class VictoryUMG : ModuleRules
{
    public VictoryUMG(ReadOnlyTargetRules Target) : base(Target)
	{
        // 添加插件依赖的模块
        PublicDependencyModuleNames.AddRange(
			new string[] { 
				"Core", 
				"CoreUObject", 
				"Engine", 
				"InputCore",
				"RHI",
				"RenderCore",		 
				"UMG", 
				"Slate", 
				"SlateCore", 
                "APPFRAMEWORK" //ColorPicker需要这个模块 -Rama
		
			}
		);
		
		//Private Paths
        PrivateIncludePaths.AddRange(new string[] { 
			"VictoryUMG/Public",
			"VictoryUMG/Private"
		});
	}
}
