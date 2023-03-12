


add_executable(uxui_demo
        src/main.cpp
)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows"
        AND ${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set_target_properties(uxui_demo
        PROPERTIES
            WIN32_EXECUTABLE ON
    )
endif()


target_link_libraries(uxui_demo
    PUBLIC
        uxui
)


