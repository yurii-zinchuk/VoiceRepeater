/*******************************************************************************
* File Name: CapSense1_Sns.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "CapSense1_Sns.h"

static CapSense1_Sns_BACKUP_STRUCT  CapSense1_Sns_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: CapSense1_Sns_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet CapSense1_Sns_SUT.c usage_CapSense1_Sns_Sleep_Wakeup
*******************************************************************************/
void CapSense1_Sns_Sleep(void)
{
    #if defined(CapSense1_Sns__PC)
        CapSense1_Sns_backup.pcState = CapSense1_Sns_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            CapSense1_Sns_backup.usbState = CapSense1_Sns_CR1_REG;
            CapSense1_Sns_USB_POWER_REG |= CapSense1_Sns_USBIO_ENTER_SLEEP;
            CapSense1_Sns_CR1_REG &= CapSense1_Sns_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CapSense1_Sns__SIO)
        CapSense1_Sns_backup.sioState = CapSense1_Sns_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        CapSense1_Sns_SIO_REG &= (uint32)(~CapSense1_Sns_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: CapSense1_Sns_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to CapSense1_Sns_Sleep() for an example usage.
*******************************************************************************/
void CapSense1_Sns_Wakeup(void)
{
    #if defined(CapSense1_Sns__PC)
        CapSense1_Sns_PC = CapSense1_Sns_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            CapSense1_Sns_USB_POWER_REG &= CapSense1_Sns_USBIO_EXIT_SLEEP_PH1;
            CapSense1_Sns_CR1_REG = CapSense1_Sns_backup.usbState;
            CapSense1_Sns_USB_POWER_REG &= CapSense1_Sns_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CapSense1_Sns__SIO)
        CapSense1_Sns_SIO_REG = CapSense1_Sns_backup.sioState;
    #endif
}


/* [] END OF FILE */
