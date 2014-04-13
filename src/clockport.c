#include <stdio.h>
#include <stdlib.h>

#include <exec/types.h>

#include "clockport.h"

#define CLOCKPORT_BASE		0xD90001                                        
#define CLOCKPORT_STRIDE	4 

#pragma dontwarn 113

static UBYTE *cp = CLOCKPORT_BASE;

extern debug;

/* read clockport register */
UBYTE
clockport_read(UBYTE reg) 
{
	UBYTE v;
	UBYTE *ptr;

	ptr = cp + (reg * CLOCKPORT_STRIDE);
	v = *ptr;
	if (debug)
		printf("DEBUG: read %x from %p\n", (int) v, (void*) ptr);

	return v;
}

/* write register at offset */
void
clockport_write(UBYTE reg, UBYTE value)
{
	UBYTE *ptr;

	ptr = cardaddr + (reg * CLOCKPORT_STRIDE);
	if (debug)
		printf("DEBUG: write %x to %p\n", (int) value, (void*) ptr);
	*ptr = value;
}

/* set bit in clockport register */
void
clockport_set(UBYTE offset, UBYTE bits)
{
	UBYTE v;
	
	v = clockport_read(offset) | bits;
	clockport_write(offset, v);
}

/* unset bit in clockport register */
void
clockport_unset(UBYTE reg, UBYTE bits)
{
	UBYTE v;

	v = clockport_read(reg) & ~bits;
	clockport_write(reg, v);
}


