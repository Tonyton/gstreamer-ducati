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
 *  @file   ivp6vdec.h
 *
 *  @brief  This file provides definitions for the interface structures
 *  @author: Prashanth
 *
 *  @version 0.0 (March 2008) : Base version
 *  @version 0.1 (July 2009)  : IVIDDEC3 changes[Vikas]
 *  @version 0.1 (Dec 2009)   : Coding Guidelines[Vikas]
********************************************************************************
*/
#ifndef _IVP6VDEC_
#define _IVP6VDEC_


/****************************************************************************
*   INCLUDE FILES
*****************************************************************************/
/* -------------------- system and platform files ------------------------- */
/* ------------------------- program files -------------------------------- */
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividdec3.h>
#include <ti/xdais/ires.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp2.h>



/****************************************************************************
*   EXTERNAL REFERENCES NOTE : only use if not found in header file
*****************************************************************************/
/* ------------------------ data declarations ----------------------------- */
/* ----------------------- function prototypes ---------------------------- */

/****************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*****************************************************************************/

/* ---------------------------- macros ------------------------------------ */

/* Extending control method commands                                        */

/**
 * The Macro indicates the Get Status Command Enum for the Control API
*/
#define Ivp6VDEC_GETSTATUS              XDM_GETSTATUS

/**
 * The Macro indicates the SET PARAMS Command Enum for the Control API
*/
#define Ivp6VDEC_SETPARAMS              XDM_SETPARAMS

/**
 * The Macro indicates the XDM RESET Command Enum for the Control API
*/
#define Ivp6VDEC_RESET                  XDM_RESET

/**
 * The Macro indicates the XDM FLUSH Command Enum for the Control API
*/
#define Ivp6VDEC_FLUSH                  XDM_FLUSH

/**
 * The Macro indicates the SET DEFUALT Command Enum for the Control API
*/
#define Ivp6VDEC_SETDEFAULT             XDM_SETDEFAULT

/**
 * The Macro indicates the Get BUFINFO Command Enum for the Control API
*/
#define Ivp6VDEC_GETBUFINFO             XDM_GETBUFINFO

/**
* The Macro indicates the Get context info Command Enum for the Control API
*/
#define Ivp6VDEC_GETCONTEXTINFO         XDM_GETCONTEXTINFO

/**
* The Macro indicates the Get dynamaic params Command Enum for the Control API
*/
#define Ivp6VDEC_GETDYNPARAMSDEFAULT    XDM_GETDYNPARAMSDEFAULT

/**
* The Macro indicates the Get VERSION Command Enum for the Control API
*/
#define Ivp6VDEC_XDM_GETVERSION         XDM_GETVERSION
/**
 * The Macro indicates the Late Acquire Arguement provided by Application.
*/
#define Ivp6VDEC_SETLATEACQUIREARG     XDM_SETLATEACQUIREARG
/**
* This macro is valid only in case of Ivf bitstreams & tells to decode Ivf
* header which appears once at beginning of bitstream
*/
#define IVP6VDEC_DECODE_IVF_HEADER 256

/* ----------------------- data declarations ------------------------------ */


/**
********************************************************************************
 *  @struct  Ivp6VDEC_Obj
 *
 *  @brief   This structure must be the first field of all vp6VDEC instance
 *           objects
 *
 *  @param  fxns
 *          Handle to extented vp6 video decoder library interface functions
********************************************************************************
 */
typedef struct Ivp6VDEC_Obj
{
    struct Ivp6VDEC_Fxns *fxns;
} Ivp6VDEC_Obj;

/**
 *******************************************************************************
 *  @struct   Ivp6VDEC_Handle
 *
 *  @brief   This handle is used to reference all vp6VDEC instance objects
 *
 *  @see    None
 *******************************************************************************
 */
typedef struct Ivp6VDEC_Obj *Ivp6VDEC_Handle;


