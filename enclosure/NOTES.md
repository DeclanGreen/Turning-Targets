# Enclosure design notes

Status: first draft, NOT test printed. Component sizes are assumed until measured.

## Files
- `gen.mjs` generates both STLs (Node, needs `npm install manifold-3d@3.0.0`). Run `node gen.mjs`.
- `turning-targets-base.stl`, `turning-targets-lid.stl`

## Layout
Box 186 x 126 x 55 mm, 3 mm walls, lid 3 mm held by 4 x M3 screws into corner posts. Print the lid face-down.
- Base: Arduino Uno standoffs, left-wall USB/power cutouts, retaining pockets for relay, buck converter, DFPlayer and amp, rear holes for DC jack (11 mm) and relay cable (12 mm).
- Lid: LCD window, 5 button holes, 6 LED holes, speaker grille with locating ring.

## Measurements still needed (edit the values in `gen.mjs`)
| Item | Assumed | Where in gen.mjs |
|---|---|---|
| Button hole diameter | 12.5 mm | `BTN_D` |
| LED hole diameter | 5.3 mm (bare 5 mm LED) | `LED_D` |
| Speaker diameter | 57 mm (ring ID 58) | `sx,sy`, ring |
| LCD module / window | 80x36 / 71x24 mm, holes 75x31 | `lcx,lcy` |
| Relay module | 50 x 26 mm | `pocket(80,8,...)` |
| Buck converter | 43 x 21 mm | `pocket(80,44,...)` |
| DFPlayer Mini | 21 x 21 mm | `pocket(140,8,...)` |
| Amp board | 20 x 16 mm | `pocket(140,40,...)` |
| DC jack / cable gland | 11 mm / 12 mm | rear-wall cuts |
| Screw-hole positions on the small boards | not modelled | pockets are for tape/glue/ties |

## Other open items
- Pause feature was discussed but is NOT implemented. The sketch uses 3 buttons (pins 10, 11, 12); the other 2 are unwired in code.
- `TEST_MODE` is 1 in the sketch. Set to 0 before range use.
- README MP3 track table only lists 9 tracks.
