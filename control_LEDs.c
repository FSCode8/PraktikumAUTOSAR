#include "autosar_simu.h"
//#include "Pwm.h"
//#include "Spi.h"

// PWM LED Control Functions
// ========================

/**
 * Set RGB LED brightness using PWM
 * @param red_channel: PWM channel for red LED
 * @param green_channel: PWM channel for green LED  
 * @param blue_channel: PWM channel for blue LED
 * @param red_brightness: 0x0000 (min) to 0x8000 (max)
 * @param green_brightness: 0x0000 (min) to 0x8000 (max)
 * @param blue_brightness: 0x0000 (min) to 0x8000 (max)
 */
void SetRgbLed(Pwm_ChannelType red_channel, Pwm_ChannelType green_channel, 
               Pwm_ChannelType blue_channel, uint16 red_brightness, 
               uint16 green_brightness, uint16 blue_brightness)
{
    Pwm_SetDutyCycle(red_channel, red_brightness);
    Pwm_SetDutyCycle(green_channel, green_brightness);
    Pwm_SetDutyCycle(blue_channel, blue_brightness);
}

/**
 * Turn off RGB LED completely
 */
void TurnOffRgbLed(Pwm_ChannelType red_channel, Pwm_ChannelType green_channel, 
                   Pwm_ChannelType blue_channel)
{
    Pwm_SetDutyCycle(red_channel, 0x0000);
    Pwm_SetDutyCycle(green_channel, 0x0000);
    Pwm_SetDutyCycle(blue_channel, 0x0000);
}

/**
 * Set RGB LED to maximum brightness
 */
void SetRgbLedMax(Pwm_ChannelType red_channel, Pwm_ChannelType green_channel, 
                  Pwm_ChannelType blue_channel)
{
    Pwm_SetDutyCycle(red_channel, 0x8000);
    Pwm_SetDutyCycle(green_channel, 0x8000);
    Pwm_SetDutyCycle(blue_channel, 0x8000);
}

// SPI LED Stripe Control Functions
// ================================

// Buffer for 10 LEDs * 3 colors (RGB) = 30 bytes
uint8 ledStripeBuffer[30];

/**
 * Set color for a specific LED in the stripe
 * @param led_index: LED number (0-9)
 * @param red: Red intensity (0-255)
 * @param green: Green intensity (0-255)
 * @param blue: Blue intensity (0-255)
 */
void SetStripeLedColor(uint8 led_index, uint8 red, uint8 green, uint8 blue)
{
    if (led_index < 10) // Ensure valid LED index
    {
        uint8 base_index = led_index * 3;
        ledStripeBuffer[base_index] = red;      // R
        ledStripeBuffer[base_index + 1] = blue; // B  
        ledStripeBuffer[base_index + 2] = green; // G
    }
}

/**
 * Update the LED stripe with current buffer contents
 */
Std_ReturnType UpdateLedStripe(void)
{
    Std_ReturnType result;
    
    // Write data to internal SPI buffer
    result = Spi_WriteIB(0, ledStripeBuffer);
    
    if (result == E_OK)
    {
        // Transmit the buffer contents
        result = Spi_SyncTransmit(0);
    }
    
    return result;
}

/**
 * Clear all LEDs in the stripe (turn them off)
 */
void ClearLedStripe(void)
{
    uint8 i;
    for (i = 0; i < 30; i++)
    {
        ledStripeBuffer[i] = 0;
    }
    UpdateLedStripe();
}

// Example Usage Functions
// =======================

void LedControlExample(void)
{
    // Example PWM channel assignments (adjust based on your configuration)
    Pwm_ChannelType pwm_red = 0;
    Pwm_ChannelType pwm_green = 1;
    Pwm_ChannelType pwm_blue = 2;
    
    // Initialize LED stripe buffer
    ClearLedStripe();
    
    // Example 1: Set PWM LED to purple (red + blue)
    SetRgbLed(pwm_red, pwm_green, pwm_blue, 0x8000, 0x0000, 0x8000);
    
    // Example 2: Set first 3 LEDs in stripe to different colors
    SetStripeLedColor(0, 255, 0, 0);    // LED 0: Red
    SetStripeLedColor(1, 0, 255, 0);    // LED 1: Green  
    SetStripeLedColor(2, 0, 0, 255);    // LED 2: Blue
    UpdateLedStripe();
}