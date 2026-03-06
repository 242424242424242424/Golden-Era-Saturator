cmake_minimum_required(VERSION 3.22)
project(PsychoSaturator VERSION 2.4.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ELITARNA METODA: Automatyczne pobieranie JUCE w locie
include(FetchContent)
FetchContent_Declare(
    juce
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG 8.0.12 # Dokładna wersja, której potrzebujemy
)
FetchContent_MakeAvailable(juce)

juce_add_plugin(PsychoSaturator
    VERSION 2.4.0
    PLUGIN_MANUFACTURER "PsychoAudioPlugins"
    PLUGIN_MANUFACTURER_CODE PSYP
    PLUGIN_CODE PSAT
    FORMATS AU VST3
    PRODUCT_NAME "PsychoSaturator"
)

target_sources(PsychoSaturator PRIVATE
    Source/PsychoSaturatorPlugin.cpp
    Source/PsychoSaturatorProcessor.cpp
    Source/PsychoSaturatorPluginEditor.cpp
    Source/main.cpp
)

target_compile_definitions(PsychoSaturator PRIVATE
    JUCE_PLUGINHOST_AU=1
    JUCE_VST3_CAN_REPLACE_VST2=0
)

target_link_libraries(PsychoSaturator PRIVATE
    juce::juce_audio_processors
    juce::juce_audio_utils
    juce::juce_dsp
    juce::juce_graphics
)
