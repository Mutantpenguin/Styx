##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=styx
ConfigurationName      :=Debug
WorkspacePath          :=/home/charon/Projekte/styx
ProjectPath            :=/home/charon/Projekte/styx/styx
IntermediateDirectory  :=./bin/Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Markus Lobedann
Date                   :=08/23/18
CodeLitePath           :=/home/charon/.codelite
LinkerName             :=/usr/bin/clang++
SharedObjectLinkerName :=/usr/bin/clang++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)GLM_ENABLE_EXPERIMENTAL $(PreprocessorSwitch)MTR_ENABLED $(PreprocessorSwitch)STYX_DEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="styx.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)freeimage $(LibrarySwitch)freeimageplus $(LibrarySwitch)SDL2 $(LibrarySwitch)GL $(LibrarySwitch)glbinding $(LibrarySwitch)openal $(LibrarySwitch)assimp 
ArLibs                 :=  "freeimage" "freeimageplus" "SDL2" "GL" "glbinding" "openal" "assimp" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/llvm-ar rcu
CXX      := /usr/bin/clang++
CC       := /usr/bin/clang
CXXFLAGS := -Wmain -pedantic-errors -Wfatal-errors -ansi -pedantic -Wall -Wextra -Wmissing-include-dirs -Wmissing-declarations -Wunreachable-code -Winline -Wfloat-equal -Wundef -Wcast-align -Wredundant-decls -Winit-self -Wshadow -Wint-to-void-pointer-cast -Wcast-qual -Wunused-lambda-capture -std=c++17 --system-header-prefix=src/ext/ -g -O0 -fno-omit-frame-pointer $(Preprocessors)
CFLAGS   := -Wall -g -O0 $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/llvm-as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraOrthoComponent.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_scene_components_camera_CCameraFreeComponent.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_scene_components_camera_CCameraComponent.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_helper_image_ImageHandler.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_helper_image_CImage.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_model_CModelLoader.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_model_CModelManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_sampler_CSampler.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_shader_CShaderProgram.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_texture_CTextureCache.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_engine_system_CSettings.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_components_CModelComponent.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_grp.c$(ObjectSuffix) $(IntermediateDirectory)/src_engine_logger_CLogTargetMessageBox.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_math_Math.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_model_CMeshTextureSlot.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_CUniformBuffer.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_model_CMesh.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_system_CInput.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_sampler_CSamplerManager.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_engine_system_CGameInfo.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_7z.c$(ObjectSuffix) $(IntermediateDirectory)/src_engine_system_CEngine.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_COpenGlAdapter.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_helper_geom_CPlane.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_sound_ALHelper.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_unicode.c$(ObjectSuffix) $(IntermediateDirectory)/src_engine_scene_CFrustum.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_GLHelper.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_vdf.c$(ObjectSuffix) \
	$(IntermediateDirectory)/src_engine_system_CEngineInterface.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_scene_CEntity.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_imgui_imgui.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_texture_CCubemapData.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_fmt_posix.cc$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_CGLState.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_fmt_format.cc$(ObjectSuffix) $(IntermediateDirectory)/src_engine_logger_CLogTargetConsole.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_system_Main.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_platform_posix.c$(ObjectSuffix) \
	$(IntermediateDirectory)/src_engine_states_CStatePause.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_CVAO.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_platform_os2.c$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_platform_haiku.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_minitrace_minitrace.c$(ObjectSuffix) $(IntermediateDirectory)/src_engine_sound_CSoundBufferLoader.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_system_ComputerInfo.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_helper_String.cpp$(ObjectSuffix) 

Objects1=$(IntermediateDirectory)/src_engine_sound_CSoundManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_CRenderer.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_qpak.c$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_mvl.c$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_CFrameBuffer.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_logger_CLogger.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_slb.c$(ObjectSuffix) $(IntermediateDirectory)/src_engine_helper_Date.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_scene_CScene.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_sound_CSoundBuffer.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_system_CTimer.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_resource_CResourceCacheBase.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_engine_system_CWindow.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_shader_CShaderManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_hog.c$(ObjectSuffix) $(IntermediateDirectory)/src_ext_fmt_printf.cc$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_model_CModel.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_sound_CSoundSource.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_sound_CSoundBufferCache.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_logger_CLogTargetFile.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_states_CStateGame.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_states_CStateIntro.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_ext_physfs_physfs_platform_qnx.c$(ObjectSuffix) $(IntermediateDirectory)/src_engine_states_CState.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_states_CStateMainMenu.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_system_CFileSystem.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_sdl_CSDL.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_fmt_ostream.cc$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_texture_CTextureLoader.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_material_CMaterialCache.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_dir.c$(ObjectSuffix) $(IntermediateDirectory)/src_ext_imgui_imgui_draw.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_ext_physfs_physfs.c$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_iso9660.c$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_unpacked.c$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_wad.c$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_zip.c$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_byteorder.c$(ObjectSuffix) $(IntermediateDirectory)/src_engine_resource_CResourceCacheManager.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_material_CMaterialUniform.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_platform_unix.c$(ObjectSuffix) $(IntermediateDirectory)/src_ext_physfs_physfs_platform_winrt.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/src_ext_physfs_physfs_platform_windows.c$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_material_CMaterial.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_scene_CTransform.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_material_CMaterialLoader.cpp$(ObjectSuffix) 

Objects2=$(IntermediateDirectory)/src_engine_renderer_texture_CTexture.cpp$(ObjectSuffix) $(IntermediateDirectory)/src_engine_renderer_texture_C2DArrayData.cpp$(ObjectSuffix) 



Objects=$(Objects0) $(Objects1) $(Objects2) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	@echo $(Objects1) >> $(ObjectsFileList)
	@echo $(Objects2) >> $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./bin/Debug || $(MakeDirCommand) ./bin/Debug


$(IntermediateDirectory)/.d:
	@test -d ./bin/Debug || $(MakeDirCommand) ./bin/Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraOrthoComponent.cpp$(ObjectSuffix): src/engine/scene/components/camera/CCameraOrthoComponent.cpp $(IntermediateDirectory)/src_engine_scene_components_camera_CCameraOrthoComponent.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/scene/components/camera/CCameraOrthoComponent.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraOrthoComponent.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraOrthoComponent.cpp$(DependSuffix): src/engine/scene/components/camera/CCameraOrthoComponent.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraOrthoComponent.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraOrthoComponent.cpp$(DependSuffix) -MM src/engine/scene/components/camera/CCameraOrthoComponent.cpp

$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraOrthoComponent.cpp$(PreprocessSuffix): src/engine/scene/components/camera/CCameraOrthoComponent.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_scene_components_camera_CCameraOrthoComponent.cpp$(PreprocessSuffix) src/engine/scene/components/camera/CCameraOrthoComponent.cpp

$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraFreeComponent.cpp$(ObjectSuffix): src/engine/scene/components/camera/CCameraFreeComponent.cpp $(IntermediateDirectory)/src_engine_scene_components_camera_CCameraFreeComponent.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/scene/components/camera/CCameraFreeComponent.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraFreeComponent.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraFreeComponent.cpp$(DependSuffix): src/engine/scene/components/camera/CCameraFreeComponent.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraFreeComponent.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraFreeComponent.cpp$(DependSuffix) -MM src/engine/scene/components/camera/CCameraFreeComponent.cpp

$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraFreeComponent.cpp$(PreprocessSuffix): src/engine/scene/components/camera/CCameraFreeComponent.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_scene_components_camera_CCameraFreeComponent.cpp$(PreprocessSuffix) src/engine/scene/components/camera/CCameraFreeComponent.cpp

$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraComponent.cpp$(ObjectSuffix): src/engine/scene/components/camera/CCameraComponent.cpp $(IntermediateDirectory)/src_engine_scene_components_camera_CCameraComponent.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/scene/components/camera/CCameraComponent.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraComponent.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraComponent.cpp$(DependSuffix): src/engine/scene/components/camera/CCameraComponent.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraComponent.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraComponent.cpp$(DependSuffix) -MM src/engine/scene/components/camera/CCameraComponent.cpp

$(IntermediateDirectory)/src_engine_scene_components_camera_CCameraComponent.cpp$(PreprocessSuffix): src/engine/scene/components/camera/CCameraComponent.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_scene_components_camera_CCameraComponent.cpp$(PreprocessSuffix) src/engine/scene/components/camera/CCameraComponent.cpp

$(IntermediateDirectory)/src_engine_helper_image_ImageHandler.cpp$(ObjectSuffix): src/engine/helper/image/ImageHandler.cpp $(IntermediateDirectory)/src_engine_helper_image_ImageHandler.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/helper/image/ImageHandler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_helper_image_ImageHandler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_helper_image_ImageHandler.cpp$(DependSuffix): src/engine/helper/image/ImageHandler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_helper_image_ImageHandler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_helper_image_ImageHandler.cpp$(DependSuffix) -MM src/engine/helper/image/ImageHandler.cpp

$(IntermediateDirectory)/src_engine_helper_image_ImageHandler.cpp$(PreprocessSuffix): src/engine/helper/image/ImageHandler.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_helper_image_ImageHandler.cpp$(PreprocessSuffix) src/engine/helper/image/ImageHandler.cpp

$(IntermediateDirectory)/src_engine_helper_image_CImage.cpp$(ObjectSuffix): src/engine/helper/image/CImage.cpp $(IntermediateDirectory)/src_engine_helper_image_CImage.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/helper/image/CImage.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_helper_image_CImage.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_helper_image_CImage.cpp$(DependSuffix): src/engine/helper/image/CImage.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_helper_image_CImage.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_helper_image_CImage.cpp$(DependSuffix) -MM src/engine/helper/image/CImage.cpp

