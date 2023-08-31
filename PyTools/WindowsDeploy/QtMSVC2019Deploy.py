
class QtMSVC2019Deploy:
    Command:str
    QtHost:str
    ProgramPath:str
    def __init__(this):
        this.Command = "C:\\Windows\\System32\\cmd.exe /A /Q /K __QTHOST__\\msvc2019_64\\bin\\qtenv2.bat"
        this.QtHost = "D:\\Qt5.15\\5.15.2"
