Package: glfw3:x64-windows@3.4#1

**Host Environment**

- Host: x64-windows
- Compiler: Clang 20.1.8
- CMake Version: 4.1.1-msvc1
-    vcpkg-tool version: 2025-09-03-4580816534ed8fd9634ac83d46471440edd82dfe
    vcpkg-readonly: true
    vcpkg-scripts version: b1b19307e2d2ec1eefbdb7ea069de7d4bcd31f01

**To Reproduce**

`vcpkg install `

**Failure logs**

```
Downloading https://github.com/glfw/glfw/archive/3.4.tar.gz -> glfw-glfw-3.4.tar.gz
Successfully downloaded glfw-glfw-3.4.tar.gz
-- Extracting source C:/Users/janos/AppData/Local/vcpkg/downloads/glfw-glfw-3.4.tar.gz
-- Using source at C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/src/3.4-2448ff4533.clean
-- Found external ninja('1.12.1').
-- Configuring x64-windows
CMake Error at scripts/cmake/vcpkg_execute_required_process.cmake:127 (message):
    Command failed: "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" -v
    Working Directory: C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel/vcpkg-parallel-configure
    Error code: 1
    See logs for more information:
      C:\Users\janos\source\repos\TileHexaV3\vcpkg_installed\vcpkg\blds\glfw3\config-x64-windows-dbg-CMakeCache.txt.log
      C:\Users\janos\source\repos\TileHexaV3\vcpkg_installed\vcpkg\blds\glfw3\config-x64-windows-rel-CMakeCache.txt.log
      C:\Users\janos\source\repos\TileHexaV3\vcpkg_installed\vcpkg\blds\glfw3\config-x64-windows-dbg-CMakeConfigureLog.yaml.log
      C:\Users\janos\source\repos\TileHexaV3\vcpkg_installed\vcpkg\blds\glfw3\config-x64-windows-rel-CMakeConfigureLog.yaml.log
      C:\Users\janos\source\repos\TileHexaV3\vcpkg_installed\vcpkg\blds\glfw3\config-x64-windows-out.log

Call Stack (most recent call first):
  C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/share/vcpkg-cmake/vcpkg_cmake_configure.cmake:269 (vcpkg_execute_required_process)
  C:/Users/janos/AppData/Local/vcpkg/registries/git-trees/d4bbd4f27c2ca619f57778985120cddcedadb1cc/portfile.cmake:38 (vcpkg_cmake_configure)
  scripts/ports.cmake:206 (include)



```

<details><summary>C:\Users\janos\source\repos\TileHexaV3\vcpkg_installed\vcpkg\blds\glfw3\config-x64-windows-out.log</summary>

