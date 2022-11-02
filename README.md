## BLT (Button Layout Toggler)
### v20221101
#### ArcadeTV

| Part | Value            | Device           | Package             |
| ---- | ---------------- | ---------------- | ------------------- |
| CB1  | 100nF            | C-USC0805        | C0805               |
| CB2  | 100nF            | C-USC0805        | C0805               |
| CB3  | 100nF            | C-USC0805        | C0805               |
| D1   |                  | DUOLED2X5        | DUOLED2X5           |
| IC1  | 74HC4066D        | 74HC4066D        | SOIC127P600X175-14N |
| IC2  | 74HC4066D        | 74HC4066D        | SOIC127P600X175-14N |
| IC3  | ATTINY84V-10SSUR | ATTINY84V-10SSUR | SOIC127P600X175-14N |
| R1   | 220              | R-US_R0805       | R0805               |
| R2   | 220              | R-US_R0805       | R0805               |

---
##### Microcontroller:
Please mind that the ATtiny84 microcontroller needs to be programmed
with the provided hex file.

##### Description:
This pcb remaps 4 buttons of a common-ground controller to two different layouts,
given that your controller has a 6-button-layout.
I was tired of having to reconfigure my arcade stick every time I switched games between
Street Fighter (6 Buttons) and Neo Geo (4 Buttons), so I came up with a solution that 
goes between the first four input signal lines from either a supergun or jamma harness.
The toggler pad on the pcb goes to a switch that connects to GND. This will trigger
the switching process and visual feedback can be added by an optional 2-color-LED.
Buttons 5 and 6 are not involved.

```
Layout #1 (Street Fighter Style):
   .-.   .-.   .-.
  ( 1 ) ( 2 ) ( 3 )
   '-'   '-'   '-'
 .-.   .-.   .-.
( 4 ) ( 5 ) ( 6 )
 '-'   '-'   '-'

Layout #2 (Neo Geo Style):
   .-.   .-.   .-.
  ( 2 ) ( 3 ) ( 4 )
   '-'   '-'   '-'
 .-.   .-.   .-.
( 1 ) ( 5 ) ( 6 )
 '-'   '-'   '-'

```

Tested on a HORI Fighting Stick V3 (PS3 Version) that was rewired with a DB15 cable and connector
for use with a MINIGUN v2.5. The PS button on that stick was wired for toggling.
