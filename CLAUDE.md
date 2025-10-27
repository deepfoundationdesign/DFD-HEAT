# DFD-HEAT: 3D FEM Heatflow Application for BIM

## Project Overview
A professional-grade 3D Finite Element Method (FEM) heatflow simulation application for Building Information Modeling (BIM), designed for thermal analysis of structures in the German construction industry (Gutachten and project designs).

## Core Components

### 1. 3D Modeling Environment (Godot-based)
- **Blender-like Interface**: Implement familiar 3D modeling tools mimicking Blender's workflow
- **Technical Drawing Import**: Support for importing/referencing technical drawings as modeling guides
- **Object Creation**: Standard primitives and complex geometry creation tools
- **Face Selection System**: Blender-style face/edge/vertex selection for boundary condition assignment
- **Material Assignment**: Attach building material properties to objects/faces

### 2. Meshing System (GMSH Integration)
- **GMSH DLL Integration**: Direct integration with GMSH library for mesh generation
- **Material Tagging**: Preserve material boundaries during meshing
- **Clean Geometry**: Maintain sharp boundaries between different materials
- **Mesh Quality Control**: Parameters for controlling mesh density and quality

### 3. FEM Solver
- **Conductivity Matrix Assembly**: Build thermal conductivity matrices from mesh and materials
- **Steady-State Solver**: Solve time-independent heat transfer problems
- **Transient Solver**: Solve time-dependent heat transfer problems
- **Temperature Field Calculation**: Compute temperatures at any point in the structure

### 4. Visualization & Analysis
- **Temperature Field Visualization**: Color-mapped temperature display on 3D model
- **Heat Flux Visualization**: Display heat flow vectors and paths
- **Report Generation**: Export results for Gutachten documentation

## Technical Architecture

### Technology Stack
- **3D Framework**: Qt3D with C++ and QML
- **UI Framework**: Qt6 with Qt Widgets/QML
- **Meshing**: GMSH library (C++ DLL)
- **FEM Solver**: Custom C++ implementation with Eigen
- **Material Database**: SQLite with Qt SQL module

### Key Modules
1. **Scene Manager**: Handles 3D scene, objects, and transformations
2. **Modeling Tools**: Blender-like modeling operations
3. **Material Manager**: Database of building materials with thermal properties
4. **Boundary Condition Manager**: Apply and manage boundary conditions
5. **Mesh Generator**: Interface to GMSH for mesh creation
6. **FEM Engine**: Matrix assembly and solving routines
7. **Post-Processor**: Results visualization and analysis

## Building Material Properties Required
- Thermal conductivity (λ)
- Specific heat capacity (c)
- Density (ρ)
- Emissivity (ε)
- Common materials: Concrete, brick, insulation, glass, steel, wood, air gaps

## Boundary Conditions Types
- **Temperature (Dirichlet)**: Fixed temperature on surfaces
- **Heat Flux (Neumann)**: Fixed heat flow through surfaces
- **Convection (Robin)**: Heat transfer to surrounding air
- **Radiation**: Radiative heat transfer between surfaces

## Mathematical Foundation

### Heat Equation (Transient)
```
ρc ∂T/∂t = ∇·(k∇T) + Q
```

### Steady-State
```
∇·(k∇T) + Q = 0
```

Where:
- T: Temperature
- t: Time
- k: Thermal conductivity
- Q: Heat source/sink
- ρ: Density
- c: Specific heat

## Development Phases

### Phase 1: Foundation
- Set up Godot project structure
- Implement basic 3D scene management
- Create material database schema
- Design UI layout

### Phase 2: Modeling Tools
- Implement Blender-like navigation
- Add primitive creation tools
- Implement face/edge/vertex selection
- Material assignment system

### Phase 3: GMSH Integration
- Integrate GMSH library
- Implement mesh generation pipeline
- Material boundary preservation
- Mesh quality verification

### Phase 4: FEM Solver
- Implement matrix assembly
- Steady-state solver
- Transient solver
- Boundary condition application

### Phase 5: Visualization
- Temperature field rendering
- Heat flux visualization
- Report generation
- Export capabilities

