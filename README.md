# Howitzer Simulator

An interactive C++ artillery simulation built with OpenGL, featuring real-time aiming, projectile physics, terrain collision, and a target-hit objective.

## Overview

This project simulates firing a howitzer across procedurally generated terrain. You can rotate the barrel, fire a shell, and observe the projectile trajectory over time (including drag and gravity effects). A built-in unit-test runner executes automatically at startup.

## Features

- **Interactive controls** for aiming and firing.
- **Procedurally generated terrain** with randomized target placement.
- **Projectile physics** including:
  - gravity (`9.80665 m/s²`),
  - simple drag model,
  - time-stepped integration.
- **Hit detection states**:
  - target hit,
  - ground hit,
  - out-of-bounds.
- **Trajectory trail rendering** so you can visually follow shell flight.
- **Integrated test runner** covering core simulation/math classes.

## Controls

- **Left Arrow**: rotate barrel left.
- **Right Arrow**: rotate barrel right.
- **Up Arrow**: fine adjustment toward horizontal.
- **Down Arrow**: fine adjustment away from horizontal.
- **Space**: fire (only when no active projectile is in flight).

## Build and Run

### Windows (Visual Studio)

1. Open `Lab12.sln` in Visual Studio.
2. Select `Debug|x64` (recommended for local development).
3. Build and run the `Lab12` project.

The repository already includes the referenced OpenGL-related NuGet package folders under `packages/`.

### macOS (Xcode)

1. Open `Lab12.xcodeproj`.
2. Build and run the `Lab12` scheme.

## Startup Behavior

When the app starts, it first runs unit tests from `testRunner()` and then launches the interactive OpenGL simulation window.

## Project Structure

- `main.cpp` – main loop, input handling, render callback, and simulation orchestration.
- `ground.*` – terrain generation, target placement, and drawing.
- `projectile.*` – projectile state, fire/advance logic, and flight path storage.
- `physics.*`, `velocity.*`, `acceleration.*`, `angle.*`, `position.*` – core math and physics abstractions.
- `test*.h`, `test.cpp`, `unitTest.h` – unit-test suite and runner.
- `uiDraw.*`, `uiInteract.*` – drawing/input utilities.

## Notes

- This is a simulation-style educational project and intentionally uses straightforward time-step updates for readability.
- Physics values and control tuning can be adjusted in source to experiment with behavior.

## License

No explicit license file is included in this repository. If you plan to distribute or reuse this code, add a license file first.
