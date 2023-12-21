@echo off
cd cpp_projects

for /D %%d in (*) do (
    cd %%d
    if not exist windows mkdir windows
    if not exist unix mkdir unix
    if exist *.cpp (
        g++ -o windows\%%d.exe %%d.cpp
    )
    if exist *-runnable (
        move *-runnable unix\%%d-runnable
    )
    cd ..
)

echo Compilation and organization complete.