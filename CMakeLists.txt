cmake_minimum_required(VERSION 3.16)
project(DFD-HEAT VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets 3DCore 3DRender 3DInput 3DExtras Sql Network)

set(SOURCES
    # Core
    src/core/main.cpp

    # UI
    src/ui/MainWindow.cpp
    src/ui/PropertiesPanel.cpp
    src/ui/SceneHierarchyPanel.cpp

    # Viewport
    src/viewport/Viewport3D.cpp
    src/viewport/Custom3DWindow.cpp
    src/viewport/ViewportController.cpp
    src/viewport/ViewportSettings.cpp

    # Scene
    src/scene/SceneObject.cpp
    src/scene/BoxObject.cpp
    src/scene/ObjectManager.cpp
    src/scene/SelectionManager.cpp
    src/scene/ModeManager.cpp
    src/scene/Collection.cpp

    # Entities
    src/entities/GridEntity.cpp
    src/entities/AxisEntity.cpp
    src/entities/CrosshairsOverlay.cpp
    src/entities/CrosshairsEntity3D.cpp

    # Mesh
    src/mesh/MeshData.cpp

    # Auth
    src/auth/AuthManager.cpp
)

set(HEADERS
    # UI
    include/ui/MainWindow.h
    include/ui/PropertiesPanel.h
    include/ui/SceneHierarchyPanel.h

    # Viewport
    include/viewport/Viewport3D.h
    include/viewport/Custom3DWindow.h
    include/viewport/ViewportController.h
    include/viewport/ViewportSettings.h

    # Scene
    include/scene/SceneObject.h
    include/scene/BoxObject.h
    include/scene/ObjectManager.h
    include/scene/SelectionManager.h
    include/scene/ModeManager.h
    include/scene/Collection.h

    # Entities
    include/entities/GridEntity.h
    include/entities/AxisEntity.h
    include/entities/CrosshairsOverlay.h
    include/entities/CrosshairsEntity3D.h

    # Mesh
    include/mesh/MeshData.h

    # Auth
    include/auth/AuthManager.h
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