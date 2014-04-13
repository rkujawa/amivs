#ifndef _FILE_H_
#define _FILE_H_

ULONG file_size(BYTE *path);
BOOL file_load(BYTE *path, BYTE *filebuf, ULONG filesize);

#endif /* _FILE_H_ */
