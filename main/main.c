#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
/*Alexandra Belliard
1/13/2026
This program allows an LED to toggle between ON and OFF on every other button click
Inputs: Button in pin 4
Outputs: LED in pin 10*/

#define LED_PIN  GPIO_NUM_10       // Choose your LED pin
#define BUTTON_PIN  GPIO_NUM_4    // Choose your button pin
#define BUTTON2_PIN GPIO_NUM_5    //Choose second button

bool pressed = false;            //Checks if the button is pressed
bool bstate = false;             //Remembers if the button has been pressed
bool lstate = false;             //Remember if LED flashed on the last button press
int counter = 0;                 //If counter is even, it will change the LED state, if odd, it will not change
bool loop = false;

void app_main(void) {

    gpio_reset_pin(LED_PIN);                         //Reset LED pin
    gpio_reset_pin(BUTTON_PIN);                      //Reset BUTTON pin
    gpio_reset_pin(BUTTON2_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);   //Configure LED output
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT); //Configure Button input
    gpio_set_direction(BUTTON2_PIN, GPIO_MODE_INPUT);
    gpio_pullup_en(BUTTON_PIN);                      //Enables pullup for the BUTTON pins
    gpio_pullup_en(BUTTON2_PIN);
    gpio_pulldown_dis(BUTTON_PIN);                   //Disables pulldown for the BUTTON_PINs
    gpio_pulldown_dis(BUTTON2_PIN); 
    gpio_pulldown_dis(LED_PIN);                      //Disables pullup and pulldown for the LED_PIN
    gpio_pullup_dis(LED_PIN);
    gpio_intr_disable(LED_PIN);                      //Disables the interrupt LED and BUTTON pins
    gpio_intr_disable(BUTTON_PIN);
    gpio_intr_disable(BUTTON2_PIN);

    while (1) {
        vTaskDelay(20 / portTICK_PERIOD_MS);
        if (gpio_get_level(BUTTON2_PIN)==0){
            pressed = gpio_get_level(BUTTON_PIN)==0;  //Detects when the button is pressed
             
        
            if (!bstate && pressed){                  //Remembers button is pressed
                bstate = true;
            }
            if (bstate && !pressed){                  //Remembers button is released and increases the counter
                bstate = false;
                counter++;
            }
            if (counter==2){                          //Only sets the level of the light every other button press, aka when counter=2
                lstate=!lstate;
                gpio_set_level(LED_PIN, lstate);
                counter=0;
            }
        }
    }
}