```
[1/2] "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" -E chdir "../../x64-windows-dbg" "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/src/3.4-2448ff4533.clean" "-G" "Ninja" "-DCMAKE_BUILD_TYPE=Debug" "-DCMAKE_INSTALL_PREFIX=C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/pkgs/glfw3_x64-windows/debug" "-DFETCHCONTENT_FULLY_DISCONNECTED=ON" "-DGLFW_BUILD_EXAMPLES=OFF" "-DGLFW_BUILD_TESTS=OFF" "-DGLFW_BUILD_DOCS=OFF" "-DGLFW_BUILD_WAYLAND=OFF" "-DCMAKE_MAKE_PROGRAM=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" "-DBUILD_SHARED_LIBS=ON" "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows" "-DVCPKG_SET_CHARSET_FLAG=ON" "-DVCPKG_PLATFORM_TOOLSET=v143" "-DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=ON" "-DCMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP=TRUE" "-DCMAKE_VERBOSE_MAKEFILE=ON" "-DVCPKG_APPLOCAL_DEPS=OFF" "-DCMAKE_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION=ON" "-DVCPKG_CXX_FLAGS=" "-DVCPKG_CXX_FLAGS_RELEASE=" "-DVCPKG_CXX_FLAGS_DEBUG=" "-DVCPKG_C_FLAGS=" "-DVCPKG_C_FLAGS_RELEASE=" "-DVCPKG_C_FLAGS_DEBUG=" "-DVCPKG_CRT_LINKAGE=dynamic" "-DVCPKG_LINKER_FLAGS=" "-DVCPKG_LINKER_FLAGS_RELEASE=" "-DVCPKG_LINKER_FLAGS_DEBUG=" "-DVCPKG_TARGET_ARCHITECTURE=x64" "-DCMAKE_INSTALL_LIBDIR:STRING=lib" "-DCMAKE_INSTALL_BINDIR:STRING=bin" "-D_VCPKG_ROOT_DIR=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg" "-D_VCPKG_INSTALLED_DIR=C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed" "-DVCPKG_MANIFEST_INSTALL=OFF"
FAILED: ../../x64-windows-dbg/CMakeCache.txt 
...
Skipped 21 lines
...
    clang: error: no such file or directory: '/nologo'
    clang: error: no such file or directory: '/DWIN32'
    clang: error: no such file or directory: '/D_WINDOWS'
    clang: error: no such file or directory: '/utf-8'
    clang: error: no such file or directory: '/MP'
    clang: error: no such file or directory: '/MDd'
    clang: error: no such file or directory: '/Z7'
    clang: error: no such file or directory: '/Ob0'
    clang: error: no such file or directory: '/Od'
    clang: error: no such file or directory: '/RTC1'
    ninja: build stopped: subcommand failed.
    
    



  CMake will not be able to correctly generate this project.
Call Stack (most recent call first):
  CMakeLists.txt:3 (project)


-- Configuring incomplete, errors occurred!
[2/2] "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" -E chdir ".." "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/src/3.4-2448ff4533.clean" "-G" "Ninja" "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_INSTALL_PREFIX=C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/pkgs/glfw3_x64-windows" "-DFETCHCONTENT_FULLY_DISCONNECTED=ON" "-DGLFW_BUILD_EXAMPLES=OFF" "-DGLFW_BUILD_TESTS=OFF" "-DGLFW_BUILD_DOCS=OFF" "-DGLFW_BUILD_WAYLAND=OFF" "-DCMAKE_MAKE_PROGRAM=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" "-DBUILD_SHARED_LIBS=ON" "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows" "-DVCPKG_SET_CHARSET_FLAG=ON" "-DVCPKG_PLATFORM_TOOLSET=v143" "-DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=ON" "-DCMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP=TRUE" "-DCMAKE_VERBOSE_MAKEFILE=ON" "-DVCPKG_APPLOCAL_DEPS=OFF" "-DCMAKE_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION=ON" "-DVCPKG_CXX_FLAGS=" "-DVCPKG_CXX_FLAGS_RELEASE=" "-DVCPKG_CXX_FLAGS_DEBUG=" "-DVCPKG_C_FLAGS=" "-DVCPKG_C_FLAGS_RELEASE=" "-DVCPKG_C_FLAGS_DEBUG=" "-DVCPKG_CRT_LINKAGE=dynamic" "-DVCPKG_LINKER_FLAGS=" "-DVCPKG_LINKER_FLAGS_RELEASE=" "-DVCPKG_LINKER_FLAGS_DEBUG=" "-DVCPKG_TARGET_ARCHITECTURE=x64" "-DCMAKE_INSTALL_LIBDIR:STRING=lib" "-DCMAKE_INSTALL_BINDIR:STRING=bin" "-D_VCPKG_ROOT_DIR=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg" "-D_VCPKG_INSTALLED_DIR=C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed" "-DVCPKG_MANIFEST_INSTALL=OFF"
FAILED: ../CMakeCache.txt 
"C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" -E chdir ".." "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe" "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/src/3.4-2448ff4533.clean" "-G" "Ninja" "-DCMAKE_BUILD_TYPE=Release" "-DCMAKE_INSTALL_PREFIX=C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/pkgs/glfw3_x64-windows" "-DFETCHCONTENT_FULLY_DISCONNECTED=ON" "-DGLFW_BUILD_EXAMPLES=OFF" "-DGLFW_BUILD_TESTS=OFF" "-DGLFW_BUILD_DOCS=OFF" "-DGLFW_BUILD_WAYLAND=OFF" "-DCMAKE_MAKE_PROGRAM=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" "-DBUILD_SHARED_LIBS=ON" "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake" "-DVCPKG_TARGET_TRIPLET=x64-windows" "-DVCPKG_SET_CHARSET_FLAG=ON" "-DVCPKG_PLATFORM_TOOLSET=v143" "-DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON" "-DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=ON" "-DCMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP=TRUE" "-DCMAKE_VERBOSE_MAKEFILE=ON" "-DVCPKG_APPLOCAL_DEPS=OFF" "-DCMAKE_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake" "-DCMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION=ON" "-DVCPKG_CXX_FLAGS=" "-DVCPKG_CXX_FLAGS_RELEASE=" "-DVCPKG_CXX_FLAGS_DEBUG=" "-DVCPKG_C_FLAGS=" "-DVCPKG_C_FLAGS_RELEASE=" "-DVCPKG_C_FLAGS_DEBUG=" "-DVCPKG_CRT_LINKAGE=dynamic" "-DVCPKG_LINKER_FLAGS=" "-DVCPKG_LINKER_FLAGS_RELEASE=" "-DVCPKG_LINKER_FLAGS_DEBUG=" "-DVCPKG_TARGET_ARCHITECTURE=x64" "-DCMAKE_INSTALL_LIBDIR:STRING=lib" "-DCMAKE_INSTALL_BINDIR:STRING=bin" "-D_VCPKG_ROOT_DIR=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg" "-D_VCPKG_INSTALLED_DIR=C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed" "-DVCPKG_MANIFEST_INSTALL=OFF"
-- The C compiler identification is Clang 20.1.8 with GNU-like command-line
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - failed
-- Check for working C compiler: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/clang.exe
-- Check for working C compiler: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/clang.exe - broken
CMake Error at C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeTestCCompiler.cmake:67 (message):
  The C compiler

    "C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/clang.exe"

  is not able to compile a simple test program.

  It fails with the following output:

    Change Dir: 'C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-twt51n'
    
    Run Build Command(s): "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" -v cmTC_d84f9
    [1/2] C:\PROGRA~1\MICROS~4\18\COMMUN~1\VC\Tools\Llvm\x64\bin\clang.exe   /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -D_DEBUG -D_DLL -D_MT -Xclang --dependent-lib=msvcrtd -MD -MT CMakeFiles/cmTC_d84f9.dir/testCCompiler.c.obj -MF CMakeFiles\cmTC_d84f9.dir\testCCompiler.c.obj.d -o CMakeFiles/cmTC_d84f9.dir/testCCompiler.c.obj -c C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-twt51n/testCCompiler.c
    FAILED: CMakeFiles/cmTC_d84f9.dir/testCCompiler.c.obj 
    C:\PROGRA~1\MICROS~4\18\COMMUN~1\VC\Tools\Llvm\x64\bin\clang.exe   /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -D_DEBUG -D_DLL -D_MT -Xclang --dependent-lib=msvcrtd -MD -MT CMakeFiles/cmTC_d84f9.dir/testCCompiler.c.obj -MF CMakeFiles\cmTC_d84f9.dir\testCCompiler.c.obj.d -o CMakeFiles/cmTC_d84f9.dir/testCCompiler.c.obj -c C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-twt51n/testCCompiler.c
    clang: error: no such file or directory: '/nologo'
    clang: error: no such file or directory: '/DWIN32'
    clang: error: no such file or directory: '/D_WINDOWS'
    clang: error: no such file or directory: '/utf-8'
    clang: error: no such file or directory: '/MP'
    clang: error: no such file or directory: '/MDd'
    clang: error: no such file or directory: '/Z7'
    clang: error: no such file or directory: '/Ob0'
    clang: error: no such file or directory: '/Od'
    clang: error: no such file or directory: '/RTC1'
    ninja: build stopped: subcommand failed.
    
    



  CMake will not be able to correctly generate this project.
Call Stack (most recent call first):
  CMakeLists.txt:3 (project)


-- Configuring incomplete, errors occurred!
ninja: build stopped: subcommand failed.
```
</details>

<details><summary>C:\Users\janos\source\repos\TileHexaV3\vcpkg_installed\vcpkg\blds\glfw3\config-x64-windows-rel-CMakeCache.txt.log</summary>

