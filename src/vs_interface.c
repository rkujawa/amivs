#include <stdio.h>

#include <exec/types.h>                                                         

#include "clockport.h"

#include "vs_interface.h"
#include "vs_regs.h"

void
nop_delay(ULONG delay) {

	while (delay > 0) {
		__asm("nop");
		delay--;
	}
}

void
vs_play(char *buf, ULONG size, ULONG delay)
{
	ULONG pos;

	UBYTE wr_reg;

	pos = 0;
	wr_reg = HW_SPI_DATA_WR_0;

	while (pos < size) {
		clockport_write(wr_reg++, buf[pos++]);

		if (wr_reg > HW_SPI_DATA_WR_3) {
			clockport_write(HW_CPLD_COMMAND, HW_CPLD_COMMAND_SEND);
			wr_reg = HW_SPI_DATA_WR_0;

			nop_delay(delay);
			while (clockport_read(HW_STATUS) != 0) 
				nop_delay(delay);
		}	
	}
}


void
vs_play_1b(char *buf, ULONG size, ULONG delay)
{
	ULONG pos;

	UBYTE wr_reg;

	pos = 0;

	while (pos < size) {
		/* write buffer to first clockport register */
		clockport_write(HW_SPI_DATA_WR_0, buf[pos++]);

		/* SPI send */
		clockport_write(HW_CPLD_COMMAND, HW_CPLD_COMMAND_SEND);

		/* wait infinitely until HW_STATUS is 0 */
		while (clockport_read(HW_STATUS) != 0);
	}
}


