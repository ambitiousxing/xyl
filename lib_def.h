/**
  ******************************************************************************
  * @file      lib_def.h
  * @author    Mr.Marvel
  * @version   V1.0.0
  * @date      2014/5/26
  * @brief     Global macro definition
  ******************************************************************************
*/

#ifndef  LIB_DEF_H
#define  LIB_DEF_H


/*-------------------------------------------------------------------------------
                                    Logic                               
---------------------------------------------------------------------------------*/
#define  DEF_DISABLED                                      0
#define  DEF_ENABLED                                       1

#define  DEF_FALSE                                         0
#define  DEF_TRUE                                          1

#define  DEF_NO                                            0
#define  DEF_YES                                           1

#define  DEF_OFF                                           0
#define  DEF_ON                                            1

#define  DEF_CLR                                           0
#define  DEF_SET                                           1

#define  DEF_ACTIVE                                        0
#define  DEF_INACTIVE                                      1

#define  DEF_FAIL                                          0
#define  DEF_OK                                            1
/*-------------------------------------------------------------------------------
                                     Bit                              
---------------------------------------------------------------------------------*/

#define  DEF_BIT_NONE                                   0x00

#define  DEF_BIT_00                                     0x01
#define  DEF_BIT_01                                     0x02
#define  DEF_BIT_02                                     0x04
#define  DEF_BIT_03                                     0x08
#define  DEF_BIT_04                                     0x10
#define  DEF_BIT_05                                     0x20
#define  DEF_BIT_06                                     0x40
#define  DEF_BIT_07                                     0x80

#define  DEF_BIT_08                                   0x0100
#define  DEF_BIT_09                                   0x0200
#define  DEF_BIT_10                                   0x0400
#define  DEF_BIT_11                                   0x0800
#define  DEF_BIT_12                                   0x1000
#define  DEF_BIT_13                                   0x2000
#define  DEF_BIT_14                                   0x4000
#define  DEF_BIT_15                                   0x8000

#define  DEF_BIT_16                               0x00010000
#define  DEF_BIT_17                               0x00020000
#define  DEF_BIT_18                               0x00040000
#define  DEF_BIT_19                               0x00080000
#define  DEF_BIT_20                               0x00100000
#define  DEF_BIT_21                               0x00200000
#define  DEF_BIT_22                               0x00400000
#define  DEF_BIT_23                               0x00800000

#define  DEF_BIT_24                               0x01000000
#define  DEF_BIT_25                               0x02000000
#define  DEF_BIT_26                               0x04000000
#define  DEF_BIT_27                               0x08000000
#define  DEF_BIT_28                               0x10000000
#define  DEF_BIT_29                               0x20000000
#define  DEF_BIT_30                               0x40000000
#define  DEF_BIT_31                               0x80000000


/*-------------------------------------------------------------------------------
                                     Mask                             
---------------------------------------------------------------------------------*/
#define  DEF_INT8_MASK                                  0xFF
#define  DEF_INT16_MASK                               0xFFFF
#define  DEF_INT32_MASK                           0xFFFFFFFF
#define  DEF_INT64_MASK                   0xFFFFFFFFFFFFFFFF

/*-------------------------------------------------------------------------------
                                     Bit operation                            
---------------------------------------------------------------------------------*/
#define  DEF_SHIFT_UINT_1(val)                   ((1u) << (val))
#define  DEF_SHIFT_ULINT_1(val)                  ((1ul) << (val))

#define  DEF_BIT_UINT_SET(val, pos)              val |= ((1u) << (pos))
#define  DEF_BIT_UINT_CLR(val, pos)              val &=~((1u) << (pos))
#define  DEF_BIT_UINT_NEG(val, pos)              val ^= ((1u) << (pos))

#define  DEF_BIT_ULINT_SET(val, pos)             val |= ((1ul) << (pos))
#define  DEF_BIT_ULINT_CLR(val, pos)             val &=~((1ul) << (pos))
#define  DEF_BIT_ULINT_NEG(val, pos)             val ^= ((1ul) << (pos))

#define  DEF_BIT_SET_MASK(val, mask)             val |= (mask)
#define  DEF_BIT_CLR_MASK(val, mask)             val &=~(mask) 
#define  DEF_BIT_NEG_MASK(val, mask)             val ^= (mask) 

#define  DEF_BIT_IS_SET(val, mask)               ((((val) & (mask)) == (mask)) ? (DEF_YES) : (DEF_NO ))
#define  DEF_BIT_IS_SET_ANY(val, mask)           (((val) & (mask)) ? (DEF_YES) : (DEF_NO ))

#define  DEF_BIT_IS_CLR(val, mask)               (((val) & (mask)) ? (DEF_NO ) : (DEF_YES))
#define  DEF_BIT_IS_CLR_ANY(val, mask)           ((((val) & (mask)) != (mask)) ? (DEF_YES) : (DEF_NO ))
/*-------------------------------------------------------------------------------
                                     Calculate                            
---------------------------------------------------------------------------------*/
#define  DEF_MAX(x, y)                           (((x) > (y)) ? (x) : (y))
#define  DEF_MIN(x, y)                           (((x) < (y)) ? (x) : (y))

#define  DEF_UINT_DIFF(x, y)                     (((x) > (y)) ? ((x) - (y)) : ((y) - (x)))

/*-------------------------------------------------------------------------------
                                     Data Convert                           
---------------------------------------------------------------------------------*/

#define  DEF_U8_TO_U16(h,l)                      (((unsigned int)(h) << 8)+(l))
#define  DEF_U16_TO_U8_H(x)                      ((x) >> 8)
#define  DEF_U16_TO_U8_l(x)                      ((x)& 0x00ff)
#define  DEF_U16_TO_U8(x,h,l)                    h = DEF_U16_TO_U8_H(x);l = DEF_U16_TO_U8_l(x)

#define  DEF_U8_TO_U32(h1,h0,l1,l0)              (((unsigned long)(h1) << 24)+((unsigned long)(h0) << 16)+((unsigned long)(l1) << 8)+(l0))
#define  DEF_U16_TO_U32(h,l)                     (((unsigned long)(h) << 16) + (l))

#define  DEF_U32_TO_U16_H(x)                     ((x)>> 16)
#define  DEF_U32_TO_U16_L(x)                     ((unsigned int)(x))

#define DEF_U32_TO_U8_H1(x)                      ((x) >> 24)
#define DEF_U32_TO_U8_H0(x)                      (((x)& 0x00ff0000) >> 16)
#define DEF_U32_TO_U8_L1(x)                      (((x)& 0x0000ff00) >> 8)
#define DEF_U32_TO_U8_L0(x)                      ((x)& 0x000000ff)

#define DEF_U32_TO_U8(x,h1,h0,l1,l0)             h1=DEF_U32_TO_U8_H1(x);\
                                                 h0=DEF_U32_TO_U8_H0(x);\
                                                 l1=DEF_U32_TO_U8_L1(x);\
                                                 l0=DEF_U32_TO_U8_L0(x)

#endif
/********************************* End of file *********************************/
