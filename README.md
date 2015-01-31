2015 Ramp Sensor
================

This is code for an Arduino Pro Mini to interface with a Pololu QTR-1RC
reflectivity sensor.  The 2015 competition robot will have two of these
assemblies located at the front of the robot to detect the white ramps.

Setup and Operation
-------------------

SENSOR_THRESHOLD in rampsensor.ino should be calibrated to a value that is
lower than the value returned when the robot is on red or blue carpet and above
the value returned when above the white ramps.  Use the DEBUG #define to output
sensor readings to the serial console.

Arduino GPIO pin 11 is configured as an OUTPUT and will go LOW when a white
ramp is detected.

