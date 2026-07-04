//Base exemple of lib
#include "ulp_lp_core_utils.h"
#include "ssd1306_lp.h"

// For linker ESP-IDF (do not remove)
uint32_t ulp_lp_perf_counter = 0; 
uint32_t ulp_lp_done_flag = 0;
//This for track RAM usage
uint32_t ulp_lp_memory_usage = 0;
extern uint32_t _bss_end;    

int main(void) {
    oled_lp_init(); //init display
    oled_lp_set_fps(30);  //set FPS 1-30

    while (ulp_lp_done_flag == 0) {
        ulp_lp_memory_usage = (uint32_t)&_bss_end - 0x50000000; //Track RAM
        ulp_lp_perf_counter++; 
        
        oled_lp_clear_buffer(); //clear display

        oled_lp_draw_frame(); //frame 1px                                     
        oled_lp_draw_string(10, 10, "HELLO ULP!", 1, false); //text       
        oled_lp_draw_rect(10, 24, 108, 16, 4, 1, false, true); //rect checkered fill

        oled_lp_refresh_sync(); //start update display
    }
    return 0;
}

//Stress-Test LP core & Display:
//#include "ulp_lp_core_utils.h"
//#include "ssd1306_lp.h"
//uint32_t ulp_lp_perf_counter = 0; volatile uint32_t ulp_lp_done_flag = 0; uint32_t ulp_lp_memory_usage = 0; extern uint32_t _bss_end;
//#define OBJ_COUNT 12
//typedef struct { int16_t x, y; int8_t vx, vy; uint8_t size; } DynamicObj;
//int main(void) {
//    oled_lp_init(); oled_lp_set_fps(20); DynamicObj objects[OBJ_COUNT];
//    for(uint8_t i = 0; i < OBJ_COUNT; i++) { objects[i].x = (i * 10) % 100; objects[i].y = (i * 5) % 40; objects[i].vx = (i % 2 == 0) ? 2 : -2; objects[i].vy = (i % 3 == 0) ? 2 : -2; objects[i].size = 10 + (i * 2); }
//    uint8_t frame_count = 0;
//    while (ulp_lp_done_flag == 0) {
//        ulp_lp_memory_usage = (uint32_t)&_bss_end - 0x50000000; ulp_lp_perf_counter++; frame_count++;
//        oled_lp_set_inversion((frame_count % 60) < 15); oled_lp_set_contrast(50 + (frame_count % 80)); oled_lp_clear_buffer();
//        for(uint8_t i = 0; i < OBJ_COUNT; i++) {
//            objects[i].x += objects[i].vx; objects[i].y += objects[i].vy;
//            if (objects[i].x <= 0 || objects[i].x >= 100) objects[i].vx = -objects[i].vx;
//            if (objects[i].y <= 0 || objects[i].y >= 40) objects[i].vy = -objects[i].vy;
//            oled_lp_draw_rect(objects[i].x, objects[i].y, objects[i].size, objects[i].size, (i % 4), 1, false, (i % 2 == 0));
//            oled_lp_draw_line(64, 32, objects[i].x, objects[i].y, 1);}
//        for(uint8_t i = 0; i < 8; i++) { uint8_t x_start = (frame_count * 2 + i * 15) % 128; oled_lp_draw_line(x_start, 0, 127 - x_start, 63, 1); }
//        if (frame_count % 100 < 50) oled_lp_draw_string(20, 25, "STRESS TEST", 1, false);
//        oled_lp_refresh_sync();} return 0;}
