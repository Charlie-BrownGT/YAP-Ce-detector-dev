cmake_minimum_required(VERSION 3.16...3.27)
project(TestEm1)

option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()

include(${Geant4_USE_FILE})

include_directories(${PROJECT_SOURCE_DIR}/include 
                    ${Geant4_INCLUDE_DIR})
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

#copy all macros to build directory
file(GLOB MACRO_FILES ${PROJECT_SOURCE_DIR}/macros/*.mac)
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_executable(TestEm1 TestEm1.cc ${sources} ${headers} ${TOOLS_FORTRAN_OBJECTS})
target_link_libraries(TestEm1 ${Geant4_LIBRARIES} ${HBOOK_LIBRARIES})

#set(TestEm1_SCRIPTS
#    alphaRange.mac annihil.mac brems.mac decayinfly.mac erange.mac etaDecay.mac gammaconversion.mac
#    geantino.mac ionRange.mac photoelec.mac photon.mac radioactive.mac range.mac runs.mac
#    pRange.mac stepMax.mac TestEm1.in TestEm1.out vis.mac
#  )

#foreach(_script ${TestEm1_SCRIPTS})
#  configure_file(
#    ${PROJECT_SOURCE_DIR}/${_script}
#    ${PROJECT_BINARY_DIR}/${_script}
#    COPYONLY
#    )
#endforeach()

install(TARGETS TestEm1 DESTINATION bin)

