cmake_minimum_required(VERSION 3.15)

project(MOUSE_TEST VERSION 0.0.1)

add_subdirectory(JUCE)

juce_add_gui_app(MouseInputApp
    VERSION 0.0.1
    COMPANY_NAME MckAudio
    PRODUCT_NAME "MouseInputTest"
)

juce_generate_juce_header(MouseInputApp)

target_sources(MouseInputApp
    PRIVATE
    ./Source/Main.cpp
    ./Source/MainComponent.cpp
    ./Source/MainComponent.h
)
target_compile_definitions(MouseInputApp
    PRIVATE
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_USE_XINPUT2=1
)

target_link_libraries(MouseInputApp
    PRIVATE
    juce::juce_core
    juce::juce_data_structures
    juce::juce_events
    juce::juce_graphics
    juce::juce_gui_basics
    juce::juce_gui_extra
    PUBLIC
    juce::juce_recommended_config_flags
    juce::juce_recommended_lto_flags
    juce::juce_recommended_warning_flags
)