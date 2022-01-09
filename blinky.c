/*
 * blinky.c -- working with Serial I/O and GPIO
 *
 * Assumes the LED's are connected to AXI_GPIO_0, on channel 1
 *
 * Terminal Settings:
 *  -Baud: 115200
 *  -Data bits: 8
 *  -Parity: no
 *  -Stop bits: 1
 */
#include <stdio.h>							/* printf(), getchar() */
#include "xil_types.h"					/* u32, u16 etc */
#include "platform.h"						/* ZYBOboard interface */
#include <xgpio.h>							/* Xilinx GPIO functions */
#include "xparameters.h"				/* constants used by the hardware */
#include "led.h"

#define OUTPUT 0x0							/* setting GPIO direction to output */
#define CHANNEL1 1							/* channel 1 of the GPIO port */

int main() {

   init_platform();							/* initialize the hardware platform */
   size_t BUFF = 80;
   char line[BUFF];
   //u32 led_reg;

   led_init();

   /*
		* set stdin unbuffered, forcing getchar to return immediately when
		* a character is typed.
		*/
	 setvbuf(stdin,NULL,_IONBF,0);
	 printf("[Hello]\n");
//     XGpio_Initialize(&port, XPAR_AXI_GPIO_0_DEVICE_ID);	/* initialize device AXI_GPIO_0 */
//     XGpio_SetDataDirection(&port, CHANNEL1, OUTPUT);	    /* set tristate buffer to output */
//	 XGpio_DiscreteWrite(&port, CHANNEL1, 0x1);						/* turn on led0 */

	 void getLine(char *final_string, size_t size){
		 char curr;
		 curr=getchar();
		 printf("%c", curr);
		 int i = 0;

		 while (curr != 13){
			 final_string[i] = curr;
			 i++;
			 curr = getchar();
			 printf("%c", curr);
			 fflush(stdout);
		 }

		 final_string[i] = '\0';
	 }


	do{
		printf(">");
		getLine(line, BUFF);
		printf("\n");
		fflush(stdout);

		if (strcmp(line, "0") == 0 || strcmp(line, "1") == 0 || strcmp(line, "2") == 0 || strcmp(line, "3") == 0){

			if (strcmp(line, "0") == 0){
//				//led_reg = XGpio_DiscreteRead(&port, CHANNEL1);
//				led_reg = led_get()
//				if (led_reg == 0x0){
//					XGpio_DiscreteWrite(&port, CHANNEL1, 0x1);
//				}else if(led_reg == 0x1){
//					XGpio_DiscreteWrite(&port, CHANNEL1, 0x0);
//				}
				led_toggle(0);

			}

			printf("[%s]\n\r", line);
		}

	}while(strcmp(line, "q") != 0);




	//XGpio_DiscreteWrite(&port, CHANNEL1, 0x0);
	cleanup_platform();					/* cleanup the hardware platform */
	return 0;
}
