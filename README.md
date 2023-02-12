![Connection Diagram](connection_diagram.png "Connection Diagram")

## Compilation

Run Arduino IDE.  
Open "pwm_to_sbus_pro_mini_3v3.ino".  
Select board -> "Arduino Pro or Pro Mini".  
Tools -> Processor -> "ATmega328P (3.3V, 8 MHz)".  
Sketch -> Verify/Compile.  
Sketch -> Upload.  

## Connection

Connect directly to the RCIN(SBUS) port of the controller.

WHITE: 3.3V SBUS output  
RED: 5V power input  
BLACK: GND  

Arduino pins 2 to 9: PWM inputs.  
CH1: pin 9  
...  
CH8: pin 2  
