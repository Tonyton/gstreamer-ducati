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
 * @file  ivp7vdec.h
 *
 * @brief This file provides definisions for the interface handles.
 *
********************************************************************************
*/
#ifndef __IVP7VDEC__
#define __IVP7VDEC__


/*******************************************************************************
*   INCLUDE FILES
*******************************************************************************/
/*--------------------- system and platform files ----------------------------*/
#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividdec3.h>
#include <ti/xdais/ires.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp2.h>

/*******************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*------------------------ data declarations ---------------------------------*/

/**
 * The Macro indicates the number of Hrdware Resources required by the Algorithm
 * to run?
*/
#define NUM_RESOURCES               2

/**
 *******************************************************************************
 *  @struct Ivp7VDEC_Obj
 *  @brief  This structure must be the first field of all vp7VDEC instance
 *          objects.
 *
 *  @param  fxns : Parameter containing the Min Value of Bool Decoding.
 *          Handle to extented vp7 video decoder library interface functions
 *
 *******************************************************************************
*/
typedef struct Ivp7VDEC_Obj
{
    struct Ivp7VDEC_Fxns *fxns;
} Ivp7VDEC_Obj;




/**
 *******************************************************************************
 *  @struct Ivp7VDEC_Handle
 *  @brief  This handle is used to reference all vp7VDEC instance objects
 *
 *******************************************************************************
*/
typedef struct Ivp7VDEC_Obj *Ivp7VDEC_Handle;

/**
 *******************************************************************************
 *  @enum     Ivp7VDEC_ExtendedCommonErrorCodes
 *
 *  @brief    Enumeration for which returns common Error Codes Detected by the
 *            Decoder & updates in outArgs.
 *
 *******************************************************************************
*/
typedef enum
{
    /* Common Error Code if Create Params are wrong                         */
    IVP7DEC_ERR_UNSUPPORTED_VIDDEC3PARAMS = 0,
    /* Common Error Code if Dynamic Params are wrong                        */
    IVP7DEC_ERR_UNSUPPORTED_VIDDEC3DYNAMICPARAMS,
    /* Common Error Code if Dynamic Params are wrong in Control Call        */
    IVP7DEC_ERR_UNSUPPORTED_VP7DECDYNAMICPARAMS,
    /* Common Error Code if Data Sync Params are wrong                      */
    IVP7DEC_ERR_IMPROPER_DATASYNC_SETTING,
    /* Common Error Code if there is no slice present                       */
    IVP7DEC_ERR_NOSLICE,
    /* Common Error Code if there no slice header present                   */
    IVP7DEC_ERR_SLICEHDR,
    /* Common Error Code if Error is detected in MB Data Decoding           */
    IVP7DEC_ERR_MBDATA,
    /* Common Error Code if unsupported Feature Decoding                    */
    IVP7DEC_ERR_UNSUPPFEATURE,
    /* Common Error Code if unexpected input Bytes Ends                     */
    IVP7DEC_ERR_STREAM_END = 16,
    /* Common Error Code if Codecs detects unsupported Resolution Detected  */
    IVP7DEC_ERR_UNSUPPRESOLUTION,
    /* Common Error Code if IVAHD is not in Standby Mode                    */
    IVP7DEC_ERR_STANDBY,
    /* Common Error Code if mailbox interrupt request recieved for wrong
       message                                                              */
    IVP7DEC_ERR_INVALID_MBOX_MESSAGE,
    /* Common Error Code if Hdvicp Reset Done is not proper                 */
    IVP7DEC_ERR_HDVICP_RESET,
    /* Common Error Code if Hdvicp Wait exits early                         */
    IVP7DEC_ERR_HDVICP_WAIT_NOT_CLEAN_EXIT,
    /* Common Error Code if Decoder is not initialized                      */
    IVP7DEC_ERR_DECODER_INSTANCE_NOT_INITIALIZED,
    /* Common Error Code if Error Flush occurs                              */
    IVP7DEC_ERR_DECODER_FLUSH ,
    /* Common Error Code if Change in resolution detected                   */
    IVP7DEC_ERR_PICSIZECHANGE
}Ivp7VDEC_ExtendedCommonErrorCodes;




