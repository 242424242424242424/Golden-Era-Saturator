# ⚜️ Golden Era Saturator v2.4.0 (Elite Signature Edition)
![Version](https://img.shields.io/badge/Version-2.4.0-gold) ![Build](https://img.shields.io/badge/Build-Succeeded-green) ![Platform](https://img.shields.io/badge/Platform-macOS%20%7C%20Windows-blue) ![Technology](https://img.shields.io/badge/Technology-ADAA%20%7C%20JUCE-orange)

Developed by **PSYCHODEL BEATS** & **PsychoAudioPlugins**

**Golden Era Saturator** is a professional-grade virtual analog saturation plugin. It leverages cutting-edge DSP techniques to deliver the warmth, depth, and harmonic richness of vintage tube hardware with modern digital precision.

## ⚛️ Cutting-Edge DSP Architecture

### 1. ADAA Technology (Anti-Derivative Antialiasing)
Unlike standard saturation algorithms that suffer from aliasing (digital harshness), our engine implements **First-Order ADAA**. By using the mathematical antiderivative of the saturation curve, we eliminate aliasing artifacts at the source, providing a silky-smooth high-end even at extreme drive settings.

### 2. 4x Polyphase IIR Oversampling
The entire non-linear signal path is wrapped in a high-quality **4x Oversampling** engine using Polyphase IIR filters. This ensures maximum phase linearity and perfect reconstruction of the analog waveform.

### 3. Magnetic Hysteresis Modeling
We don't just "clip" the signal. Our engine models **Magnetic Hysteresis**, simulating the physical memory effects of tape heads and transformers. This results in a unique "punch" and "weight" that is missing in typical digital saturators.

### 4. Asymmetric Tube Emulation
The saturation curve is meticulously tuned to generate **rich even-order harmonics**, mimicking the behavior of triode vacuum tubes. One half of the waveform saturates exponentially, while the other follows a trigonometric curve, creating a complex, pleasing harmonic profile.

## 📦 Key Features
- **Elite Analog Warmth:** From subtle enhancement to aggressive grit.
- **RMS Auto-Gain Compensation:** Perceived volume stays consistent regardless of the Drive setting.
- **Denormal Protection:** Rock-solid stability for professional production environments.
- **Phase-Aligned Mixing:** Perfect Dry/Wet blend for parallel processing.

## 🛠️ Installation
### macOS
1. Download the `.pkg` installer from the [Releases](https://github.com/242424242424242424/Golden-Era-Saturator/releases) section.
2. Run the installer to place the **Audio Unit (AU)** and **VST3** in your system folders.
3. Restart your DAW.

### Windows
1. Copy the `GoldenEraSaturator.vst3` file to your VST3 directory (typically `C:\Program Files\Common Files\VST3`).

---
## 💻 For Developers (Source Code)
This project is built using **C++17** and the **JUCE Framework**.
To compile from source:
```bash
git clone https://github.com/242424242424242424/Golden-Era-Saturator.git
cd Golden-Era-Saturator
cmake -B build
cmake --build build --config Release
```

---
*© 2026 PSYCHODEL BEATS & PsychoAudioPlugins. Powered by Psycho AI 24.*
