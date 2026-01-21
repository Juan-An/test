#include <common/bk_include.h>
#include <driver/lcd_types.h>

#define ST7789_CMD_NOP         0x00
#define ST7789_CMD_SWRESET     0x01
#define ST7789_CMD_SLPIN       0x10
#define ST7789_CMD_SLPOUT      0x11
#define ST7789_CMD_INVOFF      0x20
#define ST7789_CMD_INVON       0x21
#define ST7789_CMD_DISPOFF     0x28
#define ST7789_CMD_DISPON      0x29
#define ST7789_CMD_CASET       0x2A
#define ST7789_CMD_RASET       0x2B
#define ST7789_CMD_RAMWR       0x2C
#define ST7789_CMD_MADCTL      0x36
#define ST7789_CMD_COLMOD      0x3A
#define ST7789_CMD_PORCTRL     0xB2
#define ST7789_CMD_GCTRL       0xB7
#define ST7789_CMD_VCOMS       0xBB
#define ST7789_CMD_LCMCTRL     0xC0
#define ST7789_CMD_VRHSET      0xC3
#define ST7789_CMD_VDVSET      0xC4
#define ST7789_CMD_VCMOFSET    0xC5
#define ST7789_CMD_FRCTRL2     0xC6
#define ST7789_CMD_PWCTRL1     0xD0
#define ST7789_CMD_PVGAMCTRL   0xE0
#define ST7789_CMD_NVGAMCTRL   0xE1

static const lcd_qspi_init_cmd_t st7789v3_init_cmds[] = {
    { ST7789_CMD_SWRESET, {}, 0 },
    { 0xFF, { 0x05 }, 1 },
    
    { ST7789_CMD_SLPOUT, {}, 0 },
    { 0xFF, { 0x78 }, 1 },
    
    { ST7789_CMD_CASET, { 0x00, 0x28, 0x01, 0x67 }, 4 },  //列: 320
    { ST7789_CMD_RASET, { 0x00, 0x35, 0x01, 0x01 }, 4 },  //行: 172
    
    { ST7789_CMD_PORCTRL, { 0x0C, 0x0C, 0x00, 0x33, 0x33 }, 5 },
    { ST7789_CMD_FRCTRL2, { 0x00, 0x18 }, 2 },
    { ST7789_CMD_GCTRL, { 0x35 }, 1 },
    { ST7789_CMD_VCOMS, { 0x20 }, 1 },
    { ST7789_CMD_LCMCTRL, { 0x2C }, 1 },
    { ST7789_CMD_VRHSET, { 0x10 }, 1 },
    { ST7789_CMD_VDVSET, { 0x20 }, 1 },
    { ST7789_CMD_VCMOFSET, { 0x20 }, 1 },
    { ST7789_CMD_COLMOD, { 0x55 }, 1 },
    { ST7789_CMD_MADCTL, { 0x60 }, 1 },
    { ST7789_CMD_PWCTRL1, { 0xA4, 0xA1 }, 2 },
    { ST7789_CMD_PVGAMCTRL, {
    0xF0, 0x10, 0x12, 0x08, 0x06, 0x18, 0x2F,
    0x54, 0x42, 0x3C, 0x17, 0x14, 0x18, 0x1B
    }, 14 },
    { ST7789_CMD_NVGAMCTRL, {
    0xE0, 0x10, 0x12, 0x08, 0x06, 0x08, 0x29,
    0x54, 0x42, 0x3B, 0x16, 0x14, 0x17, 0x1B
    }, 14 },
    { ST7789_CMD_INVON, {}, 0 },
    { ST7789_CMD_DISPON, {}, 0 },


    { 0xFF, { 0x78 }, 1 },
};

static const lcd_spi_t lcd_spi_st7789v3_config = {
    .clk = LCD_QSPI_30M,
    .init_cmd = st7789v3_init_cmds,
    .device_init_cmd_len = sizeof(st7789v3_init_cmds) / sizeof(lcd_qspi_init_cmd_t),
};

const lcd_device_t lcd_device_st7789v3 = {
    .id = LCD_DEVICE_ST7789V3,
    .name = "st7789v3",
    .type = LCD_TYPE_SPI,
    .ppi = (205) << 16 | 320,
    .spi = &lcd_spi_st7789v3_config,
    .init = NULL,
    .lcd_off = NULL,
};