$(IntermediateDirectory)/src_engine_helper_image_CImage.cpp$(PreprocessSuffix): src/engine/helper/image/CImage.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_helper_image_CImage.cpp$(PreprocessSuffix) src/engine/helper/image/CImage.cpp

$(IntermediateDirectory)/src_engine_renderer_model_CModelLoader.cpp$(ObjectSuffix): src/engine/renderer/model/CModelLoader.cpp $(IntermediateDirectory)/src_engine_renderer_model_CModelLoader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/model/CModelLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_model_CModelLoader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_model_CModelLoader.cpp$(DependSuffix): src/engine/renderer/model/CModelLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_model_CModelLoader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_model_CModelLoader.cpp$(DependSuffix) -MM src/engine/renderer/model/CModelLoader.cpp

$(IntermediateDirectory)/src_engine_renderer_model_CModelLoader.cpp$(PreprocessSuffix): src/engine/renderer/model/CModelLoader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_model_CModelLoader.cpp$(PreprocessSuffix) src/engine/renderer/model/CModelLoader.cpp

$(IntermediateDirectory)/src_engine_renderer_model_CModelManager.cpp$(ObjectSuffix): src/engine/renderer/model/CModelManager.cpp $(IntermediateDirectory)/src_engine_renderer_model_CModelManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/model/CModelManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_model_CModelManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_model_CModelManager.cpp$(DependSuffix): src/engine/renderer/model/CModelManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_model_CModelManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_model_CModelManager.cpp$(DependSuffix) -MM src/engine/renderer/model/CModelManager.cpp

$(IntermediateDirectory)/src_engine_renderer_model_CModelManager.cpp$(PreprocessSuffix): src/engine/renderer/model/CModelManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_model_CModelManager.cpp$(PreprocessSuffix) src/engine/renderer/model/CModelManager.cpp

$(IntermediateDirectory)/src_engine_renderer_sampler_CSampler.cpp$(ObjectSuffix): src/engine/renderer/sampler/CSampler.cpp $(IntermediateDirectory)/src_engine_renderer_sampler_CSampler.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/sampler/CSampler.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_sampler_CSampler.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_sampler_CSampler.cpp$(DependSuffix): src/engine/renderer/sampler/CSampler.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_sampler_CSampler.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_sampler_CSampler.cpp$(DependSuffix) -MM src/engine/renderer/sampler/CSampler.cpp

$(IntermediateDirectory)/src_engine_renderer_sampler_CSampler.cpp$(PreprocessSuffix): src/engine/renderer/sampler/CSampler.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_sampler_CSampler.cpp$(PreprocessSuffix) src/engine/renderer/sampler/CSampler.cpp

$(IntermediateDirectory)/src_engine_renderer_shader_CShaderProgram.cpp$(ObjectSuffix): src/engine/renderer/shader/CShaderProgram.cpp $(IntermediateDirectory)/src_engine_renderer_shader_CShaderProgram.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/shader/CShaderProgram.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_shader_CShaderProgram.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_shader_CShaderProgram.cpp$(DependSuffix): src/engine/renderer/shader/CShaderProgram.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_shader_CShaderProgram.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_shader_CShaderProgram.cpp$(DependSuffix) -MM src/engine/renderer/shader/CShaderProgram.cpp

$(IntermediateDirectory)/src_engine_renderer_shader_CShaderProgram.cpp$(PreprocessSuffix): src/engine/renderer/shader/CShaderProgram.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_shader_CShaderProgram.cpp$(PreprocessSuffix) src/engine/renderer/shader/CShaderProgram.cpp

$(IntermediateDirectory)/src_engine_renderer_texture_CTextureCache.cpp$(ObjectSuffix): src/engine/renderer/texture/CTextureCache.cpp $(IntermediateDirectory)/src_engine_renderer_texture_CTextureCache.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/texture/CTextureCache.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_texture_CTextureCache.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_texture_CTextureCache.cpp$(DependSuffix): src/engine/renderer/texture/CTextureCache.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_texture_CTextureCache.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_texture_CTextureCache.cpp$(DependSuffix) -MM src/engine/renderer/texture/CTextureCache.cpp

$(IntermediateDirectory)/src_engine_renderer_texture_CTextureCache.cpp$(PreprocessSuffix): src/engine/renderer/texture/CTextureCache.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_texture_CTextureCache.cpp$(PreprocessSuffix) src/engine/renderer/texture/CTextureCache.cpp

$(IntermediateDirectory)/src_engine_system_CSettings.cpp$(ObjectSuffix): src/engine/system/CSettings.cpp $(IntermediateDirectory)/src_engine_system_CSettings.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/system/CSettings.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_system_CSettings.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_system_CSettings.cpp$(DependSuffix): src/engine/system/CSettings.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_system_CSettings.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_system_CSettings.cpp$(DependSuffix) -MM src/engine/system/CSettings.cpp

$(IntermediateDirectory)/src_engine_system_CSettings.cpp$(PreprocessSuffix): src/engine/system/CSettings.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_system_CSettings.cpp$(PreprocessSuffix) src/engine/system/CSettings.cpp

$(IntermediateDirectory)/src_engine_renderer_components_CModelComponent.cpp$(ObjectSuffix): src/engine/renderer/components/CModelComponent.cpp $(IntermediateDirectory)/src_engine_renderer_components_CModelComponent.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/components/CModelComponent.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_components_CModelComponent.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_components_CModelComponent.cpp$(DependSuffix): src/engine/renderer/components/CModelComponent.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_components_CModelComponent.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_components_CModelComponent.cpp$(DependSuffix) -MM src/engine/renderer/components/CModelComponent.cpp

$(IntermediateDirectory)/src_engine_renderer_components_CModelComponent.cpp$(PreprocessSuffix): src/engine/renderer/components/CModelComponent.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_components_CModelComponent.cpp$(PreprocessSuffix) src/engine/renderer/components/CModelComponent.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_grp.c$(ObjectSuffix): src/ext/physfs/physfs_archiver_grp.c $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_grp.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_archiver_grp.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_grp.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_grp.c$(DependSuffix): src/ext/physfs/physfs_archiver_grp.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_grp.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_grp.c$(DependSuffix) -MM src/ext/physfs/physfs_archiver_grp.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_grp.c$(PreprocessSuffix): src/ext/physfs/physfs_archiver_grp.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_grp.c$(PreprocessSuffix) src/ext/physfs/physfs_archiver_grp.c

$(IntermediateDirectory)/src_engine_logger_CLogTargetMessageBox.cpp$(ObjectSuffix): src/engine/logger/CLogTargetMessageBox.cpp $(IntermediateDirectory)/src_engine_logger_CLogTargetMessageBox.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/logger/CLogTargetMessageBox.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_logger_CLogTargetMessageBox.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_logger_CLogTargetMessageBox.cpp$(DependSuffix): src/engine/logger/CLogTargetMessageBox.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_logger_CLogTargetMessageBox.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_logger_CLogTargetMessageBox.cpp$(DependSuffix) -MM src/engine/logger/CLogTargetMessageBox.cpp

$(IntermediateDirectory)/src_engine_logger_CLogTargetMessageBox.cpp$(PreprocessSuffix): src/engine/logger/CLogTargetMessageBox.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_logger_CLogTargetMessageBox.cpp$(PreprocessSuffix) src/engine/logger/CLogTargetMessageBox.cpp

$(IntermediateDirectory)/src_engine_math_Math.cpp$(ObjectSuffix): src/engine/math/Math.cpp $(IntermediateDirectory)/src_engine_math_Math.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/math/Math.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_math_Math.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_math_Math.cpp$(DependSuffix): src/engine/math/Math.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_math_Math.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_math_Math.cpp$(DependSuffix) -MM src/engine/math/Math.cpp

$(IntermediateDirectory)/src_engine_math_Math.cpp$(PreprocessSuffix): src/engine/math/Math.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_math_Math.cpp$(PreprocessSuffix) src/engine/math/Math.cpp

$(IntermediateDirectory)/src_engine_renderer_model_CMeshTextureSlot.cpp$(ObjectSuffix): src/engine/renderer/model/CMeshTextureSlot.cpp $(IntermediateDirectory)/src_engine_renderer_model_CMeshTextureSlot.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/model/CMeshTextureSlot.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_model_CMeshTextureSlot.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_model_CMeshTextureSlot.cpp$(DependSuffix): src/engine/renderer/model/CMeshTextureSlot.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_model_CMeshTextureSlot.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_model_CMeshTextureSlot.cpp$(DependSuffix) -MM src/engine/renderer/model/CMeshTextureSlot.cpp

$(IntermediateDirectory)/src_engine_renderer_model_CMeshTextureSlot.cpp$(PreprocessSuffix): src/engine/renderer/model/CMeshTextureSlot.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_model_CMeshTextureSlot.cpp$(PreprocessSuffix) src/engine/renderer/model/CMeshTextureSlot.cpp

$(IntermediateDirectory)/src_engine_renderer_CUniformBuffer.cpp$(ObjectSuffix): src/engine/renderer/CUniformBuffer.cpp $(IntermediateDirectory)/src_engine_renderer_CUniformBuffer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/CUniformBuffer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_CUniformBuffer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_CUniformBuffer.cpp$(DependSuffix): src/engine/renderer/CUniformBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_CUniformBuffer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_CUniformBuffer.cpp$(DependSuffix) -MM src/engine/renderer/CUniformBuffer.cpp

