#include "notes.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

/**
* Converts a frequency to a note.
* @param freq frequency, in Hz
* @param stringbuff pointer to a string with space for 2 characters and null terminator
*/
void freq2note(float frequency, char *stringbuff) {
    if (frequency >= 82.41 && frequency <= 329.63) { // E4 to E2
        char *notes[] = {"E4", "B3", "G3", "F3", "D3", "A2", "E2"};
        int note_nr = round(12 * log2(frequency / 329.63));
        note_nr = note_nr % 26;
        if (note_nr < 0) {
            note_nr += 26;
        }
        strcpy(stringbuff, notes[note_nr]);
    } else {
        strcpy(stringbuff, "?"); // Unknown or out of range frequency
    }
}