/**
 *******************************************************************************
 *  @enum     Ivp6VDEC_ExtendedCommonErrorCodes
 *
 *  @brief    Enumeration for which returns common Error Codes Detected by the
 *            Decoder & updates in outArgs.
 *
 *******************************************************************************
*/
typedef enum
{
    /* Common Error Code if Create Params are wrong                         */
    IVP6DEC_ERR_UNSUPPORTED_VIDDEC3PARAMS = 0,
    /* Common Error Code if Dynamic Params are wrong                        */
    IVP6DEC_ERR_UNSUPPORTED_VIDDEC3DYNAMICPARAMS,
    /* Common Error Code if VP6 extended Params are wrong in Control Call   */
    IVP6DEC_ERR_UNSUPPORTED_VP6DECDYNAMICPARAMS,
    /* Common Error Code if Data Sync Params are wrong                      */
    IVP6DEC_ERR_IMPROPER_DATASYNC_SETTING,
    /* Common Error Code if there is no slice present                       */
    IVP6DEC_ERR_NOSLICE,
    /* Common Error Code if there no slice header present                   */
    IVP6DEC_ERR_SLICEHDR,
    /* Common Error Code if Error is detected in MB Data Decoding           */
    IVP6DEC_ERR_MBDATA,
    /* Common Error Code if unsupported Feature Decoding                    */
    IVP6DEC_ERR_UNSUPPFEATURE,
    /* Common Error Code if unexpected input Bytes Ends                     */
    IVP6DEC_ERR_STREAM_END = 16,
    /* Common Error Code if Codecs detects unsupported Resolution Detected  */
    IVP6DEC_ERR_UNSUPPRESOLUTION,
    /* Common Error Code if IVAHD is not in Standby Mode                    */
    IVP6DEC_ERR_STANDBY,
    /* Common Error Code if mailbox interrupt request recieved for wrong
       message                                                              */
    IVP6DEC_ERR_INVALID_MBOX_MESSAGE,
    /* Common Error Code if Hdvicp Reset Done is not proper                 */
    IVP6DEC_ERR_HDVICP_RESET,
    /* Common Error Code if Hdvicp Wait exits early                         */
    IVP6DEC_ERR_HDVICP_WAIT_NOT_CLEAN_EXIT,
    /* Common Error Code if Decoder is not initialized                      */
    IVP6DEC_ERR_DECODER_INSTANCE_NOT_INITIALIZED,
    /* Common Error Code if Error Flush occurs                              */
    IVP6DEC_ERR_DECODER_XDM_FLUSH,
    /* Common error code if resolution changes                              */
    IVP6DEC_ERR_PICSIZECHANGE
}Ivp6VDEC_ExtendedCommonErrorCodes;


