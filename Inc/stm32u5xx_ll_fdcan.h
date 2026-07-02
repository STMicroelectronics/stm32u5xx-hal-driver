/**
  ******************************************************************************
  * @file    stm32u5xx_ll_fdcan.h
  * @author  MCD Application Team
  * @brief   Header file of FDCAN LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#ifndef STM32U5xx_LL_FDCAN_H
#define STM32U5xx_LL_FDCAN_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32u5xx.h"

/** @addtogroup STM32U5xx_LL_Driver
  * @{
  */

#if defined(FDCAN1)

/** @defgroup FDCAN_LL FDCAN
  * @{
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup FDCAN_LL_Private_Macros FDCAN Private Macros
  * @{
  */
#define IS_LL_FDCAN_ALL_INSTANCE(__INSTANCE__) IS_FDCAN_ALL_INSTANCE(__INSTANCE__)
/**
  * @}
  */

/* Exported types ------------------------------------------------------------*/
#if defined(USE_FULL_LL_DRIVER)
/** @defgroup FDCAN_LL_Exported_Types FDCAN Exported Types
  * @{
  */

/**
  * @brief  FDCAN init structure definition
  */
typedef struct {
    uint32_t ClockDivider; /*!< Specifies the FDCAN kernel clock divider.
                                       This parameter can be a value of @ref FDCAN_LL_EC_CLOCK_DIVIDER.

                                       This feature can be modified afterwards using unitary function
                                       @ref LL_FDCAN_SetClockDivider(). */

    uint32_t FrameFormat; /*!< Specifies the FDCAN frame format.
                                       This parameter can be a value of @ref FDCAN_LL_EC_FRAME_FORMAT.

                                       This feature can be modified afterwards using unitary function
                                       @ref LL_FDCAN_SetFrameFormat(). */

    uint32_t Mode; /*!< Specifies the FDCAN operating mode.
                                       This parameter can be a value of @ref FDCAN_LL_EC_MODE.

                                       This feature can be modified afterwards using unitary function
                                       @ref LL_FDCAN_SetMode(). */

    uint32_t AutoRetransmission; /*!< Specifies whether automatic retransmission is enabled.
                                       This parameter can be a value of @ref FDCAN_LL_EC_AUTO_RETRANSMISSION.

                                       This feature can be modified afterwards using unitary functions
                                       @ref LL_FDCAN_EnableAutoRetransmission() and
                                       @ref LL_FDCAN_DisableAutoRetransmission(). */

    uint32_t TransmitPause; /*!< Specifies whether transmit pause is enabled.
                                       This parameter can be a value of @ref FDCAN_LL_EC_TRANSMIT_PAUSE.

                                       This feature can be modified afterwards using unitary functions
                                       @ref LL_FDCAN_EnableTransmitPause() and @ref LL_FDCAN_DisableTransmitPause(). */

    uint32_t ProtocolException; /*!< Specifies whether protocol exception handling is enabled.
                                       This parameter can be a value of @ref FDCAN_LL_EC_PROTOCOL_EXCEPTION.

                                       This feature can be modified afterwards using unitary functions
                                       @ref LL_FDCAN_EnableProtocolException() and
                                       @ref LL_FDCAN_DisableProtocolException(). */

    uint32_t NominalPrescaler; /*!< Specifies the nominal bit time prescaler.
                                       This parameter must be a number between 1 and 512. */

    uint32_t NominalSyncJumpWidth; /*!< Specifies the nominal sync jump width.
                                       This parameter must be a number between 1 and 128. */

    uint32_t NominalTimeSeg1; /*!< Specifies nominal bit segment 1.
                                       This parameter must be a number between 1 and 256. */

    uint32_t NominalTimeSeg2; /*!< Specifies nominal bit segment 2.
                                       This parameter must be a number between 1 and 128. */

    uint32_t DataPrescaler; /*!< Specifies the data bit time prescaler.
                                       This parameter must be a number between 1 and 32. */

    uint32_t DataSyncJumpWidth; /*!< Specifies the data sync jump width.
                                       This parameter must be a number between 1 and 16. */

    uint32_t DataTimeSeg1; /*!< Specifies data bit segment 1.
                                       This parameter must be a number between 1 and 32. */

    uint32_t DataTimeSeg2; /*!< Specifies data bit segment 2.
                                       This parameter must be a number between 1 and 16. */

    uint32_t StdFiltersNbr; /*!< Specifies the number of standard filters.
                                       This parameter must be a number between 0 and LL_FDCAN_MAX_STD_FILTERS. */

    uint32_t ExtFiltersNbr; /*!< Specifies the number of extended filters.
                                       This parameter must be a number between 0 and LL_FDCAN_MAX_EXT_FILTERS. */

    uint32_t TxFifoQueueMode; /*!< Specifies Tx FIFO/Queue mode.
                                       This parameter can be a value of @ref FDCAN_LL_EC_TX_FIFO_QUEUE_MODE.

                                       This feature can be modified afterwards using unitary function
                                       @ref LL_FDCAN_SetTxFifoQueueMode(). */
} LL_FDCAN_InitTypeDef;

/**
  * @brief  FDCAN message RAM block addresses definition
  */
typedef struct {
    uint32_t StandardFilterSA; /*!< Standard filter list start address */
    uint32_t ExtendedFilterSA; /*!< Extended filter list start address */
    uint32_t RxFIFO0SA; /*!< Rx FIFO 0 start address            */
    uint32_t RxFIFO1SA; /*!< Rx FIFO 1 start address            */
    uint32_t TxEventFIFOSA; /*!< Tx event FIFO start address        */
    uint32_t TxFIFOQSA; /*!< Tx FIFO/Queue start address        */
} LL_FDCAN_MessageRAMTypeDef;

/**
  * @brief  FDCAN filter structure definition
  */
typedef struct {
    uint32_t IdType; /*!< Specifies the identifier type.
                              This parameter can be a value of @ref FDCAN_LL_EC_ID_TYPE. */
    uint32_t FilterIndex; /*!< Specifies the filter index. */
    uint32_t FilterType; /*!< Specifies the filter type.
                              This parameter can be a value of @ref FDCAN_LL_EC_FILTER_TYPE. */
    uint32_t FilterConfig; /*!< Specifies the filter configuration.
                              This parameter can be a value of @ref FDCAN_LL_EC_FILTER_CONFIG. */
    uint32_t FilterID1; /*!< Specifies filter identification 1. */
    uint32_t FilterID2; /*!< Specifies filter identification 2. */
} LL_FDCAN_FilterTypeDef;

/**
  * @brief  FDCAN Tx header structure definition
  */
typedef struct {
    uint32_t Identifier; /*!< Specifies the identifier. */
    uint32_t IdType; /*!< Specifies the identifier type.
                                     This parameter can be a value of @ref FDCAN_LL_EC_ID_TYPE. */
    uint32_t TxFrameType; /*!< Specifies the frame type.
                                     This parameter can be a value of @ref FDCAN_LL_EC_FRAME_TYPE. */
    uint32_t DataLength; /*!< Specifies the frame data length code.
                                     This parameter can be a value of @ref FDCAN_LL_EC_DATA_LENGTH. */
    uint32_t ErrorStateIndicator; /*!< Specifies the error state indicator.
                                     This parameter can be a value of @ref FDCAN_LL_EC_ERROR_STATE_INDICATOR. */
    uint32_t BitRateSwitch; /*!< Specifies whether bit rate switching is used.
                                     This parameter can be a value of @ref FDCAN_LL_EC_BIT_RATE_SWITCH. */
    uint32_t FDFormat; /*!< Specifies Classic CAN or FD CAN format.
                                     This parameter can be a value of @ref FDCAN_LL_EC_FD_FORMAT. */
    uint32_t TxEventFifoControl; /*!< Specifies Tx event FIFO control.
                                     This parameter can be a value of @ref FDCAN_LL_EC_TX_EVENT_FIFO_CONTROL. */
    uint32_t MessageMarker; /*!< Specifies the message marker. */
} LL_FDCAN_TxHeaderTypeDef;

