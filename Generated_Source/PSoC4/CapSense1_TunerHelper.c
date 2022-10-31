/*******************************************************************************
* File Name: CapSense1_TunerHelper.c
* Version 2.60
*
* Description:
*  This file provides the source code of the Tuner helper APIs for the CapSense CSD
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2013-2016, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CapSense1_TunerHelper.h"
#include "cyapicallbacks.h"

#if (CapSense1_TUNER_API_GENERATE)
    #include "SCB.h"
    #include "SCB_EZI2C.h"
    volatile CapSense1_MAILBOXES CapSense1_mailboxesComm;
#endif  /* (CapSense1_TUNER_API_GENERATE) */

/* `#START CapSense1_TunerHelper_HEADER` */

/* `#END` */

/*******************************************************************************
* Function Name: CapSense1_TunerStart
********************************************************************************
*
* Summary:
*  Initializes the CapSense CSD component and EzI2C communication component to use
*  a mailbox data structure for communication with the Tuner GUI.
*  Start the scanning, after initialization is complete.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
*******************************************************************************/
void CapSense1_TunerStart(void)
{
    #if (0u != CapSense1_TUNER_API_GENERATE)

        /* Init mbx and quick check */
        CapSense1_InitMailbox(&CapSense1_mailboxesComm.csdMailbox);
        CapSense1_mailboxesComm.numMailBoxes = CapSense1_DEFAULT_MAILBOXES_NUMBER;

        /* Start CapSense and baselines */
        CapSense1_Start();

        /* Initialize baselines */
        #if(0u != CapSense1_CSHL_API_GENERATE)
            CapSense1_InitializeEnabledBaselines();
        #endif /* (0u != CapSense1_CSHL_API_GENERATE) */

        /* Start EzI2C, clears buf pointers */
        SCB_Start();

        /* Setup EzI2C buffers */
        SCB_EzI2CSetBuffer1(sizeof(CapSense1_mailboxesComm), sizeof(CapSense1_mailboxesComm),
                                                   (volatile uint8 *) &CapSense1_mailboxesComm);

        /* Starts scan all enabled sensors */
        CapSense1_ScanEnabledWidgets();

    #endif  /* (0u != CapSense1_TUNER_API_GENERATE) */
}


/*******************************************************************************
* Function Name: CapSense1_TunerComm
********************************************************************************
*
* Summary:
*  This function is blocking. It waits till scanning loop is completed and applies
*  the new parameters from the Tuner GUI if available (the manual tuning mode only). Updates
*  the enabled baselines and state of widgets. Waits while the Tuner GUI reports that
*  the mailbox content  could be modified. Then loads the report data into the outbox
*  and sets a busy flag. Starts a new scanning loop.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global Variables:
*  None
*
*******************************************************************************/
void CapSense1_TunerComm(void)
{
    #if (0u != CapSense1_TUNER_API_GENERATE)
        if (0u == CapSense1_IsBusy())
        {
            /* Apply new settings */
            #if((CapSense1_TUNING_METHOD != CapSense1__TUNING_NONE) &&\
                (0u != CapSense1_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
                (CapSense1_TUNING_METHOD == CapSense1__TUNING_MANUAL))

                CapSense1_ReadMessage(&CapSense1_mailboxesComm.csdMailbox);

            #endif  /* ((CapSense1_TUNING_METHOD != CapSense1__TUNING_NONE) &&\
                        (0u != CapSense1_TOTAL_TRACKPAD_GESTURES_COUNT) ||\
                        (CapSense1_TUNING_METHOD == CapSense1__TUNING_MANUAL)) */

            #if(0u != CapSense1_CSHL_API_GENERATE)
                /* Update all baselines and process all widgets */
                CapSense1_UpdateEnabledBaselines();
                CapSense1_ProcessAllWidgets(&CapSense1_mailboxesComm.csdMailbox.outbox);
            #endif /* (0u != CapSense1_CSHL_API_GENERATE) */

            CapSense1_PostMessage(&CapSense1_mailboxesComm.csdMailbox);

            /* Enable EZI2C interrupts, after scan complete */
            SCB_EnableInt();

            while((CapSense1_mailboxesComm.csdMailbox.type != CapSense1_TYPE_ID) ||
                  (0u != (SCB_EzI2CGetActivity() & SCB_EZI2C_STATUS_BUSY))){}

            /* Disable EZI2C interrupts, while scanning */
            SCB_DisableInt();

            /* Start scan all sensors */
            CapSense1_ScanEnabledWidgets();
        }
    #endif /* (0u != CapSense1_TUNER_API_GENERATE) */
}