$(IntermediateDirectory)/src_engine_renderer_CUniformBuffer.cpp$(PreprocessSuffix): src/engine/renderer/CUniformBuffer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_CUniformBuffer.cpp$(PreprocessSuffix) src/engine/renderer/CUniformBuffer.cpp

$(IntermediateDirectory)/src_engine_renderer_model_CMesh.cpp$(ObjectSuffix): src/engine/renderer/model/CMesh.cpp $(IntermediateDirectory)/src_engine_renderer_model_CMesh.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/model/CMesh.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_model_CMesh.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_model_CMesh.cpp$(DependSuffix): src/engine/renderer/model/CMesh.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_model_CMesh.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_model_CMesh.cpp$(DependSuffix) -MM src/engine/renderer/model/CMesh.cpp

$(IntermediateDirectory)/src_engine_renderer_model_CMesh.cpp$(PreprocessSuffix): src/engine/renderer/model/CMesh.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_model_CMesh.cpp$(PreprocessSuffix) src/engine/renderer/model/CMesh.cpp

$(IntermediateDirectory)/src_engine_system_CInput.cpp$(ObjectSuffix): src/engine/system/CInput.cpp $(IntermediateDirectory)/src_engine_system_CInput.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/system/CInput.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_system_CInput.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_system_CInput.cpp$(DependSuffix): src/engine/system/CInput.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_system_CInput.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_system_CInput.cpp$(DependSuffix) -MM src/engine/system/CInput.cpp

$(IntermediateDirectory)/src_engine_system_CInput.cpp$(PreprocessSuffix): src/engine/system/CInput.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_system_CInput.cpp$(PreprocessSuffix) src/engine/system/CInput.cpp

$(IntermediateDirectory)/src_engine_renderer_sampler_CSamplerManager.cpp$(ObjectSuffix): src/engine/renderer/sampler/CSamplerManager.cpp $(IntermediateDirectory)/src_engine_renderer_sampler_CSamplerManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/sampler/CSamplerManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_sampler_CSamplerManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_sampler_CSamplerManager.cpp$(DependSuffix): src/engine/renderer/sampler/CSamplerManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_sampler_CSamplerManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_sampler_CSamplerManager.cpp$(DependSuffix) -MM src/engine/renderer/sampler/CSamplerManager.cpp

$(IntermediateDirectory)/src_engine_renderer_sampler_CSamplerManager.cpp$(PreprocessSuffix): src/engine/renderer/sampler/CSamplerManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_sampler_CSamplerManager.cpp$(PreprocessSuffix) src/engine/renderer/sampler/CSamplerManager.cpp

$(IntermediateDirectory)/src_engine_system_CGameInfo.cpp$(ObjectSuffix): src/engine/system/CGameInfo.cpp $(IntermediateDirectory)/src_engine_system_CGameInfo.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/system/CGameInfo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_system_CGameInfo.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_system_CGameInfo.cpp$(DependSuffix): src/engine/system/CGameInfo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_system_CGameInfo.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_system_CGameInfo.cpp$(DependSuffix) -MM src/engine/system/CGameInfo.cpp

$(IntermediateDirectory)/src_engine_system_CGameInfo.cpp$(PreprocessSuffix): src/engine/system/CGameInfo.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_system_CGameInfo.cpp$(PreprocessSuffix) src/engine/system/CGameInfo.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_7z.c$(ObjectSuffix): src/ext/physfs/physfs_archiver_7z.c $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_7z.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_archiver_7z.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_7z.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_7z.c$(DependSuffix): src/ext/physfs/physfs_archiver_7z.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_7z.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_7z.c$(DependSuffix) -MM src/ext/physfs/physfs_archiver_7z.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_7z.c$(PreprocessSuffix): src/ext/physfs/physfs_archiver_7z.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_7z.c$(PreprocessSuffix) src/ext/physfs/physfs_archiver_7z.c

$(IntermediateDirectory)/src_engine_system_CEngine.cpp$(ObjectSuffix): src/engine/system/CEngine.cpp $(IntermediateDirectory)/src_engine_system_CEngine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/system/CEngine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_system_CEngine.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_system_CEngine.cpp$(DependSuffix): src/engine/system/CEngine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_system_CEngine.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_system_CEngine.cpp$(DependSuffix) -MM src/engine/system/CEngine.cpp

$(IntermediateDirectory)/src_engine_system_CEngine.cpp$(PreprocessSuffix): src/engine/system/CEngine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_system_CEngine.cpp$(PreprocessSuffix) src/engine/system/CEngine.cpp

$(IntermediateDirectory)/src_engine_renderer_COpenGlAdapter.cpp$(ObjectSuffix): src/engine/renderer/COpenGlAdapter.cpp $(IntermediateDirectory)/src_engine_renderer_COpenGlAdapter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/COpenGlAdapter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_COpenGlAdapter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_COpenGlAdapter.cpp$(DependSuffix): src/engine/renderer/COpenGlAdapter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_COpenGlAdapter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_COpenGlAdapter.cpp$(DependSuffix) -MM src/engine/renderer/COpenGlAdapter.cpp

$(IntermediateDirectory)/src_engine_renderer_COpenGlAdapter.cpp$(PreprocessSuffix): src/engine/renderer/COpenGlAdapter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_COpenGlAdapter.cpp$(PreprocessSuffix) src/engine/renderer/COpenGlAdapter.cpp

$(IntermediateDirectory)/src_engine_helper_geom_CPlane.cpp$(ObjectSuffix): src/engine/helper/geom/CPlane.cpp $(IntermediateDirectory)/src_engine_helper_geom_CPlane.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/helper/geom/CPlane.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_helper_geom_CPlane.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_helper_geom_CPlane.cpp$(DependSuffix): src/engine/helper/geom/CPlane.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_helper_geom_CPlane.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_helper_geom_CPlane.cpp$(DependSuffix) -MM src/engine/helper/geom/CPlane.cpp

$(IntermediateDirectory)/src_engine_helper_geom_CPlane.cpp$(PreprocessSuffix): src/engine/helper/geom/CPlane.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_helper_geom_CPlane.cpp$(PreprocessSuffix) src/engine/helper/geom/CPlane.cpp

$(IntermediateDirectory)/src_engine_sound_ALHelper.cpp$(ObjectSuffix): src/engine/sound/ALHelper.cpp $(IntermediateDirectory)/src_engine_sound_ALHelper.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/sound/ALHelper.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_sound_ALHelper.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_sound_ALHelper.cpp$(DependSuffix): src/engine/sound/ALHelper.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_sound_ALHelper.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_sound_ALHelper.cpp$(DependSuffix) -MM src/engine/sound/ALHelper.cpp

$(IntermediateDirectory)/src_engine_sound_ALHelper.cpp$(PreprocessSuffix): src/engine/sound/ALHelper.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_sound_ALHelper.cpp$(PreprocessSuffix) src/engine/sound/ALHelper.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_unicode.c$(ObjectSuffix): src/ext/physfs/physfs_unicode.c $(IntermediateDirectory)/src_ext_physfs_physfs_unicode.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_unicode.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_unicode.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_unicode.c$(DependSuffix): src/ext/physfs/physfs_unicode.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_unicode.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_unicode.c$(DependSuffix) -MM src/ext/physfs/physfs_unicode.c

$(IntermediateDirectory)/src_ext_physfs_physfs_unicode.c$(PreprocessSuffix): src/ext/physfs/physfs_unicode.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_unicode.c$(PreprocessSuffix) src/ext/physfs/physfs_unicode.c

$(IntermediateDirectory)/src_engine_scene_CFrustum.cpp$(ObjectSuffix): src/engine/scene/CFrustum.cpp $(IntermediateDirectory)/src_engine_scene_CFrustum.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/scene/CFrustum.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_scene_CFrustum.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_scene_CFrustum.cpp$(DependSuffix): src/engine/scene/CFrustum.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_scene_CFrustum.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_scene_CFrustum.cpp$(DependSuffix) -MM src/engine/scene/CFrustum.cpp

$(IntermediateDirectory)/src_engine_scene_CFrustum.cpp$(PreprocessSuffix): src/engine/scene/CFrustum.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_scene_CFrustum.cpp$(PreprocessSuffix) src/engine/scene/CFrustum.cpp

$(IntermediateDirectory)/src_engine_renderer_GLHelper.cpp$(ObjectSuffix): src/engine/renderer/GLHelper.cpp $(IntermediateDirectory)/src_engine_renderer_GLHelper.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/GLHelper.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_GLHelper.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_GLHelper.cpp$(DependSuffix): src/engine/renderer/GLHelper.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_GLHelper.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_GLHelper.cpp$(DependSuffix) -MM src/engine/renderer/GLHelper.cpp

$(IntermediateDirectory)/src_engine_renderer_GLHelper.cpp$(PreprocessSuffix): src/engine/renderer/GLHelper.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_GLHelper.cpp$(PreprocessSuffix) src/engine/renderer/GLHelper.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_vdf.c$(ObjectSuffix): src/ext/physfs/physfs_archiver_vdf.c $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_vdf.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_archiver_vdf.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_vdf.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_vdf.c$(DependSuffix): src/ext/physfs/physfs_archiver_vdf.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_vdf.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_vdf.c$(DependSuffix) -MM src/ext/physfs/physfs_archiver_vdf.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_vdf.c$(PreprocessSuffix): src/ext/physfs/physfs_archiver_vdf.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_vdf.c$(PreprocessSuffix) src/ext/physfs/physfs_archiver_vdf.c

