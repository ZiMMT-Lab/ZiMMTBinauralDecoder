# ZiMMT Binaural Decoder

A real-time binaural decoder for the 32-channel hemispherical loudspeaker array of the Center for Immersive Media Art, Music and Technology (ZiMMT) in Leipzig. The plugin performs partitioned convolution using measured BRIRs from a dummy head equipped with DPA microphones, enabling binaural monitoring of spatial audio productions.

## Download

Pre-built binaries for Windows, macOS, and Linux are available on the [Releases page](https://github.com/ZiMMT-Lab/ZiMMTBinauralDecoder/releases).

## Build Instructions

### Prerequisites
- CMake 3.15 or higher
- C++ compiler with C++17 support
- Git

### Building from Source
```bash
git clone --recursive https://github.com/ZiMMT-Lab/ZiMMTBinauralDecoder.git
cd ZiMMTBinauralDecoder
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Built plugins will be located in:
- **VST3**: `build/ZiMMTBinauralDecoder_artefacts/Release/VST3/`
- **Standalone**: `build/ZiMMTBinauralDecoder_artefacts/Release/Standalone/`

## License

This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International License - see the [LICENSE](LICENSE) file for details.