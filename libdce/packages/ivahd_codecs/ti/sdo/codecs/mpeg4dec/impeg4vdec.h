/* ====================================================================
 *   Copyright (C) 2010 Texas Instruments Incorporated
 *
 *   All rights reserved. Property of Texas Instruments Incorporated.
 *   Restricted rights to use, duplicate or disclose this code are
 *   granted through contract.
 *
 *   The program may not be used without the written permission
 *   of Texas Instruments Incorporated or against the terms and conditions
 *   stipulated in the agreement under which this program has been
 *   supplied.
 * ==================================================================== */
/**
********************************************************************************
* @file <impeg4vdec.h>
*
* @brief This file provides definisions for the interface handles.
*
* @author: Ashish Singh   (ashish.singh@ti.com)
*
* @version 0.0 (June 2009) : Base version created [Ashish]
*
* @version 0.1 (Apr 2010) : Review Comments Added [Ananya]
*
* @version 0.2 (oct 2010) : cleared doxygen warning and fixed VOP non coded
*                           related bugs.
*
* @version 0.3 (Nov 2010) : Modified the error bit 20.
*
* @version 0.4 (Dec 2010) : Removed the sorenson support and compile time
*                           parameter _DEBUGTRACE. [Nitesh]
*
*******************************************************************************
*/
#ifndef _IMPEG4VDEC_H_
#define _IMPEG4VDEC_H_


/****************************************************************************
*   INCLUDE FILES
*****************************************************************************/
/* -------------------- system and platform files ------------------------- */
/* ------------------------- program files -------------------------------- */

#include <ti/xdais/xdas.h>
#include <ti/xdais/dm/ividdec3.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp2.h>
#include <ti/xdais/ialg.h>


/****************************************************************************
*   EXTERNAL REFERENCES NOTE : only use if not found in header file
*****************************************************************************/
/* ------------------------ data declarations ----------------------------- */
/* ----------------------- function prototypes ---------------------------- */

/****************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*****************************************************************************/
/* ----------------------- data declarations ------------------------------ */

#define TILER_PITCH (16*1024)
#define VERSION_BUFSIZE 60
#define CONST_OFFSET              10
#define IMPEG4DEC_VERSION_LENGTH  60
#define SYNTAX_NOT_PRESENT -1
extern IRES_Fxns MPEG4VDEC_TI_IRES;

typedef enum
{
  FRAME_FLUSH_DISABLE = 0,
  FRAME_FLUSH_ENABLE
}eFrameFlushstate;


/**
*  Default value of buffer ID
*/
#define RESET_BUFFER_ID 0

typedef enum
{
  BFRAME_COLOCATED_MBDATA_DISABLE = 0,
  BFRAME_COLOCATED_MBDATA_ENABLE
}eColocatedMBdata;


typedef enum
{
  DEBLOCK_DISABLE = 0,
  DEBLOCK_ENABLE
}eFrameDeblock;


typedef enum
{
  EC_DISABLE = 0,
  EC_ENABLE
}eFrameErrorConcealment;

/**
*******************************************************************************
*  @struct   IMPEG4VDEC_Obj
*
*  @brief   This structure must be the first field of all mp4VDEC instance
*           objects
*
*  @param  fxns
*          Handle to extented mpeg4 video decoder library interface functions
*
*  @note    None
********************************************************************************
*/
typedef struct IMPEG4VDEC_Obj
{
  struct IMPEG4VDEC_Fxns *fxns;
} IMPEG4VDEC_Obj;

/**
*******************************************************************************
*  @struct   IMPEG4VDEC_Handle
*
*  @brief  This handle is used to reference all mp4VDEC instance objects
*
*  @note    None
********************************************************************************
*/
typedef struct IMPEG4VDEC_Obj *IMPEG4VDEC_Handle;

/**
*******************************************************************************
*  @struct   IMPEG4VDEC_Status
*
*  @brief  Status structure defines the parameters that can be changed or
*          read during real-time operation of the alogrithm.
*
*  @param  viddec3Status
*          Handle to base class status struture which defines the all
*          run time parameters.
*
*  @note    None
********************************************************************************
*/
typedef struct IMPEG4VDEC_Status
{
  IVIDDEC3_Status  viddec3Status;

  XDAS_UInt32   debugTraceLevel;
  XDAS_UInt32   lastNFramesToLog;
  XDAS_UInt32 * extMemoryDebugTraceAddr;
  XDAS_UInt32   extMemoryDebugTraceSize;

} IMPEG4VDEC_Status;

/**
*******************************************************************************
*  @struct  IMPEG4VDEC_Cmd
*
*  @brief  The Cmd enumeration defines the control commands for the MPEG4
*          video decoder control method.
*
*  @note    None
********************************************************************************
*/
typedef IVIDDEC3_Cmd IMPEG4VDEC_Cmd;

