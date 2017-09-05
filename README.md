# lab20-soton

This project was written for a university assignment. The goal was to communicate between two Raspberry Pis (model 3).
The end result was a drawing application (similar to Microsoft Paint) that was run on two RPis connected to each other via GPIO pins.
When a drawing is drawn on the application of one RPi, it is instantaneously replicated on the application present on the other RPi. It is also thread safe, thus allowing two artists to collaborate and work on a piece of art at the same time without conflicts. The drawing whiteboard, is the GUI of the app.It is written in the C++ framework, QT. The protocols for sending data over GPIO are written and need no additional communication protocols( i.e: I2C, UART) to work.

# Requirements

* C++11
* QT 5.8 (could work with other QT versions, hasn't been tested)
* WiringPi library. Can be downloaded from http://wiringpi.com/download-and-install
* POSIX thread library:
  * Install for Debian/Ubuntu:
    ```
    sudo apt-get install libpthread-stubs0-dev
    ```
* Run the program as root as it uses GPIO pins:
  ```
  sudo ./lab20
  ```
# Pin Configuration

The current pin configuration is hardcoded, but could be changed to be read from a file or arg.

|First RPI|Connect|Second RPI|
| ------- |-----| -------- |
| Pin 0   |<------>| Pin 1    |
| Pin 2   |<------>| Pin 4    |
| Pin 3   |<------>| Pin 5    |
| Pin 1   |<------>| Pin 0    |
| Pin 4   |<------>| Pin 2    |
| Pin 5   |<------>| Pin 3    |