```
# This is the CMakeCache file.
# For build in directory: c:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel
# It was generated by CMake: C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe
# You can edit this file to change values found and used by cmake.
# If you do not want to change any of the values, simply exit the editor.
# If you do want to change a value, simply edit, save, and exit the editor.
# The syntax for the file is as follows:
# KEY:TYPE=VALUE
# KEY is the name of a variable in the cache.
# TYPE is a hint to GUIs for the type of VALUE, DO NOT EDIT TYPE!.
# VALUE is the current value for the KEY.

########################
# EXTERNAL cache entries
########################

//No help, variable specified on the command line.
BUILD_SHARED_LIBS:UNINITIALIZED=ON

//Path to a program.
CMAKE_ADDR2LINE:FILEPATH=CMAKE_ADDR2LINE-NOTFOUND

//Path to a program.
CMAKE_AR:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/llvm-ar.exe

//Choose the type of build, options are: None Debug Release RelWithDebInfo
// MinSizeRel ...
CMAKE_BUILD_TYPE:STRING=Release

CMAKE_CROSSCOMPILING:STRING=OFF

CMAKE_CXX_FLAGS:STRING=' /nologo /DWIN32 /D_WINDOWS /utf-8 /GR /EHsc /MP '

CMAKE_CXX_FLAGS_DEBUG:STRING='/MDd /Z7 /Ob0 /Od /RTC1 '

CMAKE_CXX_FLAGS_RELEASE:STRING='/MD /O2 /Oi /Gy /DNDEBUG /Z7 '

//C compiler
CMAKE_C_COMPILER:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/clang.exe

//LLVM archiver
CMAKE_C_COMPILER_AR:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/llvm-ar.exe

//`clang-scan-deps` dependency scanner
CMAKE_C_COMPILER_CLANG_SCAN_DEPS:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/clang-scan-deps.exe

//Generate index for LLVM archive
CMAKE_C_COMPILER_RANLIB:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/llvm-ranlib.exe

CMAKE_C_FLAGS:STRING=' /nologo /DWIN32 /D_WINDOWS /utf-8 /MP '

CMAKE_C_FLAGS_DEBUG:STRING='/MDd /Z7 /Ob0 /Od /RTC1 '

//Flags used by the C compiler during MINSIZEREL builds.
CMAKE_C_FLAGS_MINSIZEREL:STRING=-Os -DNDEBUG

CMAKE_C_FLAGS_RELEASE:STRING='/MD /O2 /Oi /Gy /DNDEBUG /Z7 '

//Flags used by the C compiler during RELWITHDEBINFO builds.
CMAKE_C_FLAGS_RELWITHDEBINFO:STRING=-O2 -DNDEBUG

//Libraries linked by default with all C applications.
CMAKE_C_STANDARD_LIBRARIES:STRING=-lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 -loldnames

//Path to a program.
CMAKE_DLLTOOL:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/llvm-dlltool.exe

//No help, variable specified on the command line.
CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION:UNINITIALIZED=ON

//Flags used by the linker during all build types.
CMAKE_EXE_LINKER_FLAGS:STRING=

//Flags used by the linker during DEBUG builds.
CMAKE_EXE_LINKER_FLAGS_DEBUG:STRING=/nologo

//Flags used by the linker during MINSIZEREL builds.
CMAKE_EXE_LINKER_FLAGS_MINSIZEREL:STRING=

CMAKE_EXE_LINKER_FLAGS_RELEASE:STRING='/nologo /DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF  '

//Flags used by the linker during RELWITHDEBINFO builds.
CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO:STRING=

//Enable/Disable output of build database during the build.
CMAKE_EXPORT_BUILD_DATABASE:BOOL=

//Enable/Disable output of compile commands during generation.
CMAKE_EXPORT_COMPILE_COMMANDS:BOOL=

//No help, variable specified on the command line.
CMAKE_EXPORT_NO_PACKAGE_REGISTRY:UNINITIALIZED=ON

//No help, variable specified on the command line.
CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY:UNINITIALIZED=ON

//No help, variable specified on the command line.
CMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY:UNINITIALIZED=ON

//Value Computed by CMake.
CMAKE_FIND_PACKAGE_REDIRECTS_DIR:STATIC=C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel/CMakeFiles/pkgRedirects

//No help, variable specified on the command line.
CMAKE_INSTALL_BINDIR:STRING=bin

//No help, variable specified on the command line.
CMAKE_INSTALL_LIBDIR:STRING=lib

//Install path prefix, prepended onto install directories.
CMAKE_INSTALL_PREFIX:PATH=C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/pkgs/glfw3_x64-windows

//No help, variable specified on the command line.
CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP:UNINITIALIZED=TRUE

//Path to a program.
CMAKE_LINKER:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/lld-link.exe

//make program
CMAKE_MAKE_PROGRAM:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe

...
Skipped 218 lines
...

//No help, variable specified on the command line.
VCPKG_PLATFORM_TOOLSET:UNINITIALIZED=v143

//Appends the vcpkg paths to CMAKE_PREFIX_PATH, CMAKE_LIBRARY_PATH
// and CMAKE_FIND_ROOT_PATH so that vcpkg libraries/packages are
// found after toolchain/system libraries/packages.
VCPKG_PREFER_SYSTEM_LIBS:BOOL=OFF

//Enable the setup of CMAKE_PROGRAM_PATH to vcpkg paths
VCPKG_SETUP_CMAKE_PROGRAM_PATH:BOOL=ON

//No help, variable specified on the command line.
VCPKG_SET_CHARSET_FLAG:UNINITIALIZED=ON

//No help, variable specified on the command line.
VCPKG_TARGET_ARCHITECTURE:UNINITIALIZED=x64

//Vcpkg target triplet (ex. x86-windows)
VCPKG_TARGET_TRIPLET:STRING=x64-windows

//Trace calls to find_package()
VCPKG_TRACE_FIND_PACKAGE:BOOL=OFF

//Enables messages from the VCPKG toolchain for debugging purposes.
VCPKG_VERBOSE:BOOL=OFF

//(experimental) Automatically copy dependencies into the install
// target directory for executables. Requires CMake 3.14.
X_VCPKG_APPLOCAL_DEPS_INSTALL:BOOL=OFF

//(experimental) Add USES_TERMINAL to VCPKG_APPLOCAL_DEPS to force
// serialization.
X_VCPKG_APPLOCAL_DEPS_SERIALIZED:BOOL=OFF

//The directory which contains the installed libraries for each
// triplet
_VCPKG_INSTALLED_DIR:PATH=C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed

//No help, variable specified on the command line.
_VCPKG_ROOT_DIR:UNINITIALIZED=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg


########################
# INTERNAL cache entries
########################

//ADVANCED property for variable: CMAKE_ADDR2LINE
CMAKE_ADDR2LINE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_AR
CMAKE_AR-ADVANCED:INTERNAL=1
//This is the directory where this CMakeCache.txt was created
CMAKE_CACHEFILE_DIR:INTERNAL=c:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel
//Major version of cmake used to create the current loaded cache
CMAKE_CACHE_MAJOR_VERSION:INTERNAL=4
//Minor version of cmake used to create the current loaded cache
CMAKE_CACHE_MINOR_VERSION:INTERNAL=1
//Patch version of cmake used to create the current loaded cache
CMAKE_CACHE_PATCH_VERSION:INTERNAL=1
//Path to CMake executable.
CMAKE_COMMAND:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe
//Path to cpack program executable.
CMAKE_CPACK_COMMAND:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cpack.exe
//Path to ctest program executable.
CMAKE_CTEST_COMMAND:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/ctest.exe
//ADVANCED property for variable: CMAKE_C_COMPILER
CMAKE_C_COMPILER-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_COMPILER_AR
CMAKE_C_COMPILER_AR-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_COMPILER_CLANG_SCAN_DEPS
CMAKE_C_COMPILER_CLANG_SCAN_DEPS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_COMPILER_RANLIB
CMAKE_C_COMPILER_RANLIB-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS
CMAKE_C_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_DEBUG
CMAKE_C_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_MINSIZEREL
CMAKE_C_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_RELEASE
CMAKE_C_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_RELWITHDEBINFO
CMAKE_C_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_STANDARD_LIBRARIES
CMAKE_C_STANDARD_LIBRARIES-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_DLLTOOL
CMAKE_DLLTOOL-ADVANCED:INTERNAL=1
//Executable file format
CMAKE_EXECUTABLE_FORMAT:INTERNAL=Unknown
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS
CMAKE_EXE_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_DEBUG
CMAKE_EXE_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_MINSIZEREL
CMAKE_EXE_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_RELEASE
CMAKE_EXE_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXPORT_BUILD_DATABASE
CMAKE_EXPORT_BUILD_DATABASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXPORT_COMPILE_COMMANDS
CMAKE_EXPORT_COMPILE_COMMANDS-ADVANCED:INTERNAL=1
//Name of external makefile project generator.
CMAKE_EXTRA_GENERATOR:INTERNAL=
//Name of generator.
CMAKE_GENERATOR:INTERNAL=Ninja
//Generator instance identifier.
CMAKE_GENERATOR_INSTANCE:INTERNAL=
//Name of generator platform.
CMAKE_GENERATOR_PLATFORM:INTERNAL=
//Name of generator toolset.
CMAKE_GENERATOR_TOOLSET:INTERNAL=
//Source directory with the top level CMakeLists.txt file for this
// project
CMAKE_HOME_DIRECTORY:INTERNAL=C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/src/3.4-2448ff4533.clean
//ADVANCED property for variable: CMAKE_LINKER
CMAKE_LINKER-ADVANCED:INTERNAL=1
//Name of CMakeLists files to read
CMAKE_LIST_FILE_NAME:INTERNAL=CMakeLists.txt
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS
CMAKE_MODULE_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_DEBUG
CMAKE_MODULE_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL
CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_RELEASE
CMAKE_MODULE_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_NM
CMAKE_NM-ADVANCED:INTERNAL=1
//number of local generators
CMAKE_NUMBER_OF_MAKEFILES:INTERNAL=1
//ADVANCED property for variable: CMAKE_OBJCOPY
CMAKE_OBJCOPY-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_OBJDUMP
CMAKE_OBJDUMP-ADVANCED:INTERNAL=1
//Platform information initialized
CMAKE_PLATFORM_INFO_INITIALIZED:INTERNAL=1
//ADVANCED property for variable: CMAKE_POLICY_VERSION_MINIMUM
CMAKE_POLICY_VERSION_MINIMUM-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RANLIB
CMAKE_RANLIB-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_COMPILER
CMAKE_RC_COMPILER-ADVANCED:INTERNAL=1
CMAKE_RC_COMPILER_WORKS:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS
CMAKE_RC_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_DEBUG
CMAKE_RC_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_MINSIZEREL
CMAKE_RC_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_RELEASE
CMAKE_RC_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_RELWITHDEBINFO
CMAKE_RC_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_READELF
CMAKE_READELF-ADVANCED:INTERNAL=1
//Path to CMake installation.
CMAKE_ROOT:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS
CMAKE_SHARED_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_DEBUG
CMAKE_SHARED_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL
CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_RELEASE
CMAKE_SHARED_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SKIP_INSTALL_RPATH
CMAKE_SKIP_INSTALL_RPATH-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SKIP_RPATH
CMAKE_SKIP_RPATH-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS
CMAKE_STATIC_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_DEBUG
CMAKE_STATIC_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL
CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_RELEASE
CMAKE_STATIC_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STRIP
CMAKE_STRIP-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_TAPI
CMAKE_TAPI-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_TOOLCHAIN_FILE
CMAKE_TOOLCHAIN_FILE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_VERBOSE_MAKEFILE
CMAKE_VERBOSE_MAKEFILE-ADVANCED:INTERNAL=1
//Install the dependencies listed in your manifest:
//\n    If this is off, you will have to manually install your dependencies.
//\n    See https://github.com/microsoft/vcpkg/tree/master/docs/specifications/manifests.md
// for more info.
//\n
VCPKG_MANIFEST_INSTALL:INTERNAL=OFF
//ADVANCED property for variable: VCPKG_VERBOSE
VCPKG_VERBOSE-ADVANCED:INTERNAL=1
//Making sure VCPKG_MANIFEST_MODE doesn't change
Z_VCPKG_CHECK_MANIFEST_MODE:INTERNAL=OFF
//Vcpkg root directory
Z_VCPKG_ROOT_DIR:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg

```
</details>

