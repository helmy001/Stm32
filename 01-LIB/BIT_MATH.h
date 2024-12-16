/**************************************************************/
/* Author    : Helmy                                          */
/* Date      : 11/12/2024                                     */
/* Version   : v1.0                                           */
/************************************************************ */

#ifndef BIT_MATH_H
#define BIT_MATH_H



/*****************************************************************************/
/*  GLOBAL CONSTANT MACROS                                                   */
/*****************************************************************************/

#define SET_BIT(REG,BIT)          ((REG)|=(1<<(BIT)))
#define CLEAR_BIT(REG,BIT)        ((REG)&=~(1<<(BIT)))
#define GET_BIT(REG,BIT)          ((REG>>BIT)&(1))
#define TOGGLE_BIT(REG,BIT)       ((REG)^=(1<<(BIT)))


 



#endif