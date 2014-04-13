#ifndef _CLOCKPORT_H_
#define _CLOCKPORT_H_

UBYTE clockport_read(UBYTE reg);
void clockport_write(UBYTE reg, UBYTE value);
void clockport_set(UBYTE offset, UBYTE bits);
void clockport_unset(UBYTE reg, UBYTE bits);

#endif /* _CLOCKPORT_H_ */

