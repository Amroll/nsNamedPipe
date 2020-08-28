# nsNamedPipe
NSIS r/w NamedPipeLine Plugin

# How to use
1. Build project with *release ANSI* 
2. copy "Release/nsNamedPipe.dll" to NSIS InstallDir/x86-ansi
3. Add NSIS Script
```NSIS
  nsNamedPipe::ReadNamedPipe "\\.\pipe\PipeName" "SendContent"
  MessageBox MB_OK $0
  ;$0 = 0 Read Error
```