## Technical Decisions

### 1. Architecture
- **Framework**: Qt6 with Qt3D for complete application
- **Language**: Pure C++ for entire application (UI and solver)
- **3D Rendering**: Qt3D scene graph with custom geometry
- **FEM Solver**: Integrated C++ implementation using Eigen

### 2. GMSH Integration
- Direct DLL integration with GMSH 4.11+
- Use MSH format for mesh data exchange
- Material tagging preserved through physical groups

### 3. FEM Solver
- Custom C++ implementation using Eigen library
- Phase 1: Steady-state solver
- Phase 2: Transient solver (future enhancement)
- Problem size: Desktop up to 2M nodes, Server 10-100M nodes (future)

### 4. Material Database
- Include DIN 4108 and EN ISO 10456 standard materials
- SQLite database via Qt SQL module
- Temperature-dependent properties for advanced simulations

### 5. File Formats (Initial Phase)
- **Project**: Custom format (.dfdheat) - JSON/Binary hybrid using Qt JSON
- **Mesh**: MSH format from GMSH
- **Future**: IFC import for geometry (not in MVP)

### 6. 3D Modeling and Navigation
- Custom Qt3D viewport with Blender-like navigation
- Qt3D entity-component system for scene management
- Custom mesh manipulation tools
- Focus on wall elements and simple geometries initially

### 7. Performance Targets
- Desktop: Handle up to 2M elements
- Real-time preview for smaller models
- Server infrastructure for 10-100M elements (future phase)

### 8. Development Priority
1. Main application structure and architecture
2. Basic UI layout
3. Core classes and interfaces
4. Simple 3D modeling capabilities
5. Basic meshing and boundary conditions
6. Steady-state solver
7. Visualization
8. Advanced features (IFC import, transient solver, etc.)

## Implementation Challenges and Solutions

### Qt3D Mouse Event Handling

**Challenge**: Qt3DWindow captures all mouse events internally, making custom navigation controls difficult to implement.

**Problem Investigation**:
- Initial approach using QWidget::eventFilter() failed because Qt3DWindow consumes mouse events
- QOrbitCameraController exists but has hardcoded mouse button mappings (left=move, right=rotate)
- Cannot subclass QOrbitCameraController due to private implementation details
- Documentation shows this is a common Qt3D limitation

**Research Sources**:
- Qt Forum discussions about overriding QOrbitCameraController behavior
- Stack Overflow questions about Qt3DWindow mouse event handling
- Qt3D documentation on input handling system

**Solution Implemented**:
1. **Custom Qt3DWindow Subclass**: Created `Custom3DWindow` inheriting from `Qt3DExtras::Qt3DWindow`
2. **Override Mouse Events**: Directly override `mousePressEvent()`, `mouseMoveEvent()`, `mouseReleaseEvent()`, `wheelEvent()`
3. **Signal-Based Communication**: Custom window emits signals (`orbitRequested`, `panRequested`, `zoomRequested`)
4. **Blender-Style Controls**:
   - Middle mouse + drag = Orbit camera
   - Shift + Middle mouse + drag = Pan camera
   - Mouse wheel = Zoom
5. **Event Handling Logic**:
   ```cpp
   if (event->button() == Qt::MiddleButton) {
       m_shiftPressed = (event->modifiers() & Qt::ShiftModifier);
       if (m_shiftPressed) {
           m_panning = true;
       } else {
           m_orbiting = true;
       }
   }
   ```

**Key Technical Details**:
- Must include `<Qt3DExtras/QForwardRenderer>` for background color control
- Use `setMouseGrabEnabled(true)` for proper mouse tracking
- Connect signals from Custom3DWindow to ViewportController for camera manipulation
- Fallback to Qt3DWindow default behavior for non-middle mouse events

**Alternative Approaches Considered**:
1. **Qt3D Input System**: Using QMouseDevice/QMouseHandler (more complex, QML-oriented)
2. **Event Filter on Container**: Doesn't work due to Qt3DWindow event consumption
3. **Modifying QOrbitCameraController**: Not possible due to private implementation