/**
  * @brief  FDCAN Rx header structure definition
  */
typedef struct {
    uint32_t Identifier; /*!< Specifies the identifier. */
    uint32_t IdType; /*!< Specifies the identifier type.
                                       This parameter can be a value of @ref FDCAN_LL_EC_ID_TYPE. */
    uint32_t RxFrameType; /*!< Specifies the frame type.
                                       This parameter can be a value of @ref FDCAN_LL_EC_FRAME_TYPE. */
    uint32_t DataLength; /*!< Specifies the frame data length code.
                                       This parameter can be a value of @ref FDCAN_LL_EC_DATA_LENGTH. */
    uint32_t ErrorStateIndicator; /*!< Specifies the error state indicator.
                                       This parameter can be a value of @ref FDCAN_LL_EC_ERROR_STATE_INDICATOR. */
    uint32_t BitRateSwitch; /*!< Specifies whether bit rate switching was used.
                                       This parameter can be a value of @ref FDCAN_LL_EC_BIT_RATE_SWITCH. */
    uint32_t FDFormat; /*!< Specifies Classic CAN or FD CAN format.
                                       This parameter can be a value of @ref FDCAN_LL_EC_FD_FORMAT. */
    uint32_t RxTimestamp; /*!< Specifies the Rx timestamp. */
    uint32_t FilterIndex; /*!< Specifies the matching Rx acceptance filter index. */
    uint32_t
        IsFilterMatchingFrame; /*!< Specifies whether the accepted frame did not match any Rx filter. */
} LL_FDCAN_RxHeaderTypeDef;

/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/* Exported constants --------------------------------------------------------*/
/** @defgroup FDCAN_LL_Exported_Constants FDCAN Exported Constants
  * @{
  */

#define LL_FDCAN_MAX_STD_FILTERS (28U)
#define LL_FDCAN_MAX_EXT_FILTERS (8U)
#define LL_FDCAN_MAX_RX_FIFO0_ELEMENTS (3U)
#define LL_FDCAN_MAX_RX_FIFO1_ELEMENTS (3U)
#define LL_FDCAN_MAX_TX_EVENT_FIFO_ELEMENTS (3U)
#define LL_FDCAN_MAX_TX_FIFO_QUEUE_ELEMENTS (3U)
#define LL_FDCAN_MESSAGE_RAM_SIZE (848U)

/** @defgroup FDCAN_LL_EC_GET_FLAG Get Flags Defines
  * @{
  */
