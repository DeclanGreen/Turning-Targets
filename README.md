# Turning-Targets
This is for my Turning Targets project for Downshire Rifle Club.
Project created using an Arduino Uno v3 with MP3 player for voice callouts.
There are 6 LED's, 5 Buttons - 3 used and 2 unused; 1 x Relay controlling signal to the Turning Targets;
Sound amp and a 5W speaker for callouts; LCD Screen for menu selection; buck converter to reduce input voltage from 12v to 5v.

## Courses of fire

Use **Up** and **Down** to scroll the menu and **Select** to start.

| Menu item | What it runs |
|---|---|
| Precision Stage | Sport Pistol: Load, Attention, face 300 s, Unload |
| Rapid Fire | Sport Pistol: 5 cycles of edge 7 s, face 3 s |
| 150 Sec Series | Standard Pistol: face 150 s |
| 20 Sec Series | Standard Pistol: face 20 s |
| 10 Sec Series | Standard Pistol: face 10 s |
| T&P1 Practice 1 | Face 2 minutes (12 shots including reload) |
| T&P1 Practice 2 | 6 appearances of 2 s, 5 s apart |
| T&P1 Practice 3 | 3 appearances of 3 s, 5 s apart |
| Multi-Target P1 | Face 15 s |
| Multi-Target P2 | Face 10 s |
| Multi-Target P3 | 3 appearances of 3 s, 5 s apart |
| Multi-Target P4 | Face 8 s |
| About | Credits |
| Reset Counters | Sets every series counter back to the start |
| Load Wait | Changes the wait between "Load" and "Attention" |

The Sport and Standard Pistol stages follow the sequence documents in this repo: announce **Load**, wait, announce **Attention** and turn the targets to edge, face them 7 s later, then turn them to edge with **Unload** and face them again 7 s after that.

## Range Officer features

### Series counter
Each stage counts its series so the Range Officer knows where they are in the programme. The LCD shows it all the way through, for example `Series 3/6`.

| Stage | Series |
|---|---|
| Precision Stage | Sighter, then 1/6 to 6/6 |
| Rapid Fire | Sighter, then 1/6 to 6/6 |
| 150 Sec Series | Sighter, then 1/4 to 4/4 |
| 20 Sec Series | 1/4 to 4/4 |
| 10 Sec Series | 1/4 to 4/4 |

Each time a stage is selected it runs the next series. After the last one the LCD shows "All series done" and the counter goes back to the start. **Reset Counters** clears them all at once. The counters are lost when the power goes off.

### Early stop
During the face period of the **Precision Stage** (300 s) and the **150 Sec Series**, the LCD counts down the seconds left (`Face 287 SEL=End`). If all the shooters have finished, press **Select**. The targets turn to edge, "Unload" is announced, and they face again 7 s later.

### Adjustable load wait
The wait between "Load" and "Attention" is 60 s. To shorten it, select **Load Wait**, use **Up**/**Down** to change it in 10 s steps (10 to 60 s), and press **Select** to save. It applies to every Sport and Standard Pistol stage, and goes back to 60 s when the power is switched on.

## Test mode
The line `#define TEST_MODE 1` at the top of `sketch_mar20b.ino` selects short timings for bench testing, and the startup screen shows "TEST MODE". **Set it to `0` before uploading for use on the range.**

| Timing | Test mode (1) | Match (0) |
|---|---|---|
| Load wait | 6 s (adjustable 1 to 6 s) | 60 s (adjustable 10 to 60 s) |
| Precision face | 3 s | 300 s |
| 150 Sec Series face | 5 s | 150 s |
| 20 Sec Series face | 2 s | 20 s |
| T&P1 Practice 1 face | 5 s | 120 s |

All the other timings are the same in both modes.

## Wiring

| Pin | Connected to |
|---|---|
| 2, 3 | DFPlayer Mini (pin 2 to module RX, pin 3 to module TX) |
| 4 | LED: 10 Sec Series |
| 5 | Relay: HIGH = targets edge, LOW = targets face |
| 6 | LED: 150 Sec Series |
| 7 | LED: Rapid Fire |
| 8 | LED: 20 Sec Series |
| 9 | LED: Precision, T&P1 and Multi-Target |
| 10, 11, 12 | Up, Down and Select buttons (to ground, internal pull-ups) |
| A4, A5 | I2C LCD at address 0x27 |

## MP3 tracks on the SD card

| Track | Callout |
|---|---|
| 1 | Unload |
| 2 | Attention |
| 3 | 10 Seconds Series - Load |
| 4 | 20 Seconds Series - Load |
| 5 | 150 Seconds Series - Load |
| 7 | Precision Stage - Load |
| 8 | Rapid Fire Stage - Load |
| 16 | About screen |
| 19 | Initialising System - Please Wait |

## Building
Open `sketch_mar20b.ino` in the Arduino IDE with the board set to **Arduino Uno**. It needs two libraries from the Library Manager: **LiquidCrystal I2C** (Frank de Brabander) and **DFRobotDFPlayerMini**.