<details><summary>C:\Users\janos\source\repos\TileHexaV3\vcpkg_installed\vcpkg\blds\glfw3\config-x64-windows-dbg-CMakeCache.txt.log</summary>

```
# This is the CMakeCache file.
# For build in directory: c:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-dbg
# It was generated by CMake: C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe
# You can edit this file to change values found and used by cmake.
# If you do not want to change any of the values, simply exit the editor.
# If you do want to change a value, simply edit, save, and exit the editor.
# The syntax for the file is as follows:
# KEY:TYPE=VALUE
# KEY is the name of a variable in the cache.
# TYPE is a hint to GUIs for the type of VALUE, DO NOT EDIT TYPE!.
# VALUE is the current value for the KEY.

########################
# EXTERNAL cache entries
########################

//No help, variable specified on the command line.
BUILD_SHARED_LIBS:UNINITIALIZED=ON

//Path to a program.
CMAKE_ADDR2LINE:FILEPATH=CMAKE_ADDR2LINE-NOTFOUND

//Path to a program.
CMAKE_AR:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/llvm-ar.exe

//Choose the type of build, options are: None Debug Release RelWithDebInfo
// MinSizeRel ...
CMAKE_BUILD_TYPE:STRING=Debug

CMAKE_CROSSCOMPILING:STRING=OFF

CMAKE_CXX_FLAGS:STRING=' /nologo /DWIN32 /D_WINDOWS /utf-8 /GR /EHsc /MP '

CMAKE_CXX_FLAGS_DEBUG:STRING='/MDd /Z7 /Ob0 /Od /RTC1 '

CMAKE_CXX_FLAGS_RELEASE:STRING='/MD /O2 /Oi /Gy /DNDEBUG /Z7 '

//C compiler
CMAKE_C_COMPILER:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/clang.exe

//LLVM archiver
CMAKE_C_COMPILER_AR:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/llvm-ar.exe

//`clang-scan-deps` dependency scanner
CMAKE_C_COMPILER_CLANG_SCAN_DEPS:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/clang-scan-deps.exe

//Generate index for LLVM archive
CMAKE_C_COMPILER_RANLIB:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/llvm-ranlib.exe

CMAKE_C_FLAGS:STRING=' /nologo /DWIN32 /D_WINDOWS /utf-8 /MP '

CMAKE_C_FLAGS_DEBUG:STRING='/MDd /Z7 /Ob0 /Od /RTC1 '

//Flags used by the C compiler during MINSIZEREL builds.
CMAKE_C_FLAGS_MINSIZEREL:STRING=-Os -DNDEBUG

CMAKE_C_FLAGS_RELEASE:STRING='/MD /O2 /Oi /Gy /DNDEBUG /Z7 '

//Flags used by the C compiler during RELWITHDEBINFO builds.
CMAKE_C_FLAGS_RELWITHDEBINFO:STRING=-O2 -DNDEBUG

//Libraries linked by default with all C applications.
CMAKE_C_STANDARD_LIBRARIES:STRING=-lkernel32 -luser32 -lgdi32 -lwinspool -lshell32 -lole32 -loleaut32 -luuid -lcomdlg32 -ladvapi32 -loldnames

//Path to a program.
CMAKE_DLLTOOL:FILEPATH=C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/llvm-dlltool.exe

//No help, variable specified on the command line.
CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION:UNINITIALIZED=ON

//Flags used by the linker during all build types.
CMAKE_EXE_LINKER_FLAGS:STRING=

//Flags used by the linker during DEBUG builds.
CMAKE_EXE_LINKER_FLAGS_DEBUG:STRING=/nologo

//Flags used by the linker during MINSIZEREL builds.
CMAKE_EXE_LINKER_FLAGS_MINSIZEREL:STRING=

CMAKE_EXE_LINKER_FLAGS_RELEASE:STRING='/nologo /DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF  '

//Flags used by the linker during RELWITHDEBINFO builds.
CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO:STRING=

//Enable/Disable output of build database during the build.
CMAKE_EXPORT_BUILD_DATABASE:BOOL=

//Enable/Disable output of compile commands during generation.
CMAKE_EXPORT_COMPILE_COMMANDS:BOOL=

//No help, variable specified on the command line.
CMAKE_EXPORT_NO_PACKAGE_REGISTRY:UNINITIALIZED=ON

//No help, variable specified on the command line.
CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY:UNINITIALIZED=ON

//No help, variable specified on the command line.
CMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY:UNINITIALIZED=ON

//Value Computed by CMake.
CMAKE_FIND_PACKAGE_REDIRECTS_DIR:STATIC=C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-dbg/CMakeFiles/pkgRedirects

...
Skipped 285 lines
...
//ADVANCED property for variable: CMAKE_AR
CMAKE_AR-ADVANCED:INTERNAL=1
//This is the directory where this CMakeCache.txt was created
CMAKE_CACHEFILE_DIR:INTERNAL=c:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-dbg
//Major version of cmake used to create the current loaded cache
CMAKE_CACHE_MAJOR_VERSION:INTERNAL=4
//Minor version of cmake used to create the current loaded cache
CMAKE_CACHE_MINOR_VERSION:INTERNAL=1
//Patch version of cmake used to create the current loaded cache
CMAKE_CACHE_PATCH_VERSION:INTERNAL=1
//Path to CMake executable.
CMAKE_COMMAND:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe
//Path to cpack program executable.
CMAKE_CPACK_COMMAND:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cpack.exe
//Path to ctest program executable.
CMAKE_CTEST_COMMAND:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/ctest.exe
//ADVANCED property for variable: CMAKE_C_COMPILER
CMAKE_C_COMPILER-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_COMPILER_AR
CMAKE_C_COMPILER_AR-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_COMPILER_CLANG_SCAN_DEPS
CMAKE_C_COMPILER_CLANG_SCAN_DEPS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_COMPILER_RANLIB
CMAKE_C_COMPILER_RANLIB-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS
CMAKE_C_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_DEBUG
CMAKE_C_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_MINSIZEREL
CMAKE_C_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_RELEASE
CMAKE_C_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_RELWITHDEBINFO
CMAKE_C_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_STANDARD_LIBRARIES
CMAKE_C_STANDARD_LIBRARIES-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_DLLTOOL
CMAKE_DLLTOOL-ADVANCED:INTERNAL=1
//Executable file format
CMAKE_EXECUTABLE_FORMAT:INTERNAL=Unknown
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS
CMAKE_EXE_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_DEBUG
CMAKE_EXE_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_MINSIZEREL
CMAKE_EXE_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_RELEASE
CMAKE_EXE_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXPORT_BUILD_DATABASE
CMAKE_EXPORT_BUILD_DATABASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXPORT_COMPILE_COMMANDS
CMAKE_EXPORT_COMPILE_COMMANDS-ADVANCED:INTERNAL=1
//Name of external makefile project generator.
CMAKE_EXTRA_GENERATOR:INTERNAL=
//Name of generator.
CMAKE_GENERATOR:INTERNAL=Ninja
//Generator instance identifier.
CMAKE_GENERATOR_INSTANCE:INTERNAL=
//Name of generator platform.
CMAKE_GENERATOR_PLATFORM:INTERNAL=
//Name of generator toolset.
CMAKE_GENERATOR_TOOLSET:INTERNAL=
//Source directory with the top level CMakeLists.txt file for this
// project
CMAKE_HOME_DIRECTORY:INTERNAL=C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/src/3.4-2448ff4533.clean
//ADVANCED property for variable: CMAKE_LINKER
CMAKE_LINKER-ADVANCED:INTERNAL=1
//Name of CMakeLists files to read
CMAKE_LIST_FILE_NAME:INTERNAL=CMakeLists.txt
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS
CMAKE_MODULE_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_DEBUG
CMAKE_MODULE_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL
CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_RELEASE
CMAKE_MODULE_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_NM
CMAKE_NM-ADVANCED:INTERNAL=1
//number of local generators
CMAKE_NUMBER_OF_MAKEFILES:INTERNAL=1
//ADVANCED property for variable: CMAKE_OBJCOPY
CMAKE_OBJCOPY-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_OBJDUMP
CMAKE_OBJDUMP-ADVANCED:INTERNAL=1
//Platform information initialized
CMAKE_PLATFORM_INFO_INITIALIZED:INTERNAL=1
//ADVANCED property for variable: CMAKE_POLICY_VERSION_MINIMUM
CMAKE_POLICY_VERSION_MINIMUM-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RANLIB
CMAKE_RANLIB-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_COMPILER
CMAKE_RC_COMPILER-ADVANCED:INTERNAL=1
CMAKE_RC_COMPILER_WORKS:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS
CMAKE_RC_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_DEBUG
CMAKE_RC_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_MINSIZEREL
CMAKE_RC_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_RELEASE
CMAKE_RC_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_RELWITHDEBINFO
CMAKE_RC_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_READELF
CMAKE_READELF-ADVANCED:INTERNAL=1
//Path to CMake installation.
CMAKE_ROOT:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS
CMAKE_SHARED_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_DEBUG
CMAKE_SHARED_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL
CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_RELEASE
CMAKE_SHARED_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SKIP_INSTALL_RPATH
CMAKE_SKIP_INSTALL_RPATH-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SKIP_RPATH
CMAKE_SKIP_RPATH-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS
CMAKE_STATIC_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_DEBUG
CMAKE_STATIC_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL
CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_RELEASE
CMAKE_STATIC_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STRIP
CMAKE_STRIP-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_TAPI
CMAKE_TAPI-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_TOOLCHAIN_FILE
CMAKE_TOOLCHAIN_FILE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_VERBOSE_MAKEFILE
CMAKE_VERBOSE_MAKEFILE-ADVANCED:INTERNAL=1
//Install the dependencies listed in your manifest:
//\n    If this is off, you will have to manually install your dependencies.
//\n    See https://github.com/microsoft/vcpkg/tree/master/docs/specifications/manifests.md
// for more info.
//\n
VCPKG_MANIFEST_INSTALL:INTERNAL=OFF
//ADVANCED property for variable: VCPKG_VERBOSE
VCPKG_VERBOSE-ADVANCED:INTERNAL=1
//Making sure VCPKG_MANIFEST_MODE doesn't change
Z_VCPKG_CHECK_MANIFEST_MODE:INTERNAL=OFF
//Vcpkg root directory
Z_VCPKG_ROOT_DIR:INTERNAL=C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg

```
</details>

