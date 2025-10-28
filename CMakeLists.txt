cmake_minimum_required(VERSION 3.16)
project(DFD-HEAT VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets 3DCore 3DRender 3DInput 3DExtras Sql Network)

set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/Viewport3D.cpp
    src/Custom3DWindow.cpp
    src/ViewportController.cpp
    src/ViewportSettings.cpp
    src/GridEntity.cpp
    src/AxisEntity.cpp
    src/AuthManager.cpp
    src/ModeManager.cpp
    src/MeshData.cpp
    src/SceneObject.cpp
    src/BoxObject.cpp
    src/ObjectManager.cpp
    src/SelectionManager.cpp
    src/PropertiesPanel.cpp
)

set(HEADERS
    include/MainWindow.h
    include/Viewport3D.h
    include/Custom3DWindow.h
    include/ViewportController.h
    include/ViewportSettings.h
    include/GridEntity.h
    include/AxisEntity.h
    include/AuthManager.h
    include/ModeManager.h
    include/MeshData.h
    include/SceneObject.h
    include/BoxObject.h
    include/ObjectManager.h
    include/SelectionManager.h
    include/PropertiesPanel.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Widgets
    Qt6::3DCore
    Qt6::3DRender
    Qt6::3DInput
    Qt6::3DExtras
    Qt6::Sql
    Qt6::Network
)

if(WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)