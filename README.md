# STM32 Ball-and-Beam Closed-Loop Control System

Designed from the ground up to **mimic an industry-style, production-grade embedded software architecture**, this project implements a rigorous multi-layered abstraction model. Featuring a custom Board Support Package (BSP), decoupled peripheral drivers, and a robust, optimized PID control loop.

---

## Key Features

* **Custom PID Controller**: Implements time-weighted integration (`dt`), a low-pass filtered derivative term to eliminate sensor noise jitter, and division-by-zero protection.
* **Dynamic Anti-Windup Clamping**: Scales the raw integrator limit dynamically by `1 / Ki`, turning the limit into a true, predictable degree-based ceiling to neutralize stiction without severe windup overshoot.
* **High-Speed Hardware FPU**: Leverages the ARM Cortex-M4 floating-point unit for cycle-efficient single-precision floating-point math.
* **Live Virtual COM Port Interaction**: Allows real-time monitoring via 100ms asynchronous UART logs and live setpoint adjustments directly from a terminal.

---

## System Architecture & Directory Structure

```text
ball-and-beam/
├── App/                # Core application orchestration and run loop
├── BSP/                # Board Support Package (modular peripheral wrappers)
├── Common/             # Shared system-wide definitions and error codes
├── Controls/           # PID controller logic and mathematical routines
├── Core/               # STMicroelectronics CubeMX generated HAL & core setup
├── cad/                # Mechanical assets (.step interchange and .stl meshes)
├── CMakeLists.txt
└── README.md
```

---

## Hardware & Components

* **Microcontroller**: STMicroelectronics STM32L475VG (ARM Cortex-M4 with FPU)
* **Distance Sensor**: VL53L0X Time-of-Flight (ToF) sensor communicating via I²C
* **Actuator**: Standard Servo motor driven via hardware PWM (Timer channels)
* **Development Toolchain**: CMake, Ninja, VS Code, and STM32CubeMX

---

## Control Loop Mathematics & Logic

To effectively manage physical **static friction (stiction)** near the center balance point without introducing violent limit-cycle rocking, the PID routine incorporates several safeguards:

1. **Derivative Filtering**: 
   `derivative_filtered = (alpha * prev_derivative) + ((1.0 - alpha) * raw_derivative)`
   * Smooths millimeter-level jitter from the VL53L0X sensor before the derivative term multiplies it.
2. **Scaled Integrator Clamping**: 
   `integrator_limit = degree_limit / Ki`
   * Prevents runaway accumulation while allowing the integrator to build just enough torque to break through mechanical stiction cleanly.

---

## Live Telemetry & Control

The system transmits real-time telemetry over UART every 100 ms:
```text
Distance: 77.34 mm | Set Point: 77.00 | Error: -0.34 | Integrator: -40.35
```

---

## Getting Started

1. **Clone the Repository**:
   ```bash
   git clone [https://github.com/aniranaway/ball-and-beam.git](https://github.com/aniranaway/ball-and-beam.git)
   ```
2. **Open in VS Code**: Open the workspace directory with CMake and Ninja configured for ARM-none-eabi.
3. **Build the Project**:
   ```bash
   cmake --preset default
   cmake --build build
   ```
4. **Flash & Run**: Flash the resulting binary to your STM32L475VG using STM32CubeProgrammer or your preferred debugger.