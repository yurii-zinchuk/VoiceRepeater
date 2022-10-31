/*******************************************************************************
* File Name: CapSense1_Sns.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_CapSense1_Sns_H) /* Pins CapSense1_Sns_H */
#define CY_PINS_CapSense1_Sns_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CapSense1_Sns_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} CapSense1_Sns_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   CapSense1_Sns_Read(void);
void    CapSense1_Sns_Write(uint8 value);
uint8   CapSense1_Sns_ReadDataReg(void);
#if defined(CapSense1_Sns__PC) || (CY_PSOC4_4200L) 
    void    CapSense1_Sns_SetDriveMode(uint8 mode);
#endif
void    CapSense1_Sns_SetInterruptMode(uint16 position, uint16 mode);
uint8   CapSense1_Sns_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void CapSense1_Sns_Sleep(void); 
void CapSense1_Sns_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(CapSense1_Sns__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define CapSense1_Sns_DRIVE_MODE_BITS        (3)
    #define CapSense1_Sns_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CapSense1_Sns_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the CapSense1_Sns_SetDriveMode() function.
         *  @{
         */
        #define CapSense1_Sns_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define CapSense1_Sns_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define CapSense1_Sns_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define CapSense1_Sns_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define CapSense1_Sns_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define CapSense1_Sns_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define CapSense1_Sns_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define CapSense1_Sns_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define CapSense1_Sns_MASK               CapSense1_Sns__MASK
#define CapSense1_Sns_SHIFT              CapSense1_Sns__SHIFT
#define CapSense1_Sns_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in CapSense1_Sns_SetInterruptMode() function.
     *  @{
     */
        #define CapSense1_Sns_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define CapSense1_Sns_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define CapSense1_Sns_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define CapSense1_Sns_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(CapSense1_Sns__SIO)
    #define CapSense1_Sns_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(CapSense1_Sns__PC) && (CY_PSOC4_4200L)
    #define CapSense1_Sns_USBIO_ENABLE               ((uint32)0x80000000u)
    #define CapSense1_Sns_USBIO_DISABLE              ((uint32)(~CapSense1_Sns_USBIO_ENABLE))
    #define CapSense1_Sns_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define CapSense1_Sns_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define CapSense1_Sns_USBIO_ENTER_SLEEP          ((uint32)((1u << CapSense1_Sns_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << CapSense1_Sns_USBIO_SUSPEND_DEL_SHIFT)))
    #define CapSense1_Sns_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << CapSense1_Sns_USBIO_SUSPEND_SHIFT)))
    #define CapSense1_Sns_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << CapSense1_Sns_USBIO_SUSPEND_DEL_SHIFT)))
    #define CapSense1_Sns_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(CapSense1_Sns__PC)
    /* Port Configuration */
    #define CapSense1_Sns_PC                 (* (reg32 *) CapSense1_Sns__PC)
#endif
/* Pin State */
#define CapSense1_Sns_PS                     (* (reg32 *) CapSense1_Sns__PS)
/* Data Register */
#define CapSense1_Sns_DR                     (* (reg32 *) CapSense1_Sns__DR)
/* Input Buffer Disable Override */
#define CapSense1_Sns_INP_DIS                (* (reg32 *) CapSense1_Sns__PC2)

/* Interrupt configuration Registers */
#define CapSense1_Sns_INTCFG                 (* (reg32 *) CapSense1_Sns__INTCFG)
#define CapSense1_Sns_INTSTAT                (* (reg32 *) CapSense1_Sns__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define CapSense1_Sns_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(CapSense1_Sns__SIO)
    #define CapSense1_Sns_SIO_REG            (* (reg32 *) CapSense1_Sns__SIO)
#endif /* (CapSense1_Sns__SIO_CFG) */

/* USBIO registers */
#if !defined(CapSense1_Sns__PC) && (CY_PSOC4_4200L)
    #define CapSense1_Sns_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define CapSense1_Sns_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define CapSense1_Sns_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define CapSense1_Sns_DRIVE_MODE_SHIFT       (0x00u)
#define CapSense1_Sns_DRIVE_MODE_MASK        (0x07u << CapSense1_Sns_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins CapSense1_Sns_H */


/* [] END OF FILE */
