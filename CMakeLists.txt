# Copyright (C) 2022-2023 Jacob R. Green
# All Rights Reserved.


add_library(uxui
    STATIC
        src/Uxui.cpp
        src/Application.cpp
        src/Window.cpp
        src/Events.cpp
        src/UIElement.cpp
        src/Visual.cpp
        src/Controls/Control.cpp
        src/Controls/ContentControl.cpp
        src/Controls/Button.cpp
        src/Controls/Border.cpp
        src/Controls/Label.cpp
        src/Controls/Image.cpp
        src/Panels/Panel.cpp
        src/Panels/StackPanel.cpp
        src/Panels/GridPanel.cpp
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