#if ((0u != CapSense1_TUNER_API_GENERATE) && (0u != CapSense1_CSHL_API_GENERATE))
    /*******************************************************************************
    * Function Name: CapSense1_ProcessAllWidgets
    ********************************************************************************
    *
    * Summary:
    *  Calls the required functions to update all the widgets' state:
    *   - CapSense1_GetCentroidPos() - calls only if linear sliders are
    *     available.
    *   - CapSense1_GetRadialCentroidPos() - calls only if the  radial slider is
    *     available.
    *   - CapSense1_GetTouchCentroidPos() - calls only if the  touchpad slider
    *     available.
    *   - CapSense1_CheckIsAnyWidgetActive();
    *  The results of operations are copied to OUTBOX.
    *
    * Parameters:
    *  None
    *
    * Return:
    *  None
    *
    * Global Variables:
    *  CapSense1_OUTBOX outbox - the structure which is used as an output
    *  buffer to report data to the Tuner GUI.
    *  Update fields:
    *    - position[];
    *    - OnMask[];
    *
    * Global Variables:
    *  None
    *
    *******************************************************************************/
    void CapSense1_ProcessAllWidgets(volatile CapSense1_OUTBOX *outbox)
    {
        uint8  i = 0u;

        #if (0u != CapSense1_TOTAL_MATRIX_BUTTONS_COUNT)
            uint8 mbPositionBuf[CapSense1_MB_POSITION_BUFFER_SIZE];
        #endif /* (0u != CapSense1_TOTAL_MATRIX_BUTTONS_COUNT) */

        #if (0u != CapSense1_TOTAL_TOUCH_PADS_BASIC_COUNT)
            uint16 centroidPosBuf[CapSense1_CENTROID_POSITION_BUFFER_SIZE];
        #endif  /* (0u != CapSense1_TOTAL_TOUCH_PADS_BASIC_COUNT) */

        #if(0u != CapSense1_TOTAL_TRACKPAD_GESTURES_COUNT)
            CapSense1_POSITION_STRUCT trackpadPosBuf[CapSense1_CENTROID_POSITION_BUFFER_SIZE];
        #endif  /* (0u != CapSense1_TOTAL_TRACKPAD_GESTURES_COUNT) */

        #if ( (0u != CapSense1_TOTAL_RADIAL_SLIDERS_COUNT) || (0u != CapSense1_TOTAL_TOUCH_PADS_COUNT) || \
              (0u != CapSense1_TOTAL_MATRIX_BUTTONS_COUNT))
            uint8 widgetCnt;
        #endif  /* ((0u != CapSense1_TOTAL_RADIAL_SLIDERS_COUNT) || (0u != CapSense1_TOTAL_TOUCH_PADS_COUNT)) ||
                *   (0u != CapSense1_TOTAL_MATRIX_BUTTONS_COUNT)
                */

        /* Calculate widget with centroids */
        #if (0u != CapSense1_TOTAL_LINEAR_SLIDERS_COUNT)
            for(; i < CapSense1_TOTAL_LINEAR_SLIDERS_COUNT; i++)
            {
                outbox->centroidPosition[i] = (uint16)CapSense1_GetCentroidPos((uint32)i);
            }
        #endif /* (0u != CapSense1_TOTAL_LINEAR_SLIDERS_COUNT) */

        #if (0u != CapSense1_TOTAL_RADIAL_SLIDERS_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + CapSense1_TOTAL_RADIAL_SLIDERS_COUNT); i++)
            {
                outbox->centroidPosition[i] = (uint16)CapSense1_GetRadialCentroidPos((uint32)i);
            }
        #endif /* (0u != CapSense1_TOTAL_RADIAL_SLIDERS_COUNT) */

        #if (0u != CapSense1_TOTAL_TOUCH_PADS_BASIC_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + (CapSense1_TOTAL_TOUCH_PADS_BASIC_COUNT * 2u)); i=i+2u)
            {
                if(CapSense1_GetTouchCentroidPos((uint32)i, centroidPosBuf) == 0u)
                {
                    outbox->centroidPosition[i + CapSense1_FIRST_FINGER_X_INDEX] = CapSense1_MAX_UINT_16;
                    outbox->centroidPosition[i + CapSense1_FIRST_FINGER_Y_INDEX] = CapSense1_MAX_UINT_16;
                }
                else
                {
                    outbox->centroidPosition[i + CapSense1_FIRST_FINGER_X_INDEX] =
                    (uint16) centroidPosBuf[CapSense1_FIRST_FINGER_X_INDEX];

                    outbox->centroidPosition[i + CapSense1_FIRST_FINGER_Y_INDEX] =
                    (uint16) centroidPosBuf[CapSense1_FIRST_FINGER_Y_INDEX];
                }
            }
        #endif /* (0u != CapSense1_TOTAL_TOUCH_PADS_BASIC_COUNT) */

        #if (0u != CapSense1_TOTAL_TRACKPAD_GESTURES_COUNT)
            widgetCnt = i;
            for(; i < (widgetCnt + (CapSense1_TOTAL_TRACKPAD_GESTURES_COUNT * 4u)); i=i+4u)
            {
                outbox->fingersNum[CapSense1_DEFAULT_TRACKPAD_INDEX] =
                (uint8)CapSense1_GetDoubleTouchCentroidPos(trackpadPosBuf);

                outbox->gestureID[CapSense1_DEFAULT_TRACKPAD_INDEX] =
                (uint8)CapSense1_DecodeAllGestures((uint32)outbox->fingersNum[CapSense1_DEFAULT_TRACKPAD_INDEX], trackpadPosBuf);

                #if((0u != CapSense1_ST_SCROLL_GEST_ENABLED) || (0u != CapSense1_DT_SCROLL_GEST_ENABLED))
                    /*
                    Report Scroll count only for scroll and Inertial Scroll gestures.
                    For all other gestures report scroll count as zero to tuner.
                     */
                    if (((outbox->gestureID[CapSense1_DEFAULT_TRACKPAD_INDEX] & CapSense1_GESTURE_TYPE_MASK) == CapSense1_NON_INERTIAL_SCROLL) ||
                        ((outbox->gestureID[CapSense1_DEFAULT_TRACKPAD_INDEX] & CapSense1_GESTURE_TYPE_MASK) == CapSense1_INERTIAL_SCROLL))
                    {
                        outbox->scrollCnt = CapSense1_GetScrollCnt();
                    }
                    else
                    {
                        outbox->scrollCnt = 0u;
                    }
                #endif /* ((0u != CapSense1_ST_SCROLL_GEST_ENABLED) || (0u != CapSense1_DT_SCROLL_GEST_ENABLED)) */

                outbox->centroidPosition[i + CapSense1_FIRST_FINGER_X_INDEX] = CapSense1_MAX_UINT_16;
                outbox->centroidPosition[i + CapSense1_FIRST_FINGER_Y_INDEX] = CapSense1_MAX_UINT_16;
                outbox->centroidPosition[i + CapSense1_SECOND_FINGER_X_INDEX] = CapSense1_MAX_UINT_16;
                outbox->centroidPosition[i + CapSense1_SECOND_FINGER_Y_INDEX] = CapSense1_MAX_UINT_16;

                if(0u != outbox->fingersNum[CapSense1_DEFAULT_TRACKPAD_INDEX])
                {
                    outbox->centroidPosition[i + CapSense1_FIRST_FINGER_X_INDEX] =
                    (uint16) trackpadPosBuf[CapSense1_FIRST_FINGER_INDEX].x;

                    outbox->centroidPosition[i + CapSense1_FIRST_FINGER_Y_INDEX] =
                    (uint16) trackpadPosBuf[CapSense1_FIRST_FINGER_INDEX].y;

                    if(outbox->fingersNum[CapSense1_DEFAULT_TRACKPAD_INDEX] > 1u)
                    {
                        outbox->centroidPosition[i + CapSense1_SECOND_FINGER_X_INDEX] =
                        (uint16) trackpadPosBuf[CapSense1_SECOND_FINGER_INDEX].x;

                        outbox->centroidPosition[i + CapSense1_SECOND_FINGER_Y_INDEX] =
                        (uint16) trackpadPosBuf[CapSense1_SECOND_FINGER_INDEX].y;
                    }
                }
            }
        #endif /* (0u != CapSense1_TOTAL_TRACKPAD_GESTURES_COUNT) */

        #if (0u != CapSense1_TOTAL_MATRIX_BUTTONS_COUNT)
            i += CapSense1_TOTAL_BUTTONS_COUNT;
            widgetCnt = 0u;
            for(; widgetCnt < (CapSense1_TOTAL_MATRIX_BUTTONS_COUNT * 2u); widgetCnt += 2u)
            {
                if(CapSense1_GetMatrixButtonPos((uint32)i, mbPositionBuf) == 0u)
                {
                    outbox->mbPosition[widgetCnt] = CapSense1_MAX_UINT_8;
                    outbox->mbPosition[widgetCnt+1u] = CapSense1_MAX_UINT_8;
                }
                else
                {
                    outbox->mbPosition[widgetCnt] = mbPositionBuf[0u];
                    outbox->mbPosition[widgetCnt+1u] = mbPositionBuf[1u];
                }
                i += 2u;
            }
        #endif /* (0u != CapSense1_TOTAL_MATRIX_BUTTONS_COUNT) */

        #if(0u != CapSense1_CSHL_API_GENERATE)
            /* Update On/Off State */
            (void)CapSense1_CheckIsAnyWidgetActive();

            /* Copy OnMask */
            for(i=0u; i < CapSense1_TOTAL_SENSOR_MASK_COUNT; i++)
            {
                outbox->onMask[i]  = CapSense1_sensorOnMask[i];
            }
        #endif /* (0u != CapSense1_CSHL_API_GENERATE) */

        /* `#START CapSense1_ProcessAllWidgets_Debug` */

        /* `#END` */

        #ifdef CapSense1_PROCESS_ALL_WIDGETS_CALLBACK
            CapSense1_ProcessAllWidgets_Callback();
        #endif /* CapSense1_PROCESS_ALL_WIDGETS_CALLBACK */
    }


#endif /* ((0u != CapSense1_TUNER_API_GENERATE) && (0u != CapSense1_CSHL_API_GENERATE)) */


/* [] END OF FILE */