**Lessons Learned**:
- Qt3D input handling requires careful approach due to internal event processing
- Subclassing Qt3DWindow is the most reliable method for custom mouse controls
- Always check Qt documentation and community forums for Qt3D-specific limitations
- Signal-slot pattern works well for decoupling input handling from camera logic

This solution provides professional Blender-style navigation that feels natural to CAD users while maintaining clean architecture.

### Qt3D Lighting and Materials Setup

**Challenge**: Initial 3D objects appeared completely black with white background, indicating lighting/material issues.

**Root Cause Analysis**:
- Qt3D requires proper lighting setup - objects appear black without adequate lighting
- Default Qt3D background is white, unprofessional for CAD applications
- Basic material properties insufficient for realistic rendering
- Need proper Phong shading model implementation

**Solution Implemented**:

1. **Three-Point Lighting System**:
   ```cpp
   // Key Light (main illumination)
   auto *light = new Qt3DRender::QDirectionalLight();
   light->setColor(QColor(255, 255, 255));
   light->setIntensity(1.0f);
   light->setWorldDirection(QVector3D(-0.5f, -1.0f, -0.5f).normalized());

   // Fill Light (soften shadows)
   auto *fillLight = new Qt3DRender::QDirectionalLight();
   fillLight->setColor(QColor(180, 180, 200));
   fillLight->setIntensity(0.4f);

   // Rim Light (edge definition)
   auto *rimLight = new Qt3DRender::QDirectionalLight();
   rimLight->setColor(QColor(255, 255, 220));
   rimLight->setIntensity(0.3f);
   ```

2. **Professional Material Properties**:
   ```cpp
   auto *material = new Qt3DExtras::QPhongMaterial();
   material->setDiffuse(QColor(120, 150, 220));      // Base color
   material->setAmbient(QColor(60, 75, 110));        // Shadow color
   material->setSpecular(QColor(255, 255, 255));     // Highlight color
   material->setShininess(50.0f);                    // Surface finish
   ```

3. **Dark Professional Background**:
   ```cpp
   // In Custom3DWindow constructor
   defaultFrameGraph()->setClearColor(QColor(60, 60, 60));
   ```

**Key Technical Requirements**:
- Each light must be attached to its own QEntity
- Include `<Qt3DExtras/QForwardRenderer>` for background color access
- Use `QDirectionalLight` for consistent lighting across scene
- Apply complete Phong material properties (diffuse/ambient/specular/shininess)
- Normalize light direction vectors for predictable behavior

**Visual Results**:
- Professional dark gray background (like Blender/Autodesk products)
- Properly lit objects with realistic shading and highlights
- Clear material differentiation between objects
- Suitable for long CAD sessions (easier on eyes)

This creates the professional appearance expected from engineering software while maintaining good performance for complex 3D scenes.

## Current Status

### ✅ Completed Features:
- Qt6/Qt3D application framework with CMake build system
- Professional MainWindow with docking panels for all FEM tools
- Custom Blender-style 3D navigation (middle mouse orbit, shift+middle pan, wheel zoom)
- Professional three-point lighting system with proper materials
- Dark CAD-style background and realistic object shading
- Comprehensive project documentation and architecture

### 🔧 Technical Achievements:
- Solved Qt3D mouse event handling through custom Qt3DWindow subclass
- Implemented professional lighting system for realistic 3D rendering
- Clean OOP architecture with proper separation of concerns
- Signal-slot communication pattern for decoupled component interaction

### 📊 Application State:
The application now provides a solid foundation for FEM thermal analysis with professional-grade 3D visualization that matches the quality of commercial CAD software.

## Next Steps
1. Implement RGB axis lines and 1m engineering grid
2. Create material database with DIN/EN standards
3. Develop object creation tools for building elements
4. Integrate GMSH for mesh generation
5. Build FEM solver with Eigen linear algebra
3. Create proof-of-concept for each major component
4. Iterative development with testing

## Commands for Development
- Lint: `godot --check-only`
- Test: `godot --test`
- Build: `godot --export`