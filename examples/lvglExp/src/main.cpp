#include <stdio.h>
#include "pico/stdlib.h"



#include "hardware/clocks.h"
extern "C"{
#include "bsp_i2c.h"
#include "lv_port.h"
#include "bsp_battery.h"
#include "bsp_lcd_brightness.h"
#include "Widgets.h"
}


void set_cpu_clock(uint32_t freq_khz)
{
    set_sys_clock_khz(freq_khz, true);
    clock_configure(
        clk_peri,
        0,
        CLOCKS_CLK_PERI_CTRL_AUXSRC_VALUE_CLKSRC_PLL_SYS,
        freq_khz * 1000,
        freq_khz * 1000);
}

int main()
{
    stdio_init_all();
    bsp_battery_init(100);
    set_cpu_clock(220 * 1000);
    bsp_i2c_init();
    lv_port_init();
    bsp_lcd_brightness_init();
    bsp_lcd_brightness_set(50);

    Widgets_Init();
    while (true)
    {
        lv_timer_handler();
        sleep_ms(1);
    }
}