/**
 *******************************************************************************
 *  @enum     Ivp7VDEC_ErrorStatus
 *
 *  @brief    Enumeration for which returns Extended Error Codes Detected by the
 *            Decoder & updates in extended parameters of the Status Structure.
 *
 *******************************************************************************
*/
typedef enum
{
    /* extended Error Code if Create Params size is wrong                   */
    IVP7DEC_ERR_DYNAMIC_PARAMS_SIZE = 0,
    /* extended Error Code if Status Params size is wrong                   */
    IVP7DEC_ERR_STATUS_PARAMS_SIZE,
    /* extended Error Code if Decoded Header is wrong                       */
    IVP7DEC_ERR_DECODE_HEADER,
    /* extended Error Code if display width is wrong                        */
    IVP7DEC_ERR_DISPLAY_WIDTH,
    /* extended Error Code if skip Mode is wrong                            */
    IVP7DEC_ERR_FRAME_SKIP_MODE,
    /* extended Error Code if new frame flag is wrong                       */
    IVP7DEC_NEW_FRAME_FLAG,
    /* extended Error Code if late Acquire Arg Param is wrong               */
    IVP7DEC_ERR_LATE_ACQUIRE_ARG,
    /* extended Error Code buffers provided in Get Version command is wrong */
    IVP7DEC_ERR_GETVERSION,
    /* extended Error Code if the arguements to the Process Call are NULL   */
    IVP7DEC_ERR_PROCESS_PARAMS_NULL_POINTER,
    /* extended Error Code if process call Params sizes are wrong           */
    IVP7DEC_ERR_PROCESS_PARAMS_SIZE,
    /* extended Error Code if invalid Bytes are present                     */
    IVP7DEC_ERR_INVALID_ID_OR_INVALID_BYTES,
    /* extended Error Code if invalid Bytes are present in flush mode       */
    IVP7DEC_ERR_INVALID_INPUT_BYTES_IN_FLUSH_MODE,
    /* extended Error Code if there are no buffers to flush out             */
    IVP7DEC_ERR_NO_BUFFERS_TO_FLUSH_OUT,
    /* extended Error Code if decoder is not initializzed                   */
    IVP7DEC_ERR_DECODER_NOT_INITIALIZED,
    /* extended Error Code if invalid input buffer or Bytes are present     */
    IVP7DEC_ERR_INVALID_INPUTBUF_OR_BYTES,
    /* extended Error Code if excess input buffers are provided             */
    IVP7DEC_ERR_EXCESS_NUM_OF_INPUT_BUFFERS,
    /* extended Error Code if invalid memory type                           */
    IVP7DEC_ERR_INVALID_INPUT_BUFFER_MEMTYPE,
    /* extended Error Code for error in out Args                            */
    IVP7DEC_ERR_OUTARGS_BUF_STRUCURE,
    /* extended Error Code if invalid output buffers are provided           */
    IVP7DEC_ERR_INVALID_OUTPUT_BUFFERS,
    /* extended Error Code if invalid bytes are provided for output buffers */
    IVP7DEC_ERR_INVALID_OUTPUT_BUFFER_NUMBYTES,
    /* extended Error Code for invalid number of output buffers             */
    IVP7DEC_ERR_INVALID_NUM_OF_OUTPUT_BUFFERS,
    /* extended Error Code wrong output buffer type                         */
    IVP7DEC_ERR_INVALID_OUTPUT_BUFFERS_MEMTYPE,
    /* extended Error Code for invalid dimensions of output tiled memory    */
    IVP7DEC_ERR_INVALID_OUTPUT_BUFFERS_TILED_WIDTH_OR_HEIGHT,
    /* extended Error Code wrong memory compatibilty in successive frames   */
    IVP7DEC_ERR_INVALID_MEMORY_TYPE_COMPATIBILITY,
    /* extended Error Code for wrong frame size                             */
    IVP7DEC_ERR_INVALID_FRAME_SIZE,
    /* extended Error Code wrong output buffers alignement                  */
    IVP7DEC_ERR_INVALID_OUTPUT_BUFFERS_ALIGNMENT,
    /* extended Error Code if first frame is non Key frame                  */
    IVP7DEC_ERR_FIRST_FRAME_IS_NON_KEY_FRAME,
    /* extended Error Code for unsupported input width                      */
    IVP7DEC_ERR_UNSUPPORTED_WIDTH,
    /* extended Error Code for unsupported input height                     */
    IVP7DEC_ERR_UNSUPPORTED_HEIGHT,
    /* extended Error Code for invalid partition length                     */
    IVP7DEC_ERR_INVALID_PARTITION_LENGTH,
    /* extended Error Code for unsupported prediction pitch                 */
    IVP7DEC_ERR_UNSUPPORTED_PREDICTION_PITCH,
    /* extended Error Code for unsupported destination pitch                */
    IVP7DEC_ERR_UNSUPPORTED_DESTINATION_PITCH,
    /* extended Error Code for fading of non reference frame                */
    IVP7DEC_ERR_FADED_REFERENCE_FRAME,
    /* extended Error Code fading Alpha Parameter                           */
    IVP7DEC_ERR_FADING_ALPHA_NOT_SUPPORTED,
    /* extended Error Code fading Beta Parameter                            */
    IVP7DEC_ERR_FADING_BETA_NOT_SUPPORTED,
    /* extended Error Code decoder consumes excess bytes than provided      */
    IVP7DEC_ERR_EXCESS_BYTE_CONSUMPTION,
    /* extended Error Code for unsupported scaling width                    */
    IVP7DEC_ERR_UNSUPPORTED_SCALE_WIDTH,
    /* extended Error Code for unsupported scaling height                   */
    IVP7DEC_ERR_UNSUPPORTED_SCALE_HEIGHT,
    /* extended Error Code if non reference frame exists in VP7.0           */
    IVP7DEC_ERR_WRONG_PROFILE_NON_REFERENCE,
    /* extended Error Code if Golden Frame comes as non Reference           */
    IVP7DEC_ERR_GF_NON_REFERENCE
}Ivp7VDEC_ErrorStatus;

