# metronome
Prints tick

Initial timer = 500ms (for now)

Chose `CLOCK_MONOTONIC` instead of cpu clock because- when the process stops, the clock pauses- this will cause inconsistency.

Highest priority is set just after `clock_nanosleep` wakes up so the cpu will schedule it as soon as it moves from `blocked` > `ready`.

Printing current time to check efficiency at each _tick_.
