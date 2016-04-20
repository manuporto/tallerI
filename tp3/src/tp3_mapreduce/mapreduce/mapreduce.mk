##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=mapreduce
ConfigurationName      :=Release
WorkspacePath          := "/home/montag/Documents/tallerI/tp3/src/tp3_mapreduce"
ProjectPath            := "/home/montag/Documents/tallerI/tp3/src/tp3_mapreduce/mapreduce"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=04/19/16
CodeLitePath           :="/home/montag/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="mapreduce.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/client_main.cpp$(ObjectSuffix) $(IntermediateDirectory)/common_socket.cpp$(ObjectSuffix) $(IntermediateDirectory)/client_client.cpp$(ObjectSuffix) $(IntermediateDirectory)/server_server.cpp$(ObjectSuffix) $(IntermediateDirectory)/server_thread.cpp$(ObjectSuffix) $(IntermediateDirectory)/server_mutex.cpp$(ObjectSuffix) $(IntermediateDirectory)/server_main.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Release || $(MakeDirCommand) ./Release


$(IntermediateDirectory)/.d:
	@test -d ./Release || $(MakeDirCommand) ./Release

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/client_main.cpp$(ObjectSuffix): ../../client_main.cpp $(IntermediateDirectory)/client_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/montag/Documents/tallerI/tp3/src/client_main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/client_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/client_main.cpp$(DependSuffix): ../../client_main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/client_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/client_main.cpp$(DependSuffix) -MM "../../client_main.cpp"

$(IntermediateDirectory)/client_main.cpp$(PreprocessSuffix): ../../client_main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/client_main.cpp$(PreprocessSuffix) "../../client_main.cpp"

$(IntermediateDirectory)/common_socket.cpp$(ObjectSuffix): ../../common_socket.cpp $(IntermediateDirectory)/common_socket.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/montag/Documents/tallerI/tp3/src/common_socket.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/common_socket.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/common_socket.cpp$(DependSuffix): ../../common_socket.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/common_socket.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/common_socket.cpp$(DependSuffix) -MM "../../common_socket.cpp"

$(IntermediateDirectory)/common_socket.cpp$(PreprocessSuffix): ../../common_socket.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/common_socket.cpp$(PreprocessSuffix) "../../common_socket.cpp"

$(IntermediateDirectory)/client_client.cpp$(ObjectSuffix): ../../client_client.cpp $(IntermediateDirectory)/client_client.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/montag/Documents/tallerI/tp3/src/client_client.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/client_client.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/client_client.cpp$(DependSuffix): ../../client_client.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/client_client.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/client_client.cpp$(DependSuffix) -MM "../../client_client.cpp"

$(IntermediateDirectory)/client_client.cpp$(PreprocessSuffix): ../../client_client.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/client_client.cpp$(PreprocessSuffix) "../../client_client.cpp"

$(IntermediateDirectory)/server_server.cpp$(ObjectSuffix): ../../server_server.cpp $(IntermediateDirectory)/server_server.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/montag/Documents/tallerI/tp3/src/server_server.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server_server.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server_server.cpp$(DependSuffix): ../../server_server.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server_server.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/server_server.cpp$(DependSuffix) -MM "../../server_server.cpp"

$(IntermediateDirectory)/server_server.cpp$(PreprocessSuffix): ../../server_server.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server_server.cpp$(PreprocessSuffix) "../../server_server.cpp"

$(IntermediateDirectory)/server_thread.cpp$(ObjectSuffix): ../../server_thread.cpp $(IntermediateDirectory)/server_thread.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/montag/Documents/tallerI/tp3/src/server_thread.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server_thread.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server_thread.cpp$(DependSuffix): ../../server_thread.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server_thread.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/server_thread.cpp$(DependSuffix) -MM "../../server_thread.cpp"

$(IntermediateDirectory)/server_thread.cpp$(PreprocessSuffix): ../../server_thread.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server_thread.cpp$(PreprocessSuffix) "../../server_thread.cpp"

$(IntermediateDirectory)/server_mutex.cpp$(ObjectSuffix): ../../server_mutex.cpp $(IntermediateDirectory)/server_mutex.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/montag/Documents/tallerI/tp3/src/server_mutex.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server_mutex.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server_mutex.cpp$(DependSuffix): ../../server_mutex.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server_mutex.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/server_mutex.cpp$(DependSuffix) -MM "../../server_mutex.cpp"

$(IntermediateDirectory)/server_mutex.cpp$(PreprocessSuffix): ../../server_mutex.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server_mutex.cpp$(PreprocessSuffix) "../../server_mutex.cpp"

$(IntermediateDirectory)/server_main.cpp$(ObjectSuffix): ../../server_main.cpp $(IntermediateDirectory)/server_main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/montag/Documents/tallerI/tp3/src/server_main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/server_main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/server_main.cpp$(DependSuffix): ../../server_main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/server_main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/server_main.cpp$(DependSuffix) -MM "../../server_main.cpp"

$(IntermediateDirectory)/server_main.cpp$(PreprocessSuffix): ../../server_main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/server_main.cpp$(PreprocessSuffix) "../../server_main.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Release/


