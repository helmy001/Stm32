/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 11/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef STD_TYPES_H
#define STD_TYPES_H


#define E_OK          0u
#define E_NOT_OK      1u

typedef unsigned char u8;              /*           0 .. 255             */
typedef unsigned short int u16;        /*           0 .. 65535           */
typedef unsigned long int u32;         /*           0 .. 4294967295      */

#ifndef TRUE
   #define TRUE   1u
#endif

#ifndef FALSE
   #define FALSE  0u
#endif
 
#ifndef ENABLE
   #define ENABLE  1u
#endif

#ifndef DISABLE
   #define DISABLE  0u
#endif

#endif