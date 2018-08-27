# Common Ambient Variables:
#   CURRENT_BUILDTREES_DIR    = ${VCPKG_ROOT_DIR}\buildtrees\${PORT}
#   CURRENT_PACKAGES_DIR      = ${VCPKG_ROOT_DIR}\packages\${PORT}_${TARGET_TRIPLET}
#   CURRENT_PORT_DIR          = ${VCPKG_ROOT_DIR}\ports\${PORT}
#   PORT                      = current port name (zlib, etc)
#   TARGET_TRIPLET            = current triplet (x86-windows, x64-windows-static, etc)
#   VCPKG_CRT_LINKAGE         = C runtime linkage type (static, dynamic)
#   VCPKG_LIBRARY_LINKAGE     = target library linkage type (static, dynamic)
#   VCPKG_ROOT_DIR            = <C:\path\to\current\vcpkg>
#   VCPKG_TARGET_ARCHITECTURE = target architecture (x64, x86, arm)
#

include(vcpkg_common_functions)
set(VCPKG_POLICY_DLLS_WITHOUT_LIBS enabled)
set(SOURCE_PATH ${CURRENT_BUILDTREES_DIR}/src/tcc-0.9.27)
vcpkg_download_distfile(ARCHIVE
    URLS "@URL@"
    FILENAME "tcc-0.9.27.zip"
    SHA512 df3a274d59cf9625d1fe3ee24799558af6b8e911312dae651d134077bb0b5f5715ab21d7ac436d57b1e36da25847d44034f71eee2e4920e7ebd8352afd740fe5
)
vcpkg_extract_source_archive(${ARCHIVE})



# vcpkg_configure_cmake(
    # SOURCE_PATH ${SOURCE_PATH}
# )

# vcpkg_install_cmake()

file(INSTALL ${SOURCE_PATH}/include/ DESTINATION ${CURRENT_PACKAGES_DIR}/include/tcc)

file(INSTALL ${SOURCE_PATH}/lib/ DESTINATION ${CURRENT_PACKAGES_DIR}/lib/tcc)

file(INSTALL ${SOURCE_PATH}/libtcc/libtcc.h DESTINATION ${CURRENT_PACKAGES_DIR}/include/tcc)

file(INSTALL ${SOURCE_PATH}/libtcc/libtcc.def DESTINATION ${CURRENT_PACKAGES_DIR}/lib/tcc)

file(INSTALL ${SOURCE_PATH}/tools/ DESTINATION ${CURRENT_PACKAGES_DIR}/tools)

file(INSTALL ${SOURCE_PATH}/examples DESTINATION ${CURRENT_PACKAGES_DIR}/share/tcc RENAME examples)

file(INSTALL ${SOURCE_PATH}/share/COPYING DESTINATION ${CURRENT_PACKAGES_DIR}/share/tcc RENAME copyright)

file(INSTALL ${SOURCE_PATH}/doc/tcc-win32.txt DESTINATION ${CURRENT_PACKAGES_DIR}/share/tcc RENAME tcc-win32.txt)
