from pathlib import Path
from functools import reduce

lines = (Path(__file__).resolve().parent.parent.parent / 'data' / 'day10.txt').read_text().splitlines()
p1, hist = 0, reduce(lambda s, l: (s[0] + (int(l.split(' ')[1])) if l.split(' ')[0] == 'addx' else s[0],
                                   [*s[1], *([s[0]] * (2 if l.split(' ')[0] == 'addx' else 1))]), lines[:], (1, []))[1]

print("Part 2: ")
for i in range(0, len(hist)):
    if i % 40 == 20:
        p1 += hist[i - 1] * i

    sprite_position = hist[i]
    screen_x = i % (40 * 6) % 40
    do_draw = abs(sprite_position - screen_x) < 2

    print('#' if do_draw else '.', end='\n' if (screen_x + 1) % 40 == 0 else '')

print("Part 1", p1)
