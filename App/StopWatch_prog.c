#include "../Library/STD_TYPES.h"
#include <util/delay.h>

#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"
#include "../HAL/KPD/KPD_interface.h"
#include "../HAL/LED/LED_interface.h"
#include "../HAL/BUZZ/BUZZ_interface.h"

#include "StopWatch_interface.h"
#include "StopWatch_prv.h"
#include "StopWatch_cfg.h"

void voidDrawArrow(uint8 Copy_u8XPos, uint8 Copy_u8YPos)
{
	uint8 Local_au8Arrow[8]={0b00100,0b01110,0b10101,0b00100,0b00100,0b00100,0b00100,0b00000};
	CLCD_u8SendSpecialCharacter(HR_LEFT_LOC,Local_au8Arrow,Copy_u8XPos,Copy_u8YPos);
}

void voidStartAlarm(void)
{

	uint8 Local_u8Alert_Counter;

	/*set led configuration*/
	LED_Config_t Local_stLED={
			.u8Port= DIO_u8PORTC,
			.u8Pin= DIO_u8PIN0,
			.u8ACT_type= LED_ACT_HIGH,

	};

	/*set buzzer configuration*/
	BUZZ_Config_t Local_stBuzzer={
			.u8Port= DIO_u8PORTC,
			.u8Pin= DIO_u8PIN5,
			.u8ACT_type= BUZZ_ACT_HIGH,

	};

	for(Local_u8Alert_Counter=0;Local_u8Alert_Counter < u8ALARM_ON_TIME_CONSTANT ;Local_u8Alert_Counter++)
	{
		LED_u8Toggle(&Local_stLED);
		BUZZ_u8Toggle(&Local_stBuzzer);
		_delay_ms(f64ALARAM_DELAY_TIME_MS);
	}
}

