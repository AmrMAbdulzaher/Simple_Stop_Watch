#ifndef BUZZ_INTERFACE_H
#define BUZZ_INTERFACE_H

typedef enum
{
	BUZZ_ACT_LOW=0u,
	BUZZ_ACT_HIGH=1u
}BUZZ_ACT_t;

typedef struct
{
	uint8 u8Pin;
	uint8 u8Port;
	BUZZ_ACT_t u8ACT_type;
}BUZZ_Config_t;

uint8 BUZZ_u8SetOn(const BUZZ_Config_t* Copy_pstConfig);
uint8 BUZZ_u8SetOff(const BUZZ_Config_t* Copy_pstConfig);
uint8 BUZZ_u8Toggle(const BUZZ_Config_t* Copy_pstConfig);

#endif
