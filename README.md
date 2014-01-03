EggbotSimulator_v1
==================

Version 1 of the EggbotSimulator
This Sketch is written to simulate an EiBotBoard: http://www.schmalzhaus.com/EBB/

It is configured for two Stepper motors driven with an ULN2003 (4 wires). To change this check the Accelstepper library.
The Servo is connected to pin 13.
The GSerialCommand can be found on my github.
"SM,1000,-3200,1600" MotorA executes one full revolution CCW. MotorB exectues half a turn in CW. Both stepper motors start the same time and end the same time. When done, returns OK
"SP,1" turns the Servo to 0. "SP,2" turns the Servo to 180 degrees.
"v" returns "EBB Version 2.1-\n", than "OK\n\r\n"
"QB" querries if the pause button has been clicked (0=not clicked, 1=clicked). For now itreturns "0\nOK\n\r" in the future a button will be added to toggle 1.
Any other command will be processed and will return OK.

Check http://mijnpws.wordpress.com/arduino-simuleert-eibotboard-inkscape-plugin/ for more information.
