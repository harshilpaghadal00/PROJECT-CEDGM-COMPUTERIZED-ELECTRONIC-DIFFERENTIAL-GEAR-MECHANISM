# PROJECT CEDGM : COMPUTERIZED ELECTRONIC DIFFERENTIAL GEAR MECHANISM

<img width="715" height="715" alt="image" src="https://github.com/user-attachments/assets/01364dd7-0ade-43f1-a03b-7f7150a98125" />

Welcome to the **PROJECT CEDGM : COMPUTERIZED ELECTRONIC DIFFERENTIAL GEAR MECHANISM** project. This repository contains the complete suite of mechanical designs, electronic documentation, and firmware required to build, assemble, and run an Arduino-controlled Differential Gear Mechanism.

## Project Structure

The project is divided into three main subsystems:

### 1. Mechanical System (`01 - PROJECT CEDGM : COMPUTERIZED ELECTRONIC DIFFERENTIAL GEAR MECHANISM - MECHANICAL SYSTEM`)

Contains the CAD models for 3D printing and modification. Files are provided in `.f3d` (Fusion 360), `.step` (Standard 3D CAD), and `.stl` (Ready for 3D Printing) formats.

* **01 - Standard External Involute Miter Bevel Gear**
* **02 - T-Shape Standard External Involute Miter Bevel Gear Connector**
* **03 - 28BYJ-48 Stepper Motor (Mockup/Mount)**
* **04 - Primary Support Mechanism (Right Side)**
* **05 - Primary Support Mechanism (Left Side)**
* **06 - Differential Gear Mechanism** (Full assembly)
* **07 - Differential Gear Mechanism Base**

### 2. Electronic System (`02 - PROJECT CEDGM : COMPUTERIZED ELECTRONIC DIFFERENTIAL GEAR MECHANISM - ELECTRONIC SYSTEM`)

Contains all necessary datasheets and wiring documentation to safely build the circuit.

* **01 - 28BYJ-48 Stepper Motor Data Sheet**
* **02 - ULN2003 Stepper Motor Driver Data Sheet**
* **03 - Arduino UNO Data Sheet**
* **04 - Power Supply & Pin Configuration Documentation**

### 3. Embedded System & Software (`03 - PROJECT CEDGM : COMPUTERIZED ELECTRONIC DIFFERENTIAL GEAR MECHANISM - EMBEDDED SYSTEM & SOFTWARE`)

Contains the logic and control code for the microcontroller.

* **FINAL_FIRMWARE.ino**: The main Arduino sketch to upload to the board.
* **FIRMWARE FLOW.cpp**: A C++ file detailing the logic flow and algorithm of the firmware.

---

## 🛠️ Hardware Requirements

To build this project physically, you will need:

* 1x **Arduino UNO** (or compatible microcontroller)
* 1x (or more, as required) **28BYJ-48 Stepper Motor**
* 1x **ULN2003 Stepper Motor Driver Board**
* Appropriate **Power Supply** (Refer to the Power Supply Documentation in the Electronics folder)
* Jumper wires
* A 3D Printer and filament (PLA/PETG recommended) to print the mechanical parts.

---

## 🚀 Getting Started Guide

### Step 1: Mechanical Assembly

1. Locate the `.stl` files in the `01 - PROJECT CEDGM : COMPUTERIZED ELECTRONIC DIFFERENTIAL GEAR MECHANISM - MECHANICAL SYSTEM` folder.
2. Slice and 3D print the Base, Left/Right Support Mechanisms, Bevel Gears, and Connectors.
3. Assemble the printed parts. Use the Fusion 360 (`.f3d` or `.f3z`) files as a visual reference for how the components fit together.
4. Mount the **28BYJ-48 Stepper Motor** into the designated slot on the support mechanism.

### Step 2: Electronics Wiring

1. Connect the **28BYJ-48 Stepper Motor** to the **ULN2003 Driver Board**.
2. Open `04 - POWER SUPPLY & PIN CONFIGURATION DOCUMENTATION.pdf` in the Electronics folder to find the exact pin mapping.
3. Wire the ULN2003 Driver Board to the corresponding Digital I/O pins on the **Arduino UNO**.
4. Connect the power supply safely, ensuring the Arduino and the Motors receive appropriate voltage (do not draw stepper motor power directly from the Arduino's 5V pin if under heavy load).

### Step 3: Software Setup & Flashing

1. Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Navigate to `03 - PROJECT CEDGM : COMPUTERIZED ELECTRONIC DIFFERENTIAL GEAR MECHANISM - EMBEDDED SYSTEM & SOFTWARE/FINAL_FIRMWARE/`.
3. Open `FINAL_FIRMWARE.ino` in the Arduino IDE.
4. Connect your Arduino UNO to your computer via USB.
5. In the Arduino IDE, go to **Tools > Board** and select "Arduino Uno".
6. Go to **Tools > Port** and select the appropriate COM port.
7. Click the **Upload** button to flash the firmware to the board.

### Step 4: Execution

Once the upload is complete and power is supplied, the Arduino will begin executing the logic defined in `FIRMWARE FLOW.cpp`, driving the stepper motor and actuating the differential gear mechanism.
