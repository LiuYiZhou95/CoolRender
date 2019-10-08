cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
add_definitions("-DGLM_FORCE_SIZE_T_LENGTH -DGLM_FORCE_RADIANS")

SET(Source_Common_Dir "${CMAKE_CURRENT_SOURCE_DIR}/../../klinSource")
SET(Source_TP_Dir "${CMAKE_CURRENT_SOURCE_DIR}/../../klinThirdParty")
SET(Source_Android_Dir "${CMAKE_CURRENT_SOURCE_DIR}/src/main/cpp")

file(GLOB srcSource "${Source_Common_Dir}/Core/*.cpp"
                    "${Source_Common_Dir}/RenderCore/*.cpp"
                    "${Source_Common_Dir}/*.cpp"
                    "${Source_Common_Dir}/Math/*.cpp"
                    "${Source_Common_Dir}/Graphics/*.cpp"
                    "${Source_Common_Dir}/Sample/*.cpp"
                    "${Source_Common_Dir}/Engine/*.cpp"
                    "${Source_Common_Dir}/Resource/*.cpp"
                    "${Source_Common_Dir}/Scene/*.cpp"
                    "${Source_Common_Dir}/Container/*.cpp"
                    "${Source_TP_Dir}/glm/detail/*.cpp"
                    "${Source_TP_Dir}/stbImage/*.cpp"

                    "${Source_Android_Dir}/*.cpp"

    )

add_library(StudyCoreObjec SHARED ${srcSource})

target_include_directories( StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Core/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Engine/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Math/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Resource/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Graphics/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Sample/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/RenderCore/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Scene/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Common_Dir}/Container/>

                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_TP_Dir}/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_TP_Dir}/glm>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_TP_Dir}/glm/gtc/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_TP_Dir}/glm/gtx/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_TP_Dir}/glm/detail/>
                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_TP_Dir}/stbImage/>

                            StudyCoreObjec PRIVATE $<BUILD_INTERFACE:${Source_Android_Dir}/Android/>
                          )

target_link_libraries(StudyCoreObjec
     android
     GLESv3
     log
     )