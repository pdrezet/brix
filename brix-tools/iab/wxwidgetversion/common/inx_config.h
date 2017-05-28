#ifndef _INX_CONFIG_H
#define _INX_CONFIG_H

#define INXWINDOWS 1
#define INXMAC 2
#define INXLINUX 3

//#define _INX_PLATFORM_ INXWINDOWS
#define _INX_PLATFORM_ INXLINUX

#if (_INX_PLATFORM_ == INXWINDOWS)

#elif (_INX_PLATFORM_ == INXMAC)

#elif (_INX_PLATFORM_ == INXLINUX)

#elif (_INX_PLATFORM_ == ANY)

#else
//#error "_INXPLATFORM_ is not defined
#endif


#endif

