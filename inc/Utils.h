/*
 * Utils.h
 *
 * Created: 9/5/2022 7:42:01 PM
 *  Author: Ahmed
 */ 


#ifndef UTILS_H_
#define UTILS_H_

#define SET_BIT(reg, bit)		( reg |= ( 1 << (bit) ) )
#define CLEAR_BIT(reg, bit)		( reg &= ~( 1 << (bit) ) )
#define TOGGLE_BIT(reg, bit)		( reg ^= ( 1 << (bit) ) )
#define READ_BIT(reg, bit)		( ( reg >> (bit) ) & 1 )

#define WRITE_MASK_POS(reg, mask, pos, val)	((reg) = ((reg) & (~((mask) << (pos)))) | ((val) << (pos)))

#define WRITE_MASK(reg, mask, val)			((reg) = ((reg) & (~(mask))) | (val))
											
#define CLEAR_MASK(reg, mask)				(reg &= ~(mask))
#define SET_MASK(reg, mask)					(reg |= (mask))

#define READ_MASK_POS(reg, mask, pos)		(( reg >> (pos) ) & (mask))

#define READ_MASK(reg, mask)					(reg & (mask))


#endif /* UTILS_H_ */
