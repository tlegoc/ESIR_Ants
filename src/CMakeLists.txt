add_executable(Ants
    main.cpp
    Environment.h
    Environment.cpp
    MathUtils.h
    Rectangle.h
    Renderer.h
    Renderer.cpp
    Timer.h
    Timer.cpp
    Vector2.h
    Agent.h
    Agent.cpp
    Food.h
    Food.cpp
    Anthill.h
    Anthill.cpp
    AntBase.h
    AntBase.cpp
    SillyAnt.h
    SillyAnt.cpp
)

target_link_libraries(Ants Threads::Threads SDL2::Main SDL2::GFX)