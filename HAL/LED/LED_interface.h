#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

typedef enum
{
	LED_ACT_LOW=0u,
	LED_ACT_HIGH=1u
}LED_ACT_t;

typedef struct
{
	uint8 u8Pin;
	uint8 u8Port;
	LED_ACT_t u8ACT_type;
}LED_Config_t;

uint8 LED_u8SetOn(const LED_Config_t* Copy_pstConfig);
uint8 LED_u8SetOff(const LED_Config_t* Copy_pstConfig);
uint8 LED_u8Toggle(const LED_Config_t* Copy_pstConfig);

#endif
