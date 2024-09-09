# Project Virealis

**Project Virealis** is a 3D physics simulation application written in C++, mainly using the Standard Library (STL) and dependencies on OpenGL and ImGui. It is my personal project to explore various theories and methodologies, including:

- Basic game physics engine capabilities
- Physics-based animation (PBA) algorithms
- Graphics rendering pipeline
- Modern C++ development practices
- Entity-Component-System (ECS) architecture

The current focus is achieving basic interactive 3D functionalities, with plans to implement advanced PBA algorithms soon.




virealis/
├── assets/
├── build/
├── build-debug/
├── include/
│   ├── glad/
│   │   └── glad.h
│   ├── KHR/
│   │   └── khrplatform.h
│   ├── imgui/
│   │   ├── imconfig.h
│   │   ├── imgui_impl_glfw.h
│   │   └── ...other imgui headers
│   └── virealis/
│       ├── Math/
│       │   ├── Constants.hpp
│       │   ├── Matrix4x4.hpp
│       │   ├── Vector2.hpp
│       │   └── Vector3.hpp
│       ├── Core/
│       │   ├── Entity.hpp
│       │   └── EntityManager.hpp
│       ├── Components/
│       │   ├── CameraComponentManager.hpp
│       │   ├── MaterialComponentManager.hpp
│       │   ├── MeshComponentManager.hpp
│       │   └── TransformComponentManager.hpp
│       ├── Rendering/
│       │   └── Shader.hpp
│       ├── Scene/
│       │   └── Scene.hpp
│       └── Systems/
│           └── RenderingSystem.hpp
├── shaders/
├── src/
│   ├── Math/
│   │   ├── Matrix4x4.cpp
│   │   └── Vector3.cpp
│   ├── Core/
│   │   └── EntityManager.cpp
│   ├── Components/
│   │   ├── CameraComponentManager.cpp
│   │   ├── MaterialComponentManager.cpp
│   │   ├── MeshComponentManager.cpp
│   │   └── TransformComponentManager.cpp
│   ├── glad/
│   │   └── glad.c
│   ├── imgui/
│   │   └── ...imgui source files
│   ├── Rendering/
│   │   └── Shader.cpp
│   ├── Scene/
│   │   └── Scene.cpp
│   └── Systems/
│       └── RenderingSystem.cpp
├── tests/
├── CMakeLists.txt
├── main.cpp
└── README.md

