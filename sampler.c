#include "sampler.h"
#include <driver/adc.h>
#include "esp_timer.h" 
#include <esp_log.h>


static esp_timer_handle_t timer_handle;
static const adc_channel_t channel = ADC_CHANNEL_6;
static const adc_bits_width_t width = ADC_WIDTH_BIT_12;
static const adc_atten_t atten = ADC_ATTEN_DB_11;
int DEFAULT_VREF = 1100;
int sample = 1100;
int previous = 0;
int counter = 0;

void IRAM_ATTR isr_handler(void* arg){
    previous = sample;
    sample = adc1_get_raw(channel);
    if ((sample < DEFAULT_VREF && previous > DEFAULT_VREF) ||
        (sample > DEFAULT_VREF && previous < DEFAULT_VREF)) {
        counter++;
    }
}

/**
* Starts sampling on a given pin (GPIO34) with a given frequency.
* Parameter freq: the sampling frequency
*/
void startSampling(int freq){
    // ADC
    adc1_config_width(width);
    adc1_config_channel_atten(channel, atten);

    // Timer-interrupts
    esp_timer_create_args_t timer_config = {
        .callback = isr_handler, 
        .name = "sample_timer"
    };

    esp_timer_create(&timer_config, &timer_handle);
    esp_timer_start_periodic(timer_handle, 1000000 / freq); 
}

/**
* Stops the sampling process.
*/
void stopSampling(){
    esp_timer_stop(timer_handle);
}

/**
* Resets frequency detection without stopping the sampling process.
*/
void resetSampling(){
    counter = 0;
}

/**
* Computes the average frequency of the signal that has been (or is being) sampled.
*/
float getFrequency(){
    float freq = counter / 2.0;
    return freq;
}
