#include <stdio.h>
#include <esp_task_wdt.h>
#include <esp_timer.h>
#include "sampler.h"
#include "notes.h"
#include "pins.h"
#include <driver/gpio.h>

#define ESP_INTR_FLAG_DEFAULT 0
#define PUSH_TIME_US 250000 //250ms
static volatile uint64_t lastPush = -PUSH_TIME_US;
static volatile float fr;
int currentNote = 0;


static void buttonPress_handler(void *arg){
    uint64_t now = esp_timer_get_time();
    if ((now - lastPush) > PUSH_TIME_US){
        lastPush = now;
        if (currentNote < 5){
            currentNote++;
        } else if (currentNote == 5){
            currentNote = 0;
        }
    }
}

void setLeds(float freq, float min, float max){
    if (freq >= min && freq <= max){
        setLED(12,1);
        setLED(13,1);
    } else if (freq < min) {
        setLED(12,1);
    } else if (freq > max){
        setLED(13,1);
    }   
}

void app_main(){
    initLEDPin(12);
    initLEDPin(13);
    initButtonPin(18);
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(18,buttonPress_handler,NULL);
    vTaskDelay(pdMS_TO_TICKS(5000));

    printf("If this led turns on it means the note is too low \n");
    setLED(12,1);
    setLED(13,0);
    vTaskDelay(pdMS_TO_TICKS(4000));

    printf("If this led turns on it means the note is too high \n");
    setLED(12,0);
    setLED(13,1);
    vTaskDelay(pdMS_TO_TICKS(4000));

    for (int i = 0; i < 5; i++) {
        setLED(12, 1);
        setLED(13, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
        setLED(12, 0);
        setLED(13, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
    }

    while (1) {
        setLED(12, 0);
        setLED(13, 0);
        vTaskDelay(pdMS_TO_TICKS(2000));
        printf("\n");

        startSampling(6000);
        vTaskDelay(pdMS_TO_TICKS(1000));
        stopSampling();
        fr = getFrequency();

        switch(currentNote){
            case 0:
                //String: 1 (E), Freq: 329.63 Hz, Note: E4
                printf("Trying for note E4 \n");
                setLeds(fr,326.63,332.63);
                printf("Frequency is %.2f\n", fr);
                vTaskDelay(pdMS_TO_TICKS(2000));
                resetSampling();
                break;

            case 1:
                //String: 2 (B), Freq: 246.94 Hz, Note: B3
                printf("Trying for note B3 \n");
                setLeds(fr,243.94,249.94);
                printf("Frequency is %.2f\n", fr);
                vTaskDelay(pdMS_TO_TICKS(2000));
                resetSampling();
                break;

            case 2:
                //String: 3 (G), Freq: 196.00 Hz, Note: G3
                printf("Trying for note G3 \n");
                setLeds(fr,193.00,199.00);
                printf("Frequency is %.2f\n", fr);
                vTaskDelay(pdMS_TO_TICKS(2000));
                resetSampling();
                break;
                
            case 3:
                //String: 4 (D), Freq: 146.83 Hz, Note: D3
                printf("Trying for note D3 \n");
                setLeds(fr,143.83,149.83);
                printf("Frequency is %.2f\n", fr);
                vTaskDelay(pdMS_TO_TICKS(2000));
                resetSampling();
                break;

            case 4:
                //String: 5 (A), Freq: 110.00 Hz, Note: A2
                printf("Trying for note A2 \n");
                setLeds(fr,107.00,113.00);
                printf("Frequency is %.2f\n", fr);
                vTaskDelay(pdMS_TO_TICKS(2000));
                resetSampling();
                break;

            case 5:
                //String: 6 (E), Freq: 82.41 Hz, Note: E2
                printf("Trying for note E2 \n");
                setLeds(fr,79.41,85.41);
                printf("Frequency is %.2f\n", fr);
                vTaskDelay(pdMS_TO_TICKS(2000));
                resetSampling();
                break;

        }
    }
}