$(IntermediateDirectory)/src_engine_system_CEngineInterface.cpp$(ObjectSuffix): src/engine/system/CEngineInterface.cpp $(IntermediateDirectory)/src_engine_system_CEngineInterface.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/system/CEngineInterface.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_system_CEngineInterface.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_system_CEngineInterface.cpp$(DependSuffix): src/engine/system/CEngineInterface.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_system_CEngineInterface.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_system_CEngineInterface.cpp$(DependSuffix) -MM src/engine/system/CEngineInterface.cpp

$(IntermediateDirectory)/src_engine_system_CEngineInterface.cpp$(PreprocessSuffix): src/engine/system/CEngineInterface.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_system_CEngineInterface.cpp$(PreprocessSuffix) src/engine/system/CEngineInterface.cpp

$(IntermediateDirectory)/src_engine_scene_CEntity.cpp$(ObjectSuffix): src/engine/scene/CEntity.cpp $(IntermediateDirectory)/src_engine_scene_CEntity.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/scene/CEntity.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_scene_CEntity.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_scene_CEntity.cpp$(DependSuffix): src/engine/scene/CEntity.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_scene_CEntity.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_scene_CEntity.cpp$(DependSuffix) -MM src/engine/scene/CEntity.cpp

$(IntermediateDirectory)/src_engine_scene_CEntity.cpp$(PreprocessSuffix): src/engine/scene/CEntity.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_scene_CEntity.cpp$(PreprocessSuffix) src/engine/scene/CEntity.cpp

$(IntermediateDirectory)/src_ext_imgui_imgui.cpp$(ObjectSuffix): src/ext/imgui/imgui.cpp $(IntermediateDirectory)/src_ext_imgui_imgui.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/imgui/imgui.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_imgui_imgui.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_imgui_imgui.cpp$(DependSuffix): src/ext/imgui/imgui.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_imgui_imgui.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_imgui_imgui.cpp$(DependSuffix) -MM src/ext/imgui/imgui.cpp

$(IntermediateDirectory)/src_ext_imgui_imgui.cpp$(PreprocessSuffix): src/ext/imgui/imgui.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_imgui_imgui.cpp$(PreprocessSuffix) src/ext/imgui/imgui.cpp

$(IntermediateDirectory)/src_engine_renderer_texture_CCubemapData.cpp$(ObjectSuffix): src/engine/renderer/texture/CCubemapData.cpp $(IntermediateDirectory)/src_engine_renderer_texture_CCubemapData.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/texture/CCubemapData.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_texture_CCubemapData.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_texture_CCubemapData.cpp$(DependSuffix): src/engine/renderer/texture/CCubemapData.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_texture_CCubemapData.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_texture_CCubemapData.cpp$(DependSuffix) -MM src/engine/renderer/texture/CCubemapData.cpp

$(IntermediateDirectory)/src_engine_renderer_texture_CCubemapData.cpp$(PreprocessSuffix): src/engine/renderer/texture/CCubemapData.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_texture_CCubemapData.cpp$(PreprocessSuffix) src/engine/renderer/texture/CCubemapData.cpp

$(IntermediateDirectory)/src_ext_fmt_posix.cc$(ObjectSuffix): src/ext/fmt/posix.cc $(IntermediateDirectory)/src_ext_fmt_posix.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/fmt/posix.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_fmt_posix.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_fmt_posix.cc$(DependSuffix): src/ext/fmt/posix.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_fmt_posix.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_fmt_posix.cc$(DependSuffix) -MM src/ext/fmt/posix.cc

$(IntermediateDirectory)/src_ext_fmt_posix.cc$(PreprocessSuffix): src/ext/fmt/posix.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_fmt_posix.cc$(PreprocessSuffix) src/ext/fmt/posix.cc

$(IntermediateDirectory)/src_engine_renderer_CGLState.cpp$(ObjectSuffix): src/engine/renderer/CGLState.cpp $(IntermediateDirectory)/src_engine_renderer_CGLState.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/CGLState.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_CGLState.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_CGLState.cpp$(DependSuffix): src/engine/renderer/CGLState.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_CGLState.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_CGLState.cpp$(DependSuffix) -MM src/engine/renderer/CGLState.cpp

$(IntermediateDirectory)/src_engine_renderer_CGLState.cpp$(PreprocessSuffix): src/engine/renderer/CGLState.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_CGLState.cpp$(PreprocessSuffix) src/engine/renderer/CGLState.cpp

$(IntermediateDirectory)/src_ext_fmt_format.cc$(ObjectSuffix): src/ext/fmt/format.cc $(IntermediateDirectory)/src_ext_fmt_format.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/fmt/format.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_fmt_format.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_fmt_format.cc$(DependSuffix): src/ext/fmt/format.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_fmt_format.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_fmt_format.cc$(DependSuffix) -MM src/ext/fmt/format.cc

$(IntermediateDirectory)/src_ext_fmt_format.cc$(PreprocessSuffix): src/ext/fmt/format.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_fmt_format.cc$(PreprocessSuffix) src/ext/fmt/format.cc

$(IntermediateDirectory)/src_engine_logger_CLogTargetConsole.cpp$(ObjectSuffix): src/engine/logger/CLogTargetConsole.cpp $(IntermediateDirectory)/src_engine_logger_CLogTargetConsole.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/logger/CLogTargetConsole.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_logger_CLogTargetConsole.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_logger_CLogTargetConsole.cpp$(DependSuffix): src/engine/logger/CLogTargetConsole.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_logger_CLogTargetConsole.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_logger_CLogTargetConsole.cpp$(DependSuffix) -MM src/engine/logger/CLogTargetConsole.cpp

$(IntermediateDirectory)/src_engine_logger_CLogTargetConsole.cpp$(PreprocessSuffix): src/engine/logger/CLogTargetConsole.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_logger_CLogTargetConsole.cpp$(PreprocessSuffix) src/engine/logger/CLogTargetConsole.cpp

$(IntermediateDirectory)/src_engine_system_Main.cpp$(ObjectSuffix): src/engine/system/Main.cpp $(IntermediateDirectory)/src_engine_system_Main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/system/Main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_system_Main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_system_Main.cpp$(DependSuffix): src/engine/system/Main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_system_Main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_system_Main.cpp$(DependSuffix) -MM src/engine/system/Main.cpp

$(IntermediateDirectory)/src_engine_system_Main.cpp$(PreprocessSuffix): src/engine/system/Main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_system_Main.cpp$(PreprocessSuffix) src/engine/system/Main.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_posix.c$(ObjectSuffix): src/ext/physfs/physfs_platform_posix.c $(IntermediateDirectory)/src_ext_physfs_physfs_platform_posix.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_platform_posix.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_platform_posix.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_platform_posix.c$(DependSuffix): src/ext/physfs/physfs_platform_posix.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_platform_posix.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_platform_posix.c$(DependSuffix) -MM src/ext/physfs/physfs_platform_posix.c

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_posix.c$(PreprocessSuffix): src/ext/physfs/physfs_platform_posix.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_platform_posix.c$(PreprocessSuffix) src/ext/physfs/physfs_platform_posix.c

$(IntermediateDirectory)/src_engine_states_CStatePause.cpp$(ObjectSuffix): src/engine/states/CStatePause.cpp $(IntermediateDirectory)/src_engine_states_CStatePause.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/states/CStatePause.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_states_CStatePause.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_states_CStatePause.cpp$(DependSuffix): src/engine/states/CStatePause.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_states_CStatePause.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_states_CStatePause.cpp$(DependSuffix) -MM src/engine/states/CStatePause.cpp

$(IntermediateDirectory)/src_engine_states_CStatePause.cpp$(PreprocessSuffix): src/engine/states/CStatePause.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_states_CStatePause.cpp$(PreprocessSuffix) src/engine/states/CStatePause.cpp

$(IntermediateDirectory)/src_engine_renderer_CVAO.cpp$(ObjectSuffix): src/engine/renderer/CVAO.cpp $(IntermediateDirectory)/src_engine_renderer_CVAO.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/CVAO.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_CVAO.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_CVAO.cpp$(DependSuffix): src/engine/renderer/CVAO.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_CVAO.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_CVAO.cpp$(DependSuffix) -MM src/engine/renderer/CVAO.cpp

$(IntermediateDirectory)/src_engine_renderer_CVAO.cpp$(PreprocessSuffix): src/engine/renderer/CVAO.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_CVAO.cpp$(PreprocessSuffix) src/engine/renderer/CVAO.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_os2.c$(ObjectSuffix): src/ext/physfs/physfs_platform_os2.c $(IntermediateDirectory)/src_ext_physfs_physfs_platform_os2.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_platform_os2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_platform_os2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_platform_os2.c$(DependSuffix): src/ext/physfs/physfs_platform_os2.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_platform_os2.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_platform_os2.c$(DependSuffix) -MM src/ext/physfs/physfs_platform_os2.c

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_os2.c$(PreprocessSuffix): src/ext/physfs/physfs_platform_os2.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_platform_os2.c$(PreprocessSuffix) src/ext/physfs/physfs_platform_os2.c

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_haiku.cpp$(ObjectSuffix): src/ext/physfs/physfs_platform_haiku.cpp $(IntermediateDirectory)/src_ext_physfs_physfs_platform_haiku.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_platform_haiku.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_platform_haiku.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_platform_haiku.cpp$(DependSuffix): src/ext/physfs/physfs_platform_haiku.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_platform_haiku.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_platform_haiku.cpp$(DependSuffix) -MM src/ext/physfs/physfs_platform_haiku.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_haiku.cpp$(PreprocessSuffix): src/ext/physfs/physfs_platform_haiku.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_platform_haiku.cpp$(PreprocessSuffix) src/ext/physfs/physfs_platform_haiku.cpp

