/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hello.pio.h"

// This example uses the default led pin
// You can change this by defining HELLO_PIO_LED_PIN to use a different gpio

int main() {
    PIO pio; //the pio block we are using
    uint sm; //sm is short for state machine (each pio has 2)
    uint offset; //the offset where ur program is actually in pio memory

    int input_pin = 15; //this goes by GPIO number, not the pin number, EX this is gpio 15, not pin 15.

    stdio_init_all();
    
    // This will find a free pio and state machine for our program and load it for us
    // We use pio_claim_free_sm_and_add_program_for_gpio_range so we can address gpios >= 32 if needed and supported by the hardware
    bool success = pio_claim_free_sm_and_add_program_for_gpio_range(&hello_program, &pio, &sm, &offset, input_pin, 1, true);
        //&hello_program: pointer to where your pio program is
        //&pio: either pio1, or pio2
        //&sm: which state machine is being used in the pio
        //&offset: sets the PC to the offset where your program actually is
        //HELLO_PID_LED_PIN: the GPIO pin we are going to use as output
        //1: how many gpio pins we are using
        //true: as far as I understand this is always true?
    hard_assert(success);
    
    // Configure it to run our program, and start it, using the
    // helper function we included in our .pio file.
    printf("Using gpio %d\n", input_pin);
    hello_program_init(pio, sm, offset, input_pin);

    uint32_t data = 0;
    while (true) {
        data = pio_sm_get_blocking(pio, sm);
        printf("data (in hex): %x\n", data);
        //sleep_ms(500);
    }



    // This will free resources and unload our program
    pio_remove_program_and_unclaim_sm(&hello_program, pio, sm, offset);
}