/**
 *******************************************************************************
 *  @enum     Ivp6VDEC_ErrorStatus
 *
 *  @brief    Enumeration for which returns Extended Error Codes Detected by the
 *            Decoder & updates in extended parameters of the Status Structure.
 *
 *******************************************************************************
*/
typedef enum
{
    /* extended Error Code if Create Params size is wrong                   */
    IVP6DEC_ERR_DYNAMIC_PARAMS_SIZE = 0,
    /* extended Error Code if Status Params size is wrong                   */
    IVP6DEC_ERR_STATUS_PARAMS_SIZE,
    /* extended Error Code if Decoded Header is wrong                       */
    IVP6DEC_ERR_DECODE_HEADER,
    /* extended Error Code if display width is wrong                        */
    IVP6DEC_ERR_DISPLAY_WIDTH,
    /* extended Error Code if skip Mode is wrong                            */
    IVP6DEC_ERR_FRAME_SKIP_MODE,
    /* extended Error Code if new frame flag is wrong                       */
    IVP6DEC_ERR_NEW_FRAME_FLAG,
    /* extended Error Code if late Acquire Arg Param is wrong               */
    IVP6DEC_ERR_LATE_ACQUIRE_ARG,
    /* extended Error Code if input Params is null                          */
    IVP6DEC_ERR_PROCESS_INPUT_PARAMS_NULL_POINTER,
    /* extended Error Code if input Params size is wrong                    */
    IVP6DEC_ERR_PROCESS_INPUT_PARAMS_SIZE,
    /* extended Error Code if invalid Bytes are present                     */
    IVP6DEC_ERR_INVALID_ID_OR_INAVLID_BYTES,
    /* extended Error Code if decoder is not initializzed                   */
    IVP6DEC_ERR_DECODER_NOT_INITIALIZED,
    /* extended Error Code if invalid input buffer or Bytes are present     */
    IVP6DEC_ERR_INVALID_INPUTBUF_OR_BYTES_NUMBUFS,
    /* extended Error Code if excess input buffers are provided             */
    IVP6DEC_ERR_EXCESS_NUM_OF_INPUT_BUFFERS,
    /* extended Error Code if invalid memory type                           */
    IVP6DEC_ERR_INVALID_INPUT_BUFFER_MEMTYPE,
    /* extended Error Code for error in out Args                            */
    IVP6DEC_ERR_OUTARGS_BUF_STRUCURE,
    /* extended Error Code for wrong bytes of output buffers                */
    IVP6DEC_ERR_INVALID_OUTPUT_BUFFERS_BYTES,
    /* extended Error Code for wrong bytes of output buffers for raw memory */
    IVP6DEC_ERR_INVALID_OUTPUT_BUFFERS_RAW_MEM_BYTES,
    /* extended Error Code for invalid number of output buffers             */
    IVP6DEC_ERR_INVALID_NUM_OF_OUTPUT_BUFFERS,
    /* extended Error Code wrong output buffer type                         */
    IVP6DEC_ERR_INVALID_OUTPUT_BUFFERS_MEMTYPE,
    /* extended Error Code for invalid dimensions of output tiled memory    */
    IVP6DEC_ERR_INVALID_OUTPUT_BUFFERS_TILED_WIDTH_OR_HEIGHT,
    /* extended Error Code wrong memory compatibilty in successive frames   */
    IVP6DEC_ERR_INVALID_MEMORY_TYPE_COMPATIBILITY,
    /* extended Error Code for excess byte consumption                      */
    IVP6DEC_ERR_EXCESS_BYTE_CONSUMPTION,
    /* extended Error Code if first frame is non Key frame                  */
    IVP6DEC_ERR_FIRST_FRAME_IS_NON_KEY_FRAME,
    /* extended Error Code for unsupported input width                      */
    IVP6DEC_ERR_UNSUPPORTED_WIDTH,
    /* extended Error Code for unsupported input height                     */
    IVP6DEC_ERR_UNSUPPORTED_HEIGHT,
    /* extended Error Code for invalid partition length                     */
    IVP6DEC_ERR_INVALID_PARTITION_LENGTH,
    /* extended Error Code for wrong version in bitstream                   */
    IVP6DEC_ERR_WRONG_VERSION_ERROR,
    /* extended Error Code for wrong profile in bitstream                   */
    IVP6DEC_ERR_WRONG_PROFILE_ERROR,
    /* extended Error Code for unsupported scaling width                    */
    IVP6DEC_ERR_UNSUPPORTED_SCALED_WIDTH_ERROR,
    /* extended Error Code for unsupported scaling height                   */
    IVP6DEC_ERR_UNSUPPORTED_SCALED_HEIGHT_ERROR,
    /* extended Error Code if there are no buffers to flush out             */
    IVP6DEC_ERR_NO_BUFFERS_TO_BE_FREED,
    /* extended Error Code if buffer size is in sufficient to return the
    version of the codec          */
    IVP6DEC_ERR_GETVERSION,
    /* extended Error Code if output buffers are unaligned                  */
    IVP6DEC_ERR_ADDRESS_NOT_ALIGN128,
    /* Huffman error                                                        */
    IVP6DEC_ERR_HUFFMAN

}Ivp6VDEC_ErrorStatus;



/**
********************************************************************************
 *  @struct   Ivp6VDEC_Status
 *
 *  @brief   Status structure defines the parameters that can be changed or
 *          read during real-time operation of the alogrithm.
 *
 *  @param  viddecStatus
 *          Handle to base class status struture which defines the all
 *          run time parameters.
********************************************************************************
 */
typedef struct Ivp6VDEC_Status
{
    /* must be followed for all video decoders   */
    IVIDDEC3_Status  viddecStatus;
    /* Extended Error Code0 returned by decoder  */
    XDAS_UInt32 extendedErrorCode0;
    /* Extended Error Code1 returned by decoder  */
    XDAS_UInt32 extendedErrorCode1;
    /* Extended Error Code2 returned by decoder  */
    XDAS_UInt32 extendedErrorCode2;
    /* Extended Error Code3 returned by decoder  */
    XDAS_UInt32 extendedErrorCode3;
    /*To enable Debug trace level                */
    XDAS_UInt32   debugTraceLevel;
    /*To set the last N frames to log            */
    XDAS_UInt32   lastNFramesToLog;
    /*Address in External memory of the debug trace info    */
    XDAS_UInt32 * extMemoryDebugTraceAddr;
    /*Size of the debug trace info                */
    XDAS_UInt32   extMemoryDebugTraceSize;


} Ivp6VDEC_Status;



