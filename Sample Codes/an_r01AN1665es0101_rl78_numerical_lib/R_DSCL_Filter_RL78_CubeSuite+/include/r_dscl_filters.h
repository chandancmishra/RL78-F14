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
* File Name    : r_dscl_filters.h
* Version      : 0.1
* Device(s)    : RL78/G14
* Tool-Chain   : CubeSuite+, CA78K0R V1.30
* Description  : PUBLIC header file for filter kernels of DSCL library
* Operation    :
* Limitations  :
******************************************************************************/

/****************************************************************************** 
* History      : YYYY.MM.DD  Version  Description 
*              : 2012.08.01  0.10     First draft
******************************************************************************/ 

#ifndef R_DSCL_FILTERS_H
#define R_DSCL_FILTERS_H


/****************************************************************************** 
Includes
******************************************************************************/ 
#include "r_dscl_types.h"


/****************************************************************************** 
Macro definitions 
******************************************************************************/ 
#define	FIR_SCALE_C		(15)
#define	IIR_SP_SCALE_C	(15)
#define	IIR_BQ_SCALE_C	(14)
/****************************************************************************** 
Typedef definitions 
******************************************************************************/ 
/*---------------------------*/
/* Generic FIR filter        */
/*---------------------------*/
typedef struct 
{ 
    uint16_t taps;     // number of filter taps 
    void *   coefs;    // pointer to filter coefficients 
    void *   state;    // pointer to filter state data, including the filter’s delay line  
                       // and any other implementation-dependent state 
    uint16_t options;  // options that specify rounding, saturation, or other behaviors 
} r_dscl_firfilter_t; 

/*---------------------------*/
/* IIR Biquad filter         */
/*---------------------------*/

typedef struct 
{ 
    uint16_t stages;     // number of biquad stages 
    void *   coefs;      // pointer to filter coefficients 
    void *   state;      // pointer to filter’s internal state (delay line)  
    uint16_t options;    // options that specify rounding, saturation, or other behaviors 
} r_dscl_iirbiquad_t; 

/*---------------------------*/
/* Single-pole IIR filter    */
/*---------------------------*/
typedef struct 
{ 
	void *    coefs; 
    void *    state;   // feedback state 
    uint16_t  options; // options that specify rounding, saturation, or other behaviors 
} r_dscl_iirsinglepole_t; 


/****************************************************************************** 
Filter API Function prototypes
******************************************************************************/ 
/*---------------------------*/
/* Generic FIR filter        */
/*---------------------------*/

/* Real input: i16; Real output: i16 */ 
int16_t R_DSCL_FIR_StateSize_i16i16 (
    const r_dscl_firfilter_t * handle
);

int16_t R_DSCL_FIR_Init_i16i16 (
    r_dscl_firfilter_t * handle
);

int16_t R_DSCL_FIR_i16i16 (
    const r_dscl_firfilter_t * handle, 
    const vector_t * input, 
    vector_t * output
);

/*---------------------------*/
/* IIR Biquad filter         */
/*---------------------------*/

/* Real input: i16; Real output: i16 */ 
int16_t R_DSCL_IIRBiquad_StateSize_i16i16 (
    const r_dscl_iirbiquad_t * handle
);

int16_t R_DSCL_IIRBiquad_Init_i16i16 (
    r_dscl_iirbiquad_t * handle
);

int16_t R_DSCL_IIRBiquad_i16i16 (
    const r_dscl_iirbiquad_t * handle, 
    const vector_t * input, 
    vector_t * output
);

/*---------------------------*/
/* Single-pole IIR filter    */
/*---------------------------*/

/* Real input: i16; Real output: i16 */ 
int16_t R_DSCL_IIRSinglePole_i16i16 (
    const r_dscl_iirsinglepole_t * handle, 
    const vector_t * input, 
    vector_t * output
);


#endif
/* End of file */


