#include "../../Library/STD_TYPES.h"
#include "../../Library/BIT_MATH.h"
#include "../../Library/ErrType.h"
#include <util/delay.h>

#include "../../MCAL/DIO/DIO_interface.h"
#include "LED_cfg.h"
#include "LED_interface.h"
#include "LED_prv.h"


uint8 LED_u8SetOn(const LED_Config_t* Copy_pstConfig)
{
	uint8 Local_ErrorState = OK;

	if(Copy_pstConfig != NULL)
	{
		if(Copy_pstConfig->u8ACT_type == LED_ACT_HIGH)
		{
			DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin,DIO_u8PIN_HIGH);
		}
		else if(Copy_pstConfig->u8ACT_type == LED_ACT_LOW)
		{
			DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin,DIO_u8PIN_LOW);
		}
		else
		{
			Local_ErrorState = NOK;
		}
	}
	else
	{
		Local_ErrorState = NULL_PTR_ERR;
	}

	return Local_ErrorState;
}
uint8 LED_u8SetOff(const LED_Config_t* Copy_pstConfig)
{
	uint8 Local_ErrorState = OK;

	if(Copy_pstConfig != NULL)
	{
		if(Copy_pstConfig->u8ACT_type == LED_ACT_HIGH)
		{
			DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin,DIO_u8PIN_LOW);
		}
		else if(Copy_pstConfig->u8ACT_type == LED_ACT_LOW)
		{
			DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin,DIO_u8PIN_LOW);
		}
		else
		{
			Local_ErrorState = NOK;
		}
	}
	else
	{
		Local_ErrorState = NULL_PTR_ERR;
	}

	return Local_ErrorState;
}
uint8 LED_u8Toggle(const LED_Config_t* Copy_pstConfig)
{
	uint8 Local_ErrorState = OK;
	if(Copy_pstConfig != NULL)
	{
		DIO_u8TogglePinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin);
	}
	else
	{
		Local_ErrorState = NULL_PTR_ERR;
	}
	return Local_ErrorState;
}