#define LL_FDCAN_FLAG_TX_COMPLETE FDCAN_IR_TC
#define LL_FDCAN_FLAG_TX_ABORT_COMPLETE FDCAN_IR_TCF
#define LL_FDCAN_FLAG_TX_FIFO_EMPTY FDCAN_IR_TFE
#define LL_FDCAN_FLAG_RX_HIGH_PRIORITY_MSG FDCAN_IR_HPM
#define LL_FDCAN_FLAG_TX_EVT_FIFO_ELT_LOST FDCAN_IR_TEFL
#define LL_FDCAN_FLAG_TX_EVT_FIFO_FULL FDCAN_IR_TEFF
#define LL_FDCAN_FLAG_TX_EVT_FIFO_NEW_DATA FDCAN_IR_TEFN
#define LL_FDCAN_FLAG_RX_FIFO0_MESSAGE_LOST FDCAN_IR_RF0L
#define LL_FDCAN_FLAG_RX_FIFO0_FULL FDCAN_IR_RF0F
#define LL_FDCAN_FLAG_RX_FIFO0_NEW_MESSAGE FDCAN_IR_RF0N
#define LL_FDCAN_FLAG_RX_FIFO1_MESSAGE_LOST FDCAN_IR_RF1L
#define LL_FDCAN_FLAG_RX_FIFO1_FULL FDCAN_IR_RF1F
#define LL_FDCAN_FLAG_RX_FIFO1_NEW_MESSAGE FDCAN_IR_RF1N
#define LL_FDCAN_FLAG_RAM_ACCESS_FAILURE FDCAN_IR_MRAF
#define LL_FDCAN_FLAG_ERROR_LOGGING_OVERFLOW FDCAN_IR_ELO
#define LL_FDCAN_FLAG_ERROR_PASSIVE FDCAN_IR_EP
#define LL_FDCAN_FLAG_ERROR_WARNING FDCAN_IR_EW
#define LL_FDCAN_FLAG_BUS_OFF FDCAN_IR_BO
#define LL_FDCAN_FLAG_RAM_WATCHDOG FDCAN_IR_WDI
#define LL_FDCAN_FLAG_ARB_PROTOCOL_ERROR FDCAN_IR_PEA
#define LL_FDCAN_FLAG_DATA_PROTOCOL_ERROR FDCAN_IR_PED
#define LL_FDCAN_FLAG_RESERVED_ADDRESS_ACCESS FDCAN_IR_ARA
#define LL_FDCAN_FLAG_TIMESTAMP_WRAPAROUND FDCAN_IR_TSW
#define LL_FDCAN_FLAG_TIMEOUT_OCCURRED FDCAN_IR_TOO
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_IT IT Defines
  * @{
  */
#define LL_FDCAN_IT_TX_COMPLETE FDCAN_IE_TCE
#define LL_FDCAN_IT_TX_ABORT_COMPLETE FDCAN_IE_TCFE
#define LL_FDCAN_IT_TX_FIFO_EMPTY FDCAN_IE_TFEE
#define LL_FDCAN_IT_RX_HIGH_PRIORITY_MSG FDCAN_IE_HPME
#define LL_FDCAN_IT_TX_EVT_FIFO_ELT_LOST FDCAN_IE_TEFLE
#define LL_FDCAN_IT_TX_EVT_FIFO_FULL FDCAN_IE_TEFFE
#define LL_FDCAN_IT_TX_EVT_FIFO_NEW_DATA FDCAN_IE_TEFNE
#define LL_FDCAN_IT_RX_FIFO0_MESSAGE_LOST FDCAN_IE_RF0LE
#define LL_FDCAN_IT_RX_FIFO0_FULL FDCAN_IE_RF0FE
#define LL_FDCAN_IT_RX_FIFO0_NEW_MESSAGE FDCAN_IE_RF0NE
#define LL_FDCAN_IT_RX_FIFO1_MESSAGE_LOST FDCAN_IE_RF1LE
#define LL_FDCAN_IT_RX_FIFO1_FULL FDCAN_IE_RF1FE
#define LL_FDCAN_IT_RX_FIFO1_NEW_MESSAGE FDCAN_IE_RF1NE
#define LL_FDCAN_IT_TIMESTAMP_WRAPAROUND FDCAN_IE_TSWE
#define LL_FDCAN_IT_RAM_ACCESS_FAILURE FDCAN_IE_MRAFE
#define LL_FDCAN_IT_TIMEOUT_OCCURRED FDCAN_IE_TOOE
#define LL_FDCAN_IT_ERROR_LOGGING_OVERFLOW FDCAN_IE_ELOE
#define LL_FDCAN_IT_ERROR_PASSIVE FDCAN_IE_EPE
#define LL_FDCAN_IT_ERROR_WARNING FDCAN_IE_EWE
#define LL_FDCAN_IT_BUS_OFF FDCAN_IE_BOE
#define LL_FDCAN_IT_RAM_WATCHDOG FDCAN_IE_WDIE
#define LL_FDCAN_IT_ARB_PROTOCOL_ERROR FDCAN_IE_PEAE
#define LL_FDCAN_IT_DATA_PROTOCOL_ERROR FDCAN_IE_PEDE
#define LL_FDCAN_IT_RESERVED_ADDRESS_ACCESS FDCAN_IE_ARAE
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_INTERRUPT_LINE Interrupt Lines
  * @{
  */
#define LL_FDCAN_INTERRUPT_LINE0 FDCAN_ILE_EINT0
#define LL_FDCAN_INTERRUPT_LINE1 FDCAN_ILE_EINT1
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_IT_GROUP Interrupt Groups
  * @{
  */
#define LL_FDCAN_IT_GROUP_RX_FIFO0 FDCAN_ILS_RXFIFO0
#define LL_FDCAN_IT_GROUP_RX_FIFO1 FDCAN_ILS_RXFIFO1
#define LL_FDCAN_IT_GROUP_STATUS_MESSAGE FDCAN_ILS_SMSG
#define LL_FDCAN_IT_GROUP_TX_FIFO_ERROR FDCAN_ILS_TFERR
#define LL_FDCAN_IT_GROUP_MISC FDCAN_ILS_MISC
#define LL_FDCAN_IT_GROUP_BIT_LINE_ERROR FDCAN_ILS_BERR
#define LL_FDCAN_IT_GROUP_PROTOCOL_ERROR FDCAN_ILS_PERR
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_FRAME_FORMAT Frame Format
  * @{
  */
#define LL_FDCAN_FRAME_CLASSIC (0x00000000UL)
#define LL_FDCAN_FRAME_FD_NO_BRS FDCAN_CCCR_FDOE
#define LL_FDCAN_FRAME_FD_BRS (FDCAN_CCCR_FDOE | FDCAN_CCCR_BRSE)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_MODE Operating Mode
  * @{
  */
#define LL_FDCAN_MODE_NORMAL (0x00000000UL)
#define LL_FDCAN_MODE_RESTRICTED_OPERATION (0x00000001UL)
#define LL_FDCAN_MODE_BUS_MONITORING (0x00000002UL)
#define LL_FDCAN_MODE_INTERNAL_LOOPBACK (0x00000003UL)
#define LL_FDCAN_MODE_EXTERNAL_LOOPBACK (0x00000004UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_CLOCK_DIVIDER Clock Divider
  * @{
  */
#define LL_FDCAN_CLOCK_DIV1 (0x00000000UL)
#define LL_FDCAN_CLOCK_DIV2 (0x00000001UL)
#define LL_FDCAN_CLOCK_DIV4 (0x00000002UL)
#define LL_FDCAN_CLOCK_DIV6 (0x00000003UL)
#define LL_FDCAN_CLOCK_DIV8 (0x00000004UL)
#define LL_FDCAN_CLOCK_DIV10 (0x00000005UL)
#define LL_FDCAN_CLOCK_DIV12 (0x00000006UL)
#define LL_FDCAN_CLOCK_DIV14 (0x00000007UL)
#define LL_FDCAN_CLOCK_DIV16 (0x00000008UL)
#define LL_FDCAN_CLOCK_DIV18 (0x00000009UL)
#define LL_FDCAN_CLOCK_DIV20 (0x0000000AUL)
#define LL_FDCAN_CLOCK_DIV22 (0x0000000BUL)
#define LL_FDCAN_CLOCK_DIV24 (0x0000000CUL)
#define LL_FDCAN_CLOCK_DIV26 (0x0000000DUL)
#define LL_FDCAN_CLOCK_DIV28 (0x0000000EUL)
#define LL_FDCAN_CLOCK_DIV30 (0x0000000FUL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_AUTO_RETRANSMISSION Auto Retransmission
  * @{
  */
#define LL_FDCAN_AUTO_RETRANSMISSION_ENABLE (0x00000000UL)
#define LL_FDCAN_AUTO_RETRANSMISSION_DISABLE FDCAN_CCCR_DAR
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_TRANSMIT_PAUSE Transmit Pause
  * @{
  */
#define LL_FDCAN_TRANSMIT_PAUSE_DISABLE (0x00000000UL)
#define LL_FDCAN_TRANSMIT_PAUSE_ENABLE FDCAN_CCCR_TXP
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_PROTOCOL_EXCEPTION Protocol Exception
  * @{
  */
#define LL_FDCAN_PROTOCOL_EXCEPTION_ENABLE (0x00000000UL)
#define LL_FDCAN_PROTOCOL_EXCEPTION_DISABLE FDCAN_CCCR_PXHD
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_TX_FIFO_QUEUE_MODE Tx FIFO/Queue Mode
  * @{
  */
#define LL_FDCAN_TX_FIFO_OPERATION (0x00000000UL)
#define LL_FDCAN_TX_QUEUE_OPERATION FDCAN_TXBC_TFQM
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_ID_TYPE Identifier Type
  * @{
  */
#define LL_FDCAN_STANDARD_ID (0x00000000UL)
#define LL_FDCAN_EXTENDED_ID (0x40000000UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_FRAME_TYPE Frame Type
  * @{
  */
#define LL_FDCAN_DATA_FRAME (0x00000000UL)
#define LL_FDCAN_REMOTE_FRAME (0x20000000UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_DATA_LENGTH Data Length Code
  * @{
  */
#define LL_FDCAN_DLC_BYTES_0 (0x00000000UL)
#define LL_FDCAN_DLC_BYTES_1 (0x00000001UL)
#define LL_FDCAN_DLC_BYTES_2 (0x00000002UL)
#define LL_FDCAN_DLC_BYTES_3 (0x00000003UL)
#define LL_FDCAN_DLC_BYTES_4 (0x00000004UL)
#define LL_FDCAN_DLC_BYTES_5 (0x00000005UL)
#define LL_FDCAN_DLC_BYTES_6 (0x00000006UL)
#define LL_FDCAN_DLC_BYTES_7 (0x00000007UL)
#define LL_FDCAN_DLC_BYTES_8 (0x00000008UL)
#define LL_FDCAN_DLC_BYTES_12 (0x00000009UL)
#define LL_FDCAN_DLC_BYTES_16 (0x0000000AUL)
#define LL_FDCAN_DLC_BYTES_20 (0x0000000BUL)
#define LL_FDCAN_DLC_BYTES_24 (0x0000000CUL)
#define LL_FDCAN_DLC_BYTES_32 (0x0000000DUL)
#define LL_FDCAN_DLC_BYTES_48 (0x0000000EUL)
#define LL_FDCAN_DLC_BYTES_64 (0x0000000FUL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_ERROR_STATE_INDICATOR Error State Indicator
  * @{
  */
#define LL_FDCAN_ESI_ACTIVE (0x00000000UL)
#define LL_FDCAN_ESI_PASSIVE (0x80000000UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_BIT_RATE_SWITCH Bit Rate Switching
  * @{
  */
#define LL_FDCAN_BRS_OFF (0x00000000UL)
#define LL_FDCAN_BRS_ON (0x00100000UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_FD_FORMAT FD Format
  * @{
  */
#define LL_FDCAN_CLASSIC_CAN (0x00000000UL)
#define LL_FDCAN_FD_CAN (0x00200000UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_TX_EVENT_FIFO_CONTROL Tx Event FIFO Control
  * @{
  */
#define LL_FDCAN_NO_TX_EVENTS (0x00000000UL)
#define LL_FDCAN_STORE_TX_EVENTS (0x00800000UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_FILTER_TYPE Filter Type
  * @{
  */
#define LL_FDCAN_FILTER_RANGE (0x00000000UL)
#define LL_FDCAN_FILTER_DUAL (0x00000001UL)
#define LL_FDCAN_FILTER_MASK (0x00000002UL)
#define LL_FDCAN_FILTER_RANGE_NO_EIDM (0x00000003UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_FILTER_CONFIG Filter Config
  * @{
  */
#define LL_FDCAN_FILTER_DISABLE (0x00000000UL)
#define LL_FDCAN_FILTER_TO_RXFIFO0 (0x00000001UL)
#define LL_FDCAN_FILTER_TO_RXFIFO1 (0x00000002UL)
#define LL_FDCAN_FILTER_REJECT (0x00000003UL)
#define LL_FDCAN_FILTER_HP (0x00000004UL)
#define LL_FDCAN_FILTER_TO_RXFIFO0_HP (0x00000005UL)
#define LL_FDCAN_FILTER_TO_RXFIFO1_HP (0x00000006UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_RX_FIFO Rx FIFO
  * @{
  */
#define LL_FDCAN_RX_FIFO0 (0x00000040UL)
#define LL_FDCAN_RX_FIFO1 (0x00000041UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_RX_FIFO_MODE Rx FIFO Mode
  * @{
  */
#define LL_FDCAN_RX_FIFO_BLOCKING (0x00000000UL)
#define LL_FDCAN_RX_FIFO_OVERWRITE (0x00000001UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_TIMESTAMP Timestamp
  * @{
  */
#define LL_FDCAN_TIMESTAMP_INTERNAL (0x00000001UL)
#define LL_FDCAN_TIMESTAMP_EXTERNAL (0x00000002UL)
#define LL_FDCAN_TIMESTAMP_PRESC_1 (0x00000000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_2 (0x00010000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_3 (0x00020000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_4 (0x00030000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_5 (0x00040000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_6 (0x00050000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_7 (0x00060000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_8 (0x00070000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_9 (0x00080000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_10 (0x00090000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_11 (0x000A0000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_12 (0x000B0000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_13 (0x000C0000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_14 (0x000D0000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_15 (0x000E0000UL)
#define LL_FDCAN_TIMESTAMP_PRESC_16 (0x000F0000UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_TIMEOUT Timeout
  * @{
  */
#define LL_FDCAN_TIMEOUT_CONTINUOUS (0x00000000UL)
#define LL_FDCAN_TIMEOUT_TX_EVENT_FIFO (0x00000002UL)
#define LL_FDCAN_TIMEOUT_RX_FIFO0 (0x00000004UL)
#define LL_FDCAN_TIMEOUT_RX_FIFO1 (0x00000006UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_PROTOCOL_STATUS Protocol Status
  * @{
  */
#define LL_FDCAN_PROTOCOL_ERROR_NONE (0x00000000UL)
#define LL_FDCAN_PROTOCOL_ERROR_STUFF (0x00000001UL)
#define LL_FDCAN_PROTOCOL_ERROR_FORM (0x00000002UL)
#define LL_FDCAN_PROTOCOL_ERROR_ACK (0x00000003UL)
#define LL_FDCAN_PROTOCOL_ERROR_BIT1 (0x00000004UL)
#define LL_FDCAN_PROTOCOL_ERROR_BIT0 (0x00000005UL)
#define LL_FDCAN_PROTOCOL_ERROR_CRC (0x00000006UL)
#define LL_FDCAN_PROTOCOL_ERROR_NO_CHANGE (0x00000007UL)
#define LL_FDCAN_COM_STATE_SYNC (0x00000000UL)
#define LL_FDCAN_COM_STATE_IDLE (0x00000008UL)
#define LL_FDCAN_COM_STATE_RX (0x00000010UL)
#define LL_FDCAN_COM_STATE_TX (0x00000018UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_HP_MESSAGE_STATUS High Priority Message Status
  * @{
  */
#define LL_FDCAN_HP_STORAGE_NO_FIFO (0x00000000UL)
#define LL_FDCAN_HP_STORAGE_MSG_LOST (0x00000040UL)
#define LL_FDCAN_HP_STORAGE_RXFIFO0 (0x00000080UL)
#define LL_FDCAN_HP_STORAGE_RXFIFO1 (0x000000C0UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_NON_MATCHING_FRAMES Non Matching Frames
  * @{
  */
#define LL_FDCAN_ACCEPT_IN_RX_FIFO0 (0x00000000UL)
#define LL_FDCAN_ACCEPT_IN_RX_FIFO1 (0x00000001UL)
#define LL_FDCAN_REJECT (0x00000002UL)
/**
  * @}
  */

/** @defgroup FDCAN_LL_EC_REJECT_REMOTE_FRAMES Reject Remote Frames
  * @{
  */
#define LL_FDCAN_FILTER_REMOTE (0x00000000UL)
#define LL_FDCAN_REJECT_REMOTE (0x00000001UL)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup FDCAN_LL_Exported_Macros FDCAN Exported Macros
  * @{
  */

/** @brief  Write a value in FDCAN register */
#define LL_FDCAN_WriteReg(__INSTANCE__, __REG__, __VALUE__) \
    WRITE_REG((__INSTANCE__)->__REG__, (__VALUE__))

/** @brief  Read a value in FDCAN register */
#define LL_FDCAN_ReadReg(__INSTANCE__, __REG__) READ_REG((__INSTANCE__)->__REG__)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup FDCAN_LL_Exported_Functions FDCAN Exported Functions
  * @{
  */

/** @defgroup FDCAN_LL_EF_Configuration Configuration
  * @{
  */

/**
  * @brief  Set the FDCAN clock divider.
  * @rmtoll CKDIV        PDIV          LL_FDCAN_SetClockDivider
  * @param  ClockDivider This parameter can be a value of @ref FDCAN_LL_EC_CLOCK_DIVIDER
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_SetClockDivider(uint32_t ClockDivider) {
    MODIFY_REG(FDCAN_CONFIG->CKDIV, FDCAN_CKDIV_PDIV, ClockDivider);
}

/**
  * @brief  Get the FDCAN clock divider.
  * @rmtoll CKDIV        PDIV          LL_FDCAN_GetClockDivider
  * @retval Returned value can be a value of @ref FDCAN_LL_EC_CLOCK_DIVIDER
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetClockDivider(void) {
    return (uint32_t)(READ_BIT(FDCAN_CONFIG->CKDIV, FDCAN_CKDIV_PDIV));
}

/**
  * @brief  Request initialization mode.
  * @rmtoll CCCR         INIT          LL_FDCAN_RequestInit
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_RequestInit(FDCAN_GlobalTypeDef* FDCANx) {
    SET_BIT(FDCANx->CCCR, FDCAN_CCCR_INIT);
}

/**
  * @brief  Request normal operation by leaving initialization mode.
  * @rmtoll CCCR         INIT          LL_FDCAN_RequestOperation
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_RequestOperation(FDCAN_GlobalTypeDef* FDCANx) {
    CLEAR_BIT(FDCANx->CCCR, FDCAN_CCCR_INIT);
}

/**
  * @brief  Check if initialization mode is active.
  * @rmtoll CCCR         INIT          LL_FDCAN_IsActiveFlag_INIT
  * @param  FDCANx FDCAN Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FDCAN_IsActiveFlag_INIT(const FDCAN_GlobalTypeDef* FDCANx) {
    return ((READ_BIT(FDCANx->CCCR, FDCAN_CCCR_INIT) == FDCAN_CCCR_INIT) ? 1UL : 0UL);
}

/**
  * @brief  Enable configuration change.
  * @rmtoll CCCR         CCE           LL_FDCAN_EnableConfigurationChange
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_EnableConfigurationChange(FDCAN_GlobalTypeDef* FDCANx) {
    SET_BIT(FDCANx->CCCR, FDCAN_CCCR_CCE);
}

/**
  * @brief  Request sleep mode.
  * @rmtoll CCCR         CSR           LL_FDCAN_RequestSleep
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_RequestSleep(FDCAN_GlobalTypeDef* FDCANx) {
    SET_BIT(FDCANx->CCCR, FDCAN_CCCR_CSR);
}

/**
  * @brief  Exit sleep mode.
  * @rmtoll CCCR         CSR           LL_FDCAN_ExitSleep
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_ExitSleep(FDCAN_GlobalTypeDef* FDCANx) {
    CLEAR_BIT(FDCANx->CCCR, FDCAN_CCCR_CSR);
}

/**
  * @brief  Check if sleep acknowledge flag is active.
  * @rmtoll CCCR         CSA           LL_FDCAN_IsActiveFlag_CSA
  * @param  FDCANx FDCAN Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FDCAN_IsActiveFlag_CSA(const FDCAN_GlobalTypeDef* FDCANx) {
    return ((READ_BIT(FDCANx->CCCR, FDCAN_CCCR_CSA) == FDCAN_CCCR_CSA) ? 1UL : 0UL);
}

/**
  * @brief  Set frame format.
  * @rmtoll CCCR         FDOE          LL_FDCAN_SetFrameFormat\n
  *         CCCR         BRSE          LL_FDCAN_SetFrameFormat
  * @param  FDCANx FDCAN Instance
  * @param  FrameFormat This parameter can be a value of @ref FDCAN_LL_EC_FRAME_FORMAT
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_SetFrameFormat(FDCAN_GlobalTypeDef* FDCANx, uint32_t FrameFormat) {
    MODIFY_REG(FDCANx->CCCR, FDCAN_CCCR_FDOE | FDCAN_CCCR_BRSE, FrameFormat);
}

/**
  * @brief  Get frame format.
  * @rmtoll CCCR         FDOE          LL_FDCAN_GetFrameFormat\n
  *         CCCR         BRSE          LL_FDCAN_GetFrameFormat
  * @param  FDCANx FDCAN Instance
  * @retval Returned value can be a value of @ref FDCAN_LL_EC_FRAME_FORMAT
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetFrameFormat(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->CCCR, FDCAN_CCCR_FDOE | FDCAN_CCCR_BRSE));
}

/**
  * @brief  Enable automatic retransmission.
  * @rmtoll CCCR         DAR           LL_FDCAN_EnableAutoRetransmission
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_EnableAutoRetransmission(FDCAN_GlobalTypeDef* FDCANx) {
    CLEAR_BIT(FDCANx->CCCR, FDCAN_CCCR_DAR);
}

/**
  * @brief  Disable automatic retransmission.
  * @rmtoll CCCR         DAR           LL_FDCAN_DisableAutoRetransmission
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_DisableAutoRetransmission(FDCAN_GlobalTypeDef* FDCANx) {
    SET_BIT(FDCANx->CCCR, FDCAN_CCCR_DAR);
}

/**
  * @brief  Enable transmit pause.
  * @rmtoll CCCR         TXP           LL_FDCAN_EnableTransmitPause
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_EnableTransmitPause(FDCAN_GlobalTypeDef* FDCANx) {
    SET_BIT(FDCANx->CCCR, FDCAN_CCCR_TXP);
}

/**
  * @brief  Disable transmit pause.
  * @rmtoll CCCR         TXP           LL_FDCAN_DisableTransmitPause
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_DisableTransmitPause(FDCAN_GlobalTypeDef* FDCANx) {
    CLEAR_BIT(FDCANx->CCCR, FDCAN_CCCR_TXP);
}

/**
  * @brief  Enable protocol exception handling.
  * @rmtoll CCCR         PXHD          LL_FDCAN_EnableProtocolException
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_EnableProtocolException(FDCAN_GlobalTypeDef* FDCANx) {
    CLEAR_BIT(FDCANx->CCCR, FDCAN_CCCR_PXHD);
}

/**
  * @brief  Disable protocol exception handling.
  * @rmtoll CCCR         PXHD          LL_FDCAN_DisableProtocolException
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_DisableProtocolException(FDCAN_GlobalTypeDef* FDCANx) {
    SET_BIT(FDCANx->CCCR, FDCAN_CCCR_PXHD);
}

/**
  * @brief  Set nominal bit timing.
  * @rmtoll NBTP         NSJW          LL_FDCAN_SetNominalBitTiming\n
  *         NBTP         NTSEG1        LL_FDCAN_SetNominalBitTiming\n
  *         NBTP         NTSEG2        LL_FDCAN_SetNominalBitTiming\n
  *         NBTP         NBRP          LL_FDCAN_SetNominalBitTiming
  * @param  FDCANx FDCAN Instance
  * @param  Prescaler Nominal prescaler, from 1 to 512.
  * @param  SyncJumpWidth Nominal sync jump width, from 1 to 128.
  * @param  TimeSeg1 Nominal time segment 1, from 1 to 256.
  * @param  TimeSeg2 Nominal time segment 2, from 1 to 128.
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_SetNominalBitTiming(
    FDCAN_GlobalTypeDef* FDCANx,
    uint32_t Prescaler,
    uint32_t SyncJumpWidth,
    uint32_t TimeSeg1,
    uint32_t TimeSeg2) {
    WRITE_REG(
        FDCANx->NBTP,
        (((SyncJumpWidth - 1UL) << FDCAN_NBTP_NSJW_Pos) |
         ((TimeSeg1 - 1UL) << FDCAN_NBTP_NTSEG1_Pos) |
         ((TimeSeg2 - 1UL) << FDCAN_NBTP_NTSEG2_Pos) |
         ((Prescaler - 1UL) << FDCAN_NBTP_NBRP_Pos)));
}

/**
  * @brief  Set data bit timing.
  * @rmtoll DBTP         DSJW          LL_FDCAN_SetDataBitTiming\n
  *         DBTP         DTSEG1        LL_FDCAN_SetDataBitTiming\n
  *         DBTP         DTSEG2        LL_FDCAN_SetDataBitTiming\n
  *         DBTP         DBRP          LL_FDCAN_SetDataBitTiming
  * @param  FDCANx FDCAN Instance
  * @param  Prescaler Data prescaler, from 1 to 32.
  * @param  SyncJumpWidth Data sync jump width, from 1 to 16.
  * @param  TimeSeg1 Data time segment 1, from 1 to 32.
  * @param  TimeSeg2 Data time segment 2, from 1 to 16.
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_SetDataBitTiming(
    FDCAN_GlobalTypeDef* FDCANx,
    uint32_t Prescaler,
    uint32_t SyncJumpWidth,
    uint32_t TimeSeg1,
    uint32_t TimeSeg2) {
    WRITE_REG(
        FDCANx->DBTP,
        (((SyncJumpWidth - 1UL) << FDCAN_DBTP_DSJW_Pos) |
         ((TimeSeg1 - 1UL) << FDCAN_DBTP_DTSEG1_Pos) |
         ((TimeSeg2 - 1UL) << FDCAN_DBTP_DTSEG2_Pos) |
         ((Prescaler - 1UL) << FDCAN_DBTP_DBRP_Pos)));
}

/**
  * @brief  Set Tx FIFO/Queue operation mode.
  * @rmtoll TXBC         TFQM          LL_FDCAN_SetTxFifoQueueMode
  * @param  FDCANx FDCAN Instance
  * @param  TxFifoQueueMode This parameter can be a value of @ref FDCAN_LL_EC_TX_FIFO_QUEUE_MODE
  * @retval None
  */
__STATIC_INLINE void
    LL_FDCAN_SetTxFifoQueueMode(FDCAN_GlobalTypeDef* FDCANx, uint32_t TxFifoQueueMode) {
    MODIFY_REG(FDCANx->TXBC, FDCAN_TXBC_TFQM, TxFifoQueueMode);
}

/**
  * @brief  Configure standard and extended filter list sizes.
  * @rmtoll RXGFC        LSS           LL_FDCAN_SetFilterListSize\n
  *         RXGFC        LSE           LL_FDCAN_SetFilterListSize
  * @param  FDCANx FDCAN Instance
  * @param  StdFiltersNbr Number of standard filters.
  * @param  ExtFiltersNbr Number of extended filters.
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_SetFilterListSize(
    FDCAN_GlobalTypeDef* FDCANx,
    uint32_t StdFiltersNbr,
    uint32_t ExtFiltersNbr) {
    MODIFY_REG(
        FDCANx->RXGFC,
        FDCAN_RXGFC_LSS | FDCAN_RXGFC_LSE,
        (StdFiltersNbr << FDCAN_RXGFC_LSS_Pos) | (ExtFiltersNbr << FDCAN_RXGFC_LSE_Pos));
}

/**
  * @brief  Configure global filtering.
  * @rmtoll RXGFC        ANFS          LL_FDCAN_ConfigGlobalFilter\n
  *         RXGFC        ANFE          LL_FDCAN_ConfigGlobalFilter\n
  *         RXGFC        RRFS          LL_FDCAN_ConfigGlobalFilter\n
  *         RXGFC        RRFE          LL_FDCAN_ConfigGlobalFilter
  * @param  FDCANx FDCAN Instance
  * @param  NonMatchingStd This parameter can be a value of @ref FDCAN_LL_EC_NON_MATCHING_FRAMES
  * @param  NonMatchingExt This parameter can be a value of @ref FDCAN_LL_EC_NON_MATCHING_FRAMES
  * @param  RejectRemoteStd This parameter can be a value of @ref FDCAN_LL_EC_REJECT_REMOTE_FRAMES
  * @param  RejectRemoteExt This parameter can be a value of @ref FDCAN_LL_EC_REJECT_REMOTE_FRAMES
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_ConfigGlobalFilter(
    FDCAN_GlobalTypeDef* FDCANx,
    uint32_t NonMatchingStd,
    uint32_t NonMatchingExt,
    uint32_t RejectRemoteStd,
    uint32_t RejectRemoteExt) {
    MODIFY_REG(
        FDCANx->RXGFC,
        FDCAN_RXGFC_ANFS | FDCAN_RXGFC_ANFE | FDCAN_RXGFC_RRFS | FDCAN_RXGFC_RRFE,
        (NonMatchingStd << FDCAN_RXGFC_ANFS_Pos) | (NonMatchingExt << FDCAN_RXGFC_ANFE_Pos) |
            (RejectRemoteStd << FDCAN_RXGFC_RRFS_Pos) | (RejectRemoteExt << FDCAN_RXGFC_RRFE_Pos));
}

/**
  * @brief  Set extended ID mask.
  * @rmtoll XIDAM        EIDM          LL_FDCAN_SetExtendedIdMask
  * @param  FDCANx FDCAN Instance
  * @param  Mask Extended ID mask.
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_SetExtendedIdMask(FDCAN_GlobalTypeDef* FDCANx, uint32_t Mask) {
    WRITE_REG(FDCANx->XIDAM, Mask);
}

/**
  * @brief  Configure Rx FIFO operation mode.
  * @rmtoll RXGFC        F0OM          LL_FDCAN_SetRxFifoMode\n
  *         RXGFC        F1OM          LL_FDCAN_SetRxFifoMode
  * @param  FDCANx FDCAN Instance
  * @param  RxFifo This parameter can be a value of @ref FDCAN_LL_EC_RX_FIFO
  * @param  OperationMode This parameter can be a value of @ref FDCAN_LL_EC_RX_FIFO_MODE
  * @retval None
  */
__STATIC_INLINE void
    LL_FDCAN_SetRxFifoMode(FDCAN_GlobalTypeDef* FDCANx, uint32_t RxFifo, uint32_t OperationMode) {
    if(RxFifo == LL_FDCAN_RX_FIFO0) {
        MODIFY_REG(FDCANx->RXGFC, FDCAN_RXGFC_F0OM, (OperationMode << FDCAN_RXGFC_F0OM_Pos));
    } else {
        MODIFY_REG(FDCANx->RXGFC, FDCAN_RXGFC_F1OM, (OperationMode << FDCAN_RXGFC_F1OM_Pos));
    }
}

/**
  * @brief  Configure RAM watchdog counter start value.
  * @rmtoll RWD          WDC           LL_FDCAN_SetRAMWatchdogCounter
  * @param  FDCANx FDCAN Instance
  * @param  CounterStartValue Start value from 0x00 to 0xFF. 0 disables the counter.
  * @retval None
  */
__STATIC_INLINE void
    LL_FDCAN_SetRAMWatchdogCounter(FDCAN_GlobalTypeDef* FDCANx, uint32_t CounterStartValue) {
    MODIFY_REG(FDCANx->RWD, FDCAN_RWD_WDC, CounterStartValue);
}

/**
  * @brief  Get RAM watchdog counter value.
  * @rmtoll RWD          WDV           LL_FDCAN_GetRAMWatchdogCounter
  * @param  FDCANx FDCAN Instance
  * @retval RAM watchdog counter value.
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetRAMWatchdogCounter(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->RWD, FDCAN_RWD_WDV) >> FDCAN_RWD_WDV_Pos);
}

/**
  * @brief  Configure timestamp counter prescaler.
  * @rmtoll TSCC         TCP           LL_FDCAN_SetTimestampPrescaler
  * @param  FDCANx FDCAN Instance
  * @param  TimestampPrescaler This parameter can be a value of @ref FDCAN_LL_EC_TIMESTAMP
  * @retval None
  */
__STATIC_INLINE void
    LL_FDCAN_SetTimestampPrescaler(FDCAN_GlobalTypeDef* FDCANx, uint32_t TimestampPrescaler) {
    MODIFY_REG(FDCANx->TSCC, FDCAN_TSCC_TCP, TimestampPrescaler);
}

/**
  * @brief  Enable timestamp counter.
  * @rmtoll TSCC         TSS           LL_FDCAN_EnableTimestamp
  * @param  FDCANx FDCAN Instance
  * @param  TimestampOperation This parameter can be a value of @ref FDCAN_LL_EC_TIMESTAMP
  * @retval None
  */
__STATIC_INLINE void
    LL_FDCAN_EnableTimestamp(FDCAN_GlobalTypeDef* FDCANx, uint32_t TimestampOperation) {
    MODIFY_REG(FDCANx->TSCC, FDCAN_TSCC_TSS, TimestampOperation);
}

/**
  * @brief  Disable timestamp counter.
  * @rmtoll TSCC         TSS           LL_FDCAN_DisableTimestamp
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_DisableTimestamp(FDCAN_GlobalTypeDef* FDCANx) {
    CLEAR_BIT(FDCANx->TSCC, FDCAN_TSCC_TSS);
}

/**
  * @brief  Get timestamp counter value.
  * @rmtoll TSCV         TSC           LL_FDCAN_GetTimestampCounter
  * @param  FDCANx FDCAN Instance
  * @retval Timestamp counter value.
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetTimestampCounter(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->TSCV, FDCAN_TSCV_TSC));
}

/**
  * @brief  Reset timestamp counter value.
  * @rmtoll TSCV         TSC           LL_FDCAN_ResetTimestampCounter
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_ResetTimestampCounter(FDCAN_GlobalTypeDef* FDCANx) {
    CLEAR_REG(FDCANx->TSCV);
}

/**
  * @brief  Configure timeout counter operation and period.
  * @rmtoll TOCC         TOS           LL_FDCAN_ConfigTimeoutCounter\n
  *         TOCC         TOP           LL_FDCAN_ConfigTimeoutCounter
  * @param  FDCANx FDCAN Instance
  * @param  TimeoutOperation This parameter can be a value of @ref FDCAN_LL_EC_TIMEOUT
  * @param  TimeoutPeriod Timeout period from 0x0000 to 0xFFFF.
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_ConfigTimeoutCounter(
    FDCAN_GlobalTypeDef* FDCANx,
    uint32_t TimeoutOperation,
    uint32_t TimeoutPeriod) {
    MODIFY_REG(
        FDCANx->TOCC,
        FDCAN_TOCC_TOS | FDCAN_TOCC_TOP,
        TimeoutOperation | (TimeoutPeriod << FDCAN_TOCC_TOP_Pos));
}

/**
  * @brief  Enable timeout counter.
  * @rmtoll TOCC         ETOC          LL_FDCAN_EnableTimeoutCounter
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_EnableTimeoutCounter(FDCAN_GlobalTypeDef* FDCANx) {
    SET_BIT(FDCANx->TOCC, FDCAN_TOCC_ETOC);
}

/**
  * @brief  Disable timeout counter.
  * @rmtoll TOCC         ETOC          LL_FDCAN_DisableTimeoutCounter
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_DisableTimeoutCounter(FDCAN_GlobalTypeDef* FDCANx) {
    CLEAR_BIT(FDCANx->TOCC, FDCAN_TOCC_ETOC);
}

/**
  * @brief  Get timeout counter value.
  * @rmtoll TOCV         TOC           LL_FDCAN_GetTimeoutCounter
  * @param  FDCANx FDCAN Instance
  * @retval Timeout counter value.
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetTimeoutCounter(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->TOCV, FDCAN_TOCV_TOC));
}

/**
  * @brief  Reset timeout counter value.
  * @rmtoll TOCV         TOC           LL_FDCAN_ResetTimeoutCounter
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_ResetTimeoutCounter(FDCAN_GlobalTypeDef* FDCANx) {
    CLEAR_REG(FDCANx->TOCV);
}

/**
  * @brief  Configure transmitter delay compensation.
  * @rmtoll TDCR         TDCF          LL_FDCAN_ConfigTxDelayCompensation\n
  *         TDCR         TDCO          LL_FDCAN_ConfigTxDelayCompensation
  * @param  FDCANx FDCAN Instance
  * @param  TdcOffset Transmitter delay compensation offset from 0x00 to 0x7F.
  * @param  TdcFilter Transmitter delay compensation filter from 0x00 to 0x7F.
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_ConfigTxDelayCompensation(
    FDCAN_GlobalTypeDef* FDCANx,
    uint32_t TdcOffset,
    uint32_t TdcFilter) {
    WRITE_REG(
        FDCANx->TDCR, (TdcFilter << FDCAN_TDCR_TDCF_Pos) | (TdcOffset << FDCAN_TDCR_TDCO_Pos));
}

/**
  * @brief  Enable transmitter delay compensation.
  * @rmtoll DBTP         TDC           LL_FDCAN_EnableTxDelayCompensation
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_EnableTxDelayCompensation(FDCAN_GlobalTypeDef* FDCANx) {
    SET_BIT(FDCANx->DBTP, FDCAN_DBTP_TDC);
}

/**
  * @brief  Disable transmitter delay compensation.
  * @rmtoll DBTP         TDC           LL_FDCAN_DisableTxDelayCompensation
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_DisableTxDelayCompensation(FDCAN_GlobalTypeDef* FDCANx) {
    CLEAR_BIT(FDCANx->DBTP, FDCAN_DBTP_TDC);
}

/**
  * @brief  Enable ISO 11898-1 protocol mode.
  * @rmtoll CCCR         NISO          LL_FDCAN_EnableISOMode
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_EnableISOMode(FDCAN_GlobalTypeDef* FDCANx) {
    CLEAR_BIT(FDCANx->CCCR, FDCAN_CCCR_NISO);
}

/**
  * @brief  Disable ISO 11898-1 protocol mode.
  * @rmtoll CCCR         NISO          LL_FDCAN_DisableISOMode
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_DisableISOMode(FDCAN_GlobalTypeDef* FDCANx) {
    SET_BIT(FDCANx->CCCR, FDCAN_CCCR_NISO);
}

/**
  * @brief  Enable edge filtering during bus integration.
  * @rmtoll CCCR         EFBI          LL_FDCAN_EnableEdgeFiltering
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_EnableEdgeFiltering(FDCAN_GlobalTypeDef* FDCANx) {
    SET_BIT(FDCANx->CCCR, FDCAN_CCCR_EFBI);
}

/**
  * @brief  Disable edge filtering during bus integration.
  * @rmtoll CCCR         EFBI          LL_FDCAN_DisableEdgeFiltering
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_DisableEdgeFiltering(FDCAN_GlobalTypeDef* FDCANx) {
    CLEAR_BIT(FDCANx->CCCR, FDCAN_CCCR_EFBI);
}

/**
  * @}
  */

/** @defgroup FDCAN_LL_EF_FLAG_Management FLAG Management
  * @{
  */

/**
  * @brief  Check if one or several flags are active.
  * @param  FDCANx FDCAN Instance
  * @param  Flags This parameter can be a combination of @ref FDCAN_LL_EC_GET_FLAG
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FDCAN_IsActiveFlag(const FDCAN_GlobalTypeDef* FDCANx, uint32_t Flags) {
    return ((READ_BIT(FDCANx->IR, Flags) == Flags) ? 1UL : 0UL);
}

/**
  * @brief  Clear one or several flags.
  * @param  FDCANx FDCAN Instance
  * @param  Flags This parameter can be a combination of @ref FDCAN_LL_EC_GET_FLAG
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_ClearFlag(FDCAN_GlobalTypeDef* FDCANx, uint32_t Flags) {
    WRITE_REG(FDCANx->IR, Flags);
}

/**
  * @}
  */

/** @defgroup FDCAN_LL_EF_IT_Management IT Management
  * @{
  */

/**
  * @brief  Enable one or several interrupts.
  * @param  FDCANx FDCAN Instance
  * @param  Interrupts This parameter can be a combination of @ref FDCAN_LL_EC_IT
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_EnableIT(FDCAN_GlobalTypeDef* FDCANx, uint32_t Interrupts) {
    SET_BIT(FDCANx->IE, Interrupts);
}

/**
  * @brief  Disable one or several interrupts.
  * @param  FDCANx FDCAN Instance
  * @param  Interrupts This parameter can be a combination of @ref FDCAN_LL_EC_IT
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_DisableIT(FDCAN_GlobalTypeDef* FDCANx, uint32_t Interrupts) {
    CLEAR_BIT(FDCANx->IE, Interrupts);
}

/**
  * @brief  Check if one or several interrupt sources are enabled.
  * @param  FDCANx FDCAN Instance
  * @param  Interrupts This parameter can be a combination of @ref FDCAN_LL_EC_IT
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t
    LL_FDCAN_IsEnabledIT(const FDCAN_GlobalTypeDef* FDCANx, uint32_t Interrupts) {
    return ((READ_BIT(FDCANx->IE, Interrupts) == Interrupts) ? 1UL : 0UL);
}

/**
  * @brief  Assign interrupt groups to interrupt line 0 or 1.
  * @param  FDCANx FDCAN Instance
  * @param  ITGroups This parameter can be a combination of @ref FDCAN_LL_EC_IT_GROUP
  * @param  InterruptLine This parameter can be a value of @ref FDCAN_LL_EC_INTERRUPT_LINE
  * @retval None
  */
__STATIC_INLINE void
    LL_FDCAN_SetITLine(FDCAN_GlobalTypeDef* FDCANx, uint32_t ITGroups, uint32_t InterruptLine) {
    if(InterruptLine == LL_FDCAN_INTERRUPT_LINE1) {
        SET_BIT(FDCANx->ILS, ITGroups);
    } else {
        CLEAR_BIT(FDCANx->ILS, ITGroups);
    }
}

/**
  * @brief  Enable interrupt line.
  * @param  FDCANx FDCAN Instance
  * @param  InterruptLine This parameter can be a value of @ref FDCAN_LL_EC_INTERRUPT_LINE
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_EnableITLine(FDCAN_GlobalTypeDef* FDCANx, uint32_t InterruptLine) {
    SET_BIT(FDCANx->ILE, InterruptLine);
}

/**
  * @brief  Disable interrupt line.
  * @param  FDCANx FDCAN Instance
  * @param  InterruptLine This parameter can be a value of @ref FDCAN_LL_EC_INTERRUPT_LINE
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_DisableITLine(FDCAN_GlobalTypeDef* FDCANx, uint32_t InterruptLine) {
    CLEAR_BIT(FDCANx->ILE, InterruptLine);
}

/**
  * @}
  */

/** @defgroup FDCAN_LL_EF_FIFO_Management FIFO Management
  * @{
  */

/**
  * @brief  Get Rx FIFO fill level.
  * @param  FDCANx FDCAN Instance
  * @param  RxFifo This parameter can be a value of @ref FDCAN_LL_EC_RX_FIFO
  * @retval Rx FIFO fill level.
  */
__STATIC_INLINE uint32_t
    LL_FDCAN_GetRxFifoFillLevel(const FDCAN_GlobalTypeDef* FDCANx, uint32_t RxFifo) {
    return (RxFifo == LL_FDCAN_RX_FIFO0) ? READ_BIT(FDCANx->RXF0S, FDCAN_RXF0S_F0FL) :
                                           READ_BIT(FDCANx->RXF1S, FDCAN_RXF1S_F1FL);
}

/**
  * @brief  Get Tx FIFO/Queue free level.
  * @param  FDCANx FDCAN Instance
  * @retval Tx FIFO/Queue free level.
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetTxFifoFreeLevel(const FDCAN_GlobalTypeDef* FDCANx) {
    return READ_BIT(FDCANx->TXFQS, FDCAN_TXFQS_TFFL);
}

/**
  * @brief  Check if Tx FIFO/Queue is full.
  * @param  FDCANx FDCAN Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FDCAN_IsActiveFlag_TxFifoFull(const FDCAN_GlobalTypeDef* FDCANx) {
    return ((READ_BIT(FDCANx->TXFQS, FDCAN_TXFQS_TFQF) == FDCAN_TXFQS_TFQF) ? 1UL : 0UL);
}

/**
  * @brief  Get Tx FIFO/Queue put index.
  * @param  FDCANx FDCAN Instance
  * @retval Tx FIFO/Queue put index.
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetTxFifoQueuePutIndex(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->TXFQS, FDCAN_TXFQS_TFQPI) >> FDCAN_TXFQS_TFQPI_Pos);
}

/**
  * @brief  Add Tx request.
  * @param  FDCANx FDCAN Instance
  * @param  BufferIndex Tx buffer bit index.
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_AddTxRequest(FDCAN_GlobalTypeDef* FDCANx, uint32_t BufferIndex) {
    WRITE_REG(FDCANx->TXBAR, BufferIndex);
}

/**
  * @brief  Add Tx cancellation request.
  * @param  FDCANx FDCAN Instance
  * @param  BufferIndexes Tx buffer bit indexes.
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_AbortTxRequest(FDCAN_GlobalTypeDef* FDCANx, uint32_t BufferIndexes) {
    WRITE_REG(FDCANx->TXBCR, BufferIndexes);
}

/**
  * @brief  Check if a transmission request is pending on selected Tx buffer indexes.
  * @param  FDCANx FDCAN Instance
  * @param  BufferIndexes Tx buffer bit indexes.
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t
    LL_FDCAN_IsTxBufferMessagePending(const FDCAN_GlobalTypeDef* FDCANx, uint32_t BufferIndexes) {
    return ((READ_BIT(FDCANx->TXBRP, BufferIndexes) != 0UL) ? 1UL : 0UL);
}

/**
  * @brief  Check if Restricted Operation Mode is active.
  * @param  FDCANx FDCAN Instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t LL_FDCAN_IsRestrictedOperationMode(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->CCCR, FDCAN_CCCR_ASM) >> FDCAN_CCCR_ASM_Pos);
}

/**
  * @brief  Exit Restricted Operation Mode.
  * @param  FDCANx FDCAN Instance
  * @retval None
  */
__STATIC_INLINE void LL_FDCAN_ExitRestrictedOperationMode(FDCAN_GlobalTypeDef* FDCANx) {
    CLEAR_BIT(FDCANx->CCCR, FDCAN_CCCR_ASM);
}

/**
  * @}
  */

/** @defgroup FDCAN_LL_EF_Status Status Management
  * @{
  */

/**
  * @brief  Get high priority message storage indicator.
  * @param  FDCANx FDCAN Instance
  * @retval Returned value can be a value of @ref FDCAN_LL_EC_HP_MESSAGE_STATUS
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetHighPriorityMessageStorage(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->HPMS, FDCAN_HPMS_MSI));
}

/**
  * @brief  Get high priority message filter index.
  * @param  FDCANx FDCAN Instance
  * @retval Filter index.
  */
__STATIC_INLINE uint32_t
    LL_FDCAN_GetHighPriorityMessageFilterIndex(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->HPMS, FDCAN_HPMS_FIDX) >> FDCAN_HPMS_FIDX_Pos);
}

/**
  * @brief  Get high priority message index.
  * @param  FDCANx FDCAN Instance
  * @retval Message index.
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetHighPriorityMessageIndex(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->HPMS, FDCAN_HPMS_BIDX));
}

/**
  * @brief  Get last error code.
  * @param  FDCANx FDCAN Instance
  * @retval Returned value can be a value of @ref FDCAN_LL_EC_PROTOCOL_STATUS
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetLastErrorCode(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->PSR, FDCAN_PSR_LEC));
}

/**
  * @brief  Get data phase last error code.
  * @param  FDCANx FDCAN Instance
  * @retval Returned value can be a value of @ref FDCAN_LL_EC_PROTOCOL_STATUS
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetDataLastErrorCode(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->PSR, FDCAN_PSR_DLEC) >> FDCAN_PSR_DLEC_Pos);
}

/**
  * @brief  Get communication activity.
  * @param  FDCANx FDCAN Instance
  * @retval Returned value can be a value of @ref FDCAN_LL_EC_PROTOCOL_STATUS
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetActivity(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->PSR, FDCAN_PSR_ACT));
}

/**
  * @brief  Get transmitter delay compensation value.
  * @param  FDCANx FDCAN Instance
  * @retval TDC value.
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetTxDelayCompensationValue(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->PSR, FDCAN_PSR_TDCV) >> FDCAN_PSR_TDCV_Pos);
}

/**
  * @brief  Get Tx error counter.
  * @param  FDCANx FDCAN Instance
  * @retval Tx error counter.
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetTxErrorCounter(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->ECR, FDCAN_ECR_TEC) >> FDCAN_ECR_TEC_Pos);
}

/**
  * @brief  Get Rx error counter.
  * @param  FDCANx FDCAN Instance
  * @retval Rx error counter.
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetRxErrorCounter(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->ECR, FDCAN_ECR_REC) >> FDCAN_ECR_REC_Pos);
}

/**
  * @brief  Get error logging counter.
  * @param  FDCANx FDCAN Instance
  * @retval Error logging counter.
  */
__STATIC_INLINE uint32_t LL_FDCAN_GetErrorLoggingCounter(const FDCAN_GlobalTypeDef* FDCANx) {
    return (uint32_t)(READ_BIT(FDCANx->ECR, FDCAN_ECR_CEL) >> FDCAN_ECR_CEL_Pos);
}

/**
  * @}
  */

#if defined(USE_FULL_LL_DRIVER)
/** @defgroup FDCAN_LL_EF_Init Initialization and de-initialization functions
  * @{
  */
ErrorStatus LL_FDCAN_DeInit(const FDCAN_GlobalTypeDef* FDCANx);
ErrorStatus LL_FDCAN_Init(
    FDCAN_GlobalTypeDef* FDCANx,
    const LL_FDCAN_InitTypeDef* FDCAN_InitStruct,
    LL_FDCAN_MessageRAMTypeDef* MessageRAM);
void LL_FDCAN_StructInit(LL_FDCAN_InitTypeDef* FDCAN_InitStruct);
void LL_FDCAN_MessageRAMStructInit(LL_FDCAN_MessageRAMTypeDef* MessageRAM);
/**
  * @}
  */

/** @defgroup FDCAN_LL_EF_Message_RAM Message RAM functions
  * @{
  */
void LL_FDCAN_ConfigMessageRAM(
    FDCAN_GlobalTypeDef* FDCANx,
    uint32_t StdFiltersNbr,
    uint32_t ExtFiltersNbr,
    LL_FDCAN_MessageRAMTypeDef* MessageRAM);
void LL_FDCAN_FlushMessageRAM(void);
ErrorStatus LL_FDCAN_ConfigFilter(
    const LL_FDCAN_MessageRAMTypeDef* MessageRAM,
    const LL_FDCAN_FilterTypeDef* FilterConfig);
ErrorStatus LL_FDCAN_AddMessageToTxFifoQ(
    FDCAN_GlobalTypeDef* FDCANx,
    const LL_FDCAN_MessageRAMTypeDef* MessageRAM,
    const LL_FDCAN_TxHeaderTypeDef* TxHeader,
    const uint8_t* TxData,
    uint32_t* TxBufferIndex);
ErrorStatus LL_FDCAN_GetRxMessage(
    FDCAN_GlobalTypeDef* FDCANx,
    const LL_FDCAN_MessageRAMTypeDef* MessageRAM,
    uint32_t RxFifo,
    LL_FDCAN_RxHeaderTypeDef* RxHeader,
    uint8_t* RxData);
uint32_t LL_FDCAN_DLCToBytes(uint32_t DataLength);
/**
  * @}
  */
#endif /* USE_FULL_LL_DRIVER */

/**
  * @}
  */

/**
  * @}
  */

#endif /* defined(FDCAN1) */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32U5xx_LL_FDCAN_H */