void voidStartStopWatch(void)
{
	uint8 Local_u8KeypadKey;
	uint8 Local_u8Hour_R=0,Local_u8Hour_L=0;
	uint8 Local_u8Min_R=0,Local_u8Min_L=0;
	uint8 Local_u8Sec_R=0,Local_u8Sec_L=0;
	uint8 Local_u8Start_Flag=0;
	uint8 Local_u8Location=HR_LEFT_LOC;
	sint8 Local_Sec_Counter1,Local_Sec_Counter2;
	sint8 Local_Min_Counter1,Local_Min_Counter2;
	sint8 Local_Hour_Counter1,Local_Hour_Counter2;

	while(Local_u8Start_Flag == 0)
	{
		/*show stop watch time on the CLCD*/
		CLCD_voidGoToXY(4,0);
		CLCD_voidSendNumber(Local_u8Hour_L);
		CLCD_voidSendNumber(Local_u8Hour_R);
		CLCD_voidSendData(':');
		CLCD_voidSendNumber(Local_u8Min_L);
		CLCD_voidSendNumber(Local_u8Min_R);
		CLCD_voidSendData(':');
		CLCD_voidSendNumber(Local_u8Sec_L);
		CLCD_voidSendNumber(Local_u8Sec_R);

		do
		{
			Local_u8KeypadKey = KPD_u8GetPressedKey();
		}while(Local_u8KeypadKey == 0xff);
		switch(Local_u8KeypadKey)
		{
		case 'R':
		{
			/*removing arrow from the current position*/
			CLCD_voidGoToXY(Local_u8Location, 1);
			CLCD_u8SendString(" ");

			/*moving arrow right to the new position*/
			switch(Local_u8Location)
			{
			case HR_LEFT_LOC	: 	Local_u8Location=HR_RIGHT_LOC; 		break;
			case HR_RIGHT_LOC	: 	Local_u8Location=MIN_LEFT_LOC; 		break;
			case MIN_LEFT_LOC	: 	Local_u8Location=MIN_RIGHT_LOC; 	break;
			case MIN_RIGHT_LOC	: 	Local_u8Location=SEC_LEFT_LOC; 		break;
			case SEC_LEFT_LOC	:	Local_u8Location=SEC_RIGHT_LOC; 	break;
			case SEC_RIGHT_LOC	:	Local_u8Location=HR_LEFT_LOC; 		break;
			}
			voidDrawArrow(Local_u8Location,1);
			break;
		}
		case 'L':
		{
			/*removing arrow from the current position*/
			CLCD_voidGoToXY(Local_u8Location, 1);
			CLCD_u8SendString(" ");

			/*moving arrow left to the new position*/
			switch(Local_u8Location)
			{
			case HR_LEFT_LOC	: 	Local_u8Location=SEC_RIGHT_LOC;		break;
			case SEC_RIGHT_LOC	: 	Local_u8Location=SEC_LEFT_LOC;		break;
			case SEC_LEFT_LOC	: 	Local_u8Location=MIN_RIGHT_LOC; 	break;
			case MIN_RIGHT_LOC	: 	Local_u8Location=MIN_LEFT_LOC; 		break;
			case MIN_LEFT_LOC	: 	Local_u8Location=HR_RIGHT_LOC; 		break;
			case HR_RIGHT_LOC	: 	Local_u8Location=HR_LEFT_LOC; 		break;
			}
			voidDrawArrow(Local_u8Location,1);
			break;
		}
		case 'U':
		{
			/*adjusting time using Up button*/
			switch(Local_u8Location)
			{
			case HR_LEFT_LOC: 		Local_u8Hour_L= (Local_u8Hour_L!=MAX_HR_LEFT)? Local_u8Hour_L+1 : 0; 		break;
			case HR_RIGHT_LOC: 		Local_u8Hour_R= (Local_u8Hour_R!=MAX_HR_RIGHT)? Local_u8Hour_R+1 : 0; 		break;
			case MIN_LEFT_LOC: 		Local_u8Min_L= (Local_u8Min_L!=MAX_MIN_LEFT)? Local_u8Min_L+1 : 0; 			break;
			case MIN_RIGHT_LOC: 	Local_u8Min_R= (Local_u8Min_R!=MAX_MIN_RIGHT)? Local_u8Min_R+1 : 0; 		break;
			case SEC_LEFT_LOC: 		Local_u8Sec_L= (Local_u8Sec_L!=MAX_SEC_LEFT)? Local_u8Sec_L+1 : 0; 			break;
			case SEC_RIGHT_LOC: 	Local_u8Sec_R= (Local_u8Sec_R!=MAX_SEC_RIGHT)? Local_u8Sec_R+1 : 0; 		break;
			}
			break;
		}
		case 'D':
		{
			/*adjusting time using Down button*/
			switch(Local_u8Location)
			{
			case HR_LEFT_LOC: 		Local_u8Hour_L= (Local_u8Hour_L!=0)? Local_u8Hour_L-1 : MAX_HR_LEFT; 		break;
			case HR_RIGHT_LOC: 		Local_u8Hour_R= (Local_u8Hour_R!=0)? Local_u8Hour_R-1 : MAX_HR_RIGHT; 		break;
			case MIN_LEFT_LOC: 		Local_u8Min_L= (Local_u8Min_L!=0)? Local_u8Min_L-1 : MAX_MIN_LEFT; 			break;
			case MIN_RIGHT_LOC:		Local_u8Min_R= (Local_u8Min_R!=0)? Local_u8Min_R-1 : MAX_MIN_RIGHT; 		break;
			case SEC_LEFT_LOC:  	Local_u8Sec_L= (Local_u8Sec_L!=0)? Local_u8Sec_L-1 : MAX_SEC_LEFT; 			break;
			case SEC_RIGHT_LOC: 	Local_u8Sec_R= (Local_u8Sec_R!=0)? Local_u8Sec_R-1 : MAX_SEC_RIGHT; 		break;
			}
			break;
		}
		case 'S':
		{
			/*activate start flag*/
			Local_u8Start_Flag = 1;

			/*remove arrow*/
			CLCD_voidGoToXY(Local_u8Location, 1);
			CLCD_u8SendString(" ");

			/*start counting down of the stop watch*/
			for(Local_Hour_Counter1=(sint8)Local_u8Hour_L;Local_Hour_Counter1>=0;Local_Hour_Counter1--)
			{
				CLCD_voidGoToXY(HR_LEFT_LOC,0);
				CLCD_voidSendNumber(Local_Hour_Counter1);
				for(Local_Hour_Counter2=(sint8)Local_u8Hour_R;Local_Hour_Counter2>=0;Local_Hour_Counter2--)
				{
					CLCD_voidGoToXY(HR_RIGHT_LOC,0);
					CLCD_voidSendNumber(Local_Hour_Counter2);

					for(Local_Min_Counter1=Local_u8Min_L;Local_Min_Counter1>=0;Local_Min_Counter1--)
					{
						CLCD_voidGoToXY(MIN_LEFT_LOC,0);
						CLCD_voidSendNumber(Local_Min_Counter1);
						for(Local_Min_Counter2=Local_u8Min_R;Local_Min_Counter2>=0;Local_Min_Counter2--)
						{
							CLCD_voidGoToXY(MIN_RIGHT_LOC,0);
							CLCD_voidSendNumber(Local_Min_Counter2);

							for(Local_Sec_Counter1=Local_u8Sec_L;Local_Sec_Counter1>=0;Local_Sec_Counter1--)
							{
								CLCD_voidGoToXY(SEC_LEFT_LOC,0);
								CLCD_voidSendNumber(Local_Sec_Counter1);
								for(Local_Sec_Counter2=Local_u8Sec_R;Local_Sec_Counter2>=0;Local_Sec_Counter2--)
								{
									CLCD_voidGoToXY(SEC_RIGHT_LOC,0);
									CLCD_voidSendNumber(Local_Sec_Counter2);
									_delay_ms(1000);
								}
								Local_u8Sec_R=MAX_SEC_RIGHT;
							}
							Local_u8Sec_L=MAX_SEC_LEFT;
						}

						Local_u8Min_R=MAX_MIN_RIGHT;
					}
					Local_u8Min_L=MAX_MIN_LEFT;
				}
				Local_u8Hour_R=MAX_HR_RIGHT;
			}
			/*print time out message*/
			CLCD_voidGoToXY(4,1);
			CLCD_u8SendString("TIME OUT");

			/*toggle alert buzzer and led*/
			voidStartAlarm();
			break;
		}
		}
	}

}
