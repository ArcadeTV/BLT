## BLT (Button Layout Toggler)
### v20221101
#### ArcadeTV

![BLT pcb](https://github.com/ArcadeTV/BLT/blob/main/blt_brd.png?raw=true)

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


#### Description:
This pcb remaps 4 buttons of a common-ground controller to two different layouts,
given that your controller has a 6-button-layout.
I was tired of having to reconfigure my arcade stick every time I switched games between
Street Fighter (6 Buttons) and Neo Geo (4 Buttons), so I came up with a solution that 
goes between the first four input signal lines from either a supergun or jamma harness.
The toggler pad on the pcb goes to a switch that connects to GND. This will trigger
the switching process and visual feedback can be added by an optional 2-color-LED.
Buttons 5 and 6 are not involved.

#### Microcontroller:
Please mind that the ATtiny84 microcontroller needs to be programmed
with the provided hex file.

#### PCB
Use the provided gerber files to order your pcb from your favorite manufacturer,
e.g. (OSH Park)[https://oshpark.com/shared_projects/dgzMkW6Z]
Eagle source files for editing also exist in this repository.

#### Installation
Populate the pcb after programming the ATtiny microcontroller.
Connect the lines coming from your supergun or jamma harness to the pads
marked with IN. Connect the button-lines to the pads marked OUT.
Connect a switch to the toggler-pad on the upper right of the pcb that
connects to GND upon being pressed.
Install a 2-color-LED as you see fit. (Adjust R1 and R2 according to your LED specs)

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