/**
*******************************************************************************
*  @struct  IMPEG4VDEC_Params
*
*  @brief  This structure defines the creation parameters for all
*          mp4VDEC objects
*
*  @param  viddecParams
*          Defines the creation time parameters for
*          all IVIDDEC3 instance objects.
*
*  @param  outloopDeBlocking
*          Flag for Optional deBlock filter ON
*
*  @param  ErrorConcealmentON
*          Flag for Optional Error Concealment ON
*
*  @param  sorensonSparkStream
*          Flag reserved for future usage for sorenson spark stream
*
*  @note    None
********************************************************************************
*/
typedef struct IMPEG4VDEC_Params
{
  IVIDDEC3_Params    viddec3Params;
  XDAS_Int32         outloopDeBlocking;
  XDAS_Int32         ErrorConcealmentON;
  XDAS_Int32         sorensonSparkStream;
  XDAS_UInt32        debugTraceLevel;
  XDAS_UInt32        lastNFramesToLog;
} IMPEG4VDEC_Params;

extern IMPEG4VDEC_Params IMPEG4VDEC_PARAMS;

/**
*******************************************************************************
*  @struct   IMPEG4VDEC_DynamicParams
*
*  @brief  This structure defines the run time parameters for all
*          mp4VDEC objects
*
*  @param  viddecDynamicParams
*          Defines the ru time parameters for
*          all IVIDDEC3 instance objects.
*
*  @param  outloopDeblocking
*          This variable will be updated by client for each process call
*          for enabling or disabling Outloop de-blocking.
*
*  @param  outloopDeRinging
*          This variable will be updated by client for each process call
*          for enabling or disabling Outloop de-ringing.
*
*  @see    None
********************************************************************************
*/
typedef struct IMPEG4VDEC_DynamicParams
{
  IVIDDEC3_DynamicParams viddec3DynamicParams;
} IMPEG4VDEC_DynamicParams;

extern IMPEG4VDEC_DynamicParams IMPEG4VDEC_TI_DYNAMICPARAMS;
/**
*******************************************************************************
*  @struct   IMPEG4VDEC_InArgs
*
*  @brief  This structure defines the run time input arguments for all VIDDEC
*          objects.This structure may be extended by individual codec
*          implementation allowing customization with vendor specific
*          parameters.
*
*  @param  viddec3InArgs
*          Defines the input arguments for all IVIDDEC3 instance
*          process function.
*
*  @see    None
********************************************************************************
*/
typedef struct IMPEG4VDEC_InArgs
{
  IVIDDEC3_InArgs   viddec3InArgs;

}IMPEG4VDEC_InArgs;

/**
*******************************************************************************
*  @struct  IMPEG4VDEC_OutArgs
*
*  @brief  This structure defines the run time output arguments for VIDDEC
*          objects.This structure may be extended by individual codec
*          implementation allowing customization with vendor specific
*          parameters.
*
*  @param  viddec3OutArgs
*          Defines the output arguments for all IVIDDEC3 instance
*          process function.
*
*  @note   None
********************************************************************************
*/
typedef struct IMPEG4VDEC_OutArgs
{
  IVIDDEC3_OutArgs  viddec3OutArgs;
  XDAS_Int32 vopTimeIncrementResolution;
  XDAS_Int32 vopTimeIncrement;
  XDAS_Int32  mp4ClosedGov;
  XDAS_Int32  mp4BrokenLink;
}IMPEG4VDEC_OutArgs;