$(IntermediateDirectory)/src_ext_minitrace_minitrace.c$(ObjectSuffix): src/ext/minitrace/minitrace.c $(IntermediateDirectory)/src_ext_minitrace_minitrace.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/minitrace/minitrace.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_minitrace_minitrace.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_minitrace_minitrace.c$(DependSuffix): src/ext/minitrace/minitrace.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_minitrace_minitrace.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_minitrace_minitrace.c$(DependSuffix) -MM src/ext/minitrace/minitrace.c

$(IntermediateDirectory)/src_ext_minitrace_minitrace.c$(PreprocessSuffix): src/ext/minitrace/minitrace.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_minitrace_minitrace.c$(PreprocessSuffix) src/ext/minitrace/minitrace.c

$(IntermediateDirectory)/src_engine_sound_CSoundBufferLoader.cpp$(ObjectSuffix): src/engine/sound/CSoundBufferLoader.cpp $(IntermediateDirectory)/src_engine_sound_CSoundBufferLoader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/sound/CSoundBufferLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_sound_CSoundBufferLoader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_sound_CSoundBufferLoader.cpp$(DependSuffix): src/engine/sound/CSoundBufferLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_sound_CSoundBufferLoader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_sound_CSoundBufferLoader.cpp$(DependSuffix) -MM src/engine/sound/CSoundBufferLoader.cpp

$(IntermediateDirectory)/src_engine_sound_CSoundBufferLoader.cpp$(PreprocessSuffix): src/engine/sound/CSoundBufferLoader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_sound_CSoundBufferLoader.cpp$(PreprocessSuffix) src/engine/sound/CSoundBufferLoader.cpp

$(IntermediateDirectory)/src_engine_system_ComputerInfo.cpp$(ObjectSuffix): src/engine/system/ComputerInfo.cpp $(IntermediateDirectory)/src_engine_system_ComputerInfo.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/system/ComputerInfo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_system_ComputerInfo.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_system_ComputerInfo.cpp$(DependSuffix): src/engine/system/ComputerInfo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_system_ComputerInfo.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_system_ComputerInfo.cpp$(DependSuffix) -MM src/engine/system/ComputerInfo.cpp

$(IntermediateDirectory)/src_engine_system_ComputerInfo.cpp$(PreprocessSuffix): src/engine/system/ComputerInfo.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_system_ComputerInfo.cpp$(PreprocessSuffix) src/engine/system/ComputerInfo.cpp

$(IntermediateDirectory)/src_engine_helper_String.cpp$(ObjectSuffix): src/engine/helper/String.cpp $(IntermediateDirectory)/src_engine_helper_String.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/helper/String.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_helper_String.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_helper_String.cpp$(DependSuffix): src/engine/helper/String.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_helper_String.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_helper_String.cpp$(DependSuffix) -MM src/engine/helper/String.cpp

$(IntermediateDirectory)/src_engine_helper_String.cpp$(PreprocessSuffix): src/engine/helper/String.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_helper_String.cpp$(PreprocessSuffix) src/engine/helper/String.cpp

$(IntermediateDirectory)/src_engine_sound_CSoundManager.cpp$(ObjectSuffix): src/engine/sound/CSoundManager.cpp $(IntermediateDirectory)/src_engine_sound_CSoundManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/sound/CSoundManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_sound_CSoundManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_sound_CSoundManager.cpp$(DependSuffix): src/engine/sound/CSoundManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_sound_CSoundManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_sound_CSoundManager.cpp$(DependSuffix) -MM src/engine/sound/CSoundManager.cpp

$(IntermediateDirectory)/src_engine_sound_CSoundManager.cpp$(PreprocessSuffix): src/engine/sound/CSoundManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_sound_CSoundManager.cpp$(PreprocessSuffix) src/engine/sound/CSoundManager.cpp

$(IntermediateDirectory)/src_engine_renderer_CRenderer.cpp$(ObjectSuffix): src/engine/renderer/CRenderer.cpp $(IntermediateDirectory)/src_engine_renderer_CRenderer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/CRenderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_CRenderer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_CRenderer.cpp$(DependSuffix): src/engine/renderer/CRenderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_CRenderer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_CRenderer.cpp$(DependSuffix) -MM src/engine/renderer/CRenderer.cpp

$(IntermediateDirectory)/src_engine_renderer_CRenderer.cpp$(PreprocessSuffix): src/engine/renderer/CRenderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_CRenderer.cpp$(PreprocessSuffix) src/engine/renderer/CRenderer.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_qpak.c$(ObjectSuffix): src/ext/physfs/physfs_archiver_qpak.c $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_qpak.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_archiver_qpak.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_qpak.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_qpak.c$(DependSuffix): src/ext/physfs/physfs_archiver_qpak.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_qpak.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_qpak.c$(DependSuffix) -MM src/ext/physfs/physfs_archiver_qpak.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_qpak.c$(PreprocessSuffix): src/ext/physfs/physfs_archiver_qpak.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_qpak.c$(PreprocessSuffix) src/ext/physfs/physfs_archiver_qpak.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_mvl.c$(ObjectSuffix): src/ext/physfs/physfs_archiver_mvl.c $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_mvl.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_archiver_mvl.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_mvl.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_mvl.c$(DependSuffix): src/ext/physfs/physfs_archiver_mvl.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_mvl.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_mvl.c$(DependSuffix) -MM src/ext/physfs/physfs_archiver_mvl.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_mvl.c$(PreprocessSuffix): src/ext/physfs/physfs_archiver_mvl.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_mvl.c$(PreprocessSuffix) src/ext/physfs/physfs_archiver_mvl.c

$(IntermediateDirectory)/src_engine_renderer_CFrameBuffer.cpp$(ObjectSuffix): src/engine/renderer/CFrameBuffer.cpp $(IntermediateDirectory)/src_engine_renderer_CFrameBuffer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/CFrameBuffer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_CFrameBuffer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_CFrameBuffer.cpp$(DependSuffix): src/engine/renderer/CFrameBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_CFrameBuffer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_CFrameBuffer.cpp$(DependSuffix) -MM src/engine/renderer/CFrameBuffer.cpp

$(IntermediateDirectory)/src_engine_renderer_CFrameBuffer.cpp$(PreprocessSuffix): src/engine/renderer/CFrameBuffer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_CFrameBuffer.cpp$(PreprocessSuffix) src/engine/renderer/CFrameBuffer.cpp

$(IntermediateDirectory)/src_engine_logger_CLogger.cpp$(ObjectSuffix): src/engine/logger/CLogger.cpp $(IntermediateDirectory)/src_engine_logger_CLogger.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/logger/CLogger.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_logger_CLogger.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_logger_CLogger.cpp$(DependSuffix): src/engine/logger/CLogger.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_logger_CLogger.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_logger_CLogger.cpp$(DependSuffix) -MM src/engine/logger/CLogger.cpp

$(IntermediateDirectory)/src_engine_logger_CLogger.cpp$(PreprocessSuffix): src/engine/logger/CLogger.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_logger_CLogger.cpp$(PreprocessSuffix) src/engine/logger/CLogger.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_slb.c$(ObjectSuffix): src/ext/physfs/physfs_archiver_slb.c $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_slb.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_archiver_slb.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_slb.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_slb.c$(DependSuffix): src/ext/physfs/physfs_archiver_slb.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_slb.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_slb.c$(DependSuffix) -MM src/ext/physfs/physfs_archiver_slb.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_slb.c$(PreprocessSuffix): src/ext/physfs/physfs_archiver_slb.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_slb.c$(PreprocessSuffix) src/ext/physfs/physfs_archiver_slb.c

$(IntermediateDirectory)/src_engine_helper_Date.cpp$(ObjectSuffix): src/engine/helper/Date.cpp $(IntermediateDirectory)/src_engine_helper_Date.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/helper/Date.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_helper_Date.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_helper_Date.cpp$(DependSuffix): src/engine/helper/Date.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_helper_Date.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_helper_Date.cpp$(DependSuffix) -MM src/engine/helper/Date.cpp

$(IntermediateDirectory)/src_engine_helper_Date.cpp$(PreprocessSuffix): src/engine/helper/Date.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_helper_Date.cpp$(PreprocessSuffix) src/engine/helper/Date.cpp

$(IntermediateDirectory)/src_engine_scene_CScene.cpp$(ObjectSuffix): src/engine/scene/CScene.cpp $(IntermediateDirectory)/src_engine_scene_CScene.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/scene/CScene.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_scene_CScene.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_scene_CScene.cpp$(DependSuffix): src/engine/scene/CScene.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_scene_CScene.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_scene_CScene.cpp$(DependSuffix) -MM src/engine/scene/CScene.cpp

$(IntermediateDirectory)/src_engine_scene_CScene.cpp$(PreprocessSuffix): src/engine/scene/CScene.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_scene_CScene.cpp$(PreprocessSuffix) src/engine/scene/CScene.cpp

