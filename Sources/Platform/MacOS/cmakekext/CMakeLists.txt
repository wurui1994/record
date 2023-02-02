cmake_minimum_required(VERSION 3.0)

set(PROJECT_NAME kexthello)
project(${PROJECT_NAME})

set(KEXT_NAME ${PROJECT_NAME})
set(KEXT_CONTENTS "${KEXT_NAME}.kext/Contents")
set(KEXT_BINARY "${KEXT_CONTENTS}/MACOS/${KEXT_NAME}")

set(CMAKE_OSX_ARCHITECTURES "arm64e;x86_64")

set(KERNEL_LINKER_FLAGS
  "-Xlinker -kext -nostdlib -lkmod"
)
# c++: -kext -nostdlib -lkmodc++ -lkmod -lcc_kext

add_executable(${PROJECT_NAME}
  kexthello.c
)

add_custom_command(
  TARGET ${PROJECT_NAME}
  PRE_BUILD
  COMMAND mkdir -p "${KEXT_CONTENTS}/MacOS"
  COMMAND cp "${CMAKE_CURRENT_LIST_DIR}/Info.plist" "${KEXT_CONTENTS}/Info.plist"
  DEPENDS "${CMAKE_CURRENT_LIST_DIR}/Info.plist"
  COMMENT "Copy kernel extension Info.plist"
  VERBATIM
)

if (NOT XNU_PATH)
  message(FATAL_ERROR "Please git clone https://github.com/apple-oss-distributions/xnu.git 
    and set cmake -DXNU_PATH=<xnu repo path>")
endif()

target_include_directories(${PROJECT_NAME}
  PRIVATE
  "${CMAKE_OSX_SYSROOT}/System/Library/Frameworks/Kernel.framework/Headers"
  ${XNU_PATH}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
  LINK_FLAGS "${KERNEL_LINKER_FLAGS}"
  EXCLUDE_FROM_ALL true
  OUTPUT_NAME "${KEXT_BINARY}"
)
