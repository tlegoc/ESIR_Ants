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
    Pheromone.h
    Pheromone.cpp
    AntBasePheromone.h
    AntBasePheromone.cpp
    Ant.h
    Ant.cpp
    AbstractRule.h
    OrRule.h
    OrRule.cpp
    AbstractAntRule.h
    AntWithRules.h
    AntWithRules.cpp
)

target_link_libraries(Ants PRIVATE Threads::Threads SDL2::GFX)

target_link_libraries(Ants
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
