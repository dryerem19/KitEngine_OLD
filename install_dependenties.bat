git clone https://github.com/microsoft/vcpkg
call .\vcpkg\bootstrap-vcpkg.bat
.\vcpkg\vcpkg.exe install glew:x64-windows
.\vcpkg\vcpkg.exe install glfw3:x64-windows
.\vcpkg\vcpkg.exe  install imgui[docking-experimental,glfw-binding,opengl3-binding]:x64-windows
.\vcpkg\vcpkg.exe install imguizmo:x64-windows
.\vcpkg\vcpkg.exe install entt:x64-windows
.\vcpkg\vcpkg.exe install bullet3:x64-windows
.\vcpkg\vcpkg.exe install assimp:x64-windows