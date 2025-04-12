#include "pins.h"
#include <driver/gpio.h>

/* initialises the LED pin */
void initLEDPin(uint8_t pinN){
    gpio_config_t io_confD1;
    io_confD1.mode = GPIO_MODE_OUTPUT;
    io_confD1.pin_bit_mask = (u_int64_t)1 << pinN;
    gpio_config(&io_confD1);

}

/* initialises the button pin */
void initButtonPin(uint8_t pinN){
    gpio_config_t io_confB1;
    io_confB1.mode = GPIO_MODE_INPUT;
    io_confB1.pin_bit_mask = (u_int64_t)1 << pinN;
    io_confB1.pull_up_en = 1;
    io_confB1.pull_down_en = 0;
    io_confB1.intr_type = GPIO_INTR_NEGEDGE;
    gpio_config(&io_confB1);
}    

/* switches LED on if level!=0 or off if level==0*/
void setLED(uint8_t pinN, uint8_t level){
    if (level){
        gpio_set_level(pinN, 1);
    }
    else{
        gpio_set_level(pinN, 0);
    }
}