/**
*******************************************************************************
*  @enum   IMPEG4VDEC_ErrorBit
*
*  @brief      Mpeg4 Error Codes: Delaration of mpeg4 decoder specific Error
*              Codes.
*  @details    Error status is communicated through a 32 bit word. In this,
*              Error Bits 8 to 15 are used to indicate the XDM error bits. See
*              XDM_ErrorBit definition in xdm.h. Other bits in a 32 bit word
*              can be used to signal any codec specific errors. The staructure
*              below enumerates the mpeg4 decoder specific error bits used.
*              The algorithm can set multiple bits to 1 depending on the error
*              condition
*
********************************************************************************
*/
typedef enum
{
  MPEG4D_ERR_VOS = 0,
  /**<
* Bit 0
*  1 - No Video Object Sequence detected in the frame
*  0 - Ignore
*/

  MPEG4D_ERR_VO,
  /**<
* Bit 1
*  1 - Incorrect Video Object type
*  0 - Ignore
*/

  MPEG4D_ERR_VOL,
  /**<
* Bit 2
*  1 - Error in Video Object Layer detected
*  0 - Ignore
*/

  MPEG4D_ERR_GOV,
  /**<
* Bit 3
*  1 - Error in Group of Video parsing
*  0 - Ignore
*/

  MPEG4D_ERR_VOP,
  /**<
* Bit 4
*  1 - Error in Video Object Plane parsing
*  0 - Ignore
*/

  MPEG4D_ERR_SHORTHEADER,
  /**<
* Bit 5
*  1 - Error in short header parsing
*  0 - Ignore
*/

  MPEG4D_ERR_GOB,
  /**<
* Bit 6
*  1 - Error in GOB parsing
*  0 - Ignore
*/

  MPEG4D_ERR_VIDEOPACKET,
  /**<
* Bit 7
*  1 - Error in Video Packet parsing
*  0 - Ignore
*/

  MPEG4D_ERR_MBDATA = 16 ,
  /**<
* Bit 16
*  1 -  Error in MB data parsing
*  0 - Ignore
*/

  MPEG4D_ERR_INVALIDPARAM_IGNORE,
  /**<
* Bit 17
*  1 -  Invalid Parameter
*  0 - Ignore
*/

  MPEG4D_ERR_UNSUPPFEATURE,
  /**<
* Bit 18
*  1 -  Unsupported feature
*  0 - Ignore
*/

  MPEG4D_ERR_STREAM_END,
  /**<
* Bit 19
*  1 - End of stream reached
*  0 - Ignore
*/

  MPEG4D_ERR_MPEG4VOL_H263VOP_HEADER_NOT_FOUND,
  /**<
* Bit 20
*  1 - Vaild header not found.
*  0 - Ignore
*/

  MPEGD_ERR_UNSUPPRESOLUTION,
  /**<
* Bit 21
*  1 - Unsupported resolution by the decoder
*  0 - Ignore
*/

  MPEG4D_ERR_BITSBUF_UNDERFLOW,
  /**<
* Bit 22
*  1 - The stream buffer has underflowed
*  0 - Ignore
*/

  MPEG4D_ERR_INVALID_MBOX_MESSAGE,
  /**<
* Bit 23
*  1 - Invalid (unexpected) mail boX message recieved by IVAHD
*  0 - Ignore
*/
  MPEG4D_ERR_NO_FRAME_FOR_FLUSH,
  /**<
* Bit 24
*  1 -  Codec does not have any frame for flushing out to application
*  0 - Ignore
*/
  MPEG4D_ERR_VOP_NOT_CODED,
  /**<
* Bit 25
*  1 -  Given vop is not codec
*  0 - Ignore
*/
  MPEG4D_ERR_START_CODE_NOT_PRESENT,
  /**<
* Bit 26
*  1 -  Start code for given stream is not present in case of Parse Header
*       Mode
*  0 - Ignore
*/
  MPEGD_ERR_VOP_TIME_INCREMENT_RES_ZERO
  /**<
* Bit 27
*  1 - Unsupported resolution by the decoder
*  0 - Ignore
*/
} IMPEG4VDEC_ErrorBit;

/**
******************************************************************************
*  @enum       IMPEGVDEC_MetadataType
*  @brief      This enum indicates Meta Data types for MPEG4 ASP Decoder
*
*  @remarks    The way to get meta data from decoder is via outBufs of the
*              decoder during  process call.
******************************************************************************
*/

typedef enum
{
  IMPEGVDEC_PARSED_MB_INFO_DATA = XDM_CUSTOMENUMBASE,
  IMPEGVDEC_PARSED_MB_ERROR_INFO_DATA,
  IMPEGVDEC_PARSED_ALFA_DATA
} IMPEGVDEC_MetadataType;

/***************************************************************************/

/**
*******************************************************************************
*  @enum    IRESResourcesHost
*  @brief   This enum contains the fileds for IRES memory resources
*  @remarks  this enum explain the type of memory required by mpeg4 ASP decoder
*
*******************************************************************************
*/

typedef enum
{
  IRES_HDVICP_RESOURCE_START          = 0 ,
  IRES_HDVICP_RESOURCE_IVAHD_0        = IRES_HDVICP_RESOURCE_START        ,
  IRES_HDVICP_RESOURCE_MAX                                                ,

  IRES_TILED_MEMORY_1D_RESOURCE_START      = IRES_HDVICP_RESOURCE_MAX     ,
  IRES_TILED_MEMORY_1D_RESOURCE_COL_MBINFO =
  IRES_TILED_MEMORY_1D_RESOURCE_START,
  IRES_TILED_MEMORY_1D_RESOURCE_PERSISTENT_MEM                            ,
  IRES_TILED_MEMORY_1D_RESOURCE_MAX                                       ,

  IRES_TILED_MEMORY_2D_RESOURCE_START    =
  IRES_TILED_MEMORY_1D_RESOURCE_MAX ,
  IRES_TILED_MEMORY_2D_RESOURCE_LUMA_0   =
  IRES_TILED_MEMORY_2D_RESOURCE_START ,
  IRES_TILED_MEMORY_2D_RESOURCE_CHROMA_0                                  ,
  IRES_TILED_MEMORY_2D_RESOURCE_LUMA_1                                    ,
  IRES_TILED_MEMORY_2D_RESOURCE_CHROMA_1                                  ,
  IRES_TILED_MEMORY_2D_RESOURCE_LUMA_2                                    ,
  IRES_TILED_MEMORY_2D_RESOURCE_CHROMA_2                                  ,
  IRES_TILED_MEMORY_2D_RESOURCE_MAX                                       ,

  IRES_HDVICP_RES            = IRES_HDVICP_RESOURCE_MAX
  - IRES_HDVICP_RESOURCE_START,
  IRES_TILED_MEMORY_2D_RES   = IRES_TILED_MEMORY_2D_RESOURCE_MAX
  - IRES_TILED_MEMORY_2D_RESOURCE_START,
  IRES_TILED_MEMORY_1D_RES   = IRES_TILED_MEMORY_1D_RESOURCE_MAX
  - IRES_TILED_MEMORY_1D_RESOURCE_START,
  IRES_TOTAL_RESOURCES       = IRES_TILED_MEMORY_2D_RESOURCE_MAX
}IRESResourcesHost;

