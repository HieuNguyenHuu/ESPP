# include <stdio .h>
# include <time .h>
# include "freertos/FreeRTOS.h"
# include "freertos/task.h"
# include "driver/gpio.h"
# include "sdkconfig.h"
# include "freertos/timers.h"

# include "freertos/FreeRTOSconfig.h"
# include "esp_system.h"
# include "esp_spi_flash.h"

 TimerHandle_t timerHandle , timerHandle1 ;
 int count = 0, count1 = 0;

 void myTimerCallBackFunction ( TimerHandle_t xTimer )
 {
	if ( pvTimerGetTimerID ( xTimer ) == ( void *) 0) {
		clock_t currentTime = clock ();
		count ++;
		printf ("At: %ld(ms) | AHIHI | Counter of timer 1: %d\n", currentTime ,
		count );
		if ( count == 10) {
			xTimerStop ( timerHandle , 0);
		}
	} else {
		clock_t currentTime = clock ();
		count1 ++;
		printf ("At: %ld(ms) | IHAHA | Counter of timer 2: %d\n", currentTime ,
	count1 );
		if ( count1 == 5) {
			xTimerStop ( timerHandle1 , 0);
		}
	}
 }

 void app_main ( void )
 {
	timerHandle = xTimerCreate (" TIMER1 ",
		200 ,
		pdTRUE ,
		( void *) 0,
	myTimerCallBackFunction );
 timerHandle1 = xTimerCreate (" TIMER2 ",
		300 ,
		pdTRUE ,
		( void *) 1,
	myTimerCallBackFunction );

	if (( timerHandle ) && ( timerHandle1 )) {
		xTimerStart ( timerHandle , 0);
		xTimerStart ( timerHandle1 , 0);
	}
 }