$(IntermediateDirectory)/src_engine_sound_CSoundBuffer.cpp$(ObjectSuffix): src/engine/sound/CSoundBuffer.cpp $(IntermediateDirectory)/src_engine_sound_CSoundBuffer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/sound/CSoundBuffer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_sound_CSoundBuffer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_sound_CSoundBuffer.cpp$(DependSuffix): src/engine/sound/CSoundBuffer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_sound_CSoundBuffer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_sound_CSoundBuffer.cpp$(DependSuffix) -MM src/engine/sound/CSoundBuffer.cpp

$(IntermediateDirectory)/src_engine_sound_CSoundBuffer.cpp$(PreprocessSuffix): src/engine/sound/CSoundBuffer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_sound_CSoundBuffer.cpp$(PreprocessSuffix) src/engine/sound/CSoundBuffer.cpp

$(IntermediateDirectory)/src_engine_system_CTimer.cpp$(ObjectSuffix): src/engine/system/CTimer.cpp $(IntermediateDirectory)/src_engine_system_CTimer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/system/CTimer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_system_CTimer.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_system_CTimer.cpp$(DependSuffix): src/engine/system/CTimer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_system_CTimer.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_system_CTimer.cpp$(DependSuffix) -MM src/engine/system/CTimer.cpp

$(IntermediateDirectory)/src_engine_system_CTimer.cpp$(PreprocessSuffix): src/engine/system/CTimer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_system_CTimer.cpp$(PreprocessSuffix) src/engine/system/CTimer.cpp

$(IntermediateDirectory)/src_engine_resource_CResourceCacheBase.cpp$(ObjectSuffix): src/engine/resource/CResourceCacheBase.cpp $(IntermediateDirectory)/src_engine_resource_CResourceCacheBase.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/resource/CResourceCacheBase.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_resource_CResourceCacheBase.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_resource_CResourceCacheBase.cpp$(DependSuffix): src/engine/resource/CResourceCacheBase.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_resource_CResourceCacheBase.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_resource_CResourceCacheBase.cpp$(DependSuffix) -MM src/engine/resource/CResourceCacheBase.cpp

$(IntermediateDirectory)/src_engine_resource_CResourceCacheBase.cpp$(PreprocessSuffix): src/engine/resource/CResourceCacheBase.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_resource_CResourceCacheBase.cpp$(PreprocessSuffix) src/engine/resource/CResourceCacheBase.cpp

$(IntermediateDirectory)/src_engine_system_CWindow.cpp$(ObjectSuffix): src/engine/system/CWindow.cpp $(IntermediateDirectory)/src_engine_system_CWindow.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/system/CWindow.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_system_CWindow.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_system_CWindow.cpp$(DependSuffix): src/engine/system/CWindow.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_system_CWindow.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_system_CWindow.cpp$(DependSuffix) -MM src/engine/system/CWindow.cpp

$(IntermediateDirectory)/src_engine_system_CWindow.cpp$(PreprocessSuffix): src/engine/system/CWindow.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_system_CWindow.cpp$(PreprocessSuffix) src/engine/system/CWindow.cpp

$(IntermediateDirectory)/src_engine_renderer_shader_CShaderManager.cpp$(ObjectSuffix): src/engine/renderer/shader/CShaderManager.cpp $(IntermediateDirectory)/src_engine_renderer_shader_CShaderManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/shader/CShaderManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_shader_CShaderManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_shader_CShaderManager.cpp$(DependSuffix): src/engine/renderer/shader/CShaderManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_shader_CShaderManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_shader_CShaderManager.cpp$(DependSuffix) -MM src/engine/renderer/shader/CShaderManager.cpp

$(IntermediateDirectory)/src_engine_renderer_shader_CShaderManager.cpp$(PreprocessSuffix): src/engine/renderer/shader/CShaderManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_shader_CShaderManager.cpp$(PreprocessSuffix) src/engine/renderer/shader/CShaderManager.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_hog.c$(ObjectSuffix): src/ext/physfs/physfs_archiver_hog.c $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_hog.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_archiver_hog.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_hog.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_hog.c$(DependSuffix): src/ext/physfs/physfs_archiver_hog.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_hog.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_hog.c$(DependSuffix) -MM src/ext/physfs/physfs_archiver_hog.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_hog.c$(PreprocessSuffix): src/ext/physfs/physfs_archiver_hog.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_hog.c$(PreprocessSuffix) src/ext/physfs/physfs_archiver_hog.c

$(IntermediateDirectory)/src_ext_fmt_printf.cc$(ObjectSuffix): src/ext/fmt/printf.cc $(IntermediateDirectory)/src_ext_fmt_printf.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/fmt/printf.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_fmt_printf.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_fmt_printf.cc$(DependSuffix): src/ext/fmt/printf.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_fmt_printf.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_fmt_printf.cc$(DependSuffix) -MM src/ext/fmt/printf.cc

$(IntermediateDirectory)/src_ext_fmt_printf.cc$(PreprocessSuffix): src/ext/fmt/printf.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_fmt_printf.cc$(PreprocessSuffix) src/ext/fmt/printf.cc

$(IntermediateDirectory)/src_engine_renderer_model_CModel.cpp$(ObjectSuffix): src/engine/renderer/model/CModel.cpp $(IntermediateDirectory)/src_engine_renderer_model_CModel.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/model/CModel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_model_CModel.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_model_CModel.cpp$(DependSuffix): src/engine/renderer/model/CModel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_model_CModel.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_model_CModel.cpp$(DependSuffix) -MM src/engine/renderer/model/CModel.cpp

$(IntermediateDirectory)/src_engine_renderer_model_CModel.cpp$(PreprocessSuffix): src/engine/renderer/model/CModel.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_model_CModel.cpp$(PreprocessSuffix) src/engine/renderer/model/CModel.cpp

$(IntermediateDirectory)/src_engine_sound_CSoundSource.cpp$(ObjectSuffix): src/engine/sound/CSoundSource.cpp $(IntermediateDirectory)/src_engine_sound_CSoundSource.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/sound/CSoundSource.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_sound_CSoundSource.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_sound_CSoundSource.cpp$(DependSuffix): src/engine/sound/CSoundSource.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_sound_CSoundSource.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_sound_CSoundSource.cpp$(DependSuffix) -MM src/engine/sound/CSoundSource.cpp

$(IntermediateDirectory)/src_engine_sound_CSoundSource.cpp$(PreprocessSuffix): src/engine/sound/CSoundSource.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_sound_CSoundSource.cpp$(PreprocessSuffix) src/engine/sound/CSoundSource.cpp

$(IntermediateDirectory)/src_engine_sound_CSoundBufferCache.cpp$(ObjectSuffix): src/engine/sound/CSoundBufferCache.cpp $(IntermediateDirectory)/src_engine_sound_CSoundBufferCache.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/sound/CSoundBufferCache.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_sound_CSoundBufferCache.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_sound_CSoundBufferCache.cpp$(DependSuffix): src/engine/sound/CSoundBufferCache.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_sound_CSoundBufferCache.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_sound_CSoundBufferCache.cpp$(DependSuffix) -MM src/engine/sound/CSoundBufferCache.cpp

$(IntermediateDirectory)/src_engine_sound_CSoundBufferCache.cpp$(PreprocessSuffix): src/engine/sound/CSoundBufferCache.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_sound_CSoundBufferCache.cpp$(PreprocessSuffix) src/engine/sound/CSoundBufferCache.cpp

$(IntermediateDirectory)/src_engine_logger_CLogTargetFile.cpp$(ObjectSuffix): src/engine/logger/CLogTargetFile.cpp $(IntermediateDirectory)/src_engine_logger_CLogTargetFile.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/logger/CLogTargetFile.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_logger_CLogTargetFile.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_logger_CLogTargetFile.cpp$(DependSuffix): src/engine/logger/CLogTargetFile.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_logger_CLogTargetFile.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_logger_CLogTargetFile.cpp$(DependSuffix) -MM src/engine/logger/CLogTargetFile.cpp

$(IntermediateDirectory)/src_engine_logger_CLogTargetFile.cpp$(PreprocessSuffix): src/engine/logger/CLogTargetFile.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_logger_CLogTargetFile.cpp$(PreprocessSuffix) src/engine/logger/CLogTargetFile.cpp

$(IntermediateDirectory)/src_engine_states_CStateGame.cpp$(ObjectSuffix): src/engine/states/CStateGame.cpp $(IntermediateDirectory)/src_engine_states_CStateGame.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/states/CStateGame.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_states_CStateGame.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_states_CStateGame.cpp$(DependSuffix): src/engine/states/CStateGame.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_states_CStateGame.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_states_CStateGame.cpp$(DependSuffix) -MM src/engine/states/CStateGame.cpp

$(IntermediateDirectory)/src_engine_states_CStateGame.cpp$(PreprocessSuffix): src/engine/states/CStateGame.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_states_CStateGame.cpp$(PreprocessSuffix) src/engine/states/CStateGame.cpp

$(IntermediateDirectory)/src_engine_states_CStateIntro.cpp$(ObjectSuffix): src/engine/states/CStateIntro.cpp $(IntermediateDirectory)/src_engine_states_CStateIntro.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/states/CStateIntro.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_states_CStateIntro.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_states_CStateIntro.cpp$(DependSuffix): src/engine/states/CStateIntro.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_states_CStateIntro.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_states_CStateIntro.cpp$(DependSuffix) -MM src/engine/states/CStateIntro.cpp