/**
*******************************************************************************
*  @enum    _MemDescription
*  @brief   MemDescription of  IVAHD MPEG4 ASP Decoder implementation by TI.
*
* @remarks  this enum explain the type of memory required by mpeg4 ASP decoder
*
*******************************************************************************
*/

typedef enum _MemDescription
{
  OBJECT,
  /**
* this memory type is allocated by alg_alloc call & this is allocated
* for handle of decoder
*/
  /*HDR_DATA,*/
  /**
* this memory type is allocated by IRES & this is allocated for HDR Data
*/
  COLOC_PMBDATA,

  /**
* Number of MemTab required if no-Deblock and no-B colocated MB info
* required
*/

  COLOC_BMBDATA ,
  /**
* this memory type is allocated by IRES & this is for storing the colocated
* MB data for B Frame
*/

  DEBUGTRACESTRUCT,
  /**<
* Memtab for debug trace parameter storage
*/

  /*  ERRORCONCEAL_BUFF,*/
  /**<
* Memtab for storing the MB error infor passed to EC library
*/

  NUM_MEMTABS_DEBLOCK_OFF,
  /**
* Number of MemTab required if Deblock is Off required
*/

  LUMARECON_FRAME_BUFFDATA0 = NUM_MEMTABS_DEBLOCK_OFF,
  /**
* this memory type is allocated by IRES & this is for storing the decoded
* Luma data for Recon Frame used in case of Deblock Enable
*/
  LUMARECON_FRAME_BUFFDATA1,
  /**
* this memory type is allocated by IRES & this is for storing the decoded
* Luma data for Recon Frame used in case of Deblock Enable
*/
  LUMARECON_FRAME_BUFFDATA2,
  /**
* this memory type is allocated by IRES & this is for storing the decoded
* Luma data for Recon Frame used in case of Deblock Enable
*/
  CHROMARECON_FRAME_BUFFDATA0,
  /**
* this memory type is allocated by IRES & this is for storing the decoded
* Chroma data for Recon Frame used in case of Deblock Enable
*/
  CHROMARECON_FRAME_BUFFDATA1,
  /**
* this memory type is allocated by IRES & this is for storing the decoded
* Chroma data for Recon Frame used in case of Deblock Enable
*/
  CHROMARECON_FRAME_BUFFDATA2,
  /**
* this memory type is allocated by IRES & this is for storing the decoded
* Chroma data for Recon Frame used in case of Deblock Enable
*/

  NUM_MEMTABS_DEBLOCK_ON,
  /**
* Number of memtab required if deblock is on and it will be  maximum
* resource required by codec
*/
  MAX_NUM_MEMTABS = NUM_MEMTABS_DEBLOCK_ON
  /**
* Maximum number of memtab required
*/
}MemDescription;

/*
*  Number of 1D resource required by codec from IRES
*/
#define NUM_OF_1D_OBJECTS     0x3
/*
*  Number of 2D resource required by codec from IRES when filtering is off
*/
#define NUM_OF_MIN_2D_OBJECTS 0x0
/*
*  Number of 2D resource required by codec from IRES when filtering is on
*/
#define NUM_OF_MAX_2D_OBJECTS 0x6

/**
*******************************************************************************
*  @struct   IMPEG4VDEC_Fxns
*
*  @brief  This structure defines all of the operations on mp4VDEC objects.
*
*  @param  ividdec3
*          handle to the all function of the operations on IVIDDEC3 objects
*
*  @see    None
********************************************************************************
*/
typedef struct IMPEG4VDEC_Fxns
{
  IVIDDEC3_Fxns    ividdec3;
} IMPEG4VDEC_Fxns;

#endif /*_IMPEG4VDEC_H_*/











