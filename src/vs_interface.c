#include <stdio.h>
#include <unistd.h>

#include <exec/types.h>                                                         

#include "clockport.h"

#include "vs_interface.h"
#include "vs_regs.h"

void
vs_play(char *buf, ULONG size, ULONG delay)
{
	ULONG pos;

	UBYTE wr_reg;

	pos = 0;
	wr_reg = HW_SPI_DATA_WR_0;

	while (pos < size) {
		clockport_write(wr_reg++, buf[pos++]);

		if (wr_reg == HW_SPI_DATA_WR_3) {
			clockport_write(HW_CPLD_COMMAND, HW_CPLD_COMMAND_SEND);
			wr_reg = HW_SPI_DATA_WR_0;
			Delay(delay);
		}	
	}
}