$(IntermediateDirectory)/src_engine_states_CStateIntro.cpp$(PreprocessSuffix): src/engine/states/CStateIntro.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_states_CStateIntro.cpp$(PreprocessSuffix) src/engine/states/CStateIntro.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_qnx.c$(ObjectSuffix): src/ext/physfs/physfs_platform_qnx.c $(IntermediateDirectory)/src_ext_physfs_physfs_platform_qnx.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_platform_qnx.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_platform_qnx.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_platform_qnx.c$(DependSuffix): src/ext/physfs/physfs_platform_qnx.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_platform_qnx.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_platform_qnx.c$(DependSuffix) -MM src/ext/physfs/physfs_platform_qnx.c

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_qnx.c$(PreprocessSuffix): src/ext/physfs/physfs_platform_qnx.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_platform_qnx.c$(PreprocessSuffix) src/ext/physfs/physfs_platform_qnx.c

$(IntermediateDirectory)/src_engine_states_CState.cpp$(ObjectSuffix): src/engine/states/CState.cpp $(IntermediateDirectory)/src_engine_states_CState.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/states/CState.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_states_CState.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_states_CState.cpp$(DependSuffix): src/engine/states/CState.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_states_CState.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_states_CState.cpp$(DependSuffix) -MM src/engine/states/CState.cpp

$(IntermediateDirectory)/src_engine_states_CState.cpp$(PreprocessSuffix): src/engine/states/CState.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_states_CState.cpp$(PreprocessSuffix) src/engine/states/CState.cpp

$(IntermediateDirectory)/src_engine_states_CStateMainMenu.cpp$(ObjectSuffix): src/engine/states/CStateMainMenu.cpp $(IntermediateDirectory)/src_engine_states_CStateMainMenu.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/states/CStateMainMenu.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_states_CStateMainMenu.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_states_CStateMainMenu.cpp$(DependSuffix): src/engine/states/CStateMainMenu.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_states_CStateMainMenu.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_states_CStateMainMenu.cpp$(DependSuffix) -MM src/engine/states/CStateMainMenu.cpp

$(IntermediateDirectory)/src_engine_states_CStateMainMenu.cpp$(PreprocessSuffix): src/engine/states/CStateMainMenu.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_states_CStateMainMenu.cpp$(PreprocessSuffix) src/engine/states/CStateMainMenu.cpp

$(IntermediateDirectory)/src_engine_system_CFileSystem.cpp$(ObjectSuffix): src/engine/system/CFileSystem.cpp $(IntermediateDirectory)/src_engine_system_CFileSystem.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/system/CFileSystem.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_system_CFileSystem.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_system_CFileSystem.cpp$(DependSuffix): src/engine/system/CFileSystem.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_system_CFileSystem.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_system_CFileSystem.cpp$(DependSuffix) -MM src/engine/system/CFileSystem.cpp

$(IntermediateDirectory)/src_engine_system_CFileSystem.cpp$(PreprocessSuffix): src/engine/system/CFileSystem.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_system_CFileSystem.cpp$(PreprocessSuffix) src/engine/system/CFileSystem.cpp

$(IntermediateDirectory)/src_engine_sdl_CSDL.cpp$(ObjectSuffix): src/engine/sdl/CSDL.cpp $(IntermediateDirectory)/src_engine_sdl_CSDL.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/sdl/CSDL.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_sdl_CSDL.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_sdl_CSDL.cpp$(DependSuffix): src/engine/sdl/CSDL.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_sdl_CSDL.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_sdl_CSDL.cpp$(DependSuffix) -MM src/engine/sdl/CSDL.cpp

$(IntermediateDirectory)/src_engine_sdl_CSDL.cpp$(PreprocessSuffix): src/engine/sdl/CSDL.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_sdl_CSDL.cpp$(PreprocessSuffix) src/engine/sdl/CSDL.cpp

$(IntermediateDirectory)/src_ext_fmt_ostream.cc$(ObjectSuffix): src/ext/fmt/ostream.cc $(IntermediateDirectory)/src_ext_fmt_ostream.cc$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/fmt/ostream.cc" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_fmt_ostream.cc$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_fmt_ostream.cc$(DependSuffix): src/ext/fmt/ostream.cc
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_fmt_ostream.cc$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_fmt_ostream.cc$(DependSuffix) -MM src/ext/fmt/ostream.cc

$(IntermediateDirectory)/src_ext_fmt_ostream.cc$(PreprocessSuffix): src/ext/fmt/ostream.cc
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_fmt_ostream.cc$(PreprocessSuffix) src/ext/fmt/ostream.cc

$(IntermediateDirectory)/src_engine_renderer_texture_CTextureLoader.cpp$(ObjectSuffix): src/engine/renderer/texture/CTextureLoader.cpp $(IntermediateDirectory)/src_engine_renderer_texture_CTextureLoader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/texture/CTextureLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_texture_CTextureLoader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_texture_CTextureLoader.cpp$(DependSuffix): src/engine/renderer/texture/CTextureLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_texture_CTextureLoader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_texture_CTextureLoader.cpp$(DependSuffix) -MM src/engine/renderer/texture/CTextureLoader.cpp

$(IntermediateDirectory)/src_engine_renderer_texture_CTextureLoader.cpp$(PreprocessSuffix): src/engine/renderer/texture/CTextureLoader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_texture_CTextureLoader.cpp$(PreprocessSuffix) src/engine/renderer/texture/CTextureLoader.cpp

$(IntermediateDirectory)/src_engine_renderer_material_CMaterialCache.cpp$(ObjectSuffix): src/engine/renderer/material/CMaterialCache.cpp $(IntermediateDirectory)/src_engine_renderer_material_CMaterialCache.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/material/CMaterialCache.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_material_CMaterialCache.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_material_CMaterialCache.cpp$(DependSuffix): src/engine/renderer/material/CMaterialCache.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_material_CMaterialCache.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_material_CMaterialCache.cpp$(DependSuffix) -MM src/engine/renderer/material/CMaterialCache.cpp

$(IntermediateDirectory)/src_engine_renderer_material_CMaterialCache.cpp$(PreprocessSuffix): src/engine/renderer/material/CMaterialCache.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_material_CMaterialCache.cpp$(PreprocessSuffix) src/engine/renderer/material/CMaterialCache.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_dir.c$(ObjectSuffix): src/ext/physfs/physfs_archiver_dir.c $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_dir.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_archiver_dir.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_dir.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_dir.c$(DependSuffix): src/ext/physfs/physfs_archiver_dir.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_dir.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_dir.c$(DependSuffix) -MM src/ext/physfs/physfs_archiver_dir.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_dir.c$(PreprocessSuffix): src/ext/physfs/physfs_archiver_dir.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_dir.c$(PreprocessSuffix) src/ext/physfs/physfs_archiver_dir.c

$(IntermediateDirectory)/src_ext_imgui_imgui_draw.cpp$(ObjectSuffix): src/ext/imgui/imgui_draw.cpp $(IntermediateDirectory)/src_ext_imgui_imgui_draw.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/imgui/imgui_draw.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_imgui_imgui_draw.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_imgui_imgui_draw.cpp$(DependSuffix): src/ext/imgui/imgui_draw.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_imgui_imgui_draw.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_imgui_imgui_draw.cpp$(DependSuffix) -MM src/ext/imgui/imgui_draw.cpp

$(IntermediateDirectory)/src_ext_imgui_imgui_draw.cpp$(PreprocessSuffix): src/ext/imgui/imgui_draw.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_imgui_imgui_draw.cpp$(PreprocessSuffix) src/ext/imgui/imgui_draw.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs.c$(ObjectSuffix): src/ext/physfs/physfs.c $(IntermediateDirectory)/src_ext_physfs_physfs.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs.c$(DependSuffix): src/ext/physfs/physfs.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs.c$(DependSuffix) -MM src/ext/physfs/physfs.c

$(IntermediateDirectory)/src_ext_physfs_physfs.c$(PreprocessSuffix): src/ext/physfs/physfs.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs.c$(PreprocessSuffix) src/ext/physfs/physfs.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_iso9660.c$(ObjectSuffix): src/ext/physfs/physfs_archiver_iso9660.c $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_iso9660.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_archiver_iso9660.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_iso9660.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_iso9660.c$(DependSuffix): src/ext/physfs/physfs_archiver_iso9660.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_iso9660.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_iso9660.c$(DependSuffix) -MM src/ext/physfs/physfs_archiver_iso9660.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_iso9660.c$(PreprocessSuffix): src/ext/physfs/physfs_archiver_iso9660.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_iso9660.c$(PreprocessSuffix) src/ext/physfs/physfs_archiver_iso9660.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_unpacked.c$(ObjectSuffix): src/ext/physfs/physfs_archiver_unpacked.c $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_unpacked.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_archiver_unpacked.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_unpacked.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_unpacked.c$(DependSuffix): src/ext/physfs/physfs_archiver_unpacked.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_unpacked.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_unpacked.c$(DependSuffix) -MM src/ext/physfs/physfs_archiver_unpacked.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_unpacked.c$(PreprocessSuffix): src/ext/physfs/physfs_archiver_unpacked.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_unpacked.c$(PreprocessSuffix) src/ext/physfs/physfs_archiver_unpacked.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_wad.c$(ObjectSuffix): src/ext/physfs/physfs_archiver_wad.c $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_wad.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_archiver_wad.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_wad.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_wad.c$(DependSuffix): src/ext/physfs/physfs_archiver_wad.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_wad.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_wad.c$(DependSuffix) -MM src/ext/physfs/physfs_archiver_wad.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_wad.c$(PreprocessSuffix): src/ext/physfs/physfs_archiver_wad.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_wad.c$(PreprocessSuffix) src/ext/physfs/physfs_archiver_wad.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_zip.c$(ObjectSuffix): src/ext/physfs/physfs_archiver_zip.c $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_zip.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_archiver_zip.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_zip.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_zip.c$(DependSuffix): src/ext/physfs/physfs_archiver_zip.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_zip.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_zip.c$(DependSuffix) -MM src/ext/physfs/physfs_archiver_zip.c

