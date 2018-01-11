#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"
#include <stdio.h>
#include <unistd.h>
#include <caml/callback.h>
#include <caml/mlvalues.h>
#include <caml/fail.h>
#include <caml/memory.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

#define CAML_ERROR_CHECK(x)    \
    do                         \
    {                          \
        esp_err_t rc = (x);    \
        if (rc != ESP_OK)      \
        {                      \
            caml_failwith(#x); \
        }                      \
    } while (0);

static char *argv[] = {"mirage", NULL};
extern void caml_startup(char **argv);

void app_main()
{
    caml_startup(argv);
}

CAMLprim value console_print(value str)
{
    CAMLparam1(str);
    const char *c_str = String_val(str);
    printf("%s\n", c_str);
    CAMLreturn(Val_unit);
}

CAMLprim value set_board_led(value on)
{
    CAMLparam1(on);
    uint32_t i;

    gpio_set_direction(GPIO_NUM_22, GPIO_MODE_OUTPUT);
    i = Bool_val(on);
    gpio_set_level(GPIO_NUM_22, i);

    CAMLreturn(Val_unit);
}

CAMLprim value sleep_ml(value seconds_val)
{
    CAMLparam1(seconds_val);
    int seconds = Int_val(seconds_val);

    sleep(seconds);

    CAMLreturn(Val_unit);
}
