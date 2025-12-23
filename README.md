# Raylib

Duplico la carpeta raylib en raylib-web y raylib-desktop.
C:\cpp\lib\raylib-desktop\w64devkit\bin debe estar en el path.


## Compilo libraylib.a para desktop

```
> cd C:\cpp\lib\raylib-desktop\raylib\src
> mingw32-make.exe clean
> mingw32-make.exe PLATFORM=PLATFORM_DESKTOP
```


## Compilo libraylib.a para web

```
> cd C:\cpp\lib\raylib-web
> emsdk\emsdk_env.bat
> cd raylib\src
> emmake make clean
> emmake make PLATFORM=PLATFORM_WEB
```
