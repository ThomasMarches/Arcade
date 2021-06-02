@REM cmake
rmdir /s /q build
rmdir /s /q dependencies\build dependencies\include dependencies\lib dependencies\bin dependencies\share
rmdir /s /q Debug
rmdir /s /q Release

@REM bin
del /q arcade
del /s /q *.exe

@REM data
del /s /q save.txt

@REM libs
del /s /q lib\*.so
del /s /q lib\*.dylib
del /s /q lib\*.dll
del /s /q *.dll

@REM debug
del /s /q *.ilk
del /s /q *.pdb

@REM debug
del /s /q unit_tests