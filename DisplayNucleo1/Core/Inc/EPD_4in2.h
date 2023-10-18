/*
 * EPD_4in2.h
 *
 *  Created on: Mar 14, 2023
 *      Author: keert
 */

#ifndef SRC_EPD_4IN2_H_
#define SRC_EPD_4IN2_H_

#include "DEV_Config.h"

// Display resolution
#define EPD_4IN2_WIDTH       400
#define EPD_4IN2_HEIGHT      300

void EPD_4IN2_Init_Fast(void);
void EPD_4IN2_Init_Partial(void);
void EPD_4IN2_Clear(void);
void EPD_4IN2_Display(UBYTE *Image);
void EPD_4IN2_Sleep(void);
void EPD_4IN2_PartialDisplay(UWORD X_start,UWORD Y_start,UWORD X_end,UWORD Y_end, UBYTE *Image);

void EPD_4IN2_Init_4Gray(void);
void EPD_4IN2_4GrayDisplay(const UBYTE *Image);

#endif /* SRC_EPD_4IN2_H_ */
