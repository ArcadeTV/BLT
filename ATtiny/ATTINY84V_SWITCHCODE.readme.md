### SWITCHCODE for ATtiny84
#### v20221101
##### ArcadeTV

```
                _____
       VCC  01-|°    |-14 GND
            02-|     |-13 BUTTON  (0)
            03-|     |-12 RESET   (1)
            04-|     |-11 !RESET  (2)
            05-|     |-10 LED-R   (3)
            06-|     |-09 LED-G   (4)
!TOGGLE (6) 07-|_____|-08 TOGGLE  (5)

low:   0xE2
high:  0xD7
ext.:  0xFF
lock:  0xFF
```

-------------------------------------

### Description:

This mcu code toggles 2 pins high or low upon a button-press.
Feedback is given by 2 LED lines for 2 different colors and activation-blink-effect.
Also a 150ms reset signal is sent upon toggling from separate pins for either active-low or active-high systems.
The last state is saved to eprom and restored on power cycling.

### Compiling

Compile with Arduino IDE (select ATtinyCore as board) or your favorite AVR toolkit.

-------------------------------------

| PIN      | Function                                                                 |
| -------- | ------------------------------------------------------------------------ |
| BUTTON  | Connect a switch to GND. No external pull-up or hardware-debounce needed. |
| RESET   | Send a reset signal for 150ms to an active-high system.                  |
| !RESET  | Send a reset signal for 150ms to an active-low system.                   |
| LED-R   | Connect a red LED pin with common-cathode via an appropriate resistor.   |
| LED-G   | Connect a green LED pin with common-cathode via an appropriate resistor. |
| TOGGLE  | Is set either HIGH or LOW depending on which state is active.            |
| !TOGGLE | Is set either LOW or HIGH depending on which state is active.            |
