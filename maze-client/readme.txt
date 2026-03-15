#Project Description#
This project is based on the pololu-3pi-2040-robot sample program. It uses CMake together with the Raspberry Pi Pico SDK to compile and generate a UF2 file for the Pololu 3pi+ 2040 robot.


#Environment Setup#
Installing the Toolchain
Please refer to this README for environment configuration.
https://github.com/pololu/pololu-3pi-2040-robot/blob/master/c/README.md
In order for CMake to locate the Pico SDK, add its path (for example, the folder containing pico-sdk) to your system or user environment variables, or specify it manually when generating build configuration.


#Project Structure Reference#
C:/msys64/home/XXX/pololu-3pi-2040-robot/c/
├── pico-sdk/                 // This is the official Pico SDK
├── pololu-3pi-2040-robot/    // Optionally clone the official sample project here
├── your_project/             // This is your own project
│   ├── CMakeLists.txt
│   ├── src/
│   │   └── main.c            // Or other source files
│   └── include/              // Place header files here if needed
└── ...


#Configuring and Building an Example#
(in mysys2ucrt64)
cd your_project
mkdir build
cd build
cmake ..
cmake --build .
After a successful build, a .uf2 file will be generated in the build folder.


#Flashing the UF2 File onto the 3pi+ 2040 Robot#
Connect the robot to your computer via USB.
Press and hold the B button, then briefly press the reset button.
When the robot is recognized as a removable drive (usually named RPI-RP2), drag and drop the xxx.uf2 file from the build folder into the RPI-RP2 drive.
Once the file transfer is complete, the device will automatically reboot and run the new program.