/**
********************************************************************************
 *  @struct   Ivp6VDEC_Cmd
 *
 *  @brief   The Cmd enumeration defines the control commands for the VP6
 *          video decoder control method.
********************************************************************************
 */
typedef IVIDDEC3_Cmd Ivp6VDEC_Cmd;



/**
********************************************************************************
 *  @struct   IVP6VDEC_Params
 *
 *  @brief   This structure defines the creation parameters for all
 *          vp6VDEC objects
 *
 *  @param  viddecParams
 *          Defines the creation time parameters for
 *          all IVIDDEC1 instance objects.
********************************************************************************
 */
typedef struct Ivp6VDEC_Params
{
    /* must be followed for all video decoders                                */
    IVIDDEC3_Params    viddecParams;

    /* ivfFormat                                                              */
    XDAS_UInt32        ivfFormat;

    /* debugTraceLevel                                                        */
    XDAS_UInt32   debugTraceLevel;

    /* lastNFramesToLog                                                       */
    XDAS_UInt32   lastNFramesToLog;

    /* This parameter tells the codec if payload header is present            */
    XDAS_UInt32           payloadHeaderPresent;

    /* Need to Add more variables in future, if required                      */

} Ivp6VDEC_Params;



/**
********************************************************************************
 *  @struct   Ivp6VDEC_DynamicParams
 *
 *  @brief   This structure defines the run time parameters for all
 *          vp6VDEC objects
 *
 *  @param  viddecDynamicParams
 *          Defines the ru time parameters for
 *          all IVIDDEC1 instance objects.
********************************************************************************
 */
typedef struct Ivp6VDEC_DynamicParams
{
    /* must be followed for all video decoders                                */
    IVIDDEC3_DynamicParams viddecDynamicParams;

    /* Need to Add more variables in future, if required                      */

} Ivp6VDEC_DynamicParams;



/**
********************************************************************************
 *  @struct   Ivp6VDEC_InArgs
 *
 *  @brief   This structure defines the run time input arguments for all VIDDEC
 *          objects.This structure may be extended by individual codec
 *          implementation allowing customization with vendor specific
 *          parameters.
 *
 *  @param  viddecInArgs
 *          Defines the input arguments for all IVIDDEC1 instance
 *          process function.
********************************************************************************
 */
typedef struct Ivp6VDEC_InArgs
{
    /* must be followed for all video decoders                                */
    IVIDDEC3_InArgs   viddecInArgs;

    /* Need to Add more variables in future, if required                      */

}Ivp6VDEC_InArgs;



/**
********************************************************************************
 *  @struct   Ivp6VDEC_OutArgs
 *
 *  @brief   This structure defines the run time output arguments for VIDDEC
 *          objects.This structure may be extended by individual codec
 *          implementation allowing customization with vendor specific
 *          parameters.
 *
 *  @param  viddecOutArgs
 *          Defines the output arguments for all IVIDDEC1 instance
 *          process function.
********************************************************************************
 */
typedef struct Ivp6VDEC_OutArgs
{
    /*must be followed for all video decoders*/
    IVIDDEC3_OutArgs  viddecOutArgs;

    /* Need to Add more variables in future, if required                      */

}Ivp6VDEC_OutArgs;



/**
********************************************************************************
 *  @struct   Ivp6VDEC_Fxns
 *
 *  @brief   This structure defines all of the operations on vp6VDEC objects.
 *
 *  @param  ividdec
 *          handle to the all function of the operations on IVIDDEC1 objects
********************************************************************************
 */
typedef struct Ivp6VDEC_Fxns
{
   /* Ivp6VDEC extends IVIDDEC object.Should be second set of functions       */
   IVIDDEC3_Fxns    ividdec;

   /* Need to Add more variables in future, if required                       */

} Ivp6VDEC_Fxns;


#endif  /* _IVP6VDEC_ */
