#ifndef BOARD_HAS_PSRAM
#error "Please enable PSRAM !!!"
#endif

#include <Arduino.h>
#include "epd_driver.h"
// #include "font/firasans.h"
#include "font/jp-font.h"
#include "pins.h"

uint8_t *framebuffer = NULL;

int cursor_x = 400;
int cursor_y = 250;

char *vocab[][2] = {
  {"こんにちは", "hello"},
  {"たべもの", "food"},
  {"ひとつ", "one (thing)"},
  {"ふたつ", "two (things)"},
  {"えん", "yen"},
  {"かね", "money"},
  {"これ", "this, this one"},
  {"すいようび", "Wednesday"},
  {"あれ", "that over there"},
};

int NUM_VOCAB = 9;

int vocab_index = 1;

void setup()
{
    Serial.begin(115200);
    delay(1000);
    framebuffer = (uint8_t *)ps_calloc(sizeof(uint8_t), EPD_WIDTH * EPD_HEIGHT / 2);
    if (!framebuffer)
    {
        Serial.println("alloc memory failed !!!");
        while (1)
            ;
    }
    memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);

    epd_init();

    epd_poweron();
    epd_clear();
    // epd_poweroff();

    // epd_poweron();
}

void loop()
{
    epd_poweron();
    epd_clear();

    // write_string((GFXfont *)&FiraSans, "Hello World", &cursor_x, &cursor_y, NULL);
    // epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    // delay(1000);

    // epd_draw_hline(10, random(10, EPD_HEIGHT), EPD_WIDTH - 20, 0, framebuffer);
    // epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    // delay(1000);

    // epd_draw_rect(10, random(10, EPD_HEIGHT), random(10, 60), random(10, 120), 0, framebuffer);
    // epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    // delay(1000);

    // epd_draw_circle(random(10, EPD_WIDTH), random(10, EPD_HEIGHT), 120, 0, framebuffer);
    // epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    // delay(1000);

    // epd_fill_rect(10, random(10, EPD_HEIGHT), random(10, 60), random(10, 120), 0, framebuffer);
    // epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    // delay(1000);

    // epd_fill_circle(random(10, EPD_WIDTH), random(10, EPD_HEIGHT), random(10, 160), 0, framebuffer);
    // epd_draw_grayscale_image(epd_full_screen(), framebuffer);
    // delay(1000);

    // memset(framebuffer, 0xFF, EPD_WIDTH * EPD_HEIGHT / 2);
    // epd_clear();

    // write_string((GFXfont *)&FiraSans, "Hello!", &cursor_x, &cursor_y, NULL);
    write_string((GFXfont *)&demo, vocab[vocab_index][0], &cursor_x, &cursor_y, NULL);
    cursor_x = 400;
    cursor_y = 400;
    write_string((GFXfont *)&demo, vocab[vocab_index][1], &cursor_x, &cursor_y, NULL);

    epd_draw_grayscale_image(epd_full_screen(), framebuffer);

    epd_poweroff();

    vocab_index += 1;
    vocab_index = vocab_index % NUM_VOCAB;

    cursor_x = 400;
    cursor_y = 250;

    delay(10000);
}