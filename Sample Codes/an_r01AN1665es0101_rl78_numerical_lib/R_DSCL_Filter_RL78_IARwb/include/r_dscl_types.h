/*******************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only
* intended for use with Renesas products. No other uses are authorized. This
* software is owned by Renesas Electronics Corporation and is protected under
* all applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING
* THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING BUT NOT
* LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
* AND NON-INFRINGEMENT. ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.
* TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY LAW, NEITHER RENESAS
* ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE
* FOR ANY DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR
* ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR ITS AFFILIATES HAVE
* BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software
* and to discontinue the availability of this software. By using this software,
* you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011 Renesas Electronics Corporation. All rights reserved.
*******************************************************************************/

/*******************************************************************************
* File Name    : r_dscl_types.h
* Version      : 0.1
* Device(s)    : RL78/G14
* Tool-Chain   : IAR Embedded Workbench for Renesas RL78, IAR Compiler V1.40.X
* Description  : Common header file for DSCL library
* Operation    :
* Limitations  :
******************************************************************************/

/****************************************************************************** 
* History      : YYYY.MM.DD  Version  Description 
*              : 2012.08.01  0.10     First draft
******************************************************************************/ 

#ifndef R_DSCL_TYPES_H
#define R_DSCL_TYPES_H


/****************************************************************************** 
Includes
******************************************************************************/ 
#include "r_stdint.h"

/****************************************************************************** 
Macro definitions 
******************************************************************************/ 
#define USE_ASM_CODE	1
//#define NULL			0

/* Return code, 32-bit */
typedef enum {  
    R_DSCL_STATUS_HISTO_OUT_OF_RANGE = 3,
    R_DSCL_STATUS_UNDEFINED_RESULT   = 2,		
    R_DSCL_STATUS_OVERFLOW           = 1,
    R_DSCL_STATUS_OK                 = 0,
    R_DSCL_ERR_HANDLE_NULL           = -100,
    R_DSCL_ERR_INPUT_NULL,
    R_DSCL_ERR_OUTPUT_NULL,
    R_DSCL_ERR_STATE_NULL,
    R_DSCL_ERR_COEFF_NULL,
    R_DSCL_ERR_REFER_NULL,
    R_DSCL_INVALID_INPUT_SIZE,
    R_DSCL_INVALID_OUTPUT_SIZE,
    R_DSCL_ERR_INVALID_TAPS,
    R_DSCL_ERR_INVALID_STAGES,
    R_DSCL_ERR_INVALID_OPTIONS,
    R_DSCL_ERR_INVALID_SCALE,
    R_DSCL_ERR_DIMENSIONS,
    R_DSCL_ERR_INVALID_POINTS,
    R_DSCL_ERR_NO_MEMORY_AVAILABLE,
} r_dscl_status_t; 


/* Options, 16-bit */
/* Rounding mode, bits 0-2 */
typedef enum {  
    R_DSCL_ROUNDING_DEFAULT  = 0x00,
    R_DSCL_ROUNDING_TRUNC    = 0x01,
    R_DSCL_ROUNDING_NEAREST  = 0x02
} r_dscl_rounding_option_t; 

/****************************************************************************** 
Typedef definitions 
******************************************************************************/ 
typedef struct 
{ 
    uint16_t n; 
    void *   data; 
} vector_t; 


/****************************************************************************** 
Exported global functions (to be accessed by other files) 
******************************************************************************/ 

#endif
/* End of file */


