#include "../Library/STD_Types.h"

#include "../MCAL/PORT/PORT_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"
#include "StopWatch_interface.h"

void main(void)
{
	PORT_voidInit();
	CLCD_voidInit();

	/*show arrow at its starting location*/
	voidDrawArrow(4,1);

	while(1)
	{
		voidStartStopWatch();
	}
}



