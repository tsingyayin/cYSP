import sys
import os
ProjectName = "Visindigo"

def copyAllHeadFiles(path):
    """Step1: copy all head files to the include folder"""
    RootFolder = path+"\\"+ProjectName
    NewFileFolderDebugRoot = path+"\\x64\\DllDebug\\"+ProjectName
    NewFileFolderReleaseRoot = path+"\\x64\\DllRelease\\"+ProjectName
    #clear old files
    if os.path.exists(NewFileFolderDebugRoot):
        os.system("rd /s /q "+NewFileFolderDebugRoot)
    if os.path.exists(NewFileFolderReleaseRoot):
        os.system("rd /s /q "+NewFileFolderReleaseRoot)
    #copy new files
    for root, dirs, files in os.walk(RootFolder):
        for file in files:
            if file.endswith(".h"):
                RawFilePath = root+"\\"+file
                NewFileFolderDebug = path+"\\x64\\DllDebug\\"+ProjectName+"\\include\\"+os.path.relpath(root, RootFolder)
                NewFileFolderRelease = path+"\\x64\\DllRelease\\"+ProjectName+"\\include\\"+os.path.relpath(root, RootFolder)
                print(RawFilePath)
                if not os.path.exists(NewFileFolderDebug):
                    os.makedirs(NewFileFolderDebug)
                    print("mkdir "+NewFileFolderDebug)
                if not os.path.exists(NewFileFolderRelease):
                    os.makedirs(NewFileFolderRelease)
                    print("mkdir "+NewFileFolderRelease)
                os.system("copy "+RawFilePath+" "+NewFileFolderDebug+"\\"+file)
                os.system("copy "+RawFilePath+" "+NewFileFolderRelease+"\\"+file)
    
def createModuleHeadFiles(path):
    """Step2: create module head files"""
    RootFolder = path+"\\Visindigo"
    NewFileFolderDebugRoot = path+"\\x64\\DllDebug\\"+ProjectName+"\\include"
    NewFileFolderReleaseRoot = path+"\\x64\\DllRelease\\"+ProjectName+"\\include"
    NewFileFolderDebugModuleRoot = path+"\\x64\\DllDebug\\"+ProjectName
    NewFileFolderReleaseModuleRoot = path+"\\x64\\DllRelease\\"+ProjectName
    RootModule = os.listdir(NewFileFolderDebugRoot)
    ModuleNames = []
    for i in RootModule:
        if "." not in i:
            ModuleNames.append(i)
    for i in ModuleNames:
        ModuleHeadFile = NewFileFolderDebugModuleRoot+"\\"+i
        f = open(ModuleHeadFile, "w")
        f.write("#pragma once\n")
        f.write("#include \"include/"+i+"/"+i+".h\"\n")
        f.close()
    for i in ModuleNames:
        ModuleHeadFile = NewFileFolderReleaseModuleRoot+"\\"+i
        f = open(ModuleHeadFile, "w")
        f.write("#pragma once\n")
        f.write("#include \"include/"+i+"/"+i+".h\"\n")
        f.close()



if __name__ == "__main__":
    path:str = sys.path[0]
    pName:str = sys.argv[1]
    ProjectName = pName
    print("Current Project Name is: "+pName)
    print(path)
    os.chdir(path+"/../../")
    path = os.getcwd()
    copyAllHeadFiles(path)
    createModuleHeadFiles(path)



