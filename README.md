# 8-Step Analog Sequencer for Eurorack Modular Synthesizers

## 🎵 Overview
A fully functional 8-step analog sequencer designed for Eurorack modular synthesizer systems, featuring an Arduino Uno as the control unit. This sequencer generates control voltages (CV) and gate signals for creating melodic patterns in real-time, suitable for both studio production and live performance.

## 🎯 Key Features
- **8-step sequence** with independent voltage settings per step
- **Dual-mode operation**: Master (internal clock) & Slave (external clock)
- **Eurorack compatible**: 1V/Octave standard, 3-5V gate signals
- **Complete output set**: Main outputs + individual outputs per step
- **Visual feedback**: LEDs for each step indicating active position
- **Variable sequence length**: 1-8 steps adjustable
- **BPM control**: 60-220 BPM in Master mode
- **Real-time control**: Immediate response to potentiometer adjustments

## 🔧 Technical Specifications
| Parameter | Specification |
|-----------|---------------|
| **CV Range** | 0-2V (2 octaves) |
| **Gate Level** | 3.24V @ 13.6ms pulse width |
| **Clock Input** | 0.77V minimum for trigger |
| **Operating Voltage** | 5V (USB/External) |
| **Control Voltage** | 1V/Octave standard |
| **Tempo Range** | 60-220 BPM |
| **Interface** | 1/8" (3.5mm) mono jacks |
| **Clock Input Protection** | Transistor-based interface with diode protection |

## 📁 Hardware Design

### Circuit Design (KiCad)
- **Microcontroller**: Arduino Uno R3
- **Multiplexers**: 3x 74HC4051 (8:1 Analog MUX/DEMUX)
- **Clock Input**: 2x 2N3904 BJT transistors with protection circuitry
- **Potentiometers**: 10 total (8x tone, 1x BPM, 1x sequence length)
- **Audio Connectors**: 19x 1/8" mono jacks
- **LEDs**: 9 total (1x main activity, 8x step indicators)

### Key Circuit Sections:
1. **Clock Input Stage**: Transistor-based interface circuit for safe external clock processing
2. **CV Signal Path**: Pot → MUX → Calibration → Output with precise 2V voltage range
3. **Gate Distribution**: Arduino → MUX → individual gate outputs with LED indicators
4. **Power Regulation**: Clean 5V supply for analog and digital sections

## 💾 Firmware (Arduino)

### Program Structure
```cpp
// Main Program Flow
1. Initialization (Pin setup, Bounce2 library)
2. Mode Detection (Master/Slave toggle)
3. Clock Source Selection
4. Sequence Management (Step advancement)
5. Multiplexer Control (Address bit generation)
6. Output Generation (CV & Gate signals)