<details><summary>C:\Users\janos\source\repos\TileHexaV3\vcpkg_installed\vcpkg\blds\glfw3\config-x64-windows-rel-CMakeConfigureLog.yaml.log</summary>

```

---
events:
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeDetermineSystem.cmake:212 (message)"
      - "CMakeLists.txt:3 (project)"
    message: |
      The system is: Windows - 10.0.26200 - AMD64
  -
    kind: "find-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeDetermineCompiler.cmake:63 (find_program)"
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeDetermineCCompiler.cmake:64 (_cmake_find_compiler)"
      - "CMakeLists.txt:3 (project)"
    mode: "program"
    variable: "CMAKE_C_COMPILER"
    description: "C compiler"
    settings:
      SearchFramework: "LAST"
      SearchAppBundle: "LAST"
      CMAKE_FIND_USE_CMAKE_PATH: false
      CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH: false
      CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH: true
      CMAKE_FIND_USE_CMAKE_SYSTEM_PATH: false
      CMAKE_FIND_USE_INSTALL_PREFIX: true
    names:
      - "cc"
      - "gcc"
      - "cl"
      - "bcc"
      - "xlc"
      - "icx"
      - "clang"
    candidate_directories:
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/VC/vcpackages/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/TestWindow/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/TeamFoundation/Team Explorer/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/MSBuild/Current/Bin/Roslyn/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files (x86)/Microsoft SDKs/Windows/v10.0A/bin/NETFX 4.8 Tools/x64/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files (x86)/HTML Help Workshop/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/FSharp/Tools/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Team Tools/DiagnosticsHub/Collector/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/Extensions/Microsoft/CodeCoverage.Console/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files (x86)/Windows Kits/10/bin/10.0.26100.0/x64/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files (x86)/Windows Kits/10/bin/x64/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/MSBuild/Current/Bin/amd64/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Windows/Microsoft.NET/Framework64/v4.0.30319/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files/Microsoft Visual Studio/18/Community/Common7/Tools/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Program Files/PowerShell/7/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Windows/System32/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/Windows/"
...
Skipped 10105 lines
...
  -
    kind: "try_compile-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeDetermineCompilerABI.cmake:83 (try_compile)"
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeTestCCompiler.cmake:26 (CMAKE_DETERMINE_COMPILER_ABI)"
      - "CMakeLists.txt:3 (project)"
    checks:
      - "Detecting C compiler ABI info"
    directories:
      source: "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-y2ova4"
      binary: "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-y2ova4"
    cmakeVariables:
      CMAKE_C_FLAGS: " /nologo /DWIN32 /D_WINDOWS /utf-8 /MP "
      CMAKE_C_FLAGS_DEBUG: "/MDd /Z7 /Ob0 /Od /RTC1 "
      CMAKE_EXE_LINKER_FLAGS: ""
      CMAKE_MSVC_DEBUG_INFORMATION_FORMAT: ""
      CMAKE_MSVC_RUNTIME_LIBRARY: "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<STREQUAL:dynamic,dynamic>:DLL>"
      VCPKG_CHAINLOAD_TOOLCHAIN_FILE: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake"
      VCPKG_CRT_LINKAGE: "dynamic"
      VCPKG_CXX_FLAGS: ""
      VCPKG_CXX_FLAGS_DEBUG: ""
      VCPKG_CXX_FLAGS_RELEASE: ""
      VCPKG_C_FLAGS: ""
      VCPKG_C_FLAGS_DEBUG: ""
      VCPKG_C_FLAGS_RELEASE: ""
      VCPKG_INSTALLED_DIR: "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed"
      VCPKG_LINKER_FLAGS: ""
      VCPKG_LINKER_FLAGS_DEBUG: ""
      VCPKG_LINKER_FLAGS_RELEASE: ""
      VCPKG_PLATFORM_TOOLSET: "v143"
      VCPKG_PREFER_SYSTEM_LIBS: "OFF"
      VCPKG_SET_CHARSET_FLAG: "ON"
      VCPKG_TARGET_ARCHITECTURE: "x64"
      VCPKG_TARGET_TRIPLET: "x64-windows"
      Z_VCPKG_ROOT_DIR: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg"
    buildResult:
      variable: "CMAKE_C_ABI_COMPILED"
      cached: true
      stdout: |
        Change Dir: 'C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-y2ova4'
        
        Run Build Command(s): "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" -v cmTC_aedd2
        [1/2] C:\\PROGRA~1\\MICROS~4\\18\\COMMUN~1\\VC\\Tools\\Llvm\\x64\\bin\\clang.exe   /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -D_DEBUG -D_DLL -D_MT -Xclang --dependent-lib=msvcrtd -MD -MT CMakeFiles/cmTC_aedd2.dir/CMakeCCompilerABI.c.obj -MF CMakeFiles\\cmTC_aedd2.dir\\CMakeCCompilerABI.c.obj.d -o CMakeFiles/cmTC_aedd2.dir/CMakeCCompilerABI.c.obj -c "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeCCompilerABI.c"
        FAILED: CMakeFiles/cmTC_aedd2.dir/CMakeCCompilerABI.c.obj 
        C:\\PROGRA~1\\MICROS~4\\18\\COMMUN~1\\VC\\Tools\\Llvm\\x64\\bin\\clang.exe   /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -D_DEBUG -D_DLL -D_MT -Xclang --dependent-lib=msvcrtd -MD -MT CMakeFiles/cmTC_aedd2.dir/CMakeCCompilerABI.c.obj -MF CMakeFiles\\cmTC_aedd2.dir\\CMakeCCompilerABI.c.obj.d -o CMakeFiles/cmTC_aedd2.dir/CMakeCCompilerABI.c.obj -c "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeCCompilerABI.c"
        clang: error: no such file or directory: '/nologo'
        clang: error: no such file or directory: '/DWIN32'
        clang: error: no such file or directory: '/D_WINDOWS'
        clang: error: no such file or directory: '/utf-8'
        clang: error: no such file or directory: '/MP'
        clang: error: no such file or directory: '/MDd'
        clang: error: no such file or directory: '/Z7'
        clang: error: no such file or directory: '/Ob0'
        clang: error: no such file or directory: '/Od'
        clang: error: no such file or directory: '/RTC1'\x0d
        ninja: build stopped: subcommand failed.
        
      exitCode: 1
  -
    kind: "try_compile-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeTestCCompiler.cmake:56 (try_compile)"
      - "CMakeLists.txt:3 (project)"
    checks:
      - "Check for working C compiler: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/clang.exe"
    directories:
      source: "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-twt51n"
      binary: "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-twt51n"
    cmakeVariables:
      CMAKE_C_FLAGS: " /nologo /DWIN32 /D_WINDOWS /utf-8 /MP "
      CMAKE_C_FLAGS_DEBUG: "/MDd /Z7 /Ob0 /Od /RTC1 "
      CMAKE_EXE_LINKER_FLAGS: ""
      CMAKE_MSVC_DEBUG_INFORMATION_FORMAT: ""
      CMAKE_MSVC_RUNTIME_LIBRARY: "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<STREQUAL:dynamic,dynamic>:DLL>"
      VCPKG_CHAINLOAD_TOOLCHAIN_FILE: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake"
      VCPKG_CRT_LINKAGE: "dynamic"
      VCPKG_CXX_FLAGS: ""
      VCPKG_CXX_FLAGS_DEBUG: ""
      VCPKG_CXX_FLAGS_RELEASE: ""
      VCPKG_C_FLAGS: ""
      VCPKG_C_FLAGS_DEBUG: ""
      VCPKG_C_FLAGS_RELEASE: ""
      VCPKG_INSTALLED_DIR: "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed"
      VCPKG_LINKER_FLAGS: ""
      VCPKG_LINKER_FLAGS_DEBUG: ""
      VCPKG_LINKER_FLAGS_RELEASE: ""
      VCPKG_PLATFORM_TOOLSET: "v143"
      VCPKG_PREFER_SYSTEM_LIBS: "OFF"
      VCPKG_SET_CHARSET_FLAG: "ON"
      VCPKG_TARGET_ARCHITECTURE: "x64"
      VCPKG_TARGET_TRIPLET: "x64-windows"
      Z_VCPKG_ROOT_DIR: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg"
    buildResult:
      variable: "CMAKE_C_COMPILER_WORKS"
      cached: true
      stdout: |
        Change Dir: 'C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-twt51n'
        
        Run Build Command(s): "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" -v cmTC_d84f9
        [1/2] C:\\PROGRA~1\\MICROS~4\\18\\COMMUN~1\\VC\\Tools\\Llvm\\x64\\bin\\clang.exe   /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -D_DEBUG -D_DLL -D_MT -Xclang --dependent-lib=msvcrtd -MD -MT CMakeFiles/cmTC_d84f9.dir/testCCompiler.c.obj -MF CMakeFiles\\cmTC_d84f9.dir\\testCCompiler.c.obj.d -o CMakeFiles/cmTC_d84f9.dir/testCCompiler.c.obj -c C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-twt51n/testCCompiler.c
        FAILED: CMakeFiles/cmTC_d84f9.dir/testCCompiler.c.obj 
        C:\\PROGRA~1\\MICROS~4\\18\\COMMUN~1\\VC\\Tools\\Llvm\\x64\\bin\\clang.exe   /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -D_DEBUG -D_DLL -D_MT -Xclang --dependent-lib=msvcrtd -MD -MT CMakeFiles/cmTC_d84f9.dir/testCCompiler.c.obj -MF CMakeFiles\\cmTC_d84f9.dir\\testCCompiler.c.obj.d -o CMakeFiles/cmTC_d84f9.dir/testCCompiler.c.obj -c C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-rel/CMakeFiles/CMakeScratch/TryCompile-twt51n/testCCompiler.c
        clang: error: no such file or directory: '/nologo'
        clang: error: no such file or directory: '/DWIN32'
        clang: error: no such file or directory: '/D_WINDOWS'
        clang: error: no such file or directory: '/utf-8'
        clang: error: no such file or directory: '/MP'
        clang: error: no such file or directory: '/MDd'
        clang: error: no such file or directory: '/Z7'
        clang: error: no such file or directory: '/Ob0'
        clang: error: no such file or directory: '/Od'
        clang: error: no such file or directory: '/RTC1'\x0d
        ninja: build stopped: subcommand failed.
        
      exitCode: 1
...
```
</details>

