 cmake_minimum_required(VERSION 2.8)

PROJECT(vtkglut)

find_package(VTK REQUIRED)

include(${VTK_USE_FILE})

add_executable(vtkglut WIN32 MACOSX_BUNDLE vtkglut.cxx )

target_link_libraries(vtkglut ${VTK_LIBRARIES} )
