# ZiMMT Binaural Decoder CMakeLists.txt

cmake_minimum_required(VERSION 3.15)

project(ZiMMTBinauralDecoder VERSION 1.0.0)

if(UNIX AND NOT APPLE)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

add_subdirectory(JUCE)                  

juce_add_plugin(ZiMMTBinauralDecoder
    VERSION 1.0.0
    COMPANY_NAME "ZiMMT"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE
    PLUGIN_MANUFACTURER_CODE ZiMM
    PLUGIN_CODE ZiBD
    FORMATS VST3 Standalone
    PRODUCT_NAME "ZiMMTBinauralDecoder"
    PLUGIN_NAME "ZiMMT Binaural Decoder")

juce_generate_juce_header(ZiMMTBinauralDecoder)

target_sources(ZiMMTBinauralDecoder
    PRIVATE
        PluginEditor.cpp
        PluginProcessor.cpp)

target_compile_definitions(ZiMMTBinauralDecoder
    PUBLIC
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0)

juce_add_binary_data(BinaryData SOURCES
        assets/brirs/zimmt_brir_lspk1.wav
        assets/brirs/zimmt_brir_lspk2.wav
        assets/brirs/zimmt_brir_lspk3.wav
        assets/brirs/zimmt_brir_lspk4.wav
        assets/brirs/zimmt_brir_lspk5.wav
        assets/brirs/zimmt_brir_lspk6.wav
        assets/brirs/zimmt_brir_lspk7.wav
        assets/brirs/zimmt_brir_lspk8.wav
        assets/brirs/zimmt_brir_lspk9.wav
        assets/brirs/zimmt_brir_lspk10.wav
        assets/brirs/zimmt_brir_lspk11.wav
        assets/brirs/zimmt_brir_lspk12.wav
        assets/brirs/zimmt_brir_lspk13.wav
        assets/brirs/zimmt_brir_lspk14.wav
        assets/brirs/zimmt_brir_lspk15.wav
        assets/brirs/zimmt_brir_lspk16.wav
        assets/brirs/zimmt_brir_lspk17.wav
        assets/brirs/zimmt_brir_lspk18.wav
        assets/brirs/zimmt_brir_lspk19.wav
        assets/brirs/zimmt_brir_lspk20.wav
        assets/brirs/zimmt_brir_lspk21.wav
        assets/brirs/zimmt_brir_lspk22.wav
        assets/brirs/zimmt_brir_lspk23.wav
        assets/brirs/zimmt_brir_lspk24.wav
        assets/brirs/zimmt_brir_lspk25.wav
        assets/brirs/zimmt_brir_lspk26.wav
        assets/brirs/zimmt_brir_lspk27.wav
        assets/brirs/zimmt_brir_lspk28.wav
        assets/brirs/zimmt_brir_lspk29.wav
        assets/brirs/zimmt_brir_lspk30.wav
        assets/brirs/zimmt_brir_lspk31.wav
        assets/brirs/zimmt_brir_lspk32.wav
        assets/zimmt_bypassWindow.svg
        assets/zimmt_decodeWindow.svg
        assets/zimmt_buttonOn.svg
        assets/zimmt_buttonOff.svg
        assets/zimmt_buttonOn_hover.svg
        assets/zimmt_buttonOff_hover.svg
)

target_link_libraries(ZiMMTBinauralDecoder
    PRIVATE
        BinaryData
        juce::juce_audio_utils
        juce::juce_dsp
        juce::juce_graphics
        juce::juce_gui_basics
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)
