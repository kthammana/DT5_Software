/*
 * EPD_4in2_test.c
 *
 *  Created on: Mar 14, 2023
 *      Author: keert
 */

#include "EPD_Test.h"
#include "EPD_4in2.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//#include "20230209_Cap_Test_low_breathing.csv"

int EPD_test(void)
{
    printf("EPD_4IN2_test Demo\r\n");
    if(DEV_Module_Init()!=0){
        return -1;
    }

    printf("e-Paper Init and Clear...\r\n");
    EPD_4IN2_Init_Fast();
    EPD_4IN2_Clear();
    DEV_Delay_ms(500);

    //Create a new image cache
    UBYTE *BlackImage;
    /* you have to edit the startup_stm32fxxx.s file and set a big enough heap size */
    UWORD Imagesize = ((EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1)) * EPD_4IN2_HEIGHT;
    if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        return -1;
    }
    printf("Paint_NewImage\r\n");
    Paint_NewImage(BlackImage, EPD_4IN2_WIDTH, EPD_4IN2_HEIGHT, 0, WHITE);

#if 1   // show image for array
    printf("show image for array\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);
    Paint_DrawBitMap(gImage_4in2);
    EPD_4IN2_Display(BlackImage);
    DEV_Delay_ms(500);
#endif

#if 1   // Drawing on the image
    //1.Select Image
    printf("SelectImage:BlackImage\r\n");
    Paint_SelectImage(BlackImage);
    Paint_Clear(WHITE);

    // 2.Drawing on the image
    printf("Drawing:BlackImage\r\n");
    Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
    Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
    Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
    Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawCircle(45, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(105, 95, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
    Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
    Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
    Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
    Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);
    Paint_DrawString_CN(130, 0, "���abc", &Font12CN, BLACK, WHITE);
    Paint_DrawString_CN(130, 20, "΢ѩ����", &Font24CN, WHITE, BLACK);

    printf("EPD_Display\r\n");
    EPD_4IN2_Display(BlackImage);
	DEV_Delay_ms(2000);
#endif
	printf("Support for partial refresh, but the refresh effect is not good, but it is not recommended\r\n");
#if 0
	EPD_4IN2_Init_Partial();
	printf("Partial refresh\r\n");
	PAINT_TIME sPaint_time;
	sPaint_time.Hour = 12;
	sPaint_time.Min = 34;
	sPaint_time.Sec = 56;
	UBYTE num = 20;
	for (;;) {
		sPaint_time.Sec = sPaint_time.Sec + 1;
		if (sPaint_time.Sec == 60) {
			sPaint_time.Min = sPaint_time.Min + 1;
			sPaint_time.Sec = 0;
			if (sPaint_time.Min == 60) {
				sPaint_time.Hour =  sPaint_time.Hour + 1;
				sPaint_time.Min = 0;
				if (sPaint_time.Hour == 24) {
					sPaint_time.Hour = 0;
					sPaint_time.Min = 0;
					sPaint_time.Sec = 0;
				}
			}
		}
		Paint_ClearWindows(150, 80, 150 + Font20.Width * 7, 80 + Font20.Height, WHITE);
		Paint_DrawTime(150, 80, &sPaint_time, &Font20, WHITE, BLACK);
		EPD_4IN2_PartialDisplay(150, 80, 150 + Font20.Width * 7, 80 + Font20.Height, BlackImage);
		DEV_Delay_ms(500);//Analog clock 1s
		num = num - 1;
		if(num == 0) {
			break;
		}
    }
#endif

	EPD_4IN2_Init_4Gray();
	printf("show Gray------------------------\r\n");
	free(BlackImage);
	BlackImage = NULL;
	Imagesize = ((EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 4 ): (EPD_4IN2_WIDTH / 4 + 1)) * EPD_4IN2_HEIGHT;
	if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
			printf("Failed to apply for black memory...\r\n");
			return -1;
	}
	Paint_NewImage(BlackImage, EPD_4IN2_WIDTH, EPD_4IN2_HEIGHT, 0, WHITE);
	Paint_SetScale(4);
	Paint_Clear(WHITE);

	Paint_DrawPoint(10, 80, BLACK, DOT_PIXEL_1X1, DOT_STYLE_DFT);
	Paint_DrawPoint(10, 90, BLACK, DOT_PIXEL_2X2, DOT_STYLE_DFT);
	Paint_DrawPoint(10, 100, BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);
	Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawLine(70, 70, 20, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	Paint_DrawRectangle(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	Paint_DrawRectangle(80, 70, 130, 120, BLACK, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawCircle(45, 95, 20, BLACK, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
	Paint_DrawCircle(105, 95, 20, WHITE, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawLine(85, 95, 125, 95, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawLine(105, 75, 105, 115, BLACK, DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawString_EN(10, 0, "waveshare", &Font16, BLACK, WHITE);
	Paint_DrawString_EN(10, 20, "hello world", &Font12, WHITE, BLACK);
	Paint_DrawNum(10, 33, 123456789, &Font12, BLACK, WHITE);
	Paint_DrawNum(10, 50, 987654321, &Font16, WHITE, BLACK);
	Paint_DrawString_CN(140, 0, "���abc", &Font12CN, GRAY1, GRAY4);
	Paint_DrawString_CN(140, 40, "���abc", &Font12CN, GRAY2, GRAY3);
	Paint_DrawString_CN(140, 80, "���abc", &Font12CN, GRAY3, GRAY2);
	Paint_DrawString_CN(140, 120, "���abc", &Font12CN, GRAY4, GRAY1);

	Paint_DrawString_CN(220, 0, "΢ѩ����", &Font24CN, GRAY1, GRAY4);
	Paint_DrawString_CN(220, 40, "΢ѩ����", &Font24CN, GRAY2, GRAY3);
	Paint_DrawString_CN(220, 80, "΢ѩ����", &Font24CN, GRAY3, GRAY2);
	Paint_DrawString_CN(220, 120, "΢ѩ����", &Font24CN, GRAY4, GRAY1);

	EPD_4IN2_4GrayDisplay(BlackImage);
	DEV_Delay_ms(500);

	Paint_Clear(WHITE);
  EPD_4IN2_4GrayDisplay(gImage_4in2_4Gray);
	DEV_Delay_ms(2000);


	EPD_4IN2_Clear();
	EPD_4IN2_Init_Fast();
	printf("Goto Sleep...\r\n");
	EPD_4IN2_Sleep();
	free(BlackImage);
	BlackImage = NULL;

	// close 5V
	printf("close 5V, Module enters 0 power consumption ...\r\n");
	DEV_Module_Exit();

	return 0;
}

int EPD_test_2(void){
//initialize
	if(DEV_Module_Init()!=0){
	        return -1;
	    }
	//initize the full refresh
	EPD_4IN2_Init_Fast();
//clear screen
	EPD_4IN2_Clear();
	DEV_Delay_ms(500);
//declare image cache
	UBYTE *BlackImage;
	UWORD Imagesize = ((EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1)) * EPD_4IN2_HEIGHT;
	if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
		printf("Failed to apply for black memory...\r\n");
		return -1;
	}
//paint new image
	Paint_NewImage(BlackImage, EPD_4IN2_WIDTH, EPD_4IN2_HEIGHT, 0, WHITE);
//select image to be drawn on
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	Paint_DrawBitMap(gImage_4in2); //creates a monochrome background
	EPD_4IN2_Display(BlackImage);
	DEV_Delay_ms(500);
//draw point
	printf("SelectImage:BlackImage\r\n");
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);

	// 2.Drawing on the image
	printf("Drawing:BlackImage\r\n");
	//Paint_DrawLine(20, 70, 70, 120, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	 Paint_DrawPoint(((0.0090214/22.7260083)*400), ((9*300)/62), BLACK, DOT_PIXEL_3X3, DOT_STYLE_DFT);

	 EPD_4IN2_Display(BlackImage);
	 DEV_Delay_ms(2000);
//clear image
	 EPD_4IN2_Clear();
	 EPD_4IN2_Sleep();
	 DEV_Delay_ms(2000);
	 DEV_Module_Exit();

	 return 0;
}

int EPD_test_read_csv(void){
	//initialize
		if(DEV_Module_Init()!=0){
		        return -1;
		    }
		//initize the full refresh
		EPD_4IN2_Init_Fast();
	//clear screen
		EPD_4IN2_Clear();
		DEV_Delay_ms(500);
	//declare image cache
		UBYTE *BlackImage;
		UWORD Imagesize = ((EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1)) * EPD_4IN2_HEIGHT;
		if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
			printf("Failed to apply for black memory...\r\n");
			return -1;
		}
	//paint new image
		Paint_NewImage(BlackImage, EPD_4IN2_WIDTH, EPD_4IN2_HEIGHT, 0, WHITE);
	//select image to be drawn on
		Paint_SelectImage(BlackImage);
		Paint_Clear(WHITE);
		Paint_DrawBitMap(gImage_4in2); //creates a monochrome background
		EPD_4IN2_Display(BlackImage);
		DEV_Delay_ms(500);
		printf("SelectImage:BlackImage\r\n");
		Paint_SelectImage(BlackImage);
		Paint_Clear(WHITE);
	//write text
		Paint_DrawString_EN(100, 100, "1", &Font16, BLACK, WHITE);
		EPD_4IN2_Display(BlackImage);
		DEV_Delay_ms(2000);
	//clear image
		EPD_4IN2_Clear();
		EPD_4IN2_Sleep();
		free(BlackImage); //deallocate memory
		DEV_Delay_ms(2000);
		DEV_Module_Exit();

	return 0;

}

int EPD_partial_update(void){
//initialize
	if(DEV_Module_Init()!=0){
			return -1;
		}
//initialize the partial refresh -- doesn't work
	EPD_4IN2_Init_Fast();
//clear screen
	EPD_4IN2_Clear();
	DEV_Delay_ms(500);
//declare image cache
	UBYTE *BlackImage;
	UWORD Imagesize = ((EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1)) * EPD_4IN2_HEIGHT;
	if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
		printf("Failed to apply for black memory...\r\n");
		return -1;
	}
//paint new image
	Paint_NewImage(BlackImage, EPD_4IN2_WIDTH, EPD_4IN2_HEIGHT, 0, WHITE);
//select image to be drawn on
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	Paint_DrawBitMap(gImage_4in2); //creates a monochrome background
	EPD_4IN2_Display(BlackImage);
	DEV_Delay_ms(500);
	printf("SelectImage:BlackImage\r\n");
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
//write text
	Paint_DrawNum(10, 33, 12345, &Font12, BLACK, WHITE);
	Paint_DrawNum(100, 100, 100, &Font20, BLACK, WHITE); //should not be cleared
	EPD_4IN2_Display(BlackImage);
	DEV_Delay_ms(200);
//partial update
	Paint_DrawNum(10, 33, 12346, &Font12, BLACK, WHITE);
    EPD_4IN2_PartialDisplay(0, 0, 10 + Font12.Width * 5, 33 + Font12.Height, BlackImage);
	DEV_Delay_ms(500)
//clear image
	EPD_4IN2_Clear();
	EPD_4IN2_Sleep();
	free(BlackImage); //deallocate memory
	DEV_Delay_ms(2000);
	DEV_Module_Exit();

	return 0;
}

int EPD_paint_curve_test(void){
//initialize
	if(DEV_Module_Init()!=0){
			return -1;
		}
//initialize the fast refresh
	EPD_4IN2_Init_Fast();
//clear screen
	EPD_4IN2_Clear();
	DEV_Delay_ms(500);
//declare image cache
	UBYTE *BlackImage;
	UWORD Imagesize = ((EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1)) * EPD_4IN2_HEIGHT;
	if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
		printf("Failed to apply for black memory...\r\n");
		return -1;
	}
//paint new image
	Paint_NewImage(BlackImage, EPD_4IN2_WIDTH, EPD_4IN2_HEIGHT, 0, WHITE);
//select image to be drawn on
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	Paint_DrawBitMap(gImage_4in2); //creates a monochrome background
	EPD_4IN2_Display(BlackImage);
	DEV_Delay_ms(500);
	printf("SelectImage:BlackImage\r\n");
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
//draw points
	int old_x = 60;
	int old_y = 250;
	int new_x, new_y;

	int start_x = 60;
	int start_y = 250;
	int end_x = 380;
    int end_y = 30;

    int x_min = 0;
    int y_min =  0;
    int x_max = 10;
    int y_max = 100;


//	for(int i = 0; i <= 10; i++) {
//		// integrate ADC
////		HAL_ADC_Start(&hadc1);
////		HAL_ADC_PollForConversion(&hadc1, 1);
////		i = HAL_ADC_GetValue(&hadc1);
////		HAL_Delay(10);
//
//		new_x = (i - x_min) * (300) / (x_max - x_min) + start_x;
//		int y = (int)pow(i, 2.0);
////		int y = rand() % 100;
//		new_y = (y - y_min) * (start_y - 200 - start_y) / (y_max - y_min) + start_y;
//		Paint_DrawLine(old_x, old_y, new_x, new_y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//		old_x = new_x;
//		old_y = new_y;
//	}


//	for (int i = y_min; i <= y_max; i++) {
//	  // compute the transform
//	  int temp =  (i - y_min) * (start_y - 200 - start_y) / (y_max - y_min) + start_y;
//	  Paint_DrawLine(start_x, temp, start_x + 320, temp, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//	  Paint_DrawNum(start_x - 40, temp, i, &Font8, BLACK, WHITE);
//	  i += 9;
//	}
//
//	for (int i = x_min; i <= x_max; i++) {
//	  // compute the transform
//	  int temp =  (i - x_min) * (320) / (x_max - x_min) + start_x;
//	  Paint_DrawLine(temp, start_y, temp, start_y - 200, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
//	  Paint_DrawNum(temp, start_y + 10, i, &Font8, BLACK, WHITE);
//	}

	Paint_DrawString_EN(10, 0, "Graph Title", &Font16, BLACK, WHITE);
	DEV_Delay_ms(5000);
//clear image
	EPD_4IN2_Clear();
	EPD_4IN2_Sleep();
	free(BlackImage); //deallocate memory
	DEV_Delay_ms(2000);
	DEV_Module_Exit();

	return 0;
}

// rewritten for parameters
int EPD_graph_data(UWORD x_min, UWORD x_max, UWORD y_min, UWORD y_max) {
//initialize
	if(DEV_Module_Init()!=0){
			return -1;
		}
//initialize the partial refresh -- doesn't work
	EPD_4IN2_Init_Fast();
//	EPD_4IN2_Init_4Gray();
//clear screen
	EPD_4IN2_Clear();
	DEV_Delay_ms(500);
//declare image cache
	UBYTE *BlackImage;
	UWORD Imagesize = ((EPD_4IN2_WIDTH % 8 == 0)? (EPD_4IN2_WIDTH / 8 ): (EPD_4IN2_WIDTH / 8 + 1)) * EPD_4IN2_HEIGHT;
	if((BlackImage = (UBYTE *)malloc(Imagesize)) == NULL) {
		printf("Failed to apply for black memory...\r\n");
		return -1;
	}
//paint new image
	Paint_NewImage(BlackImage, EPD_4IN2_WIDTH, EPD_4IN2_HEIGHT, 0, WHITE);
//select image to be drawn on
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
	Paint_DrawBitMap(gImage_4in2); //creates a monochrome background
	EPD_4IN2_Display(BlackImage);
	DEV_Delay_ms(500);
	printf("SelectImage:BlackImage\r\n");
	Paint_SelectImage(BlackImage);
	Paint_Clear(WHITE);
//draw points
	int old_x = 60;
	int old_y = 250;
	int new_x, new_y;

	int start_x = 60;
	int start_y = 250;
	int end_x = 380;
	int end_y = 30;

//	int x_min = x_min;
//	int y_min =  y_min;
//	int x_max = x_max;
//	int y_max = y_max;

	for(int i = 0; i <= 10; i++) { // while

		new_x = (i - x_min) * (300) / (x_max - x_min) + start_x;
//		int y = (int)pow(i, 2.0);
		int y = rand() % 100;
		new_y = (y - y_min) * (start_y - 200 - start_y) / (y_max - y_min) + start_y;
		Paint_DrawLine(old_x, old_y, new_x, new_y, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
		old_x = new_x;
		old_y = new_y;
	}
// draw the axes
	for (int i = y_min; i <= y_max; i++) {
	  // compute the transform
	  int temp =  (i - y_min) * (start_y - 200 - start_y) / (y_max - y_min) + start_y;
	  Paint_DrawLine(start_x, temp, start_x + 320, temp, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	  Paint_DrawNum(start_x - 40, temp, i, &Font8, BLACK, WHITE);
	  i += 9;
	}

	for (int i = x_min; i <= x_max; i++) {
	  // compute the transform
	  int temp =  (i - x_min) * (320) / (x_max - x_min) + start_x;
	  Paint_DrawLine(temp, start_y, temp, start_y - 200, BLACK, DOT_PIXEL_1X1, LINE_STYLE_SOLID);
	  Paint_DrawNum(temp, start_y + 10, i, &Font8, BLACK, WHITE);
	}
	Paint_DrawString_EN(10, 0, "Graph Title", &Font16, BLACK, WHITE);
	DEV_Delay_ms(5000);
//clear image
	EPD_4IN2_Clear();
	EPD_4IN2_Sleep();
	free(BlackImage); //deallocate memory
	DEV_Delay_ms(2000);
	DEV_Module_Exit();

	return 0;
}


//	FILE* breath_data = fopen("20230209_Cap_Test_low_breathing.csv", "r");
//	if (breath_data == NULL) {
//		printf("Unable to open file.");
//	}

//  char row[2000];
//	while(fgets(line, sizeof(line), breath_data)) {
//		char *token;
//
//		token = strtok(line, ",");
//		while(token != NULL){
//			printf("%s", token);
//			token = strtok(NULL, ",");
//		}
//		printf("\n");
//	}
//
//	while (feof(breath_data) != true)
//	    {
//	        fgets(row, sizeof(row), breath_data);
//	        printf(row);
//	    }
//
//	char line[2323];
//	    while (fgets(line, 2323, breath_data))
//	    {
//	        char* tmp = strdup(line);
//	        printf(getfield(tmp, 3));
//	        Paint_DrawString_EN(100, 100, getfield(tmp, 3), &Font16, BLACK, WHITE);
//	        // NOTE strtok clobbers tmp
//	        free(tmp);
//	    }

//const char* getfield(char* line, int num)
//	{
//	    const char* tok;
//	    for (tok = strtok(line, ";");
//	            tok && *tok;
//	            tok = strtok(NULL, ";\n"))
//	    {
//	        if (!--num)
//	            return tok;
//	    }
//	    return NULL;
//	}