/**
 *******************************************************************************
 *  @struct Ivp7VDEC_Status
 *  @brief  Status structure defines the parameters that can be changed or
 *          read during real-time operation of the alogrithm.
 *
 *  @param  viddecStatus :
 *          Handle to base class status struture which defines the all run time
 *          parameters
 *
 *  @param  extendedErrorCode0 :
 *          Extended Error Code 0 [Bits 0 - 31] returned by decoder
 *
 *  @param  extendedErrorCode1 :
 *          Extended Error Code 1 [Bits 32 - 63] returned by decoder
 *
 *  @param  extendedErrorCode2 :
 *          Extended Error Code 2 [Bits 64 - 95] returned by decoder
 *
 *  @param  extendedErrorCode3 :
 *          Extended Error Code 3 [Bits 96 - 127] returned by decoder
 *
 *******************************************************************************
*/
typedef struct Ivp7VDEC_Status
{
    /* must be followed for all video decoders                    */
    IVIDDEC3_Status  viddecStatus;
    /* Extended Error Code0 returned by decoder                   */
    XDAS_UInt32 extendedErrorCode0;
    /* Extended Error Code1 returned by decoder                   */
    XDAS_UInt32 extendedErrorCode1;
    /* Extended Error Code2 returned by decoder                   */
    XDAS_UInt32 extendedErrorCode2;
    /* Extended Error Code3 returned by decoder                   */
    XDAS_UInt32 extendedErrorCode3;
    /* Debug trace level configured for the decoder               */
    XDAS_UInt32 debugTraceLevel;
    /* Number of frames for which history information is
    * maintained by the codec                                     */
    XDAS_UInt32 lastNFramesToLog;
    /* External memory address (as seen by M3) where debug trace information
     * is being dumped – last memory buffer requested by the codec */
    XDAS_UInt32 *extMemoryDebugTraceAddr;
    /* External memory buffer size (in bytes) where debug trace information
    * is being dumped - the size of last memory buffer            */
    XDAS_UInt32 extMemoryDebugTraceSize;
} Ivp7VDEC_Status;




/**
 *******************************************************************************
 *  @struct Ivp7VDEC_Cmd
 *  @brief  The Cmd enumeration defines the control commands for the VP7
 *          video decoder control method.
 *
 *******************************************************************************
*/
typedef IVIDDEC3_Cmd Ivp7VDEC_Cmd;




/**
 *******************************************************************************
 *  @struct Ivp7VDEC_Params
 *  @brief  This structure defines the creation parameters for all
 *          vp7VDEC objects.
 *
 *  @param  viddecParams :
 *          Defines the creation time parameters for
 *          all IVIDDEC3 instance objects.
 *
 *  @param  ivfFormat :
 *          It defines the VP7 Bit Stream format provded by the Applicatio.
 *
 *  @param  debugTraceLevel :
 *          This Parameter Enables the different Levels of Debug Trace Dump
 *          Info.
 *
 *  @param  lastNFramesToLog :
 *          This Parameter tells the number of Last Frames Debug Trace Dump
 *          Info.
 *
 *******************************************************************************
*/
typedef struct Ivp7VDEC_Params
{
    /* must be followed for all video decoders */
    IVIDDEC3_Params    viddecParams;

    /* This Parameter indicates whether the Input Stream is of IVF format?  */
    XDAS_UInt32        ivfFormat;
    /* This Parameter Enables the different Levels of Debug Trace Dump Info */
    XDAS_UInt32        debugTraceLevel;
    /* This Parameter tells the number of Last Frames Debug Trace Dump Info */
    XDAS_UInt32        lastNFramesToLog;
    /* This parameter tells the codec if payload header is present */
    XDAS_UInt32           payloadHeaderPresent;
    /* Add more  */

} Ivp7VDEC_Params;




