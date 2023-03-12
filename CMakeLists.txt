# Copyright (C) 2022-2023 Jacob R. Green
# All Rights Reserved.


add_library(uxui
    STATIC
        src/uxui.cpp
        src/application.cpp
        src/window.cpp
        src/events.cpp
        src/uielement.cpp
        src/visual.cpp
        src/Controls/control.cpp
        src/Controls/content_control.cpp
        src/Controls/button.cpp
        src/Controls/border.cpp
        src/Controls/label.cpp
        src/Controls/image.cpp
        src/Panels/panel.cpp
        src/Panels/stack_panel.cpp
        src/Panels/grid_panel.cpp
)

target_compile_definitions(uxui
    PRIVATE
        UXUI_INTERNALS
)


target_include_directories(uxui
    PUBLIC
        inc
)

target_link_libraries(uxui
    PUBLIC
        rndr
        xgdi
)

target_precompile_headers(uxui
    PUBLIC
        <muchcool/rndr.hpp>
        <muchcool/uxui.hpp>
)

add_subdirectory(Demo)

install(TARGETS uxui)