<details><summary>C:\Users\janos\source\repos\TileHexaV3\vcpkg_installed\vcpkg\blds\glfw3\config-x64-windows-dbg-CMakeConfigureLog.yaml.log</summary>

```

---
events:
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeDetermineSystem.cmake:212 (message)"
      - "CMakeLists.txt:3 (project)"
    message: |
      The system is: Windows - 10.0.26200 - AMD64
  -
    kind: "find-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeDetermineCompiler.cmake:63 (find_program)"
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeDetermineCCompiler.cmake:64 (_cmake_find_compiler)"
      - "CMakeLists.txt:3 (project)"
    mode: "program"
    variable: "CMAKE_C_COMPILER"
    description: "C compiler"
    settings:
      SearchFramework: "LAST"
      SearchAppBundle: "LAST"
      CMAKE_FIND_USE_CMAKE_PATH: false
      CMAKE_FIND_USE_CMAKE_ENVIRONMENT_PATH: false
      CMAKE_FIND_USE_SYSTEM_ENVIRONMENT_PATH: true
      CMAKE_FIND_USE_CMAKE_SYSTEM_PATH: false
      CMAKE_FIND_USE_INSTALL_PREFIX: true
    names:
      - "cc"
      - "gcc"
      - "cl"
      - "bcc"
      - "xlc"
      - "icx"
      - "clang"
    candidate_directories:
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/VC/vcpackages/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/TestWindow/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/TeamFoundation/Team Explorer/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/MSBuild/Current/Bin/Roslyn/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files (x86)/Microsoft SDKs/Windows/v10.0A/bin/NETFX 4.8 Tools/x64/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files (x86)/HTML Help Workshop/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/FSharp/Tools/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Team Tools/DiagnosticsHub/Collector/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/Extensions/Microsoft/CodeCoverage.Console/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files (x86)/Windows Kits/10/bin/10.0.26100.0/x64/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files (x86)/Windows Kits/10/bin/x64/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/MSBuild/Current/Bin/amd64/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Windows/Microsoft.NET/Framework64/v4.0.30319/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files/Microsoft Visual Studio/18/Community/Common7/Tools/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Program Files/PowerShell/7/"
      - "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/x64-windows/debug/Windows/System32/"
...
Skipped 10106 lines
...
  -
    kind: "try_compile-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeDetermineCompilerABI.cmake:83 (try_compile)"
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeTestCCompiler.cmake:26 (CMAKE_DETERMINE_COMPILER_ABI)"
      - "CMakeLists.txt:3 (project)"
    checks:
      - "Detecting C compiler ABI info"
    directories:
      source: "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-kgyzjn"
      binary: "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-kgyzjn"
    cmakeVariables:
      CMAKE_C_FLAGS: " /nologo /DWIN32 /D_WINDOWS /utf-8 /MP "
      CMAKE_C_FLAGS_DEBUG: "/MDd /Z7 /Ob0 /Od /RTC1 "
      CMAKE_EXE_LINKER_FLAGS: ""
      CMAKE_MSVC_DEBUG_INFORMATION_FORMAT: ""
      CMAKE_MSVC_RUNTIME_LIBRARY: "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<STREQUAL:dynamic,dynamic>:DLL>"
      VCPKG_CHAINLOAD_TOOLCHAIN_FILE: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake"
      VCPKG_CRT_LINKAGE: "dynamic"
      VCPKG_CXX_FLAGS: ""
      VCPKG_CXX_FLAGS_DEBUG: ""
      VCPKG_CXX_FLAGS_RELEASE: ""
      VCPKG_C_FLAGS: ""
      VCPKG_C_FLAGS_DEBUG: ""
      VCPKG_C_FLAGS_RELEASE: ""
      VCPKG_INSTALLED_DIR: "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed"
      VCPKG_LINKER_FLAGS: ""
      VCPKG_LINKER_FLAGS_DEBUG: ""
      VCPKG_LINKER_FLAGS_RELEASE: ""
      VCPKG_PLATFORM_TOOLSET: "v143"
      VCPKG_PREFER_SYSTEM_LIBS: "OFF"
      VCPKG_SET_CHARSET_FLAG: "ON"
      VCPKG_TARGET_ARCHITECTURE: "x64"
      VCPKG_TARGET_TRIPLET: "x64-windows"
      Z_VCPKG_ROOT_DIR: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg"
    buildResult:
      variable: "CMAKE_C_ABI_COMPILED"
      cached: true
      stdout: |
        Change Dir: 'C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-kgyzjn'
        
        Run Build Command(s): "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" -v cmTC_0b39e
        [1/2] C:\\PROGRA~1\\MICROS~4\\18\\COMMUN~1\\VC\\Tools\\Llvm\\x64\\bin\\clang.exe   /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -D_DEBUG -D_DLL -D_MT -Xclang --dependent-lib=msvcrtd -MD -MT CMakeFiles/cmTC_0b39e.dir/CMakeCCompilerABI.c.obj -MF CMakeFiles\\cmTC_0b39e.dir\\CMakeCCompilerABI.c.obj.d -o CMakeFiles/cmTC_0b39e.dir/CMakeCCompilerABI.c.obj -c "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeCCompilerABI.c"
        FAILED: CMakeFiles/cmTC_0b39e.dir/CMakeCCompilerABI.c.obj 
        C:\\PROGRA~1\\MICROS~4\\18\\COMMUN~1\\VC\\Tools\\Llvm\\x64\\bin\\clang.exe   /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -D_DEBUG -D_DLL -D_MT -Xclang --dependent-lib=msvcrtd -MD -MT CMakeFiles/cmTC_0b39e.dir/CMakeCCompilerABI.c.obj -MF CMakeFiles\\cmTC_0b39e.dir\\CMakeCCompilerABI.c.obj.d -o CMakeFiles/cmTC_0b39e.dir/CMakeCCompilerABI.c.obj -c "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeCCompilerABI.c"
        clang: error: no such file or directory: '/nologo'
        clang: error: no such file or directory: '/DWIN32'
        clang: error: no such file or directory: '/D_WINDOWS'
        clang: error: no such file or directory: '/utf-8'
        clang: error: no such file or directory: '/MP'
        clang: error: no such file or directory: '/MDd'
        clang: error: no such file or directory: '/Z7'
        clang: error: no such file or directory: '/Ob0'
        clang: error: no such file or directory: '/Od'
        clang: error: no such file or directory: '/RTC1'\x0d
        ninja: build stopped: subcommand failed.
        
      exitCode: 1
  -
    kind: "try_compile-v1"
    backtrace:
      - "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/share/cmake-4.1/Modules/CMakeTestCCompiler.cmake:56 (try_compile)"
      - "CMakeLists.txt:3 (project)"
    checks:
      - "Check for working C compiler: C:/Program Files/Microsoft Visual Studio/18/Community/VC/Tools/Llvm/x64/bin/clang.exe"
    directories:
      source: "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-c769ze"
      binary: "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-c769ze"
    cmakeVariables:
      CMAKE_C_FLAGS: " /nologo /DWIN32 /D_WINDOWS /utf-8 /MP "
      CMAKE_C_FLAGS_DEBUG: "/MDd /Z7 /Ob0 /Od /RTC1 "
      CMAKE_EXE_LINKER_FLAGS: ""
      CMAKE_MSVC_DEBUG_INFORMATION_FORMAT: ""
      CMAKE_MSVC_RUNTIME_LIBRARY: "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<STREQUAL:dynamic,dynamic>:DLL>"
      VCPKG_CHAINLOAD_TOOLCHAIN_FILE: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg/scripts/toolchains/windows.cmake"
      VCPKG_CRT_LINKAGE: "dynamic"
      VCPKG_CXX_FLAGS: ""
      VCPKG_CXX_FLAGS_DEBUG: ""
      VCPKG_CXX_FLAGS_RELEASE: ""
      VCPKG_C_FLAGS: ""
      VCPKG_C_FLAGS_DEBUG: ""
      VCPKG_C_FLAGS_RELEASE: ""
      VCPKG_INSTALLED_DIR: "C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed"
      VCPKG_LINKER_FLAGS: ""
      VCPKG_LINKER_FLAGS_DEBUG: ""
      VCPKG_LINKER_FLAGS_RELEASE: ""
      VCPKG_PLATFORM_TOOLSET: "v143"
      VCPKG_PREFER_SYSTEM_LIBS: "OFF"
      VCPKG_SET_CHARSET_FLAG: "ON"
      VCPKG_TARGET_ARCHITECTURE: "x64"
      VCPKG_TARGET_TRIPLET: "x64-windows"
      Z_VCPKG_ROOT_DIR: "C:/Program Files/Microsoft Visual Studio/18/Community/VC/vcpkg"
    buildResult:
      variable: "CMAKE_C_COMPILER_WORKS"
      cached: true
      stdout: |
        Change Dir: 'C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-c769ze'
        
        Run Build Command(s): "C:/Program Files/Microsoft Visual Studio/18/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" -v cmTC_373af
        [1/2] C:\\PROGRA~1\\MICROS~4\\18\\COMMUN~1\\VC\\Tools\\Llvm\\x64\\bin\\clang.exe   /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -D_DEBUG -D_DLL -D_MT -Xclang --dependent-lib=msvcrtd -MD -MT CMakeFiles/cmTC_373af.dir/testCCompiler.c.obj -MF CMakeFiles\\cmTC_373af.dir\\testCCompiler.c.obj.d -o CMakeFiles/cmTC_373af.dir/testCCompiler.c.obj -c C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-c769ze/testCCompiler.c
        FAILED: CMakeFiles/cmTC_373af.dir/testCCompiler.c.obj 
        C:\\PROGRA~1\\MICROS~4\\18\\COMMUN~1\\VC\\Tools\\Llvm\\x64\\bin\\clang.exe   /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /MDd /Z7 /Ob0 /Od /RTC1  -D_DEBUG -D_DLL -D_MT -Xclang --dependent-lib=msvcrtd -MD -MT CMakeFiles/cmTC_373af.dir/testCCompiler.c.obj -MF CMakeFiles\\cmTC_373af.dir\\testCCompiler.c.obj.d -o CMakeFiles/cmTC_373af.dir/testCCompiler.c.obj -c C:/Users/janos/source/repos/TileHexaV3/vcpkg_installed/vcpkg/blds/glfw3/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-c769ze/testCCompiler.c
        clang: error: no such file or directory: '/nologo'
        clang: error: no such file or directory: '/DWIN32'
        clang: error: no such file or directory: '/D_WINDOWS'
        clang: error: no such file or directory: '/utf-8'
        clang: error: no such file or directory: '/MP'
        clang: error: no such file or directory: '/MDd'
        clang: error: no such file or directory: '/Z7'
        clang: error: no such file or directory: '/Ob0'
        clang: error: no such file or directory: '/Od'
        clang: error: no such file or directory: '/RTC1'\x0d
        ninja: build stopped: subcommand failed.
        
      exitCode: 1
...
```
</details>

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "$schema": "https://raw.githubusercontent.com/microsoft/vcpkg/master/scripts/vcpkg.schema.json",
  "name": "tilehexav3",
  "version": "1.0.0",
  "dependencies": [
    "glfw3",
    "opengl"
  ],
  "builtin-baseline": "6d7bf7ef2193e2d1c5798a5ff8811d533104c861"
}

```
</details>