/**
 *******************************************************************************
 *  @struct Ivp7VDEC_DynamicParams
 *  @brief  This structure defines the run time parameters for all
 *          vp7VDEC objects.
 *
 *  @param  viddecParams :
 *          Defines the ru time parameters for
 *          all IVIDDEC3 instance objects.
 *
 *******************************************************************************
*/
typedef struct Ivp7VDEC_DynamicParams
{
     /* must be followed for all video encoders */
    IVIDDEC3_DynamicParams viddecDynamicParams;
    /* Add more  */

} Ivp7VDEC_DynamicParams;




/**
 *******************************************************************************
 *  @struct Ivp7VDEC_InArgs
 *  @brief   This structure defines the run time input arguments for all VIDDEC
 *           objects.This structure may be extended by individual codec
 *           implementation allowing customization with vendor specific
 *           parameters.
 *
 *  @param  viddecInArgs
 *          Defines the input arguments for all IVIDDEC1 instance
 *          process function.
 *
 *******************************************************************************
*/
typedef struct Ivp7VDEC_InArgs
{
    /* must be followed for all video decoders */
    IVIDDEC3_InArgs   viddecInArgs;
    /* Add more  */

}Ivp7VDEC_InArgs;




/**
 *******************************************************************************
 *  @struct Ivp7VDEC_OutArgs
 *  @brief  This structure defines the run time output arguments for VIDDEC
 *          objects.This structure may be extended by individual codec
 *          implementation allowing customization with vendor specific
 *          parameters.
 *
 *  @param  viddecInArgs
 *          Defines the output arguments for all IVIDDEC1 instance
 *          process function.
 *
 *******************************************************************************
*/
typedef struct Ivp7VDEC_OutArgs
{
    /* must be followed for all video decoders */
    IVIDDEC3_OutArgs  viddecOutArgs;
    /* Add more  */

}Ivp7VDEC_OutArgs;




/**
 *******************************************************************************
 *  @struct Ivp7VDEC_Fxns
 *  @brief  This structure defines all of the operations on vp7VDEC objects
 *
 *  @param  viddecInArgs
 *          handle to the all function of the operations on IVIDDEC1 objects.
 *
 *******************************************************************************
*/
typedef struct Ivp7VDEC_Fxns
{
    /* Ivp7VDEC extends IVIDDEC object.Should be second set of functions */
    IVIDDEC3_Fxns    ividdec;

    /* Add more  */
} Ivp7VDEC_Fxns;




/*******************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*----------------------------- macros ---------------------------------------*/
/* Extending control method commands                                        */

/**
 * The Macro indicates the Get Status Command Enum for the Control API
*/
#define Ivp7VDEC_GETSTATUS      XDM_GETSTATUS

/**
 * The Macro indicates the SET PARAMS Command Enum for the Control API
*/
#define Ivp7VDEC_SETPARAMS      XDM_SETPARAMS

/**
 * The Macro indicates the XDM RESET Command Enum for the Control API
*/
#define Ivp7VDEC_RESET          XDM_RESET

/**
 * The Macro indicates the XDM FLUSH Command Enum for the Control API
*/
#define Ivp7VDEC_FLUSH          XDM_FLUSH

/**
 * The Macro indicates the SET DEFUALT Command Enum for the Control API
*/
#define Ivp7VDEC_SETDEFAULT     XDM_SETDEFAULT

/**
 * The Macro indicates the Get BUFINFO Command Enum for the Control API
*/
#define Ivp7VDEC_GETBUFINFO     XDM_GETBUFINFO

/**
 * The Macro indicates to the Get context Info through control call.
*/
#define Ivp7VDEC_GETCONTEXTINFO         XDM_GETCONTEXTINFO

/**
 * The Macro is a command get the Default Parameters for the Dynamic Structure.
*/
#define Ivp7VDEC_GETDYNPARAMSDEFAULT    XDM_GETDYNPARAMSDEFAULT

/**
* The Macro indicates the Get VERSION Command Enum for the Control API
*/
#define Ivp7VDEC_GETVERSION     XDM_GETVERSION

/**
 * The Macro indicates the Late Acquire Arguement provided by Application.
*/
#define Ivp7VDEC_SETLATEACQUIREARG     XDM_SETLATEACQUIREARG

/**
 * The Macro indicates the Enum for the 420 Interrleaved Format
*/
#define Ivp7VDEC_YUV_420IUV     256

/**
* This macro is valid only in case of Ivf bitstreams & tells to decode
* Ivf header which appears once at beginning of bitstream
*/
#define IVP7VDEC_DECODE_IVF_HEADER 256

#endif  /* __IVP7VDEC__ */

