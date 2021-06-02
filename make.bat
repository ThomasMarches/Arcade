if not exist "build\" (
    cmake -B build -DFETCH_DEPENDENCIES=True -DCMAKE_BUILD_TYPE=Release
)
cmake --build build --config Release
xcopy /Y /s "dependencies\lib\x64\*.dll" ".\"