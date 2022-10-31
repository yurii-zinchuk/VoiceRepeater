/*******************************************************************************
* File Name: CapSense1_TunerHelper.h
* Version 2.60
*
* Description:
*  This file provides constants and structure declarations for the tuner helper
*  APIs for the CapSense CSD component.
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CAPSENSE_CSD_TUNERHELPER_CapSense1_H)
#define CY_CAPSENSE_CSD_TUNERHELPER_CapSense1_H

#include "CapSense1.h"

#if(0u != CapSense1_CSHL_API_GENERATE)
    #include "CapSense1_CSHL.h"
#endif /* (0u != CapSense1_CSHL_API_GENERATE) */

#if (CapSense1_TUNER_API_GENERATE)
    #include "CapSense1_MBX.h"
#endif /* (CapSense1_TUNER_API_GENERATE) */


/***************************************
*     Constants for mailboxes
***************************************/

#define CapSense1_DEFAULT_MAILBOXES_NUMBER       (1u)

#define CapSense1_CENTROID_POSITION_BUFFER_SIZE  (2u)
#define CapSense1_MB_POSITION_BUFFER_SIZE        (2u)

#define CapSense1_DEFAULT_TRACKPAD_INDEX         (0u)

#define CapSense1_FIRST_FINGER_INDEX             (0u)
#define CapSense1_SECOND_FINGER_INDEX            (1u)

#define CapSense1_FIRST_FINGER_X_INDEX           (0u)
#define CapSense1_FIRST_FINGER_Y_INDEX           (1u)

#define CapSense1_SECOND_FINGER_X_INDEX          (2u)
#define CapSense1_SECOND_FINGER_Y_INDEX          (3u)

#define CapSense1_GESTURE_TYPE_MASK              (0xF0u)
#define CapSense1_INERTIAL_SCROLL                (0xB0u)
#define CapSense1_NON_INERTIAL_SCROLL            (0xC0u)


/***************************************
*        Function Prototypes
***************************************/

void CapSense1_TunerStart(void);
void CapSense1_TunerComm(void);

#if (CapSense1_TUNER_API_GENERATE)
   CapSense1_NO_STRICT_VOLATILE void CapSense1_ProcessAllWidgets(volatile CapSense1_OUTBOX *outbox);
#endif /* (CapSense1_TUNER_API_GENERATE) */


/***************************************
*     Vars with External Linkage
***************************************/
#if (CapSense1_TUNER_API_GENERATE)
    extern volatile CapSense1_MAILBOXES CapSense1_mailboxesComm;
#endif /* (CapSense1_TUNER_API_GENERATE) */

#endif  /* (CY_CAPSENSE_CSD_TUNERHELPER_CapSense1_H)*/


/* [] END OF FILE */
