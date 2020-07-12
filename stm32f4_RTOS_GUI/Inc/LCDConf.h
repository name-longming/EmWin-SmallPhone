#ifndef _LCDCONF_H_
#define _LCDCONF_H_

#define LCD_XSIZE      (240)   /* X-resolution of LCD, Logical coor. */
#define LCD_YSIZE      (320)   /* Y-resolution of LCD, Logical coor. */

#define LCD_BITSPERPIXEL (16)

#define LCD_CONTROLLER 9328
#define LCD_FIXEDPALETTE   (565)   //调色板格式 
#define LCD_SWAP_RB        (1)     //红蓝反色交换 
#define LCD_INIT_CONTROLLER()   LCD_Config_Init();         //TFT初始化函

#endif



















