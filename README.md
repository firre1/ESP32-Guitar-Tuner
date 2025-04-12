# ESP32 Guitar Tuner with LED Feedback

This project implements a **basic guitar tuner** using an **ESP32 microcontroller**, analog sampling, and simple zero-crossing-based frequency detection.

When a guitar string is plucked:
- The signal is sampled using ADC
- The detected frequency is compared to standard tuning
- Two onboard LEDs (GPIO 12 and 13) indicate whether the note is:
  - Correct (both LEDs on)
  - Too low (LED 12 on)
  - Too high (LED 13 on)

---

## Supported Notes

| String | Note | Frequency (Hz) |
|--------|------|----------------|
| 1      | E4   | 329.63         |
| 2      | B3   | 246.94         |
| 3      | G3   | 196.00         |
| 4      | D3   | 146.83         |
| 5      | A2   | 110.00         |
| 6      | E2   | 82.41          |


## File Structure

| File         | Description                                   |
|--------------|-----------------------------------------------|
| `main.c`     | Entry point and main logic with LED control   |
| `notes.c/h`  | Converts frequency to musical note (optional) |
| `pins.c/h`   | GPIO setup and control (LED/button)           |
| `sampler.c/h`| ADC sampling and frequency detection          |
