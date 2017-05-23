# ;#+
## An extended version of [;#](https://codegolf.stackexchange.com/questions/121921)

;#+ is basically ;# but Turing Complete.

## Memory layout

;#+ has two accumulators: primary and secondary. They are also referred to as **A** and **B**, respectively.  There is a delta value, or **&Delta;**. Furthermore, ;#+ has a memory tape of size 1000 by default. This can be written to and read from. To read from this tape, there is a pointer, **P**.

## Commands

Without further ado:

    +    add accumulators together into the current accumulator
    ;    increase accumulator by the delta value
    :    increase pointer by delta value
    -    negate the delta value
    #    mod 127 the accumulator, output ascii char, and reset accumulator
    <    read cell from memory into accumulator
    >    save accumulator into memory
    ~    swap accumulator with secondary accumulator
    .    go to the (accumulator)th position in memory
    *    read character of input into accumulator
    (    if the accumulator is zero, skip to the next matching `)`
    )    if the accumulator is not zero, rewind to the previous matching `(`
    p    print the numeric value of the accumulator
    `    show debug information
    !    set accumulator to 1 if zero; otherwise, 0

## Proof of Turing completeness

One can show that there is a one-to-one correspondence between ;#+ and [BF](http://esolangs.org/wiki/Brainfuck):

| BF Command | ;#+ Equivalent |
|:----------:|:--------------:|
| `>`        | `:`            |
| `<`        | `-:-`          |
| `+`        | `;`            |
| `-`        | `-;-`          |
| `[`        | `(`            |
| `]`        | `)`            |
| `,`        | `*`            |
| `.`        | `#`            |

Technically, `.` and `#` have different output behaviours, but the functionality remains the same.