$(IntermediateDirectory)/src_ext_physfs_physfs_archiver_zip.c$(PreprocessSuffix): src/ext/physfs/physfs_archiver_zip.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_archiver_zip.c$(PreprocessSuffix) src/ext/physfs/physfs_archiver_zip.c

$(IntermediateDirectory)/src_ext_physfs_physfs_byteorder.c$(ObjectSuffix): src/ext/physfs/physfs_byteorder.c $(IntermediateDirectory)/src_ext_physfs_physfs_byteorder.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_byteorder.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_byteorder.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_byteorder.c$(DependSuffix): src/ext/physfs/physfs_byteorder.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_byteorder.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_byteorder.c$(DependSuffix) -MM src/ext/physfs/physfs_byteorder.c

$(IntermediateDirectory)/src_ext_physfs_physfs_byteorder.c$(PreprocessSuffix): src/ext/physfs/physfs_byteorder.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_byteorder.c$(PreprocessSuffix) src/ext/physfs/physfs_byteorder.c

$(IntermediateDirectory)/src_engine_resource_CResourceCacheManager.cpp$(ObjectSuffix): src/engine/resource/CResourceCacheManager.cpp $(IntermediateDirectory)/src_engine_resource_CResourceCacheManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/resource/CResourceCacheManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_resource_CResourceCacheManager.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_resource_CResourceCacheManager.cpp$(DependSuffix): src/engine/resource/CResourceCacheManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_resource_CResourceCacheManager.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_resource_CResourceCacheManager.cpp$(DependSuffix) -MM src/engine/resource/CResourceCacheManager.cpp

$(IntermediateDirectory)/src_engine_resource_CResourceCacheManager.cpp$(PreprocessSuffix): src/engine/resource/CResourceCacheManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_resource_CResourceCacheManager.cpp$(PreprocessSuffix) src/engine/resource/CResourceCacheManager.cpp

$(IntermediateDirectory)/src_engine_renderer_material_CMaterialUniform.cpp$(ObjectSuffix): src/engine/renderer/material/CMaterialUniform.cpp $(IntermediateDirectory)/src_engine_renderer_material_CMaterialUniform.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/material/CMaterialUniform.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_material_CMaterialUniform.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_material_CMaterialUniform.cpp$(DependSuffix): src/engine/renderer/material/CMaterialUniform.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_material_CMaterialUniform.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_material_CMaterialUniform.cpp$(DependSuffix) -MM src/engine/renderer/material/CMaterialUniform.cpp

$(IntermediateDirectory)/src_engine_renderer_material_CMaterialUniform.cpp$(PreprocessSuffix): src/engine/renderer/material/CMaterialUniform.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_material_CMaterialUniform.cpp$(PreprocessSuffix) src/engine/renderer/material/CMaterialUniform.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_unix.c$(ObjectSuffix): src/ext/physfs/physfs_platform_unix.c $(IntermediateDirectory)/src_ext_physfs_physfs_platform_unix.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_platform_unix.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_platform_unix.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_platform_unix.c$(DependSuffix): src/ext/physfs/physfs_platform_unix.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_platform_unix.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_platform_unix.c$(DependSuffix) -MM src/ext/physfs/physfs_platform_unix.c

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_unix.c$(PreprocessSuffix): src/ext/physfs/physfs_platform_unix.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_platform_unix.c$(PreprocessSuffix) src/ext/physfs/physfs_platform_unix.c

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_winrt.cpp$(ObjectSuffix): src/ext/physfs/physfs_platform_winrt.cpp $(IntermediateDirectory)/src_ext_physfs_physfs_platform_winrt.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_platform_winrt.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_platform_winrt.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_platform_winrt.cpp$(DependSuffix): src/ext/physfs/physfs_platform_winrt.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_platform_winrt.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_platform_winrt.cpp$(DependSuffix) -MM src/ext/physfs/physfs_platform_winrt.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_winrt.cpp$(PreprocessSuffix): src/ext/physfs/physfs_platform_winrt.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_platform_winrt.cpp$(PreprocessSuffix) src/ext/physfs/physfs_platform_winrt.cpp

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_windows.c$(ObjectSuffix): src/ext/physfs/physfs_platform_windows.c $(IntermediateDirectory)/src_ext_physfs_physfs_platform_windows.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/ext/physfs/physfs_platform_windows.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_ext_physfs_physfs_platform_windows.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_ext_physfs_physfs_platform_windows.c$(DependSuffix): src/ext/physfs/physfs_platform_windows.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_ext_physfs_physfs_platform_windows.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_ext_physfs_physfs_platform_windows.c$(DependSuffix) -MM src/ext/physfs/physfs_platform_windows.c

$(IntermediateDirectory)/src_ext_physfs_physfs_platform_windows.c$(PreprocessSuffix): src/ext/physfs/physfs_platform_windows.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_ext_physfs_physfs_platform_windows.c$(PreprocessSuffix) src/ext/physfs/physfs_platform_windows.c

$(IntermediateDirectory)/src_engine_renderer_material_CMaterial.cpp$(ObjectSuffix): src/engine/renderer/material/CMaterial.cpp $(IntermediateDirectory)/src_engine_renderer_material_CMaterial.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/material/CMaterial.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_material_CMaterial.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_material_CMaterial.cpp$(DependSuffix): src/engine/renderer/material/CMaterial.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_material_CMaterial.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_material_CMaterial.cpp$(DependSuffix) -MM src/engine/renderer/material/CMaterial.cpp

$(IntermediateDirectory)/src_engine_renderer_material_CMaterial.cpp$(PreprocessSuffix): src/engine/renderer/material/CMaterial.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_material_CMaterial.cpp$(PreprocessSuffix) src/engine/renderer/material/CMaterial.cpp

$(IntermediateDirectory)/src_engine_scene_CTransform.cpp$(ObjectSuffix): src/engine/scene/CTransform.cpp $(IntermediateDirectory)/src_engine_scene_CTransform.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/scene/CTransform.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_scene_CTransform.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_scene_CTransform.cpp$(DependSuffix): src/engine/scene/CTransform.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_scene_CTransform.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_scene_CTransform.cpp$(DependSuffix) -MM src/engine/scene/CTransform.cpp

$(IntermediateDirectory)/src_engine_scene_CTransform.cpp$(PreprocessSuffix): src/engine/scene/CTransform.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_scene_CTransform.cpp$(PreprocessSuffix) src/engine/scene/CTransform.cpp

$(IntermediateDirectory)/src_engine_renderer_material_CMaterialLoader.cpp$(ObjectSuffix): src/engine/renderer/material/CMaterialLoader.cpp $(IntermediateDirectory)/src_engine_renderer_material_CMaterialLoader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/material/CMaterialLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_material_CMaterialLoader.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_material_CMaterialLoader.cpp$(DependSuffix): src/engine/renderer/material/CMaterialLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_material_CMaterialLoader.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_material_CMaterialLoader.cpp$(DependSuffix) -MM src/engine/renderer/material/CMaterialLoader.cpp

$(IntermediateDirectory)/src_engine_renderer_material_CMaterialLoader.cpp$(PreprocessSuffix): src/engine/renderer/material/CMaterialLoader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_material_CMaterialLoader.cpp$(PreprocessSuffix) src/engine/renderer/material/CMaterialLoader.cpp

$(IntermediateDirectory)/src_engine_renderer_texture_CTexture.cpp$(ObjectSuffix): src/engine/renderer/texture/CTexture.cpp $(IntermediateDirectory)/src_engine_renderer_texture_CTexture.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/texture/CTexture.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_texture_CTexture.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_texture_CTexture.cpp$(DependSuffix): src/engine/renderer/texture/CTexture.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_texture_CTexture.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_texture_CTexture.cpp$(DependSuffix) -MM src/engine/renderer/texture/CTexture.cpp

$(IntermediateDirectory)/src_engine_renderer_texture_CTexture.cpp$(PreprocessSuffix): src/engine/renderer/texture/CTexture.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_texture_CTexture.cpp$(PreprocessSuffix) src/engine/renderer/texture/CTexture.cpp

$(IntermediateDirectory)/src_engine_renderer_texture_C2DArrayData.cpp$(ObjectSuffix): src/engine/renderer/texture/C2DArrayData.cpp $(IntermediateDirectory)/src_engine_renderer_texture_C2DArrayData.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/charon/Projekte/styx/styx/src/engine/renderer/texture/C2DArrayData.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_engine_renderer_texture_C2DArrayData.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_engine_renderer_texture_C2DArrayData.cpp$(DependSuffix): src/engine/renderer/texture/C2DArrayData.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_engine_renderer_texture_C2DArrayData.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_engine_renderer_texture_C2DArrayData.cpp$(DependSuffix) -MM src/engine/renderer/texture/C2DArrayData.cpp

$(IntermediateDirectory)/src_engine_renderer_texture_C2DArrayData.cpp$(PreprocessSuffix): src/engine/renderer/texture/C2DArrayData.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_engine_renderer_texture_C2DArrayData.cpp$(PreprocessSuffix) src/engine/renderer/texture/C2DArrayData.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./bin/Debug/


