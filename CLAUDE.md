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

### 6. 3D Modeling
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

## Next Steps
1. Resolve open questions
2. Set up development environment
3. Create proof-of-concept for each major component
4. Iterative development with testing

## Commands for Development
- Lint: `godot --check-only`
- Test: `godot --test`
- Build: `godot --export`