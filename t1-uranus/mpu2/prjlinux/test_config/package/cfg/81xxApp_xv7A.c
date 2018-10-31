/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-v55
 */

#define __nested__
#define __config__

#include <xdc/std.h>

/*
 * ======== GENERATED SECTIONS ========
 *     
 *     MODULE INCLUDES
 *     
 *     <module-name> INTERNALS
 *     <module-name> INHERITS
 *     <module-name> VTABLE
 *     <module-name> PATCH TABLE
 *     <module-name> DECLARATIONS
 *     <module-name> OBJECT OFFSETS
 *     <module-name> TEMPLATES
 *     <module-name> INITIALIZERS
 *     <module-name> FUNCTION STUBS
 *     <module-name> PROXY BODY
 *     <module-name> OBJECT DESCRIPTOR
 *     <module-name> SYSTEM FUNCTIONS
 *     <module-name> PRAGMAS
 *     
 *     INITIALIZATION ENTRY POINT
 *     PROGRAM GLOBALS
 *     CLINK DIRECTIVES
 */


/*
 * ======== MODULE INCLUDES ========
 */

#include <ti/sdo/utils/loggers/LogMFP.h>
#include <ti/sdo/utils/loggers/LoggerMFPNull.h>
#include <ti/sdo/utils/loggers/LoggerSysTID.h>
#include <ti/sdo/xdcruntime/linux/GateThreadSupport.h>
#include <ti/sdo/xdcruntime/linux/SemProcessSupport.h>
#include <ti/sdo/xdcruntime/linux/SemThreadSupport.h>
#include <ti/sdo/xdcruntime/linux/ThreadSupport.h>
#include <ti/sdo/xdcruntime/linux/TimestampPosix.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Core.h>
#include <xdc/runtime/Defaults.h>
#include <xdc/runtime/Diags.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/HeapStd.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Main.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Registry.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/SysStd.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Text.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/knl/GateThread.h>
#include <xdc/runtime/knl/SemProcess.h>
#include <xdc/runtime/knl/SemThread.h>
#include <xdc/runtime/knl/Thread.h>


/*
 * ======== ti.sdo.utils.loggers.LogMFP INTERNALS ========
 */


/*
 * ======== ti.sdo.utils.loggers.LogMFP_Proxy INTERNALS ========
 */

/* Module__ */
typedef struct ti_sdo_utils_loggers_LogMFP_Proxy_Module__ {
    xdc_runtime_Types_Link link;
} ti_sdo_utils_loggers_LogMFP_Proxy_Module__;

/* Module__root__V */
extern ti_sdo_utils_loggers_LogMFP_Proxy_Module__ ti_sdo_utils_loggers_LogMFP_Proxy_Module__root__V;

/* Object__ */
typedef struct ti_sdo_utils_loggers_LoggerMFPNull_Object__ {
    const ti_sdo_utils_loggers_LoggerMFPNull_Fxns__* __fxns;
    xdc_Bool enabled;
} ti_sdo_utils_loggers_LoggerMFPNull_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    ti_sdo_utils_loggers_LoggerMFPNull_Object__ obj;
} ti_sdo_utils_loggers_LoggerMFPNull_Object2__;

/* Object */
typedef ti_sdo_utils_loggers_LoggerMFPNull_Object__ ti_sdo_utils_loggers_LogMFP_Proxy_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    ti_sdo_utils_loggers_LogMFP_Proxy_Object__ obj;
} ti_sdo_utils_loggers_LogMFP_Proxy_Object2__;

/* __ParamsPtr */
#ifdef ti_sdo_utils_loggers_LogMFP_Proxy___VERS
    #define ti_sdo_utils_loggers_LogMFP_Proxy___ParamsPtr xdc_UChar*
#else
    #define ti_sdo_utils_loggers_LogMFP_Proxy___ParamsPtr xdc_Ptr
#endif


/*
 * ======== ti.sdo.utils.loggers.LoggerMFPNull INTERNALS ========
 */

/* Module__ */
typedef struct ti_sdo_utils_loggers_LoggerMFPNull_Module__ {
    xdc_runtime_Types_Link link;
} ti_sdo_utils_loggers_LoggerMFPNull_Module__;

/* Module__root__V */
extern ti_sdo_utils_loggers_LoggerMFPNull_Module__ ti_sdo_utils_loggers_LoggerMFPNull_Module__root__V;

/* <-- ti_sdo_utils_loggers_LoggerMFPNull_Object */

/* __ParamsPtr */
#ifdef ti_sdo_utils_loggers_LoggerMFPNull___VERS
    #define ti_sdo_utils_loggers_LoggerMFPNull___ParamsPtr xdc_UChar*
#else
    #define ti_sdo_utils_loggers_LoggerMFPNull___ParamsPtr xdc_Ptr
#endif


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID INTERNALS ========
 */

/* Module__ */
typedef struct ti_sdo_utils_loggers_LoggerSysTID_Module__ {
    xdc_runtime_Types_Link link;
} ti_sdo_utils_loggers_LoggerSysTID_Module__;

/* Module__root__V */
extern ti_sdo_utils_loggers_LoggerSysTID_Module__ ti_sdo_utils_loggers_LoggerSysTID_Module__root__V;

/* Object__ */
typedef struct ti_sdo_utils_loggers_LoggerSysTID_Object__ {
    const ti_sdo_utils_loggers_LoggerSysTID_Fxns__* __fxns;
    xdc_Bool enabled;
} ti_sdo_utils_loggers_LoggerSysTID_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    ti_sdo_utils_loggers_LoggerSysTID_Object__ obj;
} ti_sdo_utils_loggers_LoggerSysTID_Object2__;

/* __ParamsPtr */
#ifdef ti_sdo_utils_loggers_LoggerSysTID___VERS
    #define ti_sdo_utils_loggers_LoggerSysTID___ParamsPtr xdc_UChar*
#else
    #define ti_sdo_utils_loggers_LoggerSysTID___ParamsPtr xdc_Ptr
#endif


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID_Module_GateProxy INTERNALS ========
 */

/* Module__ */
typedef struct ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__ {
    xdc_runtime_Types_Link link;
} ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__;

/* Module__root__V */
extern ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__ ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__root__V;

/* Object__ */
typedef struct xdc_runtime_knl_GateThread_Object__ {
    const xdc_runtime_knl_GateThread_Fxns__* __fxns;
    xdc_runtime_knl_GateThread_Proxy_Handle proxyHandle;
} xdc_runtime_knl_GateThread_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_knl_GateThread_Object__ obj;
} xdc_runtime_knl_GateThread_Object2__;

/* Object */
typedef xdc_runtime_knl_GateThread_Object__ ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Object__ obj;
} ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Object2__;

/* __ParamsPtr */
#ifdef ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy___VERS
    #define ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy___ParamsPtr xdc_UChar*
#else
    #define ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy___ParamsPtr xdc_Ptr
#endif


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID_TimestampProxy INTERNALS ========
 */


/*
 * ======== ti.sdo.xdcruntime.linux.GateThreadSupport INTERNALS ========
 */

/* Module__ */
typedef struct ti_sdo_xdcruntime_linux_GateThreadSupport_Module__ {
    xdc_runtime_Types_Link link;
} ti_sdo_xdcruntime_linux_GateThreadSupport_Module__;

/* Module__root__V */
extern ti_sdo_xdcruntime_linux_GateThreadSupport_Module__ ti_sdo_xdcruntime_linux_GateThreadSupport_Module__root__V;

/* Object__ */
typedef struct ti_sdo_xdcruntime_linux_GateThreadSupport_Object__ {
    const ti_sdo_xdcruntime_linux_GateThreadSupport_Fxns__* __fxns;
    xdc_Void* gate;
} ti_sdo_xdcruntime_linux_GateThreadSupport_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    ti_sdo_xdcruntime_linux_GateThreadSupport_Object__ obj;
} ti_sdo_xdcruntime_linux_GateThreadSupport_Object2__;

/* __ParamsPtr */
#ifdef ti_sdo_xdcruntime_linux_GateThreadSupport___VERS
    #define ti_sdo_xdcruntime_linux_GateThreadSupport___ParamsPtr xdc_UChar*
#else
    #define ti_sdo_xdcruntime_linux_GateThreadSupport___ParamsPtr xdc_Ptr
#endif


/*
 * ======== ti.sdo.xdcruntime.linux.SemProcessSupport INTERNALS ========
 */

/* Module__ */
typedef struct ti_sdo_xdcruntime_linux_SemProcessSupport_Module__ {
    xdc_runtime_Types_Link link;
} ti_sdo_xdcruntime_linux_SemProcessSupport_Module__;

/* Module__root__V */
extern ti_sdo_xdcruntime_linux_SemProcessSupport_Module__ ti_sdo_xdcruntime_linux_SemProcessSupport_Module__root__V;

/* Object__ */
typedef struct ti_sdo_xdcruntime_linux_SemProcessSupport_Object__ {
    const ti_sdo_xdcruntime_linux_SemProcessSupport_Fxns__* __fxns;
    xdc_Int id;
    xdc_Int key;
    xdc_Int count;
    ti_sdo_xdcruntime_linux_SemProcessSupport_Mode mode;
} ti_sdo_xdcruntime_linux_SemProcessSupport_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    ti_sdo_xdcruntime_linux_SemProcessSupport_Object__ obj;
} ti_sdo_xdcruntime_linux_SemProcessSupport_Object2__;

/* __ParamsPtr */
#ifdef ti_sdo_xdcruntime_linux_SemProcessSupport___VERS
    #define ti_sdo_xdcruntime_linux_SemProcessSupport___ParamsPtr xdc_UChar*
#else
    #define ti_sdo_xdcruntime_linux_SemProcessSupport___ParamsPtr xdc_Ptr
#endif


/*
 * ======== ti.sdo.xdcruntime.linux.SemThreadSupport INTERNALS ========
 */

/* Module__ */
typedef struct ti_sdo_xdcruntime_linux_SemThreadSupport_Module__ {
    xdc_runtime_Types_Link link;
} ti_sdo_xdcruntime_linux_SemThreadSupport_Module__;

/* Module__root__V */
extern ti_sdo_xdcruntime_linux_SemThreadSupport_Module__ ti_sdo_xdcruntime_linux_SemThreadSupport_Module__root__V;

/* Object__ */
typedef struct ti_sdo_xdcruntime_linux_SemThreadSupport_Object__ {
    const ti_sdo_xdcruntime_linux_SemThreadSupport_Fxns__* __fxns;
    xdc_Void* sem;
    ti_sdo_xdcruntime_linux_SemThreadSupport_Mode mode;
} ti_sdo_xdcruntime_linux_SemThreadSupport_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    ti_sdo_xdcruntime_linux_SemThreadSupport_Object__ obj;
} ti_sdo_xdcruntime_linux_SemThreadSupport_Object2__;

/* __ParamsPtr */
#ifdef ti_sdo_xdcruntime_linux_SemThreadSupport___VERS
    #define ti_sdo_xdcruntime_linux_SemThreadSupport___ParamsPtr xdc_UChar*
#else
    #define ti_sdo_xdcruntime_linux_SemThreadSupport___ParamsPtr xdc_Ptr
#endif


/*
 * ======== ti.sdo.xdcruntime.linux.ThreadSupport INTERNALS ========
 */

/* Module__ */
typedef struct ti_sdo_xdcruntime_linux_ThreadSupport_Module__ {
    xdc_runtime_Types_Link link;
} ti_sdo_xdcruntime_linux_ThreadSupport_Module__;

/* Module__root__V */
extern ti_sdo_xdcruntime_linux_ThreadSupport_Module__ ti_sdo_xdcruntime_linux_ThreadSupport_Module__root__V;

/* Object__ */
typedef struct ti_sdo_xdcruntime_linux_ThreadSupport_Object__ {
    const ti_sdo_xdcruntime_linux_ThreadSupport_Fxns__* __fxns;
    xdc_Ptr tls;
    ti_sdo_xdcruntime_linux_ThreadSupport_RunFxn startFxn;
    xdc_IArg startFxnArg;
    xdc_SizeT stackSize;
    xdc_Void* tid;
    xdc_Ptr stackBase;
    xdc_Int staticOsPri;
} ti_sdo_xdcruntime_linux_ThreadSupport_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    ti_sdo_xdcruntime_linux_ThreadSupport_Object__ obj;
} ti_sdo_xdcruntime_linux_ThreadSupport_Object2__;

/* __ParamsPtr */
#ifdef ti_sdo_xdcruntime_linux_ThreadSupport___VERS
    #define ti_sdo_xdcruntime_linux_ThreadSupport___ParamsPtr xdc_UChar*
#else
    #define ti_sdo_xdcruntime_linux_ThreadSupport___ParamsPtr xdc_Ptr
#endif


/*
 * ======== ti.sdo.xdcruntime.linux.TimestampPosix INTERNALS ========
 */


/*
 * ======== xdc.runtime.Assert INTERNALS ========
 */


/*
 * ======== xdc.runtime.Core INTERNALS ========
 */


/*
 * ======== xdc.runtime.Defaults INTERNALS ========
 */


/*
 * ======== xdc.runtime.Diags INTERNALS ========
 */


/*
 * ======== xdc.runtime.Error INTERNALS ========
 */


/*
 * ======== xdc.runtime.Gate INTERNALS ========
 */


/*
 * ======== xdc.runtime.HeapStd INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_HeapStd_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_HeapStd_Module__;

/* Module__root__V */
extern xdc_runtime_HeapStd_Module__ xdc_runtime_HeapStd_Module__root__V;

/* Object__ */
typedef struct xdc_runtime_HeapStd_Object__ {
    const xdc_runtime_HeapStd_Fxns__* __fxns;
    xdc_runtime_Memory_Size remainSize;
    xdc_runtime_Memory_Size startSize;
} xdc_runtime_HeapStd_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_HeapStd_Object__ obj;
} xdc_runtime_HeapStd_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_HeapStd___VERS
    #define xdc_runtime_HeapStd___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_HeapStd___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.Log INTERNALS ========
 */


/*
 * ======== xdc.runtime.Main INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_Main_Module__ {
    xdc_runtime_Types_DiagsMask mask;
} xdc_runtime_Main_Module__;

/* Module__root__V */
extern xdc_runtime_Main_Module__ xdc_runtime_Main_Module__root__V;


/*
 * ======== xdc.runtime.Main_Module_GateProxy INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_Main_Module_GateProxy_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_Main_Module_GateProxy_Module__;

/* Module__root__V */
extern xdc_runtime_Main_Module_GateProxy_Module__ xdc_runtime_Main_Module_GateProxy_Module__root__V;

/* <-- ti_sdo_xdcruntime_linux_GateThreadSupport_Object */

/* Object */
typedef ti_sdo_xdcruntime_linux_GateThreadSupport_Object__ xdc_runtime_Main_Module_GateProxy_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_Main_Module_GateProxy_Object__ obj;
} xdc_runtime_Main_Module_GateProxy_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_Main_Module_GateProxy___VERS
    #define xdc_runtime_Main_Module_GateProxy___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_Main_Module_GateProxy___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.Memory INTERNALS ========
 */


/*
 * ======== xdc.runtime.Memory_HeapProxy INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_Memory_HeapProxy_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_Memory_HeapProxy_Module__;

/* Module__root__V */
extern xdc_runtime_Memory_HeapProxy_Module__ xdc_runtime_Memory_HeapProxy_Module__root__V;

/* <-- xdc_runtime_HeapStd_Object */

/* Object */
typedef xdc_runtime_HeapStd_Object__ xdc_runtime_Memory_HeapProxy_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_Memory_HeapProxy_Object__ obj;
} xdc_runtime_Memory_HeapProxy_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_Memory_HeapProxy___VERS
    #define xdc_runtime_Memory_HeapProxy___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_Memory_HeapProxy___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.Registry INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_Registry_Module__ {
    xdc_runtime_Types_DiagsMask mask;
} xdc_runtime_Registry_Module__;

/* Module__root__V */
extern xdc_runtime_Registry_Module__ xdc_runtime_Registry_Module__root__V;


/*
 * ======== xdc.runtime.Startup INTERNALS ========
 */


/*
 * ======== xdc.runtime.SysStd INTERNALS ========
 */


/*
 * ======== xdc.runtime.System INTERNALS ========
 */


/*
 * ======== xdc.runtime.System_Module_GateProxy INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_System_Module_GateProxy_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_System_Module_GateProxy_Module__;

/* Module__root__V */
extern xdc_runtime_System_Module_GateProxy_Module__ xdc_runtime_System_Module_GateProxy_Module__root__V;

/* <-- ti_sdo_xdcruntime_linux_GateThreadSupport_Object */

/* Object */
typedef ti_sdo_xdcruntime_linux_GateThreadSupport_Object__ xdc_runtime_System_Module_GateProxy_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_System_Module_GateProxy_Object__ obj;
} xdc_runtime_System_Module_GateProxy_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_System_Module_GateProxy___VERS
    #define xdc_runtime_System_Module_GateProxy___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_System_Module_GateProxy___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.System_SupportProxy INTERNALS ========
 */


/*
 * ======== xdc.runtime.Text INTERNALS ========
 */


/*
 * ======== xdc.runtime.Timestamp INTERNALS ========
 */


/*
 * ======== xdc.runtime.Timestamp_SupportProxy INTERNALS ========
 */


/*
 * ======== xdc.runtime.knl.GateThread INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_knl_GateThread_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_knl_GateThread_Module__;

/* Module__root__V */
extern xdc_runtime_knl_GateThread_Module__ xdc_runtime_knl_GateThread_Module__root__V;

/* <-- xdc_runtime_knl_GateThread_Object */

/* __ParamsPtr */
#ifdef xdc_runtime_knl_GateThread___VERS
    #define xdc_runtime_knl_GateThread___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_knl_GateThread___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.knl.GateThread_Proxy INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_knl_GateThread_Proxy_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_knl_GateThread_Proxy_Module__;

/* Module__root__V */
extern xdc_runtime_knl_GateThread_Proxy_Module__ xdc_runtime_knl_GateThread_Proxy_Module__root__V;

/* <-- ti_sdo_xdcruntime_linux_GateThreadSupport_Object */

/* Object */
typedef ti_sdo_xdcruntime_linux_GateThreadSupport_Object__ xdc_runtime_knl_GateThread_Proxy_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_knl_GateThread_Proxy_Object__ obj;
} xdc_runtime_knl_GateThread_Proxy_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_knl_GateThread_Proxy___VERS
    #define xdc_runtime_knl_GateThread_Proxy___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_knl_GateThread_Proxy___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.knl.SemProcess INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_knl_SemProcess_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_knl_SemProcess_Module__;

/* Module__root__V */
extern xdc_runtime_knl_SemProcess_Module__ xdc_runtime_knl_SemProcess_Module__root__V;

/* Object__ */
typedef struct xdc_runtime_knl_SemProcess_Object__ {
    const xdc_runtime_knl_SemProcess_Fxns__* __fxns;
    xdc_runtime_knl_SemProcess_Proxy_Handle proxyHandle;
} xdc_runtime_knl_SemProcess_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_knl_SemProcess_Object__ obj;
} xdc_runtime_knl_SemProcess_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_knl_SemProcess___VERS
    #define xdc_runtime_knl_SemProcess___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_knl_SemProcess___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.knl.SemProcess_Proxy INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_knl_SemProcess_Proxy_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_knl_SemProcess_Proxy_Module__;

/* Module__root__V */
extern xdc_runtime_knl_SemProcess_Proxy_Module__ xdc_runtime_knl_SemProcess_Proxy_Module__root__V;

/* <-- ti_sdo_xdcruntime_linux_SemProcessSupport_Object */

/* Object */
typedef ti_sdo_xdcruntime_linux_SemProcessSupport_Object__ xdc_runtime_knl_SemProcess_Proxy_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_knl_SemProcess_Proxy_Object__ obj;
} xdc_runtime_knl_SemProcess_Proxy_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_knl_SemProcess_Proxy___VERS
    #define xdc_runtime_knl_SemProcess_Proxy___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_knl_SemProcess_Proxy___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.knl.SemThread INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_knl_SemThread_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_knl_SemThread_Module__;

/* Module__root__V */
extern xdc_runtime_knl_SemThread_Module__ xdc_runtime_knl_SemThread_Module__root__V;

/* Object__ */
typedef struct xdc_runtime_knl_SemThread_Object__ {
    const xdc_runtime_knl_SemThread_Fxns__* __fxns;
    xdc_runtime_knl_SemThread_Proxy_Handle proxyHandle;
} xdc_runtime_knl_SemThread_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_knl_SemThread_Object__ obj;
} xdc_runtime_knl_SemThread_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_knl_SemThread___VERS
    #define xdc_runtime_knl_SemThread___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_knl_SemThread___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.knl.SemThread_Proxy INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_knl_SemThread_Proxy_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_knl_SemThread_Proxy_Module__;

/* Module__root__V */
extern xdc_runtime_knl_SemThread_Proxy_Module__ xdc_runtime_knl_SemThread_Proxy_Module__root__V;

/* <-- ti_sdo_xdcruntime_linux_SemThreadSupport_Object */

/* Object */
typedef ti_sdo_xdcruntime_linux_SemThreadSupport_Object__ xdc_runtime_knl_SemThread_Proxy_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_knl_SemThread_Proxy_Object__ obj;
} xdc_runtime_knl_SemThread_Proxy_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_knl_SemThread_Proxy___VERS
    #define xdc_runtime_knl_SemThread_Proxy___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_knl_SemThread_Proxy___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.knl.Thread INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_knl_Thread_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_knl_Thread_Module__;

/* Module__root__V */
extern xdc_runtime_knl_Thread_Module__ xdc_runtime_knl_Thread_Module__root__V;

/* Object__ */
typedef struct xdc_runtime_knl_Thread_Object__ {
    xdc_runtime_knl_Thread_Proxy_Handle proxyHandle;
    xdc_Ptr tls;
} xdc_runtime_knl_Thread_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_knl_Thread_Object__ obj;
} xdc_runtime_knl_Thread_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_knl_Thread___VERS
    #define xdc_runtime_knl_Thread___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_knl_Thread___ParamsPtr xdc_Ptr
#endif


/*
 * ======== xdc.runtime.knl.Thread_Proxy INTERNALS ========
 */

/* Module__ */
typedef struct xdc_runtime_knl_Thread_Proxy_Module__ {
    xdc_runtime_Types_Link link;
} xdc_runtime_knl_Thread_Proxy_Module__;

/* Module__root__V */
extern xdc_runtime_knl_Thread_Proxy_Module__ xdc_runtime_knl_Thread_Proxy_Module__root__V;

/* <-- ti_sdo_xdcruntime_linux_ThreadSupport_Object */

/* Object */
typedef ti_sdo_xdcruntime_linux_ThreadSupport_Object__ xdc_runtime_knl_Thread_Proxy_Object__;

/* Object2__ */
typedef struct {
    xdc_runtime_Types_InstHdr hdr;
    xdc_runtime_knl_Thread_Proxy_Object__ obj;
} xdc_runtime_knl_Thread_Proxy_Object2__;

/* __ParamsPtr */
#ifdef xdc_runtime_knl_Thread_Proxy___VERS
    #define xdc_runtime_knl_Thread_Proxy___ParamsPtr xdc_UChar*
#else
    #define xdc_runtime_knl_Thread_Proxy___ParamsPtr xdc_Ptr
#endif


/*
 * ======== ti.sdo.utils.loggers.LoggerMFPNull INHERITS ========
 */

__FAR__ const xdc_runtime_Types_Base xdc_runtime_IModule_Interface__BASE__C = {0};
__FAR__ const xdc_runtime_Types_Base xdc_runtime_ILogger_Interface__BASE__C = {(void*)&xdc_runtime_IModule_Interface__BASE__C};
__FAR__ const xdc_runtime_Types_Base ti_sdo_utils_loggers_ILoggerMFP_Interface__BASE__C = {(void*)&xdc_runtime_ILogger_Interface__BASE__C};


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID INHERITS ========
 */



/*
 * ======== ti.sdo.xdcruntime.linux.TimestampPosix INHERITS ========
 */

__FAR__ const xdc_runtime_Types_Base xdc_runtime_ITimestampClient_Interface__BASE__C = {(void*)&xdc_runtime_IModule_Interface__BASE__C};
__FAR__ const xdc_runtime_Types_Base xdc_runtime_ITimestampProvider_Interface__BASE__C = {(void*)&xdc_runtime_ITimestampClient_Interface__BASE__C};


/*
 * ======== xdc.runtime.HeapStd INHERITS ========
 */

__FAR__ const xdc_runtime_Types_Base xdc_runtime_IHeap_Interface__BASE__C = {(void*)&xdc_runtime_IModule_Interface__BASE__C};


/*
 * ======== xdc.runtime.SysStd INHERITS ========
 */

__FAR__ const xdc_runtime_Types_Base xdc_runtime_ISystemSupport_Interface__BASE__C = {(void*)&xdc_runtime_IModule_Interface__BASE__C};


/*
 * ======== xdc.runtime.Timestamp INHERITS ========
 */



/*
 * ======== xdc.runtime.knl.GateThread INHERITS ========
 */

__FAR__ const xdc_runtime_Types_Base xdc_runtime_IGateProvider_Interface__BASE__C = {(void*)&xdc_runtime_IModule_Interface__BASE__C};


/*
 * ======== xdc.runtime.knl.SemProcess INHERITS ========
 */

__FAR__ const xdc_runtime_Types_Base xdc_runtime_knl_ISemaphore_Interface__BASE__C = {(void*)&xdc_runtime_IModule_Interface__BASE__C};


/*
 * ======== xdc.runtime.knl.SemThread INHERITS ========
 */



/*
 * ======== ti.sdo.utils.loggers.LoggerMFPNull VTABLE ========
 */

/* Module__FXNS__C */
const ti_sdo_utils_loggers_LoggerMFPNull_Fxns__ ti_sdo_utils_loggers_LoggerMFPNull_Module__FXNS__C = {
    (void*)&ti_sdo_utils_loggers_ILoggerMFP_Interface__BASE__C, /* base__ */
    &ti_sdo_utils_loggers_LoggerMFPNull_Module__FXNS__C.__sfxns, /* __sysp */
    ti_sdo_utils_loggers_LoggerMFPNull_enable__E,
    ti_sdo_utils_loggers_LoggerMFPNull_disable__E,
    ti_sdo_utils_loggers_LoggerMFPNull_write0__E,
    ti_sdo_utils_loggers_LoggerMFPNull_write1__E,
    ti_sdo_utils_loggers_LoggerMFPNull_write2__E,
    ti_sdo_utils_loggers_LoggerMFPNull_write4__E,
    ti_sdo_utils_loggers_LoggerMFPNull_write8__E,
    ti_sdo_utils_loggers_LoggerMFPNull_control__E,
    {
        ti_sdo_utils_loggers_LoggerMFPNull_Object__create__S,
        ti_sdo_utils_loggers_LoggerMFPNull_Object__delete__S,
        ti_sdo_utils_loggers_LoggerMFPNull_Handle__label__S,
        0x8022, /* __mid */
    } /* __sfxns */
};


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID VTABLE ========
 */

/* Module__FXNS__C */
const ti_sdo_utils_loggers_LoggerSysTID_Fxns__ ti_sdo_utils_loggers_LoggerSysTID_Module__FXNS__C = {
    (void*)&ti_sdo_utils_loggers_ILoggerMFP_Interface__BASE__C, /* base__ */
    &ti_sdo_utils_loggers_LoggerSysTID_Module__FXNS__C.__sfxns, /* __sysp */
    ti_sdo_utils_loggers_LoggerSysTID_enable__E,
    ti_sdo_utils_loggers_LoggerSysTID_disable__E,
    ti_sdo_utils_loggers_LoggerSysTID_write0__E,
    ti_sdo_utils_loggers_LoggerSysTID_write1__E,
    ti_sdo_utils_loggers_LoggerSysTID_write2__E,
    ti_sdo_utils_loggers_LoggerSysTID_write4__E,
    ti_sdo_utils_loggers_LoggerSysTID_write8__E,
    ti_sdo_utils_loggers_LoggerSysTID_control__E,
    {
        ti_sdo_utils_loggers_LoggerSysTID_Object__create__S,
        ti_sdo_utils_loggers_LoggerSysTID_Object__delete__S,
        ti_sdo_utils_loggers_LoggerSysTID_Handle__label__S,
        0x8021, /* __mid */
    } /* __sfxns */
};


/*
 * ======== ti.sdo.xdcruntime.linux.TimestampPosix VTABLE ========
 */

/* Module__FXNS__C */
const ti_sdo_xdcruntime_linux_TimestampPosix_Fxns__ ti_sdo_xdcruntime_linux_TimestampPosix_Module__FXNS__C = {
    (void*)&xdc_runtime_ITimestampProvider_Interface__BASE__C, /* base__ */
    &ti_sdo_xdcruntime_linux_TimestampPosix_Module__FXNS__C.__sfxns, /* __sysp */
    ti_sdo_xdcruntime_linux_TimestampPosix_get32__E,
    ti_sdo_xdcruntime_linux_TimestampPosix_get64__E,
    ti_sdo_xdcruntime_linux_TimestampPosix_getFreq__E,
    {
        NULL, /* __create */
        NULL, /* __delete */
        NULL, /* __label */
        0x801e, /* __mid */
    } /* __sfxns */
};


/*
 * ======== xdc.runtime.HeapStd VTABLE ========
 */

/* Module__FXNS__C */
const xdc_runtime_HeapStd_Fxns__ xdc_runtime_HeapStd_Module__FXNS__C = {
    (void*)&xdc_runtime_IHeap_Interface__BASE__C, /* base__ */
    &xdc_runtime_HeapStd_Module__FXNS__C.__sfxns, /* __sysp */
    xdc_runtime_HeapStd_alloc__E,
    xdc_runtime_HeapStd_free__E,
    xdc_runtime_HeapStd_isBlocking__E,
    xdc_runtime_HeapStd_getStats__E,
    {
        xdc_runtime_HeapStd_Object__create__S,
        xdc_runtime_HeapStd_Object__delete__S,
        xdc_runtime_HeapStd_Handle__label__S,
        0x800b, /* __mid */
    } /* __sfxns */
};


/*
 * ======== xdc.runtime.SysStd VTABLE ========
 */

/* Module__FXNS__C */
const xdc_runtime_SysStd_Fxns__ xdc_runtime_SysStd_Module__FXNS__C = {
    (void*)&xdc_runtime_ISystemSupport_Interface__BASE__C, /* base__ */
    &xdc_runtime_SysStd_Module__FXNS__C.__sfxns, /* __sysp */
    xdc_runtime_SysStd_abort__E,
    xdc_runtime_SysStd_exit__E,
    xdc_runtime_SysStd_flush__E,
    xdc_runtime_SysStd_putch__E,
    xdc_runtime_SysStd_ready__E,
    {
        NULL, /* __create */
        NULL, /* __delete */
        NULL, /* __label */
        0x800f, /* __mid */
    } /* __sfxns */
};


/*
 * ======== xdc.runtime.Timestamp VTABLE ========
 */

/* Module__FXNS__C */
const xdc_runtime_Timestamp_Fxns__ xdc_runtime_Timestamp_Module__FXNS__C = {
    (void*)&xdc_runtime_ITimestampClient_Interface__BASE__C, /* base__ */
    &xdc_runtime_Timestamp_Module__FXNS__C.__sfxns, /* __sysp */
    xdc_runtime_Timestamp_get32__E,
    xdc_runtime_Timestamp_get64__E,
    xdc_runtime_Timestamp_getFreq__E,
    {
        NULL, /* __create */
        NULL, /* __delete */
        NULL, /* __label */
        0x8011, /* __mid */
    } /* __sfxns */
};


/*
 * ======== xdc.runtime.knl.GateThread VTABLE ========
 */

/* Module__FXNS__C */
const xdc_runtime_knl_GateThread_Fxns__ xdc_runtime_knl_GateThread_Module__FXNS__C = {
    (void*)&xdc_runtime_IGateProvider_Interface__BASE__C, /* base__ */
    &xdc_runtime_knl_GateThread_Module__FXNS__C.__sfxns, /* __sysp */
    xdc_runtime_knl_GateThread_query__E,
    xdc_runtime_knl_GateThread_enter__E,
    xdc_runtime_knl_GateThread_leave__E,
    {
        xdc_runtime_knl_GateThread_Object__create__S,
        xdc_runtime_knl_GateThread_Object__delete__S,
        xdc_runtime_knl_GateThread_Handle__label__S,
        0x8014, /* __mid */
    } /* __sfxns */
};


/*
 * ======== xdc.runtime.knl.SemProcess VTABLE ========
 */

/* Module__FXNS__C */
const xdc_runtime_knl_SemProcess_Fxns__ xdc_runtime_knl_SemProcess_Module__FXNS__C = {
    (void*)&xdc_runtime_knl_ISemaphore_Interface__BASE__C, /* base__ */
    &xdc_runtime_knl_SemProcess_Module__FXNS__C.__sfxns, /* __sysp */
    xdc_runtime_knl_SemProcess_pend__E,
    xdc_runtime_knl_SemProcess_post__E,
    {
        xdc_runtime_knl_SemProcess_Object__create__S,
        xdc_runtime_knl_SemProcess_Object__delete__S,
        xdc_runtime_knl_SemProcess_Handle__label__S,
        0x8016, /* __mid */
    } /* __sfxns */
};


/*
 * ======== xdc.runtime.knl.SemThread VTABLE ========
 */

/* Module__FXNS__C */
const xdc_runtime_knl_SemThread_Fxns__ xdc_runtime_knl_SemThread_Module__FXNS__C = {
    (void*)&xdc_runtime_knl_ISemaphore_Interface__BASE__C, /* base__ */
    &xdc_runtime_knl_SemThread_Module__FXNS__C.__sfxns, /* __sysp */
    xdc_runtime_knl_SemThread_pend__E,
    xdc_runtime_knl_SemThread_post__E,
    {
        xdc_runtime_knl_SemThread_Object__create__S,
        xdc_runtime_knl_SemThread_Object__delete__S,
        xdc_runtime_knl_SemThread_Handle__label__S,
        0x8015, /* __mid */
    } /* __sfxns */
};


/*
 * ======== ti.sdo.utils.loggers.LogMFP DECLARATIONS ========
 */


/*
 * ======== ti.sdo.utils.loggers.LogMFP_Proxy DECLARATIONS ========
 */


/*
 * ======== ti.sdo.utils.loggers.LoggerMFPNull DECLARATIONS ========
 */


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID DECLARATIONS ========
 */

/* Object__table__V */
ti_sdo_utils_loggers_LoggerSysTID_Object__ ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[1];


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID_Module_GateProxy DECLARATIONS ========
 */


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID_TimestampProxy DECLARATIONS ========
 */


/*
 * ======== ti.sdo.xdcruntime.linux.GateThreadSupport DECLARATIONS ========
 */

/* Object__table__V */
ti_sdo_xdcruntime_linux_GateThreadSupport_Object__ ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__V[2];


/*
 * ======== ti.sdo.xdcruntime.linux.SemProcessSupport DECLARATIONS ========
 */


/*
 * ======== ti.sdo.xdcruntime.linux.SemThreadSupport DECLARATIONS ========
 */

/* Module_State__ */
typedef struct ti_sdo_xdcruntime_linux_SemThreadSupport_Module_State__ {
    xdc_Void* mutex;
} ti_sdo_xdcruntime_linux_SemThreadSupport_Module_State__;

/* Module__state__V */
ti_sdo_xdcruntime_linux_SemThreadSupport_Module_State__ ti_sdo_xdcruntime_linux_SemThreadSupport_Module__state__V;


/*
 * ======== ti.sdo.xdcruntime.linux.ThreadSupport DECLARATIONS ========
 */

/* Module_State__ */
typedef struct ti_sdo_xdcruntime_linux_ThreadSupport_Module_State__ {
    xdc_Int lowestPriority;
    xdc_Int belowNormalPriority;
    xdc_Int normalPriority;
    xdc_Int aboveNormalPriority;
    xdc_Int highestPriority;
} ti_sdo_xdcruntime_linux_ThreadSupport_Module_State__;

/* Module__state__V */
ti_sdo_xdcruntime_linux_ThreadSupport_Module_State__ ti_sdo_xdcruntime_linux_ThreadSupport_Module__state__V;


/*
 * ======== ti.sdo.xdcruntime.linux.TimestampPosix DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Assert DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Core DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Defaults DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Diags DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Error DECLARATIONS ========
 */

/* Module_State__ */
typedef struct xdc_runtime_Error_Module_State__ {
    xdc_UInt16 count;
} xdc_runtime_Error_Module_State__;

/* Module__state__V */
xdc_runtime_Error_Module_State__ xdc_runtime_Error_Module__state__V;


/*
 * ======== xdc.runtime.Gate DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.HeapStd DECLARATIONS ========
 */

/* Object__table__V */
xdc_runtime_HeapStd_Object__ xdc_runtime_HeapStd_Object__table__V[1];

/* Module_State__ */
typedef struct xdc_runtime_HeapStd_Module_State__ {
    xdc_runtime_Memory_Size remainRTSSize;
} xdc_runtime_HeapStd_Module_State__;

/* Module__state__V */
xdc_runtime_HeapStd_Module_State__ xdc_runtime_HeapStd_Module__state__V;


/*
 * ======== xdc.runtime.Log DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Main DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Main_Module_GateProxy DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Memory DECLARATIONS ========
 */

/* Module_State__ */
typedef struct xdc_runtime_Memory_Module_State__ {
    xdc_SizeT maxDefaultTypeAlign;
} xdc_runtime_Memory_Module_State__;

/* Module__state__V */
xdc_runtime_Memory_Module_State__ xdc_runtime_Memory_Module__state__V;


/*
 * ======== xdc.runtime.Memory_HeapProxy DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Registry DECLARATIONS ========
 */

/* Module_State__ */
typedef struct xdc_runtime_Registry_Module_State__ {
    xdc_runtime_Registry_Desc* listHead;
    xdc_runtime_Types_ModuleId curId;
} xdc_runtime_Registry_Module_State__;

/* Module__state__V */
xdc_runtime_Registry_Module_State__ xdc_runtime_Registry_Module__state__V;


/*
 * ======== xdc.runtime.Startup DECLARATIONS ========
 */

/* Module_State__ */
typedef struct xdc_runtime_Startup_Module_State__ {
    xdc_Int* stateTab;
    xdc_Bool execFlag;
    xdc_Bool rtsDoneFlag;
} xdc_runtime_Startup_Module_State__;

/* Module__state__V */
xdc_runtime_Startup_Module_State__ xdc_runtime_Startup_Module__state__V;

/* --> xdc_runtime_System_Module_startup__E */
extern xdc_Int xdc_runtime_System_Module_startup__E(xdc_Int);

/* --> ti_sdo_xdcruntime_linux_GateThreadSupport_Module_startup__E */
extern xdc_Int ti_sdo_xdcruntime_linux_GateThreadSupport_Module_startup__E(xdc_Int);

/* --> ti_sdo_xdcruntime_linux_SemThreadSupport_Module_startup__E */
extern xdc_Int ti_sdo_xdcruntime_linux_SemThreadSupport_Module_startup__E(xdc_Int);

/* --> ti_sdo_xdcruntime_linux_SemProcessSupport_Module_startup__E */
extern xdc_Int ti_sdo_xdcruntime_linux_SemProcessSupport_Module_startup__E(xdc_Int);

/* --> ti_sdo_xdcruntime_linux_ThreadSupport_Module_startup__E */
extern xdc_Int ti_sdo_xdcruntime_linux_ThreadSupport_Module_startup__E(xdc_Int);

/* --> ti_sdo_utils_loggers_LoggerSysTID_Module_startup__E */
extern xdc_Int ti_sdo_utils_loggers_LoggerSysTID_Module_startup__E(xdc_Int);

/* --> xdc_runtime_Startup_sfxnTab__A */
const __T1_xdc_runtime_Startup_sfxnTab xdc_runtime_Startup_sfxnTab__A[6];

/* --> xdc_runtime_Startup_sfxnRts__A */
const __T1_xdc_runtime_Startup_sfxnRts xdc_runtime_Startup_sfxnRts__A[6];


/*
 * ======== xdc.runtime.SysStd DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.System DECLARATIONS ========
 */

/* Module_State__ */
typedef struct xdc_runtime_System_Module_State__ {
    __TA_xdc_runtime_System_Module_State__atexitHandlers atexitHandlers;
    xdc_Int numAtexitHandlers;
    xdc_Int exitStatus;
} xdc_runtime_System_Module_State__;

/* --> xdc_runtime_System_Module_State_0_atexitHandlers__A */
__T1_xdc_runtime_System_Module_State__atexitHandlers xdc_runtime_System_Module_State_0_atexitHandlers__A[8];

/* Module__state__V */
xdc_runtime_System_Module_State__ xdc_runtime_System_Module__state__V;

/* --> xdc_runtime_System_printfExtend__I */
extern xdc_Int xdc_runtime_System_printfExtend__I(xdc_Char**,xdc_Char**,xdc_VaList*,xdc_runtime_System_ParseData*);


/*
 * ======== xdc.runtime.System_Module_GateProxy DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.System_SupportProxy DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Text DECLARATIONS ========
 */

/* Module_State__ */
typedef struct xdc_runtime_Text_Module_State__ {
    xdc_Ptr charBase;
    xdc_Ptr nodeBase;
} xdc_runtime_Text_Module_State__;

/* Module__state__V */
xdc_runtime_Text_Module_State__ xdc_runtime_Text_Module__state__V;

/* --> xdc_runtime_Text_charTab__A */
const __T1_xdc_runtime_Text_charTab xdc_runtime_Text_charTab__A[1970];

/* --> xdc_runtime_Text_nodeTab__A */
const __T1_xdc_runtime_Text_nodeTab xdc_runtime_Text_nodeTab__A[36];


/*
 * ======== xdc.runtime.Timestamp DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.Timestamp_SupportProxy DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.knl.GateThread DECLARATIONS ========
 */

/* Object__table__V */
xdc_runtime_knl_GateThread_Object__ xdc_runtime_knl_GateThread_Object__table__V[1];


/*
 * ======== xdc.runtime.knl.GateThread_Proxy DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.knl.SemProcess DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.knl.SemProcess_Proxy DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.knl.SemThread DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.knl.SemThread_Proxy DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.knl.Thread DECLARATIONS ========
 */


/*
 * ======== xdc.runtime.knl.Thread_Proxy DECLARATIONS ========
 */


/*
 * ======== xdc.cfg.Program TEMPLATE ========
 */

/*
 *  ======== __ASM__ ========
 *  Define absolute path to program's assembly directory
 */
xdc__META(__ASM__, "@(#)__ASM__ = /mnt/hgfs/D/code/20131028_TPS/Professional_VOB/t1-uranus/mpu2/prjlinux/test_config/package/cfg/81xxApp_xv7A");

/*
 *  ======== __ISA__ ========
 *  Define the ISA of this executable.  This symbol is used by platform
 *  specific "exec" commands that support more than one ISA; e.g., gdb
 */
xdc__META(__ISA__, "@(#)__ISA__ = v7A");

/*
 *  ======== __PLAT__ ========
 *  Define the name of the platform that can run this executable.  This
 *  symbol is used by platform independent "exec" commands
 */
xdc__META(__PLAT__, "@(#)__PLAT__ = ti.platforms.evmTI816X");

/*
 *  ======== __TARG__ ========
 *  Define the name of the target used to build this executable.
 */
xdc__META(__TARG__, "@(#)__TARG__ = gnu.targets.arm.GCArmv7A");


/*
 * ======== xdc.runtime.Diags TEMPLATE ========
 */

xdc_runtime_Diags_DictElem xdc_runtime_Diags_dictElems[] = {
    {32777, &xdc_runtime_Main_Module__root__V.mask},
    {32780, &xdc_runtime_Registry_Module__root__V.mask},
    {0, 0}
};


/*
 * ======== xdc.runtime.Startup TEMPLATE ========
 */

/*
 *  ======== MODULE STARTUP DONE FUNCTIONS ========
 */
xdc_Bool xdc_runtime_System_Module__startupDone__F(void) {
    return (&xdc_runtime_Startup_Module__state__V)->stateTab == 0 || (&xdc_runtime_Startup_Module__state__V)->stateTab[0] < 0;
}
xdc_Bool ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDone__F(void) {
    return (&xdc_runtime_Startup_Module__state__V)->stateTab == 0 || (&xdc_runtime_Startup_Module__state__V)->stateTab[1] < 0;
}
xdc_Bool ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDone__F(void) {
    return (&xdc_runtime_Startup_Module__state__V)->stateTab == 0 || (&xdc_runtime_Startup_Module__state__V)->stateTab[2] < 0;
}
xdc_Bool ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDone__F(void) {
    return (&xdc_runtime_Startup_Module__state__V)->stateTab == 0 || (&xdc_runtime_Startup_Module__state__V)->stateTab[3] < 0;
}
xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDone__F(void) {
    return (&xdc_runtime_Startup_Module__state__V)->stateTab == 0 || (&xdc_runtime_Startup_Module__state__V)->stateTab[4] < 0;
}
xdc_Bool ti_sdo_utils_loggers_LoggerSysTID_Module__startupDone__F(void) {
    return (&xdc_runtime_Startup_Module__state__V)->stateTab == 0 || (&xdc_runtime_Startup_Module__state__V)->stateTab[5] < 0;
}

/* 
 * Startup_exec__I is an internal entry point called by target/platform
 * boot code. Boot code is not brought into a partial-link assembly. So,
 * without this pragma, whole program optimizers would otherwise optimize-out
 * this function.
 */
#ifdef __ti__
#pragma FUNC_EXT_CALLED(xdc_runtime_Startup_exec__I);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
xdc_Void xdc_runtime_Startup_exec__I(void) __attribute__ ((externally_visible));
#endif
#endif

/*
 *  ======== xdc_runtime_Startup_exec__I ========
 *  Initialize all used modules that have startup functions
 */
xdc_Void xdc_runtime_Startup_exec__I(void)
{
    xdc_Int state[6];
    xdc_runtime_Startup_startModsFxn__C(state, 6);
}

/*
 * ======== xdc.runtime.Reset TEMPLATE ========
 */

/* 
 * Startup_reset__I is an internal entry point called by target/platform
 * boot code. Boot code is not brought into a partial-link assembly. So,
 * without this pragma, whole program optimizers would otherwise optimize-out
 * this function.
 */
#ifdef __ti__
#pragma FUNC_EXT_CALLED(xdc_runtime_Startup_reset__I);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
xdc_Void xdc_runtime_Startup_reset__I(void) __attribute__ ((externally_visible));
#endif
#endif


/*
 *  ======== xdc_runtime_Startup_reset__I ========
 *  This function is called by bootstrap initialization code as early as
 *  possible in the startup process.  This function calls all functions in
 *  the Reset.fxns array _as well as_ Startup.resetFxn (if it's non-NULL)
 */
xdc_Void xdc_runtime_Startup_reset__I(void)
{
}

/*
 * ======== xdc.runtime.System TEMPLATE ========
 */


#include <xdc/std.h>
#include <limits.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Text.h>
#include <xdc/runtime/Assert.h>

/*
 *  ======== System_printfExtend__I ========
 *  This function processes optional extended formats of printf.
 *  
 *  It returns the number of characters added to the result.
 *
 *  Precision (maximum string length) is not supported for %$S.
 *
 *  Right-justified (which is default) minimum width is not supported
 *  for %$L, %$S, or %$F.
 */
Int xdc_runtime_System_printfExtend__I(Char **pbuf, Char **pfmt, 
    VaList *pva, xdc_runtime_System_ParseData *parse)
{
    Char    *fmt = *pfmt;
    Int     res;
    Char    c;
    Bool    found = FALSE;
    
    /* 
     * Create a local variable 'va' to ensure that the dereference of
     * pva only occurs once.
     */
    va_list va = *pva;
    
    res = 0;

    c = *fmt++;
    *pfmt = *pfmt + 1;

    
    if (c == '$') {
        c = *fmt++;
        *pfmt = *pfmt + 1;
        
        if (c == 'L') {
            xdc_runtime_Types_Label *lab = parse->aFlag ? 
                (xdc_runtime_Types_Label *)iargToPtr(va_arg(va, IArg)) :
                (xdc_runtime_Types_Label *)va_arg(va, void *);
            
            /* 
             * Call Text_putLab to write out the label, taking the precision 
             * into account.
             */
            res = xdc_runtime_Text_putLab(lab, pbuf, parse->precis);
            
            /*
             * Set the length to 0 to indicate to 'doPrint' that nothing should
             * be copied from parse.ptr.
             */
            parse->len = 0;
            
            /* Update the minimum width field. */
            parse->width -= res;
            
            found = TRUE;
        }
        
        if (c == 'F') {
            xdc_runtime_Types_Site site;
            
            /* Retrieve the file name string from the argument list */
            site.file = parse->aFlag ? (Char *) iargToPtr(va_arg(va, IArg)) :
                                       (Char *) va_arg(va, Char *);
            
            /* Retrieve the line number from the argument list. */
            site.line = parse->aFlag ? (Int) va_arg(va, IArg) : 
                                       (Int) va_arg(va, Int);
            
            /* 
             * Omit the 'mod' field, set it to 0.
             * '0' is a safe sentinel value - the IDs for named modules are 
             * 0x8000 and higher, and the IDs for unnamed modules go from 0x1
             * to 0x7fff.
             */
            site.mod = 0;
            
            /* 
             * Call putSite to format the file and line number.
             * If a precision was specified, it will be used as the maximum
             * string lengrth.
             */
            res = xdc_runtime_Text_putSite(&site, pbuf, parse->precis);
            
            /*
             * Set the length to 0 to indicate to 'doPrint' that nothing should
             * be copied from parse.ptr.
             */
            parse->len = 0;
       
            /* Update the minimum width field */
            parse->width -= res;
            
            found = TRUE;
        }
        
        if (c == 'S') {
            /* Retrieve the format string from the argument list */
            parse->ptr = parse->aFlag ? 
                (Char *) iargToPtr(va_arg(va, IArg)) :
                (Char *) va_arg(va, Char *);
            
            /* Update pva before passing it to doPrint. */
            *pva = va;
            
            /* Perform the recursive format. */
            res = xdc_runtime_System_doPrint__I(*pbuf, parse->ptr, pva, parse->aFlag);
            
            /* Update the temporary variable with any changes to *pva */
            va = *pva;
            
            /*
             * Set the length to 0 to indicate to 'doPrint' that nothing should
             * be copied from parse.ptr.
             */
            parse->len = 0;

            /* Update the minimum width field */
            parse->width -= res;
            
            /* Indicate that we were able to interperet the specifier. */
            found = TRUE;
        }
        
    }


    if (found == FALSE) {
        /* other character (like %) copy to output */
        *(parse->ptr) = c;
        parse->len = 1;
    }

    /*
     * Before returning, we must update the value of pva. We use a label here
     * so that all return points will go through this update.
     * The 'goto end' is here to ensure that there is always a reference to the
     * label (to avoid the compiler complaining). 
     */
    goto end; 
end:
    *pva = va;
    return (res);
}



/*
 * ======== xdc.runtime.Text TEMPLATE ========
 */


/*
 *  ======== xdc_runtime_Text_visitRope__I ========
 *  This function is indirectly called within Text.c through
 *  the visitRopeFxn configuration parameter of xdc.runtime.Text.
 */
Void xdc_runtime_Text_visitRope__I(xdc_runtime_Text_RopeId rope,
    xdc_Fxn visFxn, xdc_Ptr visState)
{
    xdc_String stack[5];
    xdc_runtime_Text_visitRope2__I(rope, visFxn, visState, stack);
}


/*
 * ======== ti.sdo.ce.osal.Global TEMPLATE ========
 */



/*
 *  ======== Global Configuration ========
 *  Do not modify the following; it is automatically generated from the template
 *  Server.xdt in the ti.sdo.ce package and will be overwritten next time the
 *  executable is configured
 */

Bool Memory_skipVirtualAddressTranslation = FALSE;


/* List of all packages and their versions and paths, for diagnostics */
String Global_buildInfo[] = {
    "    package ti.syslink (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/syslink_02_00_00_67_whole/ti/syslink/) [1, 0, 0, 0]",
    "    package ti.sdo.ce.global (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/codec-engine_3_21_00_10/packages/ti/sdo/ce/global/) [1, 0, 0]",
    "    package ti.xdais.dm (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdais_7_21_00_01/packages/ti/xdais/dm/) [1, 0, 7]",
    "    package ti.sdo.ce.utils.xdm (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/codec-engine_3_21_00_10/packages/ti/sdo/ce/utils/xdm/) [1, 0, 2]",
    "    package ti.xdais (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdais_7_21_00_01/packages/ti/xdais/) [1, 2.0, 1]",
    "    package ti.sdo.fc.global (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/framework-components_3_21_00_13/packages/ti/sdo/fc/global/) [1, 0, 0]",
    "    package gnu.targets (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdctools_3_20_07_86/packages/gnu/targets/) [1, 0, 1]",
    "    package gnu.targets.arm (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdctools_3_20_07_86/packages/gnu/targets/arm/) [1, 0, 0, 0]",
    "    package ti.sdo.linuxutils.cmem (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/linuxutils_3_21_00_02/packages/ti/sdo/linuxutils/cmem/) [2, 2, 0]",
    "    package ti.catalog.arm.cortexa8 (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdctools_3_20_07_86/packages/ti/catalog/arm/cortexa8/) [1, 0, 0]",
    "    package ti.catalog.peripherals.hdvicp2 (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdctools_3_20_07_86/packages/ti/catalog/peripherals/hdvicp2/) []",
    "    package ti.catalog (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdctools_3_20_07_86/packages/ti/catalog/) [1, 0, 0]",
    "    package ti.catalog.c6000 (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdctools_3_20_07_86/packages/ti/catalog/c6000/) [1, 0, 0, 0]",
    "    package ti.catalog.arm.peripherals.timers (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdctools_3_20_07_86/packages/ti/catalog/arm/peripherals/timers/) []",
    "    package ti.catalog.arm.cortexm3 (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdctools_3_20_07_86/packages/ti/catalog/arm/cortexm3/) [1, 0, 0]",
    "    package ti.platforms.evmTI816X (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdctools_3_20_07_86/packages/ti/platforms/evmTI816X/) [1, 0, 0]",
    "    package gnu.targets.arm.rtsv7A (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/xdctools_3_20_07_86/packages/gnu/targets/arm/rtsv7A/) [1, 0, 0, 0]",
    "    package ti.sdo.xdcruntime.linux (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/osal_1_21_00_05/packages/ti/sdo/xdcruntime/linux/) [1, 0, 0]",
    "    package ti.sdo.utils.loggers (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/osal_1_21_00_05/packages/ti/sdo/utils/loggers/) [1, 0, 0]",
    "    package ti.sdo.ce.node (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/codec-engine_3_21_00_10/packages/ti/sdo/ce/node/) [1, 0, 0]",
    "    package ti.sdo.ce.osal.linux (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/codec-engine_3_21_00_10/packages/ti/sdo/ce/osal/linux/) [2, 0, 1]",
    "    package ti.sdo.ce.ipc.dsplink (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/codec-engine_3_21_00_10/packages/ti/sdo/ce/ipc/dsplink/) [2, 0, 1]",
    "    package ti.sdo.ce.ipc (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/codec-engine_3_21_00_10/packages/ti/sdo/ce/ipc/) [2, 0, 1]",
    "    package ti.sdo.ce.osal (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/codec-engine_3_21_00_10/packages/ti/sdo/ce/osal/) [2, 0, 2]",
    "    package ti.sdo.ce.alg (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/codec-engine_3_21_00_10/packages/ti/sdo/ce/alg/) [1, 0, 1]",
    "    package ti.sdo.ce (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/codec-engine_3_21_00_10/packages/ti/sdo/ce/) [1, 0, 6]",
    "    package ti.sdo.ce.audio (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/codec-engine_3_21_00_10/packages/ti/sdo/ce/audio/) [1, 0, 2]",
    "    package codecs.audproc_codec (/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/10-common/lib/release/devm_ti816x/codecs/audproc_codec/) [1, 0, 0]",
    "    package codecs.audsaec_codec (/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/10-common/lib/release/devm_ti816x/codecs/audsaec_codec/) [1, 0, 0]",
    "    package codecs.audmix_codec (/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/10-common/lib/release/devm_ti816x/codecs/audmix_codec/) [1, 0, 0]",
    "    package codecs.audaec_codec (/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/10-common/lib/release/devm_ti816x/codecs/audaec_codec/) [1, 0, 0]",
    "    package codecs.auddec_codec (/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/10-common/lib/release/devm_ti816x/codecs/auddec_codec/) [1, 0, 0]",
    "    package codecs.audenc_codec (/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/10-common/lib/release/devm_ti816x/codecs/audenc_codec/) [1, 0, 0]",
    "    package ti.sdo.ce.video (/opt/ti-ezsdk_dm816x-evm_5_00_00_11/codec-engine_3_21_00_10/packages/ti/sdo/ce/video/) [1, 0, 3]",
    "    package codecs.viddec_codec (/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/10-common/lib/release/devm_ti816x/codecs/viddec_codec/) [1, 0, 0]",
    "    package codecs.videnc_codec (/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/10-common/lib/release/devm_ti816x/codecs/videnc_codec/) [1, 0, 0]",
    "    package codecs.imgproc_codec (/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/10-common/lib/release/devm_ti816x/codecs/imgproc_codec/) [1, 0, 0]",
    "    package test_config (/mnt/hgfs/D/code/20131028_TPS/Professional_VOB/t1-uranus/mpu2/prjlinux/test_config/) []",
    NULL
};

/*
 * ======== ti.sdo.ce.osal.linux.Settings TEMPLATE ========
 */


UInt32 Memory_maxCbListSize = 100;


/*
 * ======== ti.sdo.ce.ipc.Settings TEMPLATE ========
 */


/*
 * ======== ti.sdo.ce.ipc.dsplink.Ipc TEMPLATE ========
 */


/* Max timeout for MSGQ_get() allowed. */
UInt32 ti_sdo_ce_ipc_dsplink_Ipc_maxTimeout = 4294967295UL;

Void IPC_generatedInit()
{
}

/* configuration for interprocessor communication */

/* size of the communication message */
UInt32 Comm_MSGSIZE = 4096;

/* number of Comm_MSGSIZE-sized messages in the system */
UInt32 Comm_NUMMSGS = 64;

/* configure number of retries Comm_locate should do before giving up */
UInt32 Comm_LOCATERETRIES = 20;


/* Arm-side DSPLINK configuration
 * ==============================
 */

#include <ti/sdo/ce/osal/Global.h>

/* Arm-side DspLink configuration tables { */

Int Global_useLinkArbiter = FALSE;

Int LAD_connect(String clientName, Int * id) { return 0; }
Int LAD_disconnect(Int id) { return 0; }
Int LAD_getDspStatus(Int cpuId, Int * statusInfo) { return 0; }
Int LAD_releaseDsp(Int id) { return 0; }
Int LAD_startupDsp(Int id, Int cpuId, Int linkId, String image) { return 0; }


Void Power_init() {}
Int Power_on(Ptr handle) { return 0; }
Int Power_off(Ptr handle) { return 0; }
Int Power_connect(Ptr handle) { return 0; }
Int Power_disconnect(Ptr handle) { return 0; }


/*
 * ======== ti.sdo.ce.ipc.dsplink.Processor TEMPLATE ========
 */


#include <ti/sdo/ce/ipc/Processor.h>

Int16 ti_sdo_ce_ipc_dsplink__Processor_defaultSharedRegionId = 1;
Int16 ti_sdo_ce_ipc_dsplink__Processor_defaultHeapId = 0;
Int32 ti_sdo_ce_ipc_dsplink__Processor_defaultNumMsgs = 64;
Int32 ti_sdo_ce_ipc_dsplink__Processor_defaultMsgSize = 4096;

Processor_CommDesc ti_sdo_ce_ipc_dsplink__Processor_commDescs[] = {
    {
	-1,			/* numMsgs */
	-1,			/* msgSize */
	-1,			/* sharedRegionId */
	-1,			/* heapId */
	FALSE,			/* userCreatedHeap */
    }
};

UInt32 ti_sdo_ce_ipc_dsplink__Processor_numCommDescs = 1;


/*
 * ======== ti.sdo.ce.Engine TEMPLATE ========
 */

/*
 *  ======== Engine Configuration ========
 *  Do not modify following; it is automatically generated from the template
 *  Engine.xdt in the ti.sdo.ce package and will be overwritten next time the
 *  executable is configured
 */
#include <ti/sdo/ce/Engine.h>
#include <ti/xdais/ialg.h>

#include <ti/xdais/idma3.h>

#include <ti/xdais/ires.h>

/* type tables for algorithms */
extern IALG_Fxns AUDSAEC_KDC;
static String typeTab_AUDSAEC_KDC[] = {
    "ti.sdo.ce.audio.IAUDENC",
    NULL
};

extern IALG_Fxns AUDAEC_KDC;
static String typeTab_AUDAEC_KDC[] = {
    "ti.sdo.ce.audio.IAUDENC",
    NULL
};

extern IALG_Fxns AUDPROC_KDC;
static String typeTab_AUDPROC_KDC[] = {
    "ti.sdo.ce.audio.IAUDENC",
    NULL
};

extern IALG_Fxns AUDENC_KDC;
static String typeTab_AUDENC_KDC[] = {
    "ti.sdo.ce.audio.IAUDENC",
    NULL
};

extern IALG_Fxns VIDDEC_KDC;
static String typeTab_VIDDEC_KDC[] = {
    "ti.sdo.ce.video.IVIDDEC",
    NULL
};

extern IALG_Fxns AUDMIX_KDC;
static String typeTab_AUDMIX_KDC[] = {
    "ti.sdo.ce.audio.IAUDENC",
    NULL
};

extern IALG_Fxns VIDIMAGEPRO_KDC_IMAGEDEC;
static String typeTab_VIDIMAGEPRO_KDC_IMAGEDEC[] = {
    "ti.sdo.ce.video.IVIDDEC",
    NULL
};

extern IALG_Fxns AUDDEC_KDC;
static String typeTab_AUDDEC_KDC[] = {
    "ti.sdo.ce.audio.IAUDDEC",
    NULL
};

extern IALG_Fxns VIDENC_KDC;
static String typeTab_VIDENC_KDC[] = {
    "ti.sdo.ce.video.IVIDENC",
    NULL
};


/* tables of engine algorithms */
extern IALG_Fxns AUDENC_STUBS;
extern IALG_Fxns AUDENC_STUBS;
extern IALG_Fxns AUDENC_STUBS;
extern IALG_Fxns AUDENC_STUBS;
extern IALG_Fxns AUDDEC_STUBS;
extern IALG_Fxns AUDENC_STUBS;
extern IALG_Fxns VIDDEC_STUBS;
extern IALG_Fxns VIDENC_STUBS;
extern IALG_Fxns VIDDEC_STUBS;

/* algorithm-specific stub/skeleton config data objects */
extern struct codecs_viddec_codec_VIDDEC_KDC_CodecClassConfig codecs_viddec_codec_VIDDEC_KDC_codecClassConfig;
extern struct codecs_videnc_codec_VIDENC_KDC_CodecClassConfig codecs_videnc_codec_VIDENC_KDC_codecClassConfig;
extern struct codecs_imgproc_codec_IMGPROC_CODEC_CodecClassConfig codecs_imgproc_codec_IMGPROC_CODEC_codecClassConfig;

static Engine_AlgDesc engineAlgs0[] = {
    {
        "audproc",       /* name */
        {304U},   /* uuid */
        &AUDENC_STUBS,             /* fxns */
        NULL,        /* idma3Fxns */
        typeTab_AUDPROC_KDC,              /* typeTab */
        FALSE,          /* isLocal */
        2,        /* groupId */
        3,      /* protocol */
        NULL,         /* iresFxns */
        NULL,               /* stub/skel config params  */
        Engine_USECACHEDMEM_DEFAULT,    /* memType */
        "ti.sdo.ce.audio.IAUDENC",
    },
    {
        "audsaec",       /* name */
        {305U},   /* uuid */
        &AUDENC_STUBS,             /* fxns */
        NULL,        /* idma3Fxns */
        typeTab_AUDSAEC_KDC,              /* typeTab */
        FALSE,          /* isLocal */
        2,        /* groupId */
        3,      /* protocol */
        NULL,         /* iresFxns */
        NULL,               /* stub/skel config params  */
        Engine_USECACHEDMEM_DEFAULT,    /* memType */
        "ti.sdo.ce.audio.IAUDENC",
    },
    {
        "audmix",       /* name */
        {303U},   /* uuid */
        &AUDENC_STUBS,             /* fxns */
        NULL,        /* idma3Fxns */
        typeTab_AUDMIX_KDC,              /* typeTab */
        FALSE,          /* isLocal */
        2,        /* groupId */
        3,      /* protocol */
        NULL,         /* iresFxns */
        NULL,               /* stub/skel config params  */
        Engine_USECACHEDMEM_DEFAULT,    /* memType */
        "ti.sdo.ce.audio.IAUDENC",
    },
    {
        "audaec",       /* name */
        {300U},   /* uuid */
        &AUDENC_STUBS,             /* fxns */
        NULL,        /* idma3Fxns */
        typeTab_AUDAEC_KDC,              /* typeTab */
        FALSE,          /* isLocal */
        2,        /* groupId */
        3,      /* protocol */
        NULL,         /* iresFxns */
        NULL,               /* stub/skel config params  */
        Engine_USECACHEDMEM_DEFAULT,    /* memType */
        "ti.sdo.ce.audio.IAUDENC",
    },
    {
        "auddec",       /* name */
        {301U},   /* uuid */
        &AUDDEC_STUBS,             /* fxns */
        NULL,        /* idma3Fxns */
        typeTab_AUDDEC_KDC,              /* typeTab */
        FALSE,          /* isLocal */
        2,        /* groupId */
        3,      /* protocol */
        NULL,         /* iresFxns */
        NULL,               /* stub/skel config params  */
        Engine_USECACHEDMEM_DEFAULT,    /* memType */
        "ti.sdo.ce.audio.IAUDDEC",
    },
    {
        "audenc",       /* name */
        {302U},   /* uuid */
        &AUDENC_STUBS,             /* fxns */
        NULL,        /* idma3Fxns */
        typeTab_AUDENC_KDC,              /* typeTab */
        FALSE,          /* isLocal */
        2,        /* groupId */
        3,      /* protocol */
        NULL,         /* iresFxns */
        NULL,               /* stub/skel config params  */
        Engine_USECACHEDMEM_DEFAULT,    /* memType */
        "ti.sdo.ce.audio.IAUDENC",
    },
    {
        "viddec_all",       /* name */
        {200U},   /* uuid */
        &VIDDEC_STUBS,             /* fxns */
        NULL,        /* idma3Fxns */
        typeTab_VIDDEC_KDC,              /* typeTab */
        FALSE,          /* isLocal */
        2,        /* groupId */
        3,      /* protocol */
        NULL,         /* iresFxns */
        &codecs_viddec_codec_VIDDEC_KDC_codecClassConfig, /* stub/skel config params */
        Engine_USECACHEDMEM_DEFAULT,    /* memType */
        "ti.sdo.ce.video.IVIDDEC",
    },
    {
        "videnc",       /* name */
        {201U},   /* uuid */
        &VIDENC_STUBS,             /* fxns */
        NULL,        /* idma3Fxns */
        typeTab_VIDENC_KDC,              /* typeTab */
        FALSE,          /* isLocal */
        2,        /* groupId */
        3,      /* protocol */
        NULL,         /* iresFxns */
        &codecs_videnc_codec_VIDENC_KDC_codecClassConfig, /* stub/skel config params */
        Engine_USECACHEDMEM_DEFAULT,    /* memType */
        "ti.sdo.ce.video.IVIDENC",
    },
    {
        "imgproc",       /* name */
        {204U},   /* uuid */
        &VIDDEC_STUBS,             /* fxns */
        NULL,        /* idma3Fxns */
        typeTab_VIDIMAGEPRO_KDC_IMAGEDEC,              /* typeTab */
        FALSE,          /* isLocal */
        2,        /* groupId */
        3,      /* protocol */
        NULL,         /* iresFxns */
        &codecs_imgproc_codec_IMGPROC_CODEC_codecClassConfig, /* stub/skel config params */
        Engine_USECACHEDMEM_DEFAULT,    /* memType */
        "ti.sdo.ce.video.IVIDDEC",
    },
    {NULL},
};
static Engine_AlgDesc engineAlgs1[] = {
    {NULL},
};

/* table of all engines available in this application */
static Engine_Desc engineTab[] = {
    {"ti816x",	/* engine name */
      engineAlgs0,	/* alg table */
      "ti816x.xe674",		/* (optional) server name */
      NULL,        /* (optional) Link config ID */
      9,    /* number of algs in alg table */
      0          /* (optional) heap ID for eng allocs */
    },
    {"local",	/* engine name */
      engineAlgs1,	/* alg table */
      NULL,		/* (optional) server name */
      NULL,        /* (optional) Link config ID */
      0,    /* number of algs in alg table */
      0          /* (optional) heap ID for eng allocs */
    },
    {NULL, NULL, NULL, 0}	/* NULL-terminate the engine table */
};

Engine_Config Engine_config = {
    engineTab,		    /* table of all engines */
    "local"   /* local RMS engine name */
};

Bool ti_sdo_ce_Engine_initFromServer = TRUE;

/*
 * ======== ti.sdo.ce.CERuntime TEMPLATE ========
 */


#include <xdc/std.h>
#include <xdc/runtime/Diags.h>

#include <ti/sdo/ce/global/CESettings.h>
#include <ti/sdo/fc/global/FCSettings.h>

#include <ti/sdo/ce/osal/Global.h>
#include <ti/sdo/ce/ipc/Comm.h>
#include <ti/sdo/ce/osal/Loader.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Queue.h>
#include <ti/sdo/ce/osal/Trace.h>
#include <ti/sdo/ce/ipc/Processor.h>
#include <ti/sdo/ce/alg/Algorithm.h>
#include <ti/sdo/ce/Server.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/rms.h>
#include <ti/sdo/ce/utils/xdm/XdmUtils.h>


#ifdef __ti__
    #pragma FUNC_EXT_CALLED(CERuntime_init);
    #pragma FUNC_EXT_CALLED(CERuntime_exit);
#endif

/*
 *  ======== CERuntime_init ========
 */
Void CERuntime_init(Void)
{
    extern Void IPC_generatedInit();

    CESettings_init();
    FCSettings_init();


    /* if CE_DEBUG is set, turn on tracing and DSP auto trace collection */
    if (Global_getenv("CE_DEBUG") != NULL) {
        extern Bool   Engine_alwaysCollectDspTrace;
        extern String Engine_ceDebugDspTraceMask;

        Engine_alwaysCollectDspTrace = TRUE;

        /*
         * Note the strategy for setting trace masks below...
         * For any mods not yet registered, we set the
         * [FC|CE]SETTINGS_MODNAME mask.  For any mods already
         * registered, we Diags_setMask() them.
         */

        if (Global_getenv("CE_DEBUG")[0] == '1') {
            /* Turn on CE/FC levels 6 and 7 */
            xdc_runtime_Diags_setMask(CESETTINGS_MODNAME"+67");
            xdc_runtime_Diags_setMask(FCSETTINGS_MODNAME"+67");
            xdc_runtime_Diags_setMask("ti.sdo.ce.%+67");
            xdc_runtime_Diags_setMask("ti.sdo.fc.%+67");

            /* Same for any Servers */
            Engine_ceDebugDspTraceMask = "ti.sdo.ce.%+67;ti.sdo.fc.%+67";
        }
        else if (Global_getenv("CE_DEBUG")[0] == '2') {
            //GT_set(
            //    "*+01234567,CE-3,ti.sdo.ce.osal.SemMP=67,OG=467,OM=4567,OC=67,GT_time=0,GT_prefix=1235");
            // * -> ti.sdo.ce.%, ti.sdo.fc.%
            xdc_runtime_Diags_setMask(CESETTINGS_MODNAME"+EX1234567");
            xdc_runtime_Diags_setMask(FCSETTINGS_MODNAME"+EX1234567");
            xdc_runtime_Diags_setMask("ti.sdo.ce.%+EX1234567");
            xdc_runtime_Diags_setMask("ti.sdo.fc.%+EX1234567");

            // OG, OM, SemMP -> ti.sdo.xdcruntime.linux
            xdc_runtime_Diags_setMask("ti.sdo.xdcruntime.linux.%+EX1234567");

            Engine_ceDebugDspTraceMask =
                // Former GT mask:
                //"*+01234567,CR=67,ti.sdo.fc.dman3-2,ti.sdo.fc.dskt2-2,GT_prefix=1235,GT_time=3";
                // Current Diags mask: (time=2 ==> display time in delta usec
                "ti.sdo.ce.%+EX1234567;ti.sdo.fc.%+EX12345678;ti.sdo.ce.rms=67;ti.sdo.fc.dman3-2;ti.sdo.fc.dskt2-2;time=2";
        }
        else if (Global_getenv("CE_DEBUG")[0] == '0') {
            /* Don't set anything if someone tries to turn CE_DEBUG off */
        } else {
            //GT_set("*+01234567,CE-3,GT_time=0,GT_prefix=12345");
            xdc_runtime_Diags_setMask("ti.sdo.ce.%+EX1234567");
            xdc_runtime_Diags_setMask("ti.sdo.fc.%+EX1234567");
            //TEMP (jeh) xdc_runtime_Diags_setMask("ti.sdo.ce.Engine-3");
            xdc_runtime_Diags_setMask("ti.sdo.xdcruntime.linux.%+EX1234567");

            //Engine_ceDebugDspTraceMask = "*+01234567,GT_prefix=12345,GT_time=3";
            Engine_ceDebugDspTraceMask =
                "time=2;ti.sdo.fc.%+EX1234567;ti.sdo.ce.%+EX1234567;ti.sdo.fc.dskt2-2";
        }
    }
    else {
        //xdc_runtime_Diags_setMask("ti.sdo.ce.Engine-EX1234567");
        //xdc_runtime_Diags_setMask("ti.sdo.ce.VISA-EX1234567");
    }

    if (Global_getenv("CE_CHECK") != NULL) {
        extern Bool VISA_checked;

        /*
         * Currently just change _this_ processor's value... perhaps we should
         * enable remote processors as well?
         */
        if (Global_getenv("CE_CHECK")[0] == '1') {
            VISA_checked = TRUE;
            xdc_runtime_Diags_setMask("ti.sdo.ce.%+7");
        } else if (Global_getenv("CE_CHECK")[0] == '0') {
            VISA_checked = FALSE;
        } else {
            /* leave it whatever it was... maybe we should drop a warning? */
        }
    }

    /* allow user to over-ride via CE_TRACE. */
    if (Global_getenv("CE_TRACE") != NULL) {
        xdc_runtime_Diags_setMask(Global_getenv("CE_TRACE"));
    }
//% print("CERuntime.xdt: Engine.hasServer() = " + Engine.hasServer() +
//%       " Server.$used = " + Server.$used);
    IPC_generatedInit();
    Global_init();


    ti_sdo_ce_osal_Memory_init();
    Comm_init();
    Processor_init();
    Algorithm_init();
    XdmUtils_init();

    Engine_init();
    _VISA_init();
    Loader_init();
    Server_init();
    if ((Global_getenv("CE_DEBUG") != NULL) &&
        (Global_getenv("CE_DEBUG")[0] == '2')) {

        /* set up masks that must be deferred until the modules have been init'd */
        //    "*+01234567,CE-3,ti.sdo.ce.osal.SemMP=67,OG=467,OM=4567,OC=67,GT_time=0,GT_prefix=1235");
        //xdc_runtime_Diags_setMask(Comm_MODNAME"-EX12345");
        xdc_runtime_Diags_setMask("ti.sdo.ce.osal.%-EX123");
        //xdc_runtime_Diags_setMask(Algorithm_MODNAME"-EX12345");

        // CE-3 -> ti.sdo.ce.Engine-3
        xdc_runtime_Diags_setMask("ti.sdo.ce.Engine-3");

        // OC=67 -> ti.sdo.ce.ipc.Comm=67
        xdc_runtime_Diags_setMask("ti.sdo.ce.ipc.Comm=67");
    }

}

/*
 *  ======== CERuntime_exit ========
 */
Void CERuntime_exit(Void)
{
    Global_exit();
}

/* for backward compatibility with xdc-m based tools */
Void ti_sdo_ce_CERuntime_init__F(Void) {
    CERuntime_init();
}

/*
 * ======== ti.sdo.ce.Settings TEMPLATE ========
 */

/*
 *  ======== ti.sdo.ce Settings Configuration ========
 *  Do not modify following; it is automatically generated from the template
 *  Settings.xdt in the ti.sdo.ce package and will be overwritten next time the
 *  executable is configured
 */
Bool VISA_checked = FALSE;

/*
 * ======== ti.sdo.ce.video.VIDENCConfig TEMPLATE ========
 */


/* this data structure has codec-specific names and values, but class-specific
 * fields -- it's indentical to struct IVIDENC_CodecClassConfig from videnc.h.
 * Its name doesn't matter, only that the address of data is captured in the
 * "codecClassConfig" field of the algorithm description
 */
struct codecs_videnc_codec_VIDENC_KDC_CodecClassConfig {
    Bool manageInBufsCache   [ XDM_MAX_IO_BUFFERS ];
    Bool manageOutBufsCache  [ XDM_MAX_IO_BUFFERS ];
    Bool manageReconBufsCache[ XDM_MAX_IO_BUFFERS ];
} codecs_videnc_codec_VIDENC_KDC_codecClassConfig = {
    {TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE},
    {TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE},
    {TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE}
};

/*
 * ======== ti.sdo.ce.video.VIDDECConfig TEMPLATE ========
 */


/* this data structure has codec-specific names and values, but class-specific
 * fields -- it's indentical to struct IVIDENC_CodecClassConfig from videnc.h.
 * Its name doesn't matter, only that the address of data is captured in the
 * "codecClassConfig" field of the algorithm description
 */
struct codecs_viddec_codec_VIDDEC_KDC_CodecClassConfig {
    Bool manageInBufsCache     [ XDM_MAX_IO_BUFFERS ];
    Bool manageOutBufsCache    [ XDM_MAX_IO_BUFFERS ];
    Bool manageDisplayBufsCache[ XDM_MAX_IO_BUFFERS ];
} codecs_viddec_codec_VIDDEC_KDC_codecClassConfig = {
    {TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE},
    {TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE},
    {TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE}
};
/* this data structure has codec-specific names and values, but class-specific
 * fields -- it's indentical to struct IVIDENC_CodecClassConfig from videnc.h.
 * Its name doesn't matter, only that the address of data is captured in the
 * "codecClassConfig" field of the algorithm description
 */
struct codecs_imgproc_codec_IMGPROC_CODEC_CodecClassConfig {
    Bool manageInBufsCache     [ XDM_MAX_IO_BUFFERS ];
    Bool manageOutBufsCache    [ XDM_MAX_IO_BUFFERS ];
    Bool manageDisplayBufsCache[ XDM_MAX_IO_BUFFERS ];
} codecs_imgproc_codec_IMGPROC_CODEC_codecClassConfig = {
    {TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE},
    {TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE},
    {TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE,TRUE}
};

/*
 * ======== ti.sdo.ce.alg.Algorithm TEMPLATE ========
 */

Bool ti_sdo_ce_alg_Algorithm_useHeap = FALSE;
Bool ti_sdo_ce_alg_Algorithm_useCache = FALSE;

unsigned int ti_sdo_ce_alg_Algorithm_MAXGROUPID = 20;

UInt32 ti_sdo_ce_alg_Algorithm_ipcKey = 0x4f474c41;

int _ALG_groupUsed[20] = {
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0,
};

#include <xdc/runtime/knl/SemProcess.h>
#include <ti/xdais/ialg.h>

xdc_runtime_knl_SemProcess_Handle _ALG_sems[20];
int _ALG_groupRefCount[20];


IALG_Handle _Algorithm_lockOwner[20] = {
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
     NULL,
};

// No IDMA3 using algs in the system, and DMAN3 is not configured into the
// system.  Stub out these fxn calls.
Void DMAN3_CE_init()
{
}
Void DMAN3_CE_exit()
{
}

int DMAN3_grantDmaChannels(int groupId, void *algHandles, void *dmaFxns,
        int numAlgs)
{
    /* TODO:M  Could assert(false) here.  Should never be called */
    return (0);
}

int DMAN3_releaseDmaChannels(void *algHandles, void * dmaFxns, int numAlgs)
{
    /* TODO:M  Could assert(false) here.  Should never be called */
    return (0);
}
// No IRES using algs in the system, and RMAN is not configured into the
// system.  Stub out these fxn calls.
#include <ti/xdais/ires.h>   /* for IRES types */

IRES_Status RMAN_activateAllResources(IALG_Handle algHandle, IRES_Fxns *resFxns, Int scratchId)
{
    /* TODO:M  Could assert(false) here.  Should never be called */
    return (IRES_OK);
}

IRES_Status RMAN_assignResources(IALG_Handle algHandle, IRES_Fxns *resFxns,
        Int scratchGroupId)
{
    /* TODO:M  Could assert(false) here.  Should never be called */
    return (IRES_OK);
}

IRES_Status RMAN_deactivateAllResources(IALG_Handle algHandle,
        IRES_Fxns * resFxns, Int scratchId)
{
    /* TODO:M  Could assert(false) here.  Should never be called */
    return (IRES_OK);
}

IRES_Status RMAN_freeResources(IALG_Handle algHandle, IRES_Fxns * resFxns,
        Int scratchGroupId)
{
    /* TODO:M  Could assert(false) here.  Should never be called */
    return (IRES_OK);
}

IRES_Status RMAN_init(void)
{
    return (IRES_OK);
}

IRES_Status RMAN_exit(void)
{
    return (IRES_OK);
}


/*
 * ======== ti.sdo.utils.loggers.LogMFP INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__diagsEnabled ti_sdo_utils_loggers_LogMFP_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__diagsIncluded ti_sdo_utils_loggers_LogMFP_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__diagsMask ti_sdo_utils_loggers_LogMFP_Module__diagsMask__C = ((CT__ti_sdo_utils_loggers_LogMFP_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__gateObj ti_sdo_utils_loggers_LogMFP_Module__gateObj__C = ((CT__ti_sdo_utils_loggers_LogMFP_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__gatePrms ti_sdo_utils_loggers_LogMFP_Module__gatePrms__C = ((CT__ti_sdo_utils_loggers_LogMFP_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__id ti_sdo_utils_loggers_LogMFP_Module__id__C = (xdc_Bits16)0x8023;

/* Module__loggerDefined__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerDefined ti_sdo_utils_loggers_LogMFP_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerObj ti_sdo_utils_loggers_LogMFP_Module__loggerObj__C = ((CT__ti_sdo_utils_loggers_LogMFP_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn0 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn0__C = ((CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn1 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn1__C = ((CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn2 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn2__C = ((CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn4 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn4__C = ((CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn8 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn8__C = ((CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Module__startupDoneFxn ti_sdo_utils_loggers_LogMFP_Module__startupDoneFxn__C = ((CT__ti_sdo_utils_loggers_LogMFP_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Object__count ti_sdo_utils_loggers_LogMFP_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Object__heap ti_sdo_utils_loggers_LogMFP_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Object__sizeof ti_sdo_utils_loggers_LogMFP_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__ti_sdo_utils_loggers_LogMFP_Object__table ti_sdo_utils_loggers_LogMFP_Object__table__C = 0;


/*
 * ======== ti.sdo.utils.loggers.LogMFP_Proxy INITIALIZERS ========
 */


/*
 * ======== ti.sdo.utils.loggers.LoggerMFPNull INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_utils_loggers_LoggerMFPNull_Object__DESC__C;

/* Object__PARAMS__C */
__FAR__ const ti_sdo_utils_loggers_LoggerMFPNull_Params ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C = {
    sizeof (ti_sdo_utils_loggers_LoggerMFPNull_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C.__iprms, /* instance */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
ti_sdo_utils_loggers_LoggerMFPNull_Module__ ti_sdo_utils_loggers_LoggerMFPNull_Module__root__V = {
    {&ti_sdo_utils_loggers_LoggerMFPNull_Module__root__V.link,  /* link.next */
    &ti_sdo_utils_loggers_LoggerMFPNull_Module__root__V.link},  /* link.prev */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsEnabled ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsIncluded ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsMask ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsMask__C = ((CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__gateObj ti_sdo_utils_loggers_LoggerMFPNull_Module__gateObj__C = ((CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__gatePrms ti_sdo_utils_loggers_LoggerMFPNull_Module__gatePrms__C = ((CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__id ti_sdo_utils_loggers_LoggerMFPNull_Module__id__C = (xdc_Bits16)0x8022;

/* Module__loggerDefined__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerDefined ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerObj ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerObj__C = ((CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn0 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn0__C = ((CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn1 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn1__C = ((CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn2 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn2__C = ((CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn4 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn4__C = ((CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn8 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn8__C = ((CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__startupDoneFxn ti_sdo_utils_loggers_LoggerMFPNull_Module__startupDoneFxn__C = ((CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Object__count ti_sdo_utils_loggers_LoggerMFPNull_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Object__heap ti_sdo_utils_loggers_LoggerMFPNull_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Object__sizeof ti_sdo_utils_loggers_LoggerMFPNull_Object__sizeof__C = sizeof(ti_sdo_utils_loggers_LoggerMFPNull_Object__);

/* Object__table__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerMFPNull_Object__table ti_sdo_utils_loggers_LoggerMFPNull_Object__table__C = 0;


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_utils_loggers_LoggerSysTID_Object__DESC__C;

/* Object__PARAMS__C */
__FAR__ const ti_sdo_utils_loggers_LoggerSysTID_Params ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C = {
    sizeof (ti_sdo_utils_loggers_LoggerSysTID_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C.__iprms, /* instance */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
ti_sdo_utils_loggers_LoggerSysTID_Module__ ti_sdo_utils_loggers_LoggerSysTID_Module__root__V = {
    {&ti_sdo_utils_loggers_LoggerSysTID_Module__root__V.link,  /* link.next */
    &ti_sdo_utils_loggers_LoggerSysTID_Module__root__V.link},  /* link.prev */
};

/* Object__table__V */
ti_sdo_utils_loggers_LoggerSysTID_Object__ ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[1] = {
    {/* instance#0 */
        &ti_sdo_utils_loggers_LoggerSysTID_Module__FXNS__C,
        1,  /* enabled */
    },
};

/* Module__diagsEnabled__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__diagsEnabled ti_sdo_utils_loggers_LoggerSysTID_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__diagsIncluded ti_sdo_utils_loggers_LoggerSysTID_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__diagsMask ti_sdo_utils_loggers_LoggerSysTID_Module__diagsMask__C = ((CT__ti_sdo_utils_loggers_LoggerSysTID_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__gateObj ti_sdo_utils_loggers_LoggerSysTID_Module__gateObj__C = ((CT__ti_sdo_utils_loggers_LoggerSysTID_Module__gateObj)((void*)(xdc_runtime_IGateProvider_Handle)&xdc_runtime_knl_GateThread_Object__table__V[0]));

/* Module__gatePrms__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__gatePrms ti_sdo_utils_loggers_LoggerSysTID_Module__gatePrms__C = ((CT__ti_sdo_utils_loggers_LoggerSysTID_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__id ti_sdo_utils_loggers_LoggerSysTID_Module__id__C = (xdc_Bits16)0x8021;

/* Module__loggerDefined__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerDefined ti_sdo_utils_loggers_LoggerSysTID_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerObj ti_sdo_utils_loggers_LoggerSysTID_Module__loggerObj__C = ((CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn0 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn0__C = ((CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn1 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn1__C = ((CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn2 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn2__C = ((CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn4 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn4__C = ((CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn8 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn8__C = ((CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__startupDoneFxn ti_sdo_utils_loggers_LoggerSysTID_Module__startupDoneFxn__C = ((CT__ti_sdo_utils_loggers_LoggerSysTID_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Object__count ti_sdo_utils_loggers_LoggerSysTID_Object__count__C = 1;

/* Object__heap__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Object__heap ti_sdo_utils_loggers_LoggerSysTID_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Object__sizeof ti_sdo_utils_loggers_LoggerSysTID_Object__sizeof__C = sizeof(ti_sdo_utils_loggers_LoggerSysTID_Object__);

/* Object__table__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_Object__table ti_sdo_utils_loggers_LoggerSysTID_Object__table__C = ti_sdo_utils_loggers_LoggerSysTID_Object__table__V;

/* gate__C */
__FAR__ const CT__ti_sdo_utils_loggers_LoggerSysTID_gate ti_sdo_utils_loggers_LoggerSysTID_gate__C = (xdc_runtime_IGateProvider_Handle)&xdc_runtime_knl_GateThread_Object__table__V[0];


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID_Module_GateProxy INITIALIZERS ========
 */


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID_TimestampProxy INITIALIZERS ========
 */


/*
 * ======== ti.sdo.xdcruntime.linux.GateThreadSupport INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_xdcruntime_linux_GateThreadSupport_Object__DESC__C;

/* Object__PARAMS__C */
__FAR__ const ti_sdo_xdcruntime_linux_GateThreadSupport_Params ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C = {
    sizeof (ti_sdo_xdcruntime_linux_GateThreadSupport_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C.__iprms, /* instance */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
ti_sdo_xdcruntime_linux_GateThreadSupport_Module__ ti_sdo_xdcruntime_linux_GateThreadSupport_Module__root__V = {
    {&ti_sdo_xdcruntime_linux_GateThreadSupport_Module__root__V.link,  /* link.next */
    &ti_sdo_xdcruntime_linux_GateThreadSupport_Module__root__V.link},  /* link.prev */
};

/* Object__table__V */
ti_sdo_xdcruntime_linux_GateThreadSupport_Object__ ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__V[2] = {
    {/* instance#0 */
        0,
        ((xdc_Void*)0),  /* gate */
    },
    {/* instance#1 */
        0,
        ((xdc_Void*)0),  /* gate */
    },
};

/* Module__diagsEnabled__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsEnabled ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsIncluded ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsMask ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsMask__C = ((CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gateObj ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gateObj__C = ((CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gatePrms ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gatePrms__C = ((CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__id ti_sdo_xdcruntime_linux_GateThreadSupport_Module__id__C = (xdc_Bits16)0x801a;

/* Module__loggerDefined__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerDefined ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerObj ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerObj__C = ((CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn0 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn0__C = ((CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn1 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn1__C = ((CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn2 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn2__C = ((CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn4 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn4__C = ((CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn8 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn8__C = ((CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDoneFxn ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDoneFxn__C = ((CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Object__count ti_sdo_xdcruntime_linux_GateThreadSupport_Object__count__C = 2;

/* Object__heap__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Object__heap ti_sdo_xdcruntime_linux_GateThreadSupport_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Object__sizeof ti_sdo_xdcruntime_linux_GateThreadSupport_Object__sizeof__C = sizeof(ti_sdo_xdcruntime_linux_GateThreadSupport_Object__);

/* Object__table__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__C = ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__V;

/* A_POSIX_Error__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_A_POSIX_Error ti_sdo_xdcruntime_linux_GateThreadSupport_A_POSIX_Error__C = (((xdc_runtime_Assert_Id)455) << 16 | 16);

/* E_POSIX_Error__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_E_POSIX_Error ti_sdo_xdcruntime_linux_GateThreadSupport_E_POSIX_Error__C = (((xdc_runtime_Error_Id)845) << 16 | 0);


/*
 * ======== ti.sdo.xdcruntime.linux.SemProcessSupport INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_xdcruntime_linux_SemProcessSupport_Object__DESC__C;

/* Object__PARAMS__C */
__FAR__ const ti_sdo_xdcruntime_linux_SemProcessSupport_Params ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C = {
    sizeof (ti_sdo_xdcruntime_linux_SemProcessSupport_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C.__iprms, /* instance */
    xdc_runtime_knl_ISemaphore_Mode_COUNTING,  /* mode */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
ti_sdo_xdcruntime_linux_SemProcessSupport_Module__ ti_sdo_xdcruntime_linux_SemProcessSupport_Module__root__V = {
    {&ti_sdo_xdcruntime_linux_SemProcessSupport_Module__root__V.link,  /* link.next */
    &ti_sdo_xdcruntime_linux_SemProcessSupport_Module__root__V.link},  /* link.prev */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsEnabled ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsIncluded ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsMask ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsMask__C = ((CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gateObj ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gateObj__C = ((CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gatePrms ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gatePrms__C = ((CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__id ti_sdo_xdcruntime_linux_SemProcessSupport_Module__id__C = (xdc_Bits16)0x801c;

/* Module__loggerDefined__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerDefined ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerObj ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerObj__C = ((CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn0 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn0__C = ((CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn1 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn1__C = ((CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn2 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn2__C = ((CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn4 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn4__C = ((CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn8 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn8__C = ((CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDoneFxn ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDoneFxn__C = ((CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Object__count ti_sdo_xdcruntime_linux_SemProcessSupport_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Object__heap ti_sdo_xdcruntime_linux_SemProcessSupport_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Object__sizeof ti_sdo_xdcruntime_linux_SemProcessSupport_Object__sizeof__C = sizeof(ti_sdo_xdcruntime_linux_SemProcessSupport_Object__);

/* Object__table__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Object__table ti_sdo_xdcruntime_linux_SemProcessSupport_Object__table__C = 0;

/* A_unsupportedTimeout__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_A_unsupportedTimeout ti_sdo_xdcruntime_linux_SemProcessSupport_A_unsupportedTimeout__C = (((xdc_runtime_Assert_Id)546) << 16 | 16);

/* A_invalidKey__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_A_invalidKey ti_sdo_xdcruntime_linux_SemProcessSupport_A_invalidKey__C = (((xdc_runtime_Assert_Id)504) << 16 | 16);

/* A_POSIX_Error__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_A_POSIX_Error ti_sdo_xdcruntime_linux_SemProcessSupport_A_POSIX_Error__C = (((xdc_runtime_Assert_Id)455) << 16 | 16);

/* E_POSIX_Error__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_E_POSIX_Error ti_sdo_xdcruntime_linux_SemProcessSupport_E_POSIX_Error__C = (((xdc_runtime_Error_Id)845) << 16 | 0);

/* L_extant__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_L_extant ti_sdo_xdcruntime_linux_SemProcessSupport_L_extant__C = (((xdc_runtime_Log_Event)1499) << 16 | 4);

/* L_create__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_L_create ti_sdo_xdcruntime_linux_SemProcessSupport_L_create__C = (((xdc_runtime_Log_Event)1563) << 16 | 4);

/* perms__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_perms ti_sdo_xdcruntime_linux_SemProcessSupport_perms__C = (xdc_Int)0x1b6;


/*
 * ======== ti.sdo.xdcruntime.linux.SemThreadSupport INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_xdcruntime_linux_SemThreadSupport_Object__DESC__C;

/* Object__PARAMS__C */
__FAR__ const ti_sdo_xdcruntime_linux_SemThreadSupport_Params ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C = {
    sizeof (ti_sdo_xdcruntime_linux_SemThreadSupport_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C.__iprms, /* instance */
    xdc_runtime_knl_ISemaphore_Mode_COUNTING,  /* mode */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
ti_sdo_xdcruntime_linux_SemThreadSupport_Module__ ti_sdo_xdcruntime_linux_SemThreadSupport_Module__root__V = {
    {&ti_sdo_xdcruntime_linux_SemThreadSupport_Module__root__V.link,  /* link.next */
    &ti_sdo_xdcruntime_linux_SemThreadSupport_Module__root__V.link},  /* link.prev */
};

/* Module__state__V */
ti_sdo_xdcruntime_linux_SemThreadSupport_Module_State__ ti_sdo_xdcruntime_linux_SemThreadSupport_Module__state__V = {
    ((xdc_Void*)0),  /* mutex */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsEnabled ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsIncluded ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsMask ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsMask__C = ((CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gateObj ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gateObj__C = ((CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gatePrms ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gatePrms__C = ((CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__id ti_sdo_xdcruntime_linux_SemThreadSupport_Module__id__C = (xdc_Bits16)0x801b;

/* Module__loggerDefined__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerDefined ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerObj ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerObj__C = ((CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn0 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn0__C = ((CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn1 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn1__C = ((CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn2 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn2__C = ((CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn4 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn4__C = ((CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn8 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn8__C = ((CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDoneFxn ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDoneFxn__C = ((CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Object__count ti_sdo_xdcruntime_linux_SemThreadSupport_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Object__heap ti_sdo_xdcruntime_linux_SemThreadSupport_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Object__sizeof ti_sdo_xdcruntime_linux_SemThreadSupport_Object__sizeof__C = sizeof(ti_sdo_xdcruntime_linux_SemThreadSupport_Object__);

/* Object__table__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Object__table ti_sdo_xdcruntime_linux_SemThreadSupport_Object__table__C = 0;

/* A_POSIX_Error__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_A_POSIX_Error ti_sdo_xdcruntime_linux_SemThreadSupport_A_POSIX_Error__C = (((xdc_runtime_Assert_Id)455) << 16 | 16);

/* E_POSIX_Error__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_E_POSIX_Error ti_sdo_xdcruntime_linux_SemThreadSupport_E_POSIX_Error__C = (((xdc_runtime_Error_Id)845) << 16 | 0);

/* E_resetError__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_E_resetError ti_sdo_xdcruntime_linux_SemThreadSupport_E_resetError__C = (((xdc_runtime_Error_Id)907) << 16 | 0);


/*
 * ======== ti.sdo.xdcruntime.linux.ThreadSupport INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_xdcruntime_linux_ThreadSupport_Object__DESC__C;

/* Object__PARAMS__C */
__FAR__ const ti_sdo_xdcruntime_linux_ThreadSupport_Params ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C = {
    sizeof (ti_sdo_xdcruntime_linux_ThreadSupport_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C.__iprms, /* instance */
    ((xdc_IArg)0),  /* arg */
    xdc_runtime_knl_IThreadSupport_Priority_NORMAL,  /* priority */
    (xdc_Int)0x0,  /* osPriority */
    (xdc_SizeT)0x0,  /* stackSize */
    ((xdc_Ptr)0),  /* tls */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
ti_sdo_xdcruntime_linux_ThreadSupport_Module__ ti_sdo_xdcruntime_linux_ThreadSupport_Module__root__V = {
    {&ti_sdo_xdcruntime_linux_ThreadSupport_Module__root__V.link,  /* link.next */
    &ti_sdo_xdcruntime_linux_ThreadSupport_Module__root__V.link},  /* link.prev */
};

/* Module__state__V */
ti_sdo_xdcruntime_linux_ThreadSupport_Module_State__ ti_sdo_xdcruntime_linux_ThreadSupport_Module__state__V = {
    (xdc_Int)0x0,  /* lowestPriority */
    (xdc_Int)0x0,  /* belowNormalPriority */
    (xdc_Int)0x0,  /* normalPriority */
    (xdc_Int)0x0,  /* aboveNormalPriority */
    (xdc_Int)0x0,  /* highestPriority */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsEnabled ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsIncluded ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsMask ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsMask__C = ((CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__gateObj ti_sdo_xdcruntime_linux_ThreadSupport_Module__gateObj__C = ((CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__gatePrms ti_sdo_xdcruntime_linux_ThreadSupport_Module__gatePrms__C = ((CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__id ti_sdo_xdcruntime_linux_ThreadSupport_Module__id__C = (xdc_Bits16)0x801d;

/* Module__loggerDefined__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerDefined ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerObj ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerObj__C = ((CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn0 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn0__C = ((CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn1 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn1__C = ((CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn2 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn2__C = ((CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn4 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn4__C = ((CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn8 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn8__C = ((CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDoneFxn ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDoneFxn__C = ((CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Object__count ti_sdo_xdcruntime_linux_ThreadSupport_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Object__heap ti_sdo_xdcruntime_linux_ThreadSupport_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Object__sizeof ti_sdo_xdcruntime_linux_ThreadSupport_Object__sizeof__C = sizeof(ti_sdo_xdcruntime_linux_ThreadSupport_Object__);

/* Object__table__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Object__table ti_sdo_xdcruntime_linux_ThreadSupport_Object__table__C = 0;

/* E_priority__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_E_priority ti_sdo_xdcruntime_linux_ThreadSupport_E_priority__C = (((xdc_runtime_Error_Id)941) << 16 | 0);

/* A_POSIX_Error__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_A_POSIX_Error ti_sdo_xdcruntime_linux_ThreadSupport_A_POSIX_Error__C = (((xdc_runtime_Assert_Id)455) << 16 | 16);

/* E_POSIX_Error__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_E_POSIX_Error ti_sdo_xdcruntime_linux_ThreadSupport_E_POSIX_Error__C = (((xdc_runtime_Error_Id)845) << 16 | 0);

/* L_start__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_L_start ti_sdo_xdcruntime_linux_ThreadSupport_L_start__C = (((xdc_runtime_Log_Event)1596) << 16 | 4);

/* L_finish__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_L_finish ti_sdo_xdcruntime_linux_ThreadSupport_L_finish__C = (((xdc_runtime_Log_Event)1612) << 16 | 4);

/* L_join__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_ThreadSupport_L_join ti_sdo_xdcruntime_linux_ThreadSupport_L_join__C = (((xdc_runtime_Log_Event)1629) << 16 | 4);


/*
 * ======== ti.sdo.xdcruntime.linux.TimestampPosix INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsEnabled ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsIncluded ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsMask ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsMask__C = ((CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__gateObj ti_sdo_xdcruntime_linux_TimestampPosix_Module__gateObj__C = ((CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__gatePrms ti_sdo_xdcruntime_linux_TimestampPosix_Module__gatePrms__C = ((CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__id ti_sdo_xdcruntime_linux_TimestampPosix_Module__id__C = (xdc_Bits16)0x801e;

/* Module__loggerDefined__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerDefined ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerObj ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerObj__C = ((CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn0 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn0__C = ((CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn1 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn1__C = ((CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn2 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn2__C = ((CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn4 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn4__C = ((CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn8 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn8__C = ((CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDoneFxn ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDoneFxn__C = ((CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Object__count ti_sdo_xdcruntime_linux_TimestampPosix_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Object__heap ti_sdo_xdcruntime_linux_TimestampPosix_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Object__sizeof ti_sdo_xdcruntime_linux_TimestampPosix_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Object__table ti_sdo_xdcruntime_linux_TimestampPosix_Object__table__C = 0;


/*
 * ======== xdc.runtime.Assert INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_Assert_Module__diagsEnabled xdc_runtime_Assert_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_Assert_Module__diagsIncluded xdc_runtime_Assert_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_Assert_Module__diagsMask xdc_runtime_Assert_Module__diagsMask__C = ((CT__xdc_runtime_Assert_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_Assert_Module__gateObj xdc_runtime_Assert_Module__gateObj__C = ((CT__xdc_runtime_Assert_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_Assert_Module__gatePrms xdc_runtime_Assert_Module__gatePrms__C = ((CT__xdc_runtime_Assert_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_Assert_Module__id xdc_runtime_Assert_Module__id__C = (xdc_Bits16)0x8002;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_Assert_Module__loggerDefined xdc_runtime_Assert_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_Assert_Module__loggerObj xdc_runtime_Assert_Module__loggerObj__C = ((CT__xdc_runtime_Assert_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_Assert_Module__loggerFxn0 xdc_runtime_Assert_Module__loggerFxn0__C = ((CT__xdc_runtime_Assert_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_Assert_Module__loggerFxn1 xdc_runtime_Assert_Module__loggerFxn1__C = ((CT__xdc_runtime_Assert_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_Assert_Module__loggerFxn2 xdc_runtime_Assert_Module__loggerFxn2__C = ((CT__xdc_runtime_Assert_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_Assert_Module__loggerFxn4 xdc_runtime_Assert_Module__loggerFxn4__C = ((CT__xdc_runtime_Assert_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_Assert_Module__loggerFxn8 xdc_runtime_Assert_Module__loggerFxn8__C = ((CT__xdc_runtime_Assert_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_Assert_Module__startupDoneFxn xdc_runtime_Assert_Module__startupDoneFxn__C = ((CT__xdc_runtime_Assert_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_Assert_Object__count xdc_runtime_Assert_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_Assert_Object__heap xdc_runtime_Assert_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_Assert_Object__sizeof xdc_runtime_Assert_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_Assert_Object__table xdc_runtime_Assert_Object__table__C = 0;

/* E_assertFailed__C */
__FAR__ const CT__xdc_runtime_Assert_E_assertFailed xdc_runtime_Assert_E_assertFailed__C = (((xdc_runtime_Error_Id)605) << 16 | 0);


/*
 * ======== xdc.runtime.Core INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_Core_Module__diagsEnabled xdc_runtime_Core_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_Core_Module__diagsIncluded xdc_runtime_Core_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_Core_Module__diagsMask xdc_runtime_Core_Module__diagsMask__C = ((CT__xdc_runtime_Core_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_Core_Module__gateObj xdc_runtime_Core_Module__gateObj__C = ((CT__xdc_runtime_Core_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_Core_Module__gatePrms xdc_runtime_Core_Module__gatePrms__C = ((CT__xdc_runtime_Core_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_Core_Module__id xdc_runtime_Core_Module__id__C = (xdc_Bits16)0x8003;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_Core_Module__loggerDefined xdc_runtime_Core_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_Core_Module__loggerObj xdc_runtime_Core_Module__loggerObj__C = ((CT__xdc_runtime_Core_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_Core_Module__loggerFxn0 xdc_runtime_Core_Module__loggerFxn0__C = ((CT__xdc_runtime_Core_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_Core_Module__loggerFxn1 xdc_runtime_Core_Module__loggerFxn1__C = ((CT__xdc_runtime_Core_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_Core_Module__loggerFxn2 xdc_runtime_Core_Module__loggerFxn2__C = ((CT__xdc_runtime_Core_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_Core_Module__loggerFxn4 xdc_runtime_Core_Module__loggerFxn4__C = ((CT__xdc_runtime_Core_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_Core_Module__loggerFxn8 xdc_runtime_Core_Module__loggerFxn8__C = ((CT__xdc_runtime_Core_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_Core_Module__startupDoneFxn xdc_runtime_Core_Module__startupDoneFxn__C = ((CT__xdc_runtime_Core_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_Core_Object__count xdc_runtime_Core_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_Core_Object__heap xdc_runtime_Core_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_Core_Object__sizeof xdc_runtime_Core_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_Core_Object__table xdc_runtime_Core_Object__table__C = 0;

/* A_initializedParams__C */
__FAR__ const CT__xdc_runtime_Core_A_initializedParams xdc_runtime_Core_A_initializedParams__C = (((xdc_runtime_Assert_Id)1) << 16 | 16);


/*
 * ======== xdc.runtime.Defaults INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__diagsEnabled xdc_runtime_Defaults_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__diagsIncluded xdc_runtime_Defaults_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__diagsMask xdc_runtime_Defaults_Module__diagsMask__C = ((CT__xdc_runtime_Defaults_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__gateObj xdc_runtime_Defaults_Module__gateObj__C = ((CT__xdc_runtime_Defaults_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__gatePrms xdc_runtime_Defaults_Module__gatePrms__C = ((CT__xdc_runtime_Defaults_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__id xdc_runtime_Defaults_Module__id__C = (xdc_Bits16)0x8004;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerDefined xdc_runtime_Defaults_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerObj xdc_runtime_Defaults_Module__loggerObj__C = ((CT__xdc_runtime_Defaults_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerFxn0 xdc_runtime_Defaults_Module__loggerFxn0__C = ((CT__xdc_runtime_Defaults_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerFxn1 xdc_runtime_Defaults_Module__loggerFxn1__C = ((CT__xdc_runtime_Defaults_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerFxn2 xdc_runtime_Defaults_Module__loggerFxn2__C = ((CT__xdc_runtime_Defaults_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerFxn4 xdc_runtime_Defaults_Module__loggerFxn4__C = ((CT__xdc_runtime_Defaults_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__loggerFxn8 xdc_runtime_Defaults_Module__loggerFxn8__C = ((CT__xdc_runtime_Defaults_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_Defaults_Module__startupDoneFxn xdc_runtime_Defaults_Module__startupDoneFxn__C = ((CT__xdc_runtime_Defaults_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_Defaults_Object__count xdc_runtime_Defaults_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_Defaults_Object__heap xdc_runtime_Defaults_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_Defaults_Object__sizeof xdc_runtime_Defaults_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_Defaults_Object__table xdc_runtime_Defaults_Object__table__C = 0;


/*
 * ======== xdc.runtime.Diags INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_Diags_Module__diagsEnabled xdc_runtime_Diags_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_Diags_Module__diagsIncluded xdc_runtime_Diags_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_Diags_Module__diagsMask xdc_runtime_Diags_Module__diagsMask__C = ((CT__xdc_runtime_Diags_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_Diags_Module__gateObj xdc_runtime_Diags_Module__gateObj__C = ((CT__xdc_runtime_Diags_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_Diags_Module__gatePrms xdc_runtime_Diags_Module__gatePrms__C = ((CT__xdc_runtime_Diags_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_Diags_Module__id xdc_runtime_Diags_Module__id__C = (xdc_Bits16)0x8005;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_Diags_Module__loggerDefined xdc_runtime_Diags_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_Diags_Module__loggerObj xdc_runtime_Diags_Module__loggerObj__C = ((CT__xdc_runtime_Diags_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_Diags_Module__loggerFxn0 xdc_runtime_Diags_Module__loggerFxn0__C = ((CT__xdc_runtime_Diags_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_Diags_Module__loggerFxn1 xdc_runtime_Diags_Module__loggerFxn1__C = ((CT__xdc_runtime_Diags_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_Diags_Module__loggerFxn2 xdc_runtime_Diags_Module__loggerFxn2__C = ((CT__xdc_runtime_Diags_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_Diags_Module__loggerFxn4 xdc_runtime_Diags_Module__loggerFxn4__C = ((CT__xdc_runtime_Diags_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_Diags_Module__loggerFxn8 xdc_runtime_Diags_Module__loggerFxn8__C = ((CT__xdc_runtime_Diags_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_Diags_Module__startupDoneFxn xdc_runtime_Diags_Module__startupDoneFxn__C = ((CT__xdc_runtime_Diags_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_Diags_Object__count xdc_runtime_Diags_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_Diags_Object__heap xdc_runtime_Diags_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_Diags_Object__sizeof xdc_runtime_Diags_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_Diags_Object__table xdc_runtime_Diags_Object__table__C = 0;

/* setMaskEnabled__C */
__FAR__ const CT__xdc_runtime_Diags_setMaskEnabled xdc_runtime_Diags_setMaskEnabled__C = 1;

/* dictBase__C */
__FAR__ const CT__xdc_runtime_Diags_dictBase xdc_runtime_Diags_dictBase__C = ((CT__xdc_runtime_Diags_dictBase)((void*)&xdc_runtime_Diags_dictElems[0]));


/*
 * ======== xdc.runtime.Error INITIALIZERS ========
 */

/* Module__state__V */
xdc_runtime_Error_Module_State__ xdc_runtime_Error_Module__state__V = {
    (xdc_UInt16)0x0,  /* count */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_Error_Module__diagsEnabled xdc_runtime_Error_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_Error_Module__diagsIncluded xdc_runtime_Error_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_Error_Module__diagsMask xdc_runtime_Error_Module__diagsMask__C = ((CT__xdc_runtime_Error_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_Error_Module__gateObj xdc_runtime_Error_Module__gateObj__C = ((CT__xdc_runtime_Error_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_Error_Module__gatePrms xdc_runtime_Error_Module__gatePrms__C = ((CT__xdc_runtime_Error_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_Error_Module__id xdc_runtime_Error_Module__id__C = (xdc_Bits16)0x8006;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_Error_Module__loggerDefined xdc_runtime_Error_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_Error_Module__loggerObj xdc_runtime_Error_Module__loggerObj__C = ((CT__xdc_runtime_Error_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_Error_Module__loggerFxn0 xdc_runtime_Error_Module__loggerFxn0__C = ((CT__xdc_runtime_Error_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_Error_Module__loggerFxn1 xdc_runtime_Error_Module__loggerFxn1__C = ((CT__xdc_runtime_Error_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_Error_Module__loggerFxn2 xdc_runtime_Error_Module__loggerFxn2__C = ((CT__xdc_runtime_Error_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_Error_Module__loggerFxn4 xdc_runtime_Error_Module__loggerFxn4__C = ((CT__xdc_runtime_Error_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_Error_Module__loggerFxn8 xdc_runtime_Error_Module__loggerFxn8__C = ((CT__xdc_runtime_Error_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_Error_Module__startupDoneFxn xdc_runtime_Error_Module__startupDoneFxn__C = ((CT__xdc_runtime_Error_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_Error_Object__count xdc_runtime_Error_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_Error_Object__heap xdc_runtime_Error_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_Error_Object__sizeof xdc_runtime_Error_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_Error_Object__table xdc_runtime_Error_Object__table__C = 0;

/* E_generic__C */
__FAR__ const CT__xdc_runtime_Error_E_generic xdc_runtime_Error_E_generic__C = (((xdc_runtime_Error_Id)627) << 16 | 0);

/* E_memory__C */
__FAR__ const CT__xdc_runtime_Error_E_memory xdc_runtime_Error_E_memory__C = (((xdc_runtime_Error_Id)631) << 16 | 0);

/* E_msgCode__C */
__FAR__ const CT__xdc_runtime_Error_E_msgCode xdc_runtime_Error_E_msgCode__C = (((xdc_runtime_Error_Id)665) << 16 | 0);

/* policy__C */
__FAR__ const CT__xdc_runtime_Error_policy xdc_runtime_Error_policy__C = xdc_runtime_Error_UNWIND;

/* raiseHook__C */
__FAR__ const CT__xdc_runtime_Error_raiseHook xdc_runtime_Error_raiseHook__C = ((CT__xdc_runtime_Error_raiseHook)((xdc_Fxn)xdc_runtime_Error_print__E));

/* maxDepth__C */
__FAR__ const CT__xdc_runtime_Error_maxDepth xdc_runtime_Error_maxDepth__C = (xdc_UInt16)0x10;


/*
 * ======== xdc.runtime.Gate INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_Gate_Module__diagsEnabled xdc_runtime_Gate_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_Gate_Module__diagsIncluded xdc_runtime_Gate_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_Gate_Module__diagsMask xdc_runtime_Gate_Module__diagsMask__C = ((CT__xdc_runtime_Gate_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_Gate_Module__gateObj xdc_runtime_Gate_Module__gateObj__C = ((CT__xdc_runtime_Gate_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_Gate_Module__gatePrms xdc_runtime_Gate_Module__gatePrms__C = ((CT__xdc_runtime_Gate_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_Gate_Module__id xdc_runtime_Gate_Module__id__C = (xdc_Bits16)0x8007;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_Gate_Module__loggerDefined xdc_runtime_Gate_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_Gate_Module__loggerObj xdc_runtime_Gate_Module__loggerObj__C = ((CT__xdc_runtime_Gate_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_Gate_Module__loggerFxn0 xdc_runtime_Gate_Module__loggerFxn0__C = ((CT__xdc_runtime_Gate_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_Gate_Module__loggerFxn1 xdc_runtime_Gate_Module__loggerFxn1__C = ((CT__xdc_runtime_Gate_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_Gate_Module__loggerFxn2 xdc_runtime_Gate_Module__loggerFxn2__C = ((CT__xdc_runtime_Gate_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_Gate_Module__loggerFxn4 xdc_runtime_Gate_Module__loggerFxn4__C = ((CT__xdc_runtime_Gate_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_Gate_Module__loggerFxn8 xdc_runtime_Gate_Module__loggerFxn8__C = ((CT__xdc_runtime_Gate_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_Gate_Module__startupDoneFxn xdc_runtime_Gate_Module__startupDoneFxn__C = ((CT__xdc_runtime_Gate_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_Gate_Object__count xdc_runtime_Gate_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_Gate_Object__heap xdc_runtime_Gate_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_Gate_Object__sizeof xdc_runtime_Gate_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_Gate_Object__table xdc_runtime_Gate_Object__table__C = 0;


/*
 * ======== xdc.runtime.HeapStd INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_HeapStd_Object__DESC__C;

/* Object__PARAMS__C */
__FAR__ const xdc_runtime_HeapStd_Params xdc_runtime_HeapStd_Object__PARAMS__C = {
    sizeof (xdc_runtime_HeapStd_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&xdc_runtime_HeapStd_Object__PARAMS__C.__iprms, /* instance */
    ((xdc_UArg)((void*)0x0)),  /* size */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
xdc_runtime_HeapStd_Module__ xdc_runtime_HeapStd_Module__root__V = {
    {&xdc_runtime_HeapStd_Module__root__V.link,  /* link.next */
    &xdc_runtime_HeapStd_Module__root__V.link},  /* link.prev */
};

/* Object__table__V */
xdc_runtime_HeapStd_Object__ xdc_runtime_HeapStd_Object__table__V[1] = {
    {/* instance#0 */
        &xdc_runtime_HeapStd_Module__FXNS__C,
        ((xdc_UArg)((void*)0x1000)),  /* remainSize */
        ((xdc_UArg)((void*)0x1000)),  /* startSize */
    },
};

/* Module__state__V */
xdc_runtime_HeapStd_Module_State__ xdc_runtime_HeapStd_Module__state__V = {
    ((xdc_UArg)((void*)0x0)),  /* remainRTSSize */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__diagsEnabled xdc_runtime_HeapStd_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__diagsIncluded xdc_runtime_HeapStd_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__diagsMask xdc_runtime_HeapStd_Module__diagsMask__C = ((CT__xdc_runtime_HeapStd_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__gateObj xdc_runtime_HeapStd_Module__gateObj__C = ((CT__xdc_runtime_HeapStd_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__gatePrms xdc_runtime_HeapStd_Module__gatePrms__C = ((CT__xdc_runtime_HeapStd_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__id xdc_runtime_HeapStd_Module__id__C = (xdc_Bits16)0x800b;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerDefined xdc_runtime_HeapStd_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerObj xdc_runtime_HeapStd_Module__loggerObj__C = ((CT__xdc_runtime_HeapStd_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerFxn0 xdc_runtime_HeapStd_Module__loggerFxn0__C = ((CT__xdc_runtime_HeapStd_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerFxn1 xdc_runtime_HeapStd_Module__loggerFxn1__C = ((CT__xdc_runtime_HeapStd_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerFxn2 xdc_runtime_HeapStd_Module__loggerFxn2__C = ((CT__xdc_runtime_HeapStd_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerFxn4 xdc_runtime_HeapStd_Module__loggerFxn4__C = ((CT__xdc_runtime_HeapStd_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__loggerFxn8 xdc_runtime_HeapStd_Module__loggerFxn8__C = ((CT__xdc_runtime_HeapStd_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_HeapStd_Module__startupDoneFxn xdc_runtime_HeapStd_Module__startupDoneFxn__C = ((CT__xdc_runtime_HeapStd_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_HeapStd_Object__count xdc_runtime_HeapStd_Object__count__C = 1;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_HeapStd_Object__heap xdc_runtime_HeapStd_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_HeapStd_Object__sizeof xdc_runtime_HeapStd_Object__sizeof__C = sizeof(xdc_runtime_HeapStd_Object__);

/* Object__table__C */
__FAR__ const CT__xdc_runtime_HeapStd_Object__table xdc_runtime_HeapStd_Object__table__C = xdc_runtime_HeapStd_Object__table__V;

/* E_noRTSMemory__C */
__FAR__ const CT__xdc_runtime_HeapStd_E_noRTSMemory xdc_runtime_HeapStd_E_noRTSMemory__C = (((xdc_runtime_Error_Id)750) << 16 | 0);

/* A_zeroSize__C */
__FAR__ const CT__xdc_runtime_HeapStd_A_zeroSize xdc_runtime_HeapStd_A_zeroSize__C = (((xdc_runtime_Assert_Id)95) << 16 | 16);

/* A_invalidTotalFreeSize__C */
__FAR__ const CT__xdc_runtime_HeapStd_A_invalidTotalFreeSize xdc_runtime_HeapStd_A_invalidTotalFreeSize__C = (((xdc_runtime_Assert_Id)140) << 16 | 16);

/* A_invalidAlignment__C */
__FAR__ const CT__xdc_runtime_HeapStd_A_invalidAlignment xdc_runtime_HeapStd_A_invalidAlignment__C = (((xdc_runtime_Assert_Id)201) << 16 | 16);


/*
 * ======== xdc.runtime.Log INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_Log_Module__diagsEnabled xdc_runtime_Log_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_Log_Module__diagsIncluded xdc_runtime_Log_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_Log_Module__diagsMask xdc_runtime_Log_Module__diagsMask__C = ((CT__xdc_runtime_Log_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_Log_Module__gateObj xdc_runtime_Log_Module__gateObj__C = ((CT__xdc_runtime_Log_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_Log_Module__gatePrms xdc_runtime_Log_Module__gatePrms__C = ((CT__xdc_runtime_Log_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_Log_Module__id xdc_runtime_Log_Module__id__C = (xdc_Bits16)0x8008;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_Log_Module__loggerDefined xdc_runtime_Log_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_Log_Module__loggerObj xdc_runtime_Log_Module__loggerObj__C = ((CT__xdc_runtime_Log_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_Log_Module__loggerFxn0 xdc_runtime_Log_Module__loggerFxn0__C = ((CT__xdc_runtime_Log_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_Log_Module__loggerFxn1 xdc_runtime_Log_Module__loggerFxn1__C = ((CT__xdc_runtime_Log_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_Log_Module__loggerFxn2 xdc_runtime_Log_Module__loggerFxn2__C = ((CT__xdc_runtime_Log_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_Log_Module__loggerFxn4 xdc_runtime_Log_Module__loggerFxn4__C = ((CT__xdc_runtime_Log_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_Log_Module__loggerFxn8 xdc_runtime_Log_Module__loggerFxn8__C = ((CT__xdc_runtime_Log_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_Log_Module__startupDoneFxn xdc_runtime_Log_Module__startupDoneFxn__C = ((CT__xdc_runtime_Log_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_Log_Object__count xdc_runtime_Log_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_Log_Object__heap xdc_runtime_Log_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_Log_Object__sizeof xdc_runtime_Log_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_Log_Object__table xdc_runtime_Log_Object__table__C = 0;

/* L_construct__C */
__FAR__ const CT__xdc_runtime_Log_L_construct xdc_runtime_Log_L_construct__C = (((xdc_runtime_Log_Event)983) << 16 | 4);

/* L_create__C */
__FAR__ const CT__xdc_runtime_Log_L_create xdc_runtime_Log_L_create__C = (((xdc_runtime_Log_Event)1007) << 16 | 4);

/* L_destruct__C */
__FAR__ const CT__xdc_runtime_Log_L_destruct xdc_runtime_Log_L_destruct__C = (((xdc_runtime_Log_Event)1028) << 16 | 4);

/* L_delete__C */
__FAR__ const CT__xdc_runtime_Log_L_delete xdc_runtime_Log_L_delete__C = (((xdc_runtime_Log_Event)1047) << 16 | 4);

/* L_error__C */
__FAR__ const CT__xdc_runtime_Log_L_error xdc_runtime_Log_L_error__C = (((xdc_runtime_Log_Event)1064) << 16 | 192);

/* L_warning__C */
__FAR__ const CT__xdc_runtime_Log_L_warning xdc_runtime_Log_L_warning__C = (((xdc_runtime_Log_Event)1078) << 16 | 224);

/* L_info__C */
__FAR__ const CT__xdc_runtime_Log_L_info xdc_runtime_Log_L_info__C = (((xdc_runtime_Log_Event)1094) << 16 | 16384);


/*
 * ======== xdc.runtime.Main INITIALIZERS ========
 */

/* Module__root__V */
xdc_runtime_Main_Module__ xdc_runtime_Main_Module__root__V = {
    65439,  /* mask */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_Main_Module__diagsEnabled xdc_runtime_Main_Module__diagsEnabled__C = (xdc_Bits32)0x0;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_Main_Module__diagsIncluded xdc_runtime_Main_Module__diagsIncluded__C = (xdc_Bits32)0xff9f;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_Main_Module__diagsMask xdc_runtime_Main_Module__diagsMask__C = ((CT__xdc_runtime_Main_Module__diagsMask)((void*)&xdc_runtime_Main_Module__root__V.mask));

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_Main_Module__gateObj xdc_runtime_Main_Module__gateObj__C = ((CT__xdc_runtime_Main_Module__gateObj)((void*)(xdc_runtime_IGateProvider_Handle)&ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__V[0]));

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_Main_Module__gatePrms xdc_runtime_Main_Module__gatePrms__C = ((CT__xdc_runtime_Main_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_Main_Module__id xdc_runtime_Main_Module__id__C = (xdc_Bits16)0x8009;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_Main_Module__loggerDefined xdc_runtime_Main_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_Main_Module__loggerObj xdc_runtime_Main_Module__loggerObj__C = ((CT__xdc_runtime_Main_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_Main_Module__loggerFxn0 xdc_runtime_Main_Module__loggerFxn0__C = ((CT__xdc_runtime_Main_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_Main_Module__loggerFxn1 xdc_runtime_Main_Module__loggerFxn1__C = ((CT__xdc_runtime_Main_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_Main_Module__loggerFxn2 xdc_runtime_Main_Module__loggerFxn2__C = ((CT__xdc_runtime_Main_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_Main_Module__loggerFxn4 xdc_runtime_Main_Module__loggerFxn4__C = ((CT__xdc_runtime_Main_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_Main_Module__loggerFxn8 xdc_runtime_Main_Module__loggerFxn8__C = ((CT__xdc_runtime_Main_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_Main_Module__startupDoneFxn xdc_runtime_Main_Module__startupDoneFxn__C = ((CT__xdc_runtime_Main_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_Main_Object__count xdc_runtime_Main_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_Main_Object__heap xdc_runtime_Main_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_Main_Object__sizeof xdc_runtime_Main_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_Main_Object__table xdc_runtime_Main_Object__table__C = 0;


/*
 * ======== xdc.runtime.Main_Module_GateProxy INITIALIZERS ========
 */


/*
 * ======== xdc.runtime.Memory INITIALIZERS ========
 */

/* Module__state__V */
xdc_runtime_Memory_Module_State__ xdc_runtime_Memory_Module__state__V = {
    (xdc_SizeT)0x4,  /* maxDefaultTypeAlign */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_Memory_Module__diagsEnabled xdc_runtime_Memory_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_Memory_Module__diagsIncluded xdc_runtime_Memory_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_Memory_Module__diagsMask xdc_runtime_Memory_Module__diagsMask__C = ((CT__xdc_runtime_Memory_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_Memory_Module__gateObj xdc_runtime_Memory_Module__gateObj__C = ((CT__xdc_runtime_Memory_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_Memory_Module__gatePrms xdc_runtime_Memory_Module__gatePrms__C = ((CT__xdc_runtime_Memory_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_Memory_Module__id xdc_runtime_Memory_Module__id__C = (xdc_Bits16)0x800a;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_Memory_Module__loggerDefined xdc_runtime_Memory_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_Memory_Module__loggerObj xdc_runtime_Memory_Module__loggerObj__C = ((CT__xdc_runtime_Memory_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_Memory_Module__loggerFxn0 xdc_runtime_Memory_Module__loggerFxn0__C = ((CT__xdc_runtime_Memory_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_Memory_Module__loggerFxn1 xdc_runtime_Memory_Module__loggerFxn1__C = ((CT__xdc_runtime_Memory_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_Memory_Module__loggerFxn2 xdc_runtime_Memory_Module__loggerFxn2__C = ((CT__xdc_runtime_Memory_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_Memory_Module__loggerFxn4 xdc_runtime_Memory_Module__loggerFxn4__C = ((CT__xdc_runtime_Memory_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_Memory_Module__loggerFxn8 xdc_runtime_Memory_Module__loggerFxn8__C = ((CT__xdc_runtime_Memory_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_Memory_Module__startupDoneFxn xdc_runtime_Memory_Module__startupDoneFxn__C = ((CT__xdc_runtime_Memory_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_Memory_Object__count xdc_runtime_Memory_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_Memory_Object__heap xdc_runtime_Memory_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_Memory_Object__sizeof xdc_runtime_Memory_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_Memory_Object__table xdc_runtime_Memory_Object__table__C = 0;

/* defaultHeapInstance__C */
__FAR__ const CT__xdc_runtime_Memory_defaultHeapInstance xdc_runtime_Memory_defaultHeapInstance__C = (xdc_runtime_IHeap_Handle)&xdc_runtime_HeapStd_Object__table__V[0];


/*
 * ======== xdc.runtime.Memory_HeapProxy INITIALIZERS ========
 */


/*
 * ======== xdc.runtime.Registry INITIALIZERS ========
 */

/* Module__root__V */
xdc_runtime_Registry_Module__ xdc_runtime_Registry_Module__root__V = {
    0,  /* mask */
};

/* Module__state__V */
xdc_runtime_Registry_Module_State__ xdc_runtime_Registry_Module__state__V = {
    ((xdc_runtime_Types_RegDesc*)0),  /* listHead */
    (xdc_Bits16)0x7fff,  /* curId */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_Registry_Module__diagsEnabled xdc_runtime_Registry_Module__diagsEnabled__C = (xdc_Bits32)0x0;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_Registry_Module__diagsIncluded xdc_runtime_Registry_Module__diagsIncluded__C = (xdc_Bits32)0xff9f;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_Registry_Module__diagsMask xdc_runtime_Registry_Module__diagsMask__C = ((CT__xdc_runtime_Registry_Module__diagsMask)((void*)&xdc_runtime_Registry_Module__root__V.mask));

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_Registry_Module__gateObj xdc_runtime_Registry_Module__gateObj__C = ((CT__xdc_runtime_Registry_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_Registry_Module__gatePrms xdc_runtime_Registry_Module__gatePrms__C = ((CT__xdc_runtime_Registry_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_Registry_Module__id xdc_runtime_Registry_Module__id__C = (xdc_Bits16)0x800c;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_Registry_Module__loggerDefined xdc_runtime_Registry_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_Registry_Module__loggerObj xdc_runtime_Registry_Module__loggerObj__C = ((CT__xdc_runtime_Registry_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_Registry_Module__loggerFxn0 xdc_runtime_Registry_Module__loggerFxn0__C = ((CT__xdc_runtime_Registry_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_Registry_Module__loggerFxn1 xdc_runtime_Registry_Module__loggerFxn1__C = ((CT__xdc_runtime_Registry_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_Registry_Module__loggerFxn2 xdc_runtime_Registry_Module__loggerFxn2__C = ((CT__xdc_runtime_Registry_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_Registry_Module__loggerFxn4 xdc_runtime_Registry_Module__loggerFxn4__C = ((CT__xdc_runtime_Registry_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_Registry_Module__loggerFxn8 xdc_runtime_Registry_Module__loggerFxn8__C = ((CT__xdc_runtime_Registry_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_Registry_Module__startupDoneFxn xdc_runtime_Registry_Module__startupDoneFxn__C = ((CT__xdc_runtime_Registry_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_Registry_Object__count xdc_runtime_Registry_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_Registry_Object__heap xdc_runtime_Registry_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_Registry_Object__sizeof xdc_runtime_Registry_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_Registry_Object__table xdc_runtime_Registry_Object__table__C = 0;


/*
 * ======== xdc.runtime.Startup INITIALIZERS ========
 */

/* Module__state__V */
xdc_runtime_Startup_Module_State__ xdc_runtime_Startup_Module__state__V = {
    ((xdc_Int*)0),  /* stateTab */
    0,  /* execFlag */
    0,  /* rtsDoneFlag */
};

/* --> xdc_runtime_Startup_sfxnTab__A */
const __T1_xdc_runtime_Startup_sfxnTab xdc_runtime_Startup_sfxnTab__A[6] = {
    ((xdc_Int(*)(xdc_Int))((xdc_Fxn)xdc_runtime_System_Module_startup__E)),  /* [0] */
    ((xdc_Int(*)(xdc_Int))((xdc_Fxn)ti_sdo_xdcruntime_linux_GateThreadSupport_Module_startup__E)),  /* [1] */
    ((xdc_Int(*)(xdc_Int))((xdc_Fxn)ti_sdo_xdcruntime_linux_SemThreadSupport_Module_startup__E)),  /* [2] */
    ((xdc_Int(*)(xdc_Int))((xdc_Fxn)ti_sdo_xdcruntime_linux_SemProcessSupport_Module_startup__E)),  /* [3] */
    ((xdc_Int(*)(xdc_Int))((xdc_Fxn)ti_sdo_xdcruntime_linux_ThreadSupport_Module_startup__E)),  /* [4] */
    ((xdc_Int(*)(xdc_Int))((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_Module_startup__E)),  /* [5] */
};

/* --> xdc_runtime_Startup_sfxnRts__A */
const __T1_xdc_runtime_Startup_sfxnRts xdc_runtime_Startup_sfxnRts__A[6] = {
    1,  /* [0] */
    1,  /* [1] */
    0,  /* [2] */
    0,  /* [3] */
    0,  /* [4] */
    1,  /* [5] */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_Startup_Module__diagsEnabled xdc_runtime_Startup_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_Startup_Module__diagsIncluded xdc_runtime_Startup_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_Startup_Module__diagsMask xdc_runtime_Startup_Module__diagsMask__C = ((CT__xdc_runtime_Startup_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_Startup_Module__gateObj xdc_runtime_Startup_Module__gateObj__C = ((CT__xdc_runtime_Startup_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_Startup_Module__gatePrms xdc_runtime_Startup_Module__gatePrms__C = ((CT__xdc_runtime_Startup_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_Startup_Module__id xdc_runtime_Startup_Module__id__C = (xdc_Bits16)0x800d;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_Startup_Module__loggerDefined xdc_runtime_Startup_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_Startup_Module__loggerObj xdc_runtime_Startup_Module__loggerObj__C = ((CT__xdc_runtime_Startup_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_Startup_Module__loggerFxn0 xdc_runtime_Startup_Module__loggerFxn0__C = ((CT__xdc_runtime_Startup_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_Startup_Module__loggerFxn1 xdc_runtime_Startup_Module__loggerFxn1__C = ((CT__xdc_runtime_Startup_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_Startup_Module__loggerFxn2 xdc_runtime_Startup_Module__loggerFxn2__C = ((CT__xdc_runtime_Startup_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_Startup_Module__loggerFxn4 xdc_runtime_Startup_Module__loggerFxn4__C = ((CT__xdc_runtime_Startup_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_Startup_Module__loggerFxn8 xdc_runtime_Startup_Module__loggerFxn8__C = ((CT__xdc_runtime_Startup_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_Startup_Module__startupDoneFxn xdc_runtime_Startup_Module__startupDoneFxn__C = ((CT__xdc_runtime_Startup_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_Startup_Object__count xdc_runtime_Startup_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_Startup_Object__heap xdc_runtime_Startup_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_Startup_Object__sizeof xdc_runtime_Startup_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_Startup_Object__table xdc_runtime_Startup_Object__table__C = 0;

/* maxPasses__C */
__FAR__ const CT__xdc_runtime_Startup_maxPasses xdc_runtime_Startup_maxPasses__C = (xdc_Int)0x20;

/* firstFxns__C */
__FAR__ const CT__xdc_runtime_Startup_firstFxns xdc_runtime_Startup_firstFxns__C = {0, 0};

/* lastFxns__C */
__FAR__ const CT__xdc_runtime_Startup_lastFxns xdc_runtime_Startup_lastFxns__C = {0, 0};

/* startModsFxn__C */
__FAR__ const CT__xdc_runtime_Startup_startModsFxn xdc_runtime_Startup_startModsFxn__C = ((CT__xdc_runtime_Startup_startModsFxn)((xdc_Fxn)xdc_runtime_Startup_startMods__I));

/* execImpl__C */
__FAR__ const CT__xdc_runtime_Startup_execImpl xdc_runtime_Startup_execImpl__C = ((CT__xdc_runtime_Startup_execImpl)((xdc_Fxn)xdc_runtime_Startup_exec__I));

/* sfxnTab__C */
__FAR__ const CT__xdc_runtime_Startup_sfxnTab xdc_runtime_Startup_sfxnTab__C = ((CT__xdc_runtime_Startup_sfxnTab)xdc_runtime_Startup_sfxnTab__A);

/* sfxnRts__C */
__FAR__ const CT__xdc_runtime_Startup_sfxnRts xdc_runtime_Startup_sfxnRts__C = ((CT__xdc_runtime_Startup_sfxnRts)xdc_runtime_Startup_sfxnRts__A);


/*
 * ======== xdc.runtime.SysStd INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__diagsEnabled xdc_runtime_SysStd_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__diagsIncluded xdc_runtime_SysStd_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__diagsMask xdc_runtime_SysStd_Module__diagsMask__C = ((CT__xdc_runtime_SysStd_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__gateObj xdc_runtime_SysStd_Module__gateObj__C = ((CT__xdc_runtime_SysStd_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__gatePrms xdc_runtime_SysStd_Module__gatePrms__C = ((CT__xdc_runtime_SysStd_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__id xdc_runtime_SysStd_Module__id__C = (xdc_Bits16)0x800f;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__loggerDefined xdc_runtime_SysStd_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__loggerObj xdc_runtime_SysStd_Module__loggerObj__C = ((CT__xdc_runtime_SysStd_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__loggerFxn0 xdc_runtime_SysStd_Module__loggerFxn0__C = ((CT__xdc_runtime_SysStd_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__loggerFxn1 xdc_runtime_SysStd_Module__loggerFxn1__C = ((CT__xdc_runtime_SysStd_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__loggerFxn2 xdc_runtime_SysStd_Module__loggerFxn2__C = ((CT__xdc_runtime_SysStd_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__loggerFxn4 xdc_runtime_SysStd_Module__loggerFxn4__C = ((CT__xdc_runtime_SysStd_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__loggerFxn8 xdc_runtime_SysStd_Module__loggerFxn8__C = ((CT__xdc_runtime_SysStd_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_SysStd_Module__startupDoneFxn xdc_runtime_SysStd_Module__startupDoneFxn__C = ((CT__xdc_runtime_SysStd_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_SysStd_Object__count xdc_runtime_SysStd_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_SysStd_Object__heap xdc_runtime_SysStd_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_SysStd_Object__sizeof xdc_runtime_SysStd_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_SysStd_Object__table xdc_runtime_SysStd_Object__table__C = 0;


/*
 * ======== xdc.runtime.System INITIALIZERS ========
 */

/* --> xdc_runtime_System_Module_State_0_atexitHandlers__A */
__T1_xdc_runtime_System_Module_State__atexitHandlers xdc_runtime_System_Module_State_0_atexitHandlers__A[8] = {
    ((xdc_Void(*)(xdc_Int))0),  /* [0] */
    ((xdc_Void(*)(xdc_Int))0),  /* [1] */
    ((xdc_Void(*)(xdc_Int))0),  /* [2] */
    ((xdc_Void(*)(xdc_Int))0),  /* [3] */
    ((xdc_Void(*)(xdc_Int))0),  /* [4] */
    ((xdc_Void(*)(xdc_Int))0),  /* [5] */
    ((xdc_Void(*)(xdc_Int))0),  /* [6] */
    ((xdc_Void(*)(xdc_Int))0),  /* [7] */
};

/* Module__state__V */
xdc_runtime_System_Module_State__ xdc_runtime_System_Module__state__V = {
    ((void*)xdc_runtime_System_Module_State_0_atexitHandlers__A),  /* atexitHandlers */
    (xdc_Int)0x0,  /* numAtexitHandlers */
    (xdc_Int)0xcafe,  /* exitStatus */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_System_Module__diagsEnabled xdc_runtime_System_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_System_Module__diagsIncluded xdc_runtime_System_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_System_Module__diagsMask xdc_runtime_System_Module__diagsMask__C = ((CT__xdc_runtime_System_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_System_Module__gateObj xdc_runtime_System_Module__gateObj__C = ((CT__xdc_runtime_System_Module__gateObj)((void*)(xdc_runtime_IGateProvider_Handle)&ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__V[0]));

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_System_Module__gatePrms xdc_runtime_System_Module__gatePrms__C = ((CT__xdc_runtime_System_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_System_Module__id xdc_runtime_System_Module__id__C = (xdc_Bits16)0x800e;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_System_Module__loggerDefined xdc_runtime_System_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_System_Module__loggerObj xdc_runtime_System_Module__loggerObj__C = ((CT__xdc_runtime_System_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_System_Module__loggerFxn0 xdc_runtime_System_Module__loggerFxn0__C = ((CT__xdc_runtime_System_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_System_Module__loggerFxn1 xdc_runtime_System_Module__loggerFxn1__C = ((CT__xdc_runtime_System_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_System_Module__loggerFxn2 xdc_runtime_System_Module__loggerFxn2__C = ((CT__xdc_runtime_System_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_System_Module__loggerFxn4 xdc_runtime_System_Module__loggerFxn4__C = ((CT__xdc_runtime_System_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_System_Module__loggerFxn8 xdc_runtime_System_Module__loggerFxn8__C = ((CT__xdc_runtime_System_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_System_Module__startupDoneFxn xdc_runtime_System_Module__startupDoneFxn__C = ((CT__xdc_runtime_System_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_System_Object__count xdc_runtime_System_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_System_Object__heap xdc_runtime_System_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_System_Object__sizeof xdc_runtime_System_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_System_Object__table xdc_runtime_System_Object__table__C = 0;

/* A_cannotFitIntoArg__C */
__FAR__ const CT__xdc_runtime_System_A_cannotFitIntoArg xdc_runtime_System_A_cannotFitIntoArg__C = (((xdc_runtime_Assert_Id)307) << 16 | 16);

/* maxAtexitHandlers__C */
__FAR__ const CT__xdc_runtime_System_maxAtexitHandlers xdc_runtime_System_maxAtexitHandlers__C = (xdc_Int)0x8;

/* extendFxn__C */
__FAR__ const CT__xdc_runtime_System_extendFxn xdc_runtime_System_extendFxn__C = ((CT__xdc_runtime_System_extendFxn)((xdc_Fxn)xdc_runtime_System_printfExtend__I));


/*
 * ======== xdc.runtime.System_Module_GateProxy INITIALIZERS ========
 */


/*
 * ======== xdc.runtime.System_SupportProxy INITIALIZERS ========
 */


/*
 * ======== xdc.runtime.Text INITIALIZERS ========
 */

/* Module__state__V */
xdc_runtime_Text_Module_State__ xdc_runtime_Text_Module__state__V = {
    ((xdc_Ptr)((void*)&xdc_runtime_Text_charTab__A[0])),  /* charBase */
    ((xdc_Ptr)((void*)&xdc_runtime_Text_nodeTab__A[0])),  /* nodeBase */
};

/* --> xdc_runtime_Text_charTab__A */
const __T1_xdc_runtime_Text_charTab xdc_runtime_Text_charTab__A[1970] = {
    (xdc_Char)0x0,  /* [0] */
    (xdc_Char)0x41,  /* [1] */
    (xdc_Char)0x5f,  /* [2] */
    (xdc_Char)0x69,  /* [3] */
    (xdc_Char)0x6e,  /* [4] */
    (xdc_Char)0x69,  /* [5] */
    (xdc_Char)0x74,  /* [6] */
    (xdc_Char)0x69,  /* [7] */
    (xdc_Char)0x61,  /* [8] */
    (xdc_Char)0x6c,  /* [9] */
    (xdc_Char)0x69,  /* [10] */
    (xdc_Char)0x7a,  /* [11] */
    (xdc_Char)0x65,  /* [12] */
    (xdc_Char)0x64,  /* [13] */
    (xdc_Char)0x50,  /* [14] */
    (xdc_Char)0x61,  /* [15] */
    (xdc_Char)0x72,  /* [16] */
    (xdc_Char)0x61,  /* [17] */
    (xdc_Char)0x6d,  /* [18] */
    (xdc_Char)0x73,  /* [19] */
    (xdc_Char)0x3a,  /* [20] */
    (xdc_Char)0x20,  /* [21] */
    (xdc_Char)0x75,  /* [22] */
    (xdc_Char)0x6e,  /* [23] */
    (xdc_Char)0x69,  /* [24] */
    (xdc_Char)0x6e,  /* [25] */
    (xdc_Char)0x69,  /* [26] */
    (xdc_Char)0x74,  /* [27] */
    (xdc_Char)0x69,  /* [28] */
    (xdc_Char)0x61,  /* [29] */
    (xdc_Char)0x6c,  /* [30] */
    (xdc_Char)0x69,  /* [31] */
    (xdc_Char)0x7a,  /* [32] */
    (xdc_Char)0x65,  /* [33] */
    (xdc_Char)0x64,  /* [34] */
    (xdc_Char)0x20,  /* [35] */
    (xdc_Char)0x50,  /* [36] */
    (xdc_Char)0x61,  /* [37] */
    (xdc_Char)0x72,  /* [38] */
    (xdc_Char)0x61,  /* [39] */
    (xdc_Char)0x6d,  /* [40] */
    (xdc_Char)0x73,  /* [41] */
    (xdc_Char)0x20,  /* [42] */
    (xdc_Char)0x73,  /* [43] */
    (xdc_Char)0x74,  /* [44] */
    (xdc_Char)0x72,  /* [45] */
    (xdc_Char)0x75,  /* [46] */
    (xdc_Char)0x63,  /* [47] */
    (xdc_Char)0x74,  /* [48] */
    (xdc_Char)0x0,  /* [49] */
    (xdc_Char)0x48,  /* [50] */
    (xdc_Char)0x65,  /* [51] */
    (xdc_Char)0x61,  /* [52] */
    (xdc_Char)0x70,  /* [53] */
    (xdc_Char)0x4d,  /* [54] */
    (xdc_Char)0x69,  /* [55] */
    (xdc_Char)0x6e,  /* [56] */
    (xdc_Char)0x5f,  /* [57] */
    (xdc_Char)0x63,  /* [58] */
    (xdc_Char)0x72,  /* [59] */
    (xdc_Char)0x65,  /* [60] */
    (xdc_Char)0x61,  /* [61] */
    (xdc_Char)0x74,  /* [62] */
    (xdc_Char)0x65,  /* [63] */
    (xdc_Char)0x20,  /* [64] */
    (xdc_Char)0x63,  /* [65] */
    (xdc_Char)0x61,  /* [66] */
    (xdc_Char)0x6e,  /* [67] */
    (xdc_Char)0x6e,  /* [68] */
    (xdc_Char)0x6f,  /* [69] */
    (xdc_Char)0x74,  /* [70] */
    (xdc_Char)0x20,  /* [71] */
    (xdc_Char)0x68,  /* [72] */
    (xdc_Char)0x61,  /* [73] */
    (xdc_Char)0x76,  /* [74] */
    (xdc_Char)0x65,  /* [75] */
    (xdc_Char)0x20,  /* [76] */
    (xdc_Char)0x61,  /* [77] */
    (xdc_Char)0x20,  /* [78] */
    (xdc_Char)0x7a,  /* [79] */
    (xdc_Char)0x65,  /* [80] */
    (xdc_Char)0x72,  /* [81] */
    (xdc_Char)0x6f,  /* [82] */
    (xdc_Char)0x20,  /* [83] */
    (xdc_Char)0x73,  /* [84] */
    (xdc_Char)0x69,  /* [85] */
    (xdc_Char)0x7a,  /* [86] */
    (xdc_Char)0x65,  /* [87] */
    (xdc_Char)0x20,  /* [88] */
    (xdc_Char)0x76,  /* [89] */
    (xdc_Char)0x61,  /* [90] */
    (xdc_Char)0x6c,  /* [91] */
    (xdc_Char)0x75,  /* [92] */
    (xdc_Char)0x65,  /* [93] */
    (xdc_Char)0x0,  /* [94] */
    (xdc_Char)0x48,  /* [95] */
    (xdc_Char)0x65,  /* [96] */
    (xdc_Char)0x61,  /* [97] */
    (xdc_Char)0x70,  /* [98] */
    (xdc_Char)0x53,  /* [99] */
    (xdc_Char)0x74,  /* [100] */
    (xdc_Char)0x64,  /* [101] */
    (xdc_Char)0x5f,  /* [102] */
    (xdc_Char)0x63,  /* [103] */
    (xdc_Char)0x72,  /* [104] */
    (xdc_Char)0x65,  /* [105] */
    (xdc_Char)0x61,  /* [106] */
    (xdc_Char)0x74,  /* [107] */
    (xdc_Char)0x65,  /* [108] */
    (xdc_Char)0x20,  /* [109] */
    (xdc_Char)0x63,  /* [110] */
    (xdc_Char)0x61,  /* [111] */
    (xdc_Char)0x6e,  /* [112] */
    (xdc_Char)0x6e,  /* [113] */
    (xdc_Char)0x6f,  /* [114] */
    (xdc_Char)0x74,  /* [115] */
    (xdc_Char)0x20,  /* [116] */
    (xdc_Char)0x68,  /* [117] */
    (xdc_Char)0x61,  /* [118] */
    (xdc_Char)0x76,  /* [119] */
    (xdc_Char)0x65,  /* [120] */
    (xdc_Char)0x20,  /* [121] */
    (xdc_Char)0x61,  /* [122] */
    (xdc_Char)0x20,  /* [123] */
    (xdc_Char)0x7a,  /* [124] */
    (xdc_Char)0x65,  /* [125] */
    (xdc_Char)0x72,  /* [126] */
    (xdc_Char)0x6f,  /* [127] */
    (xdc_Char)0x20,  /* [128] */
    (xdc_Char)0x73,  /* [129] */
    (xdc_Char)0x69,  /* [130] */
    (xdc_Char)0x7a,  /* [131] */
    (xdc_Char)0x65,  /* [132] */
    (xdc_Char)0x20,  /* [133] */
    (xdc_Char)0x76,  /* [134] */
    (xdc_Char)0x61,  /* [135] */
    (xdc_Char)0x6c,  /* [136] */
    (xdc_Char)0x75,  /* [137] */
    (xdc_Char)0x65,  /* [138] */
    (xdc_Char)0x0,  /* [139] */
    (xdc_Char)0x48,  /* [140] */
    (xdc_Char)0x65,  /* [141] */
    (xdc_Char)0x61,  /* [142] */
    (xdc_Char)0x70,  /* [143] */
    (xdc_Char)0x53,  /* [144] */
    (xdc_Char)0x74,  /* [145] */
    (xdc_Char)0x64,  /* [146] */
    (xdc_Char)0x20,  /* [147] */
    (xdc_Char)0x69,  /* [148] */
    (xdc_Char)0x6e,  /* [149] */
    (xdc_Char)0x73,  /* [150] */
    (xdc_Char)0x74,  /* [151] */
    (xdc_Char)0x61,  /* [152] */
    (xdc_Char)0x6e,  /* [153] */
    (xdc_Char)0x63,  /* [154] */
    (xdc_Char)0x65,  /* [155] */
    (xdc_Char)0x20,  /* [156] */
    (xdc_Char)0x74,  /* [157] */
    (xdc_Char)0x6f,  /* [158] */
    (xdc_Char)0x74,  /* [159] */
    (xdc_Char)0x61,  /* [160] */
    (xdc_Char)0x6c,  /* [161] */
    (xdc_Char)0x46,  /* [162] */
    (xdc_Char)0x72,  /* [163] */
    (xdc_Char)0x65,  /* [164] */
    (xdc_Char)0x65,  /* [165] */
    (xdc_Char)0x53,  /* [166] */
    (xdc_Char)0x69,  /* [167] */
    (xdc_Char)0x7a,  /* [168] */
    (xdc_Char)0x65,  /* [169] */
    (xdc_Char)0x20,  /* [170] */
    (xdc_Char)0x69,  /* [171] */
    (xdc_Char)0x73,  /* [172] */
    (xdc_Char)0x20,  /* [173] */
    (xdc_Char)0x67,  /* [174] */
    (xdc_Char)0x72,  /* [175] */
    (xdc_Char)0x65,  /* [176] */
    (xdc_Char)0x61,  /* [177] */
    (xdc_Char)0x74,  /* [178] */
    (xdc_Char)0x65,  /* [179] */
    (xdc_Char)0x72,  /* [180] */
    (xdc_Char)0x20,  /* [181] */
    (xdc_Char)0x74,  /* [182] */
    (xdc_Char)0x68,  /* [183] */
    (xdc_Char)0x61,  /* [184] */
    (xdc_Char)0x6e,  /* [185] */
    (xdc_Char)0x20,  /* [186] */
    (xdc_Char)0x73,  /* [187] */
    (xdc_Char)0x74,  /* [188] */
    (xdc_Char)0x61,  /* [189] */
    (xdc_Char)0x72,  /* [190] */
    (xdc_Char)0x74,  /* [191] */
    (xdc_Char)0x69,  /* [192] */
    (xdc_Char)0x6e,  /* [193] */
    (xdc_Char)0x67,  /* [194] */
    (xdc_Char)0x20,  /* [195] */
    (xdc_Char)0x73,  /* [196] */
    (xdc_Char)0x69,  /* [197] */
    (xdc_Char)0x7a,  /* [198] */
    (xdc_Char)0x65,  /* [199] */
    (xdc_Char)0x0,  /* [200] */
    (xdc_Char)0x48,  /* [201] */
    (xdc_Char)0x65,  /* [202] */
    (xdc_Char)0x61,  /* [203] */
    (xdc_Char)0x70,  /* [204] */
    (xdc_Char)0x53,  /* [205] */
    (xdc_Char)0x74,  /* [206] */
    (xdc_Char)0x64,  /* [207] */
    (xdc_Char)0x5f,  /* [208] */
    (xdc_Char)0x61,  /* [209] */
    (xdc_Char)0x6c,  /* [210] */
    (xdc_Char)0x6c,  /* [211] */
    (xdc_Char)0x6f,  /* [212] */
    (xdc_Char)0x63,  /* [213] */
    (xdc_Char)0x20,  /* [214] */
    (xdc_Char)0x2d,  /* [215] */
    (xdc_Char)0x20,  /* [216] */
    (xdc_Char)0x72,  /* [217] */
    (xdc_Char)0x65,  /* [218] */
    (xdc_Char)0x71,  /* [219] */
    (xdc_Char)0x75,  /* [220] */
    (xdc_Char)0x65,  /* [221] */
    (xdc_Char)0x73,  /* [222] */
    (xdc_Char)0x74,  /* [223] */
    (xdc_Char)0x65,  /* [224] */
    (xdc_Char)0x64,  /* [225] */
    (xdc_Char)0x20,  /* [226] */
    (xdc_Char)0x61,  /* [227] */
    (xdc_Char)0x6c,  /* [228] */
    (xdc_Char)0x69,  /* [229] */
    (xdc_Char)0x67,  /* [230] */
    (xdc_Char)0x6e,  /* [231] */
    (xdc_Char)0x6d,  /* [232] */
    (xdc_Char)0x65,  /* [233] */
    (xdc_Char)0x6e,  /* [234] */
    (xdc_Char)0x74,  /* [235] */
    (xdc_Char)0x20,  /* [236] */
    (xdc_Char)0x69,  /* [237] */
    (xdc_Char)0x73,  /* [238] */
    (xdc_Char)0x20,  /* [239] */
    (xdc_Char)0x67,  /* [240] */
    (xdc_Char)0x72,  /* [241] */
    (xdc_Char)0x65,  /* [242] */
    (xdc_Char)0x61,  /* [243] */
    (xdc_Char)0x74,  /* [244] */
    (xdc_Char)0x65,  /* [245] */
    (xdc_Char)0x72,  /* [246] */
    (xdc_Char)0x20,  /* [247] */
    (xdc_Char)0x74,  /* [248] */
    (xdc_Char)0x68,  /* [249] */
    (xdc_Char)0x61,  /* [250] */
    (xdc_Char)0x6e,  /* [251] */
    (xdc_Char)0x20,  /* [252] */
    (xdc_Char)0x61,  /* [253] */
    (xdc_Char)0x6c,  /* [254] */
    (xdc_Char)0x6c,  /* [255] */
    (xdc_Char)0x6f,  /* [256] */
    (xdc_Char)0x77,  /* [257] */
    (xdc_Char)0x65,  /* [258] */
    (xdc_Char)0x64,  /* [259] */
    (xdc_Char)0x0,  /* [260] */
    (xdc_Char)0x41,  /* [261] */
    (xdc_Char)0x5f,  /* [262] */
    (xdc_Char)0x69,  /* [263] */
    (xdc_Char)0x6e,  /* [264] */
    (xdc_Char)0x76,  /* [265] */
    (xdc_Char)0x61,  /* [266] */
    (xdc_Char)0x6c,  /* [267] */
    (xdc_Char)0x69,  /* [268] */
    (xdc_Char)0x64,  /* [269] */
    (xdc_Char)0x4c,  /* [270] */
    (xdc_Char)0x6f,  /* [271] */
    (xdc_Char)0x67,  /* [272] */
    (xdc_Char)0x67,  /* [273] */
    (xdc_Char)0x65,  /* [274] */
    (xdc_Char)0x72,  /* [275] */
    (xdc_Char)0x3a,  /* [276] */
    (xdc_Char)0x20,  /* [277] */
    (xdc_Char)0x54,  /* [278] */
    (xdc_Char)0x68,  /* [279] */
    (xdc_Char)0x65,  /* [280] */
    (xdc_Char)0x20,  /* [281] */
    (xdc_Char)0x6c,  /* [282] */
    (xdc_Char)0x6f,  /* [283] */
    (xdc_Char)0x67,  /* [284] */
    (xdc_Char)0x67,  /* [285] */
    (xdc_Char)0x65,  /* [286] */
    (xdc_Char)0x72,  /* [287] */
    (xdc_Char)0x20,  /* [288] */
    (xdc_Char)0x69,  /* [289] */
    (xdc_Char)0x64,  /* [290] */
    (xdc_Char)0x20,  /* [291] */
    (xdc_Char)0x25,  /* [292] */
    (xdc_Char)0x64,  /* [293] */
    (xdc_Char)0x20,  /* [294] */
    (xdc_Char)0x69,  /* [295] */
    (xdc_Char)0x73,  /* [296] */
    (xdc_Char)0x20,  /* [297] */
    (xdc_Char)0x69,  /* [298] */
    (xdc_Char)0x6e,  /* [299] */
    (xdc_Char)0x76,  /* [300] */
    (xdc_Char)0x61,  /* [301] */
    (xdc_Char)0x6c,  /* [302] */
    (xdc_Char)0x69,  /* [303] */
    (xdc_Char)0x64,  /* [304] */
    (xdc_Char)0x2e,  /* [305] */
    (xdc_Char)0x0,  /* [306] */
    (xdc_Char)0x41,  /* [307] */
    (xdc_Char)0x5f,  /* [308] */
    (xdc_Char)0x63,  /* [309] */
    (xdc_Char)0x61,  /* [310] */
    (xdc_Char)0x6e,  /* [311] */
    (xdc_Char)0x6e,  /* [312] */
    (xdc_Char)0x6f,  /* [313] */
    (xdc_Char)0x74,  /* [314] */
    (xdc_Char)0x46,  /* [315] */
    (xdc_Char)0x69,  /* [316] */
    (xdc_Char)0x74,  /* [317] */
    (xdc_Char)0x49,  /* [318] */
    (xdc_Char)0x6e,  /* [319] */
    (xdc_Char)0x74,  /* [320] */
    (xdc_Char)0x6f,  /* [321] */
    (xdc_Char)0x41,  /* [322] */
    (xdc_Char)0x72,  /* [323] */
    (xdc_Char)0x67,  /* [324] */
    (xdc_Char)0x3a,  /* [325] */
    (xdc_Char)0x20,  /* [326] */
    (xdc_Char)0x73,  /* [327] */
    (xdc_Char)0x69,  /* [328] */
    (xdc_Char)0x7a,  /* [329] */
    (xdc_Char)0x65,  /* [330] */
    (xdc_Char)0x6f,  /* [331] */
    (xdc_Char)0x66,  /* [332] */
    (xdc_Char)0x28,  /* [333] */
    (xdc_Char)0x46,  /* [334] */
    (xdc_Char)0x6c,  /* [335] */
    (xdc_Char)0x6f,  /* [336] */
    (xdc_Char)0x61,  /* [337] */
    (xdc_Char)0x74,  /* [338] */
    (xdc_Char)0x29,  /* [339] */
    (xdc_Char)0x20,  /* [340] */
    (xdc_Char)0x3e,  /* [341] */
    (xdc_Char)0x20,  /* [342] */
    (xdc_Char)0x73,  /* [343] */
    (xdc_Char)0x69,  /* [344] */
    (xdc_Char)0x7a,  /* [345] */
    (xdc_Char)0x65,  /* [346] */
    (xdc_Char)0x6f,  /* [347] */
    (xdc_Char)0x66,  /* [348] */
    (xdc_Char)0x28,  /* [349] */
    (xdc_Char)0x41,  /* [350] */
    (xdc_Char)0x72,  /* [351] */
    (xdc_Char)0x67,  /* [352] */
    (xdc_Char)0x29,  /* [353] */
    (xdc_Char)0x0,  /* [354] */
    (xdc_Char)0x41,  /* [355] */
    (xdc_Char)0x5f,  /* [356] */
    (xdc_Char)0x7a,  /* [357] */
    (xdc_Char)0x65,  /* [358] */
    (xdc_Char)0x72,  /* [359] */
    (xdc_Char)0x6f,  /* [360] */
    (xdc_Char)0x54,  /* [361] */
    (xdc_Char)0x69,  /* [362] */
    (xdc_Char)0x6d,  /* [363] */
    (xdc_Char)0x65,  /* [364] */
    (xdc_Char)0x6f,  /* [365] */
    (xdc_Char)0x75,  /* [366] */
    (xdc_Char)0x74,  /* [367] */
    (xdc_Char)0x3a,  /* [368] */
    (xdc_Char)0x20,  /* [369] */
    (xdc_Char)0x54,  /* [370] */
    (xdc_Char)0x69,  /* [371] */
    (xdc_Char)0x6d,  /* [372] */
    (xdc_Char)0x65,  /* [373] */
    (xdc_Char)0x6f,  /* [374] */
    (xdc_Char)0x75,  /* [375] */
    (xdc_Char)0x74,  /* [376] */
    (xdc_Char)0x20,  /* [377] */
    (xdc_Char)0x76,  /* [378] */
    (xdc_Char)0x61,  /* [379] */
    (xdc_Char)0x6c,  /* [380] */
    (xdc_Char)0x75,  /* [381] */
    (xdc_Char)0x65,  /* [382] */
    (xdc_Char)0x20,  /* [383] */
    (xdc_Char)0x61,  /* [384] */
    (xdc_Char)0x6e,  /* [385] */
    (xdc_Char)0x6e,  /* [386] */
    (xdc_Char)0x6f,  /* [387] */
    (xdc_Char)0x74,  /* [388] */
    (xdc_Char)0x20,  /* [389] */
    (xdc_Char)0x62,  /* [390] */
    (xdc_Char)0x65,  /* [391] */
    (xdc_Char)0x20,  /* [392] */
    (xdc_Char)0x7a,  /* [393] */
    (xdc_Char)0x65,  /* [394] */
    (xdc_Char)0x72,  /* [395] */
    (xdc_Char)0x6f,  /* [396] */
    (xdc_Char)0x0,  /* [397] */
    (xdc_Char)0x41,  /* [398] */
    (xdc_Char)0x5f,  /* [399] */
    (xdc_Char)0x69,  /* [400] */
    (xdc_Char)0x6e,  /* [401] */
    (xdc_Char)0x76,  /* [402] */
    (xdc_Char)0x61,  /* [403] */
    (xdc_Char)0x6c,  /* [404] */
    (xdc_Char)0x69,  /* [405] */
    (xdc_Char)0x64,  /* [406] */
    (xdc_Char)0x4b,  /* [407] */
    (xdc_Char)0x65,  /* [408] */
    (xdc_Char)0x79,  /* [409] */
    (xdc_Char)0x3a,  /* [410] */
    (xdc_Char)0x20,  /* [411] */
    (xdc_Char)0x74,  /* [412] */
    (xdc_Char)0x68,  /* [413] */
    (xdc_Char)0x65,  /* [414] */
    (xdc_Char)0x20,  /* [415] */
    (xdc_Char)0x6b,  /* [416] */
    (xdc_Char)0x65,  /* [417] */
    (xdc_Char)0x79,  /* [418] */
    (xdc_Char)0x20,  /* [419] */
    (xdc_Char)0x6d,  /* [420] */
    (xdc_Char)0x75,  /* [421] */
    (xdc_Char)0x73,  /* [422] */
    (xdc_Char)0x74,  /* [423] */
    (xdc_Char)0x20,  /* [424] */
    (xdc_Char)0x62,  /* [425] */
    (xdc_Char)0x65,  /* [426] */
    (xdc_Char)0x20,  /* [427] */
    (xdc_Char)0x73,  /* [428] */
    (xdc_Char)0x65,  /* [429] */
    (xdc_Char)0x74,  /* [430] */
    (xdc_Char)0x20,  /* [431] */
    (xdc_Char)0x74,  /* [432] */
    (xdc_Char)0x6f,  /* [433] */
    (xdc_Char)0x20,  /* [434] */
    (xdc_Char)0x61,  /* [435] */
    (xdc_Char)0x20,  /* [436] */
    (xdc_Char)0x6e,  /* [437] */
    (xdc_Char)0x6f,  /* [438] */
    (xdc_Char)0x6e,  /* [439] */
    (xdc_Char)0x2d,  /* [440] */
    (xdc_Char)0x64,  /* [441] */
    (xdc_Char)0x65,  /* [442] */
    (xdc_Char)0x66,  /* [443] */
    (xdc_Char)0x61,  /* [444] */
    (xdc_Char)0x75,  /* [445] */
    (xdc_Char)0x6c,  /* [446] */
    (xdc_Char)0x74,  /* [447] */
    (xdc_Char)0x20,  /* [448] */
    (xdc_Char)0x76,  /* [449] */
    (xdc_Char)0x61,  /* [450] */
    (xdc_Char)0x6c,  /* [451] */
    (xdc_Char)0x75,  /* [452] */
    (xdc_Char)0x65,  /* [453] */
    (xdc_Char)0x0,  /* [454] */
    (xdc_Char)0x41,  /* [455] */
    (xdc_Char)0x5f,  /* [456] */
    (xdc_Char)0x50,  /* [457] */
    (xdc_Char)0x4f,  /* [458] */
    (xdc_Char)0x53,  /* [459] */
    (xdc_Char)0x49,  /* [460] */
    (xdc_Char)0x58,  /* [461] */
    (xdc_Char)0x5f,  /* [462] */
    (xdc_Char)0x45,  /* [463] */
    (xdc_Char)0x72,  /* [464] */
    (xdc_Char)0x72,  /* [465] */
    (xdc_Char)0x6f,  /* [466] */
    (xdc_Char)0x72,  /* [467] */
    (xdc_Char)0x3a,  /* [468] */
    (xdc_Char)0x20,  /* [469] */
    (xdc_Char)0x61,  /* [470] */
    (xdc_Char)0x20,  /* [471] */
    (xdc_Char)0x50,  /* [472] */
    (xdc_Char)0x4f,  /* [473] */
    (xdc_Char)0x53,  /* [474] */
    (xdc_Char)0x49,  /* [475] */
    (xdc_Char)0x58,  /* [476] */
    (xdc_Char)0x20,  /* [477] */
    (xdc_Char)0x66,  /* [478] */
    (xdc_Char)0x75,  /* [479] */
    (xdc_Char)0x6e,  /* [480] */
    (xdc_Char)0x63,  /* [481] */
    (xdc_Char)0x74,  /* [482] */
    (xdc_Char)0x69,  /* [483] */
    (xdc_Char)0x6f,  /* [484] */
    (xdc_Char)0x6e,  /* [485] */
    (xdc_Char)0x20,  /* [486] */
    (xdc_Char)0x72,  /* [487] */
    (xdc_Char)0x65,  /* [488] */
    (xdc_Char)0x74,  /* [489] */
    (xdc_Char)0x75,  /* [490] */
    (xdc_Char)0x72,  /* [491] */
    (xdc_Char)0x6e,  /* [492] */
    (xdc_Char)0x65,  /* [493] */
    (xdc_Char)0x64,  /* [494] */
    (xdc_Char)0x20,  /* [495] */
    (xdc_Char)0x66,  /* [496] */
    (xdc_Char)0x61,  /* [497] */
    (xdc_Char)0x69,  /* [498] */
    (xdc_Char)0x6c,  /* [499] */
    (xdc_Char)0x75,  /* [500] */
    (xdc_Char)0x72,  /* [501] */
    (xdc_Char)0x65,  /* [502] */
    (xdc_Char)0x0,  /* [503] */
    (xdc_Char)0x41,  /* [504] */
    (xdc_Char)0x5f,  /* [505] */
    (xdc_Char)0x69,  /* [506] */
    (xdc_Char)0x6e,  /* [507] */
    (xdc_Char)0x76,  /* [508] */
    (xdc_Char)0x61,  /* [509] */
    (xdc_Char)0x6c,  /* [510] */
    (xdc_Char)0x69,  /* [511] */
    (xdc_Char)0x64,  /* [512] */
    (xdc_Char)0x4b,  /* [513] */
    (xdc_Char)0x65,  /* [514] */
    (xdc_Char)0x79,  /* [515] */
    (xdc_Char)0x3a,  /* [516] */
    (xdc_Char)0x20,  /* [517] */
    (xdc_Char)0x70,  /* [518] */
    (xdc_Char)0x61,  /* [519] */
    (xdc_Char)0x72,  /* [520] */
    (xdc_Char)0x61,  /* [521] */
    (xdc_Char)0x6d,  /* [522] */
    (xdc_Char)0x73,  /* [523] */
    (xdc_Char)0x20,  /* [524] */
    (xdc_Char)0x6b,  /* [525] */
    (xdc_Char)0x65,  /* [526] */
    (xdc_Char)0x79,  /* [527] */
    (xdc_Char)0x20,  /* [528] */
    (xdc_Char)0x68,  /* [529] */
    (xdc_Char)0x61,  /* [530] */
    (xdc_Char)0x73,  /* [531] */
    (xdc_Char)0x20,  /* [532] */
    (xdc_Char)0x6e,  /* [533] */
    (xdc_Char)0x6f,  /* [534] */
    (xdc_Char)0x74,  /* [535] */
    (xdc_Char)0x20,  /* [536] */
    (xdc_Char)0x62,  /* [537] */
    (xdc_Char)0x65,  /* [538] */
    (xdc_Char)0x65,  /* [539] */
    (xdc_Char)0x6e,  /* [540] */
    (xdc_Char)0x20,  /* [541] */
    (xdc_Char)0x73,  /* [542] */
    (xdc_Char)0x65,  /* [543] */
    (xdc_Char)0x74,  /* [544] */
    (xdc_Char)0x0,  /* [545] */
    (xdc_Char)0x41,  /* [546] */
    (xdc_Char)0x5f,  /* [547] */
    (xdc_Char)0x75,  /* [548] */
    (xdc_Char)0x6e,  /* [549] */
    (xdc_Char)0x73,  /* [550] */
    (xdc_Char)0x75,  /* [551] */
    (xdc_Char)0x70,  /* [552] */
    (xdc_Char)0x70,  /* [553] */
    (xdc_Char)0x6f,  /* [554] */
    (xdc_Char)0x72,  /* [555] */
    (xdc_Char)0x74,  /* [556] */
    (xdc_Char)0x65,  /* [557] */
    (xdc_Char)0x64,  /* [558] */
    (xdc_Char)0x54,  /* [559] */
    (xdc_Char)0x69,  /* [560] */
    (xdc_Char)0x6d,  /* [561] */
    (xdc_Char)0x65,  /* [562] */
    (xdc_Char)0x6f,  /* [563] */
    (xdc_Char)0x75,  /* [564] */
    (xdc_Char)0x74,  /* [565] */
    (xdc_Char)0x3a,  /* [566] */
    (xdc_Char)0x20,  /* [567] */
    (xdc_Char)0x4f,  /* [568] */
    (xdc_Char)0x6e,  /* [569] */
    (xdc_Char)0x6c,  /* [570] */
    (xdc_Char)0x79,  /* [571] */
    (xdc_Char)0x20,  /* [572] */
    (xdc_Char)0x53,  /* [573] */
    (xdc_Char)0x65,  /* [574] */
    (xdc_Char)0x6d,  /* [575] */
    (xdc_Char)0x50,  /* [576] */
    (xdc_Char)0x72,  /* [577] */
    (xdc_Char)0x6f,  /* [578] */
    (xdc_Char)0x63,  /* [579] */
    (xdc_Char)0x65,  /* [580] */
    (xdc_Char)0x73,  /* [581] */
    (xdc_Char)0x73,  /* [582] */
    (xdc_Char)0x5f,  /* [583] */
    (xdc_Char)0x46,  /* [584] */
    (xdc_Char)0x4f,  /* [585] */
    (xdc_Char)0x52,  /* [586] */
    (xdc_Char)0x45,  /* [587] */
    (xdc_Char)0x56,  /* [588] */
    (xdc_Char)0x45,  /* [589] */
    (xdc_Char)0x52,  /* [590] */
    (xdc_Char)0x20,  /* [591] */
    (xdc_Char)0x69,  /* [592] */
    (xdc_Char)0x73,  /* [593] */
    (xdc_Char)0x20,  /* [594] */
    (xdc_Char)0x73,  /* [595] */
    (xdc_Char)0x75,  /* [596] */
    (xdc_Char)0x70,  /* [597] */
    (xdc_Char)0x70,  /* [598] */
    (xdc_Char)0x6f,  /* [599] */
    (xdc_Char)0x72,  /* [600] */
    (xdc_Char)0x74,  /* [601] */
    (xdc_Char)0x65,  /* [602] */
    (xdc_Char)0x64,  /* [603] */
    (xdc_Char)0x0,  /* [604] */
    (xdc_Char)0x61,  /* [605] */
    (xdc_Char)0x73,  /* [606] */
    (xdc_Char)0x73,  /* [607] */
    (xdc_Char)0x65,  /* [608] */
    (xdc_Char)0x72,  /* [609] */
    (xdc_Char)0x74,  /* [610] */
    (xdc_Char)0x69,  /* [611] */
    (xdc_Char)0x6f,  /* [612] */
    (xdc_Char)0x6e,  /* [613] */
    (xdc_Char)0x20,  /* [614] */
    (xdc_Char)0x66,  /* [615] */
    (xdc_Char)0x61,  /* [616] */
    (xdc_Char)0x69,  /* [617] */
    (xdc_Char)0x6c,  /* [618] */
    (xdc_Char)0x75,  /* [619] */
    (xdc_Char)0x72,  /* [620] */
    (xdc_Char)0x65,  /* [621] */
    (xdc_Char)0x25,  /* [622] */
    (xdc_Char)0x73,  /* [623] */
    (xdc_Char)0x25,  /* [624] */
    (xdc_Char)0x73,  /* [625] */
    (xdc_Char)0x0,  /* [626] */
    (xdc_Char)0x25,  /* [627] */
    (xdc_Char)0x24,  /* [628] */
    (xdc_Char)0x53,  /* [629] */
    (xdc_Char)0x0,  /* [630] */
    (xdc_Char)0x6f,  /* [631] */
    (xdc_Char)0x75,  /* [632] */
    (xdc_Char)0x74,  /* [633] */
    (xdc_Char)0x20,  /* [634] */
    (xdc_Char)0x6f,  /* [635] */
    (xdc_Char)0x66,  /* [636] */
    (xdc_Char)0x20,  /* [637] */
    (xdc_Char)0x6d,  /* [638] */
    (xdc_Char)0x65,  /* [639] */
    (xdc_Char)0x6d,  /* [640] */
    (xdc_Char)0x6f,  /* [641] */
    (xdc_Char)0x72,  /* [642] */
    (xdc_Char)0x79,  /* [643] */
    (xdc_Char)0x3a,  /* [644] */
    (xdc_Char)0x20,  /* [645] */
    (xdc_Char)0x68,  /* [646] */
    (xdc_Char)0x65,  /* [647] */
    (xdc_Char)0x61,  /* [648] */
    (xdc_Char)0x70,  /* [649] */
    (xdc_Char)0x3d,  /* [650] */
    (xdc_Char)0x30,  /* [651] */
    (xdc_Char)0x78,  /* [652] */
    (xdc_Char)0x25,  /* [653] */
    (xdc_Char)0x78,  /* [654] */
    (xdc_Char)0x2c,  /* [655] */
    (xdc_Char)0x20,  /* [656] */
    (xdc_Char)0x73,  /* [657] */
    (xdc_Char)0x69,  /* [658] */
    (xdc_Char)0x7a,  /* [659] */
    (xdc_Char)0x65,  /* [660] */
    (xdc_Char)0x3d,  /* [661] */
    (xdc_Char)0x25,  /* [662] */
    (xdc_Char)0x75,  /* [663] */
    (xdc_Char)0x0,  /* [664] */
    (xdc_Char)0x25,  /* [665] */
    (xdc_Char)0x73,  /* [666] */
    (xdc_Char)0x20,  /* [667] */
    (xdc_Char)0x30,  /* [668] */
    (xdc_Char)0x78,  /* [669] */
    (xdc_Char)0x25,  /* [670] */
    (xdc_Char)0x78,  /* [671] */
    (xdc_Char)0x0,  /* [672] */
    (xdc_Char)0x45,  /* [673] */
    (xdc_Char)0x5f,  /* [674] */
    (xdc_Char)0x62,  /* [675] */
    (xdc_Char)0x61,  /* [676] */
    (xdc_Char)0x64,  /* [677] */
    (xdc_Char)0x4c,  /* [678] */
    (xdc_Char)0x65,  /* [679] */
    (xdc_Char)0x76,  /* [680] */
    (xdc_Char)0x65,  /* [681] */
    (xdc_Char)0x6c,  /* [682] */
    (xdc_Char)0x3a,  /* [683] */
    (xdc_Char)0x20,  /* [684] */
    (xdc_Char)0x42,  /* [685] */
    (xdc_Char)0x61,  /* [686] */
    (xdc_Char)0x64,  /* [687] */
    (xdc_Char)0x20,  /* [688] */
    (xdc_Char)0x66,  /* [689] */
    (xdc_Char)0x69,  /* [690] */
    (xdc_Char)0x6c,  /* [691] */
    (xdc_Char)0x74,  /* [692] */
    (xdc_Char)0x65,  /* [693] */
    (xdc_Char)0x72,  /* [694] */
    (xdc_Char)0x20,  /* [695] */
    (xdc_Char)0x6c,  /* [696] */
    (xdc_Char)0x65,  /* [697] */
    (xdc_Char)0x76,  /* [698] */
    (xdc_Char)0x65,  /* [699] */
    (xdc_Char)0x6c,  /* [700] */
    (xdc_Char)0x20,  /* [701] */
    (xdc_Char)0x76,  /* [702] */
    (xdc_Char)0x61,  /* [703] */
    (xdc_Char)0x6c,  /* [704] */
    (xdc_Char)0x75,  /* [705] */
    (xdc_Char)0x65,  /* [706] */
    (xdc_Char)0x3a,  /* [707] */
    (xdc_Char)0x20,  /* [708] */
    (xdc_Char)0x25,  /* [709] */
    (xdc_Char)0x64,  /* [710] */
    (xdc_Char)0x0,  /* [711] */
    (xdc_Char)0x66,  /* [712] */
    (xdc_Char)0x72,  /* [713] */
    (xdc_Char)0x65,  /* [714] */
    (xdc_Char)0x65,  /* [715] */
    (xdc_Char)0x28,  /* [716] */
    (xdc_Char)0x29,  /* [717] */
    (xdc_Char)0x20,  /* [718] */
    (xdc_Char)0x69,  /* [719] */
    (xdc_Char)0x6e,  /* [720] */
    (xdc_Char)0x76,  /* [721] */
    (xdc_Char)0x61,  /* [722] */
    (xdc_Char)0x6c,  /* [723] */
    (xdc_Char)0x69,  /* [724] */
    (xdc_Char)0x64,  /* [725] */
    (xdc_Char)0x20,  /* [726] */
    (xdc_Char)0x69,  /* [727] */
    (xdc_Char)0x6e,  /* [728] */
    (xdc_Char)0x20,  /* [729] */
    (xdc_Char)0x67,  /* [730] */
    (xdc_Char)0x72,  /* [731] */
    (xdc_Char)0x6f,  /* [732] */
    (xdc_Char)0x77,  /* [733] */
    (xdc_Char)0x74,  /* [734] */
    (xdc_Char)0x68,  /* [735] */
    (xdc_Char)0x2d,  /* [736] */
    (xdc_Char)0x6f,  /* [737] */
    (xdc_Char)0x6e,  /* [738] */
    (xdc_Char)0x6c,  /* [739] */
    (xdc_Char)0x79,  /* [740] */
    (xdc_Char)0x20,  /* [741] */
    (xdc_Char)0x48,  /* [742] */
    (xdc_Char)0x65,  /* [743] */
    (xdc_Char)0x61,  /* [744] */
    (xdc_Char)0x70,  /* [745] */
    (xdc_Char)0x4d,  /* [746] */
    (xdc_Char)0x69,  /* [747] */
    (xdc_Char)0x6e,  /* [748] */
    (xdc_Char)0x0,  /* [749] */
    (xdc_Char)0x54,  /* [750] */
    (xdc_Char)0x68,  /* [751] */
    (xdc_Char)0x65,  /* [752] */
    (xdc_Char)0x20,  /* [753] */
    (xdc_Char)0x52,  /* [754] */
    (xdc_Char)0x54,  /* [755] */
    (xdc_Char)0x53,  /* [756] */
    (xdc_Char)0x20,  /* [757] */
    (xdc_Char)0x68,  /* [758] */
    (xdc_Char)0x65,  /* [759] */
    (xdc_Char)0x61,  /* [760] */
    (xdc_Char)0x70,  /* [761] */
    (xdc_Char)0x20,  /* [762] */
    (xdc_Char)0x69,  /* [763] */
    (xdc_Char)0x73,  /* [764] */
    (xdc_Char)0x20,  /* [765] */
    (xdc_Char)0x75,  /* [766] */
    (xdc_Char)0x73,  /* [767] */
    (xdc_Char)0x65,  /* [768] */
    (xdc_Char)0x64,  /* [769] */
    (xdc_Char)0x20,  /* [770] */
    (xdc_Char)0x75,  /* [771] */
    (xdc_Char)0x70,  /* [772] */
    (xdc_Char)0x2e,  /* [773] */
    (xdc_Char)0x20,  /* [774] */
    (xdc_Char)0x45,  /* [775] */
    (xdc_Char)0x78,  /* [776] */
    (xdc_Char)0x61,  /* [777] */
    (xdc_Char)0x6d,  /* [778] */
    (xdc_Char)0x69,  /* [779] */
    (xdc_Char)0x6e,  /* [780] */
    (xdc_Char)0x65,  /* [781] */
    (xdc_Char)0x20,  /* [782] */
    (xdc_Char)0x50,  /* [783] */
    (xdc_Char)0x72,  /* [784] */
    (xdc_Char)0x6f,  /* [785] */
    (xdc_Char)0x67,  /* [786] */
    (xdc_Char)0x72,  /* [787] */
    (xdc_Char)0x61,  /* [788] */
    (xdc_Char)0x6d,  /* [789] */
    (xdc_Char)0x2e,  /* [790] */
    (xdc_Char)0x68,  /* [791] */
    (xdc_Char)0x65,  /* [792] */
    (xdc_Char)0x61,  /* [793] */
    (xdc_Char)0x70,  /* [794] */
    (xdc_Char)0x2e,  /* [795] */
    (xdc_Char)0x0,  /* [796] */
    (xdc_Char)0x45,  /* [797] */
    (xdc_Char)0x5f,  /* [798] */
    (xdc_Char)0x62,  /* [799] */
    (xdc_Char)0x61,  /* [800] */
    (xdc_Char)0x64,  /* [801] */
    (xdc_Char)0x43,  /* [802] */
    (xdc_Char)0x6f,  /* [803] */
    (xdc_Char)0x6d,  /* [804] */
    (xdc_Char)0x6d,  /* [805] */
    (xdc_Char)0x61,  /* [806] */
    (xdc_Char)0x6e,  /* [807] */
    (xdc_Char)0x64,  /* [808] */
    (xdc_Char)0x3a,  /* [809] */
    (xdc_Char)0x20,  /* [810] */
    (xdc_Char)0x52,  /* [811] */
    (xdc_Char)0x65,  /* [812] */
    (xdc_Char)0x63,  /* [813] */
    (xdc_Char)0x65,  /* [814] */
    (xdc_Char)0x69,  /* [815] */
    (xdc_Char)0x76,  /* [816] */
    (xdc_Char)0x65,  /* [817] */
    (xdc_Char)0x64,  /* [818] */
    (xdc_Char)0x20,  /* [819] */
    (xdc_Char)0x69,  /* [820] */
    (xdc_Char)0x6e,  /* [821] */
    (xdc_Char)0x76,  /* [822] */
    (xdc_Char)0x61,  /* [823] */
    (xdc_Char)0x6c,  /* [824] */
    (xdc_Char)0x69,  /* [825] */
    (xdc_Char)0x64,  /* [826] */
    (xdc_Char)0x20,  /* [827] */
    (xdc_Char)0x63,  /* [828] */
    (xdc_Char)0x6f,  /* [829] */
    (xdc_Char)0x6d,  /* [830] */
    (xdc_Char)0x6d,  /* [831] */
    (xdc_Char)0x61,  /* [832] */
    (xdc_Char)0x6e,  /* [833] */
    (xdc_Char)0x64,  /* [834] */
    (xdc_Char)0x2c,  /* [835] */
    (xdc_Char)0x20,  /* [836] */
    (xdc_Char)0x69,  /* [837] */
    (xdc_Char)0x64,  /* [838] */
    (xdc_Char)0x3a,  /* [839] */
    (xdc_Char)0x20,  /* [840] */
    (xdc_Char)0x25,  /* [841] */
    (xdc_Char)0x64,  /* [842] */
    (xdc_Char)0x2e,  /* [843] */
    (xdc_Char)0x0,  /* [844] */
    (xdc_Char)0x45,  /* [845] */
    (xdc_Char)0x5f,  /* [846] */
    (xdc_Char)0x50,  /* [847] */
    (xdc_Char)0x4f,  /* [848] */
    (xdc_Char)0x53,  /* [849] */
    (xdc_Char)0x49,  /* [850] */
    (xdc_Char)0x58,  /* [851] */
    (xdc_Char)0x5f,  /* [852] */
    (xdc_Char)0x45,  /* [853] */
    (xdc_Char)0x72,  /* [854] */
    (xdc_Char)0x72,  /* [855] */
    (xdc_Char)0x6f,  /* [856] */
    (xdc_Char)0x72,  /* [857] */
    (xdc_Char)0x3a,  /* [858] */
    (xdc_Char)0x20,  /* [859] */
    (xdc_Char)0x61,  /* [860] */
    (xdc_Char)0x20,  /* [861] */
    (xdc_Char)0x50,  /* [862] */
    (xdc_Char)0x4f,  /* [863] */
    (xdc_Char)0x53,  /* [864] */
    (xdc_Char)0x49,  /* [865] */
    (xdc_Char)0x58,  /* [866] */
    (xdc_Char)0x20,  /* [867] */
    (xdc_Char)0x66,  /* [868] */
    (xdc_Char)0x75,  /* [869] */
    (xdc_Char)0x6e,  /* [870] */
    (xdc_Char)0x63,  /* [871] */
    (xdc_Char)0x74,  /* [872] */
    (xdc_Char)0x69,  /* [873] */
    (xdc_Char)0x6f,  /* [874] */
    (xdc_Char)0x6e,  /* [875] */
    (xdc_Char)0x20,  /* [876] */
    (xdc_Char)0x72,  /* [877] */
    (xdc_Char)0x65,  /* [878] */
    (xdc_Char)0x74,  /* [879] */
    (xdc_Char)0x75,  /* [880] */
    (xdc_Char)0x72,  /* [881] */
    (xdc_Char)0x6e,  /* [882] */
    (xdc_Char)0x65,  /* [883] */
    (xdc_Char)0x64,  /* [884] */
    (xdc_Char)0x20,  /* [885] */
    (xdc_Char)0x66,  /* [886] */
    (xdc_Char)0x61,  /* [887] */
    (xdc_Char)0x69,  /* [888] */
    (xdc_Char)0x6c,  /* [889] */
    (xdc_Char)0x75,  /* [890] */
    (xdc_Char)0x72,  /* [891] */
    (xdc_Char)0x65,  /* [892] */
    (xdc_Char)0x2c,  /* [893] */
    (xdc_Char)0x20,  /* [894] */
    (xdc_Char)0x65,  /* [895] */
    (xdc_Char)0x72,  /* [896] */
    (xdc_Char)0x72,  /* [897] */
    (xdc_Char)0x6e,  /* [898] */
    (xdc_Char)0x6f,  /* [899] */
    (xdc_Char)0x20,  /* [900] */
    (xdc_Char)0x69,  /* [901] */
    (xdc_Char)0x73,  /* [902] */
    (xdc_Char)0x20,  /* [903] */
    (xdc_Char)0x25,  /* [904] */
    (xdc_Char)0x64,  /* [905] */
    (xdc_Char)0x0,  /* [906] */
    (xdc_Char)0x45,  /* [907] */
    (xdc_Char)0x5f,  /* [908] */
    (xdc_Char)0x72,  /* [909] */
    (xdc_Char)0x65,  /* [910] */
    (xdc_Char)0x73,  /* [911] */
    (xdc_Char)0x65,  /* [912] */
    (xdc_Char)0x74,  /* [913] */
    (xdc_Char)0x45,  /* [914] */
    (xdc_Char)0x72,  /* [915] */
    (xdc_Char)0x72,  /* [916] */
    (xdc_Char)0x6f,  /* [917] */
    (xdc_Char)0x72,  /* [918] */
    (xdc_Char)0x3a,  /* [919] */
    (xdc_Char)0x20,  /* [920] */
    (xdc_Char)0x25,  /* [921] */
    (xdc_Char)0x73,  /* [922] */
    (xdc_Char)0x20,  /* [923] */
    (xdc_Char)0x72,  /* [924] */
    (xdc_Char)0x65,  /* [925] */
    (xdc_Char)0x74,  /* [926] */
    (xdc_Char)0x75,  /* [927] */
    (xdc_Char)0x72,  /* [928] */
    (xdc_Char)0x6e,  /* [929] */
    (xdc_Char)0x65,  /* [930] */
    (xdc_Char)0x64,  /* [931] */
    (xdc_Char)0x20,  /* [932] */
    (xdc_Char)0x66,  /* [933] */
    (xdc_Char)0x61,  /* [934] */
    (xdc_Char)0x69,  /* [935] */
    (xdc_Char)0x6c,  /* [936] */
    (xdc_Char)0x75,  /* [937] */
    (xdc_Char)0x72,  /* [938] */
    (xdc_Char)0x65,  /* [939] */
    (xdc_Char)0x0,  /* [940] */
    (xdc_Char)0x45,  /* [941] */
    (xdc_Char)0x5f,  /* [942] */
    (xdc_Char)0x70,  /* [943] */
    (xdc_Char)0x72,  /* [944] */
    (xdc_Char)0x69,  /* [945] */
    (xdc_Char)0x6f,  /* [946] */
    (xdc_Char)0x72,  /* [947] */
    (xdc_Char)0x69,  /* [948] */
    (xdc_Char)0x74,  /* [949] */
    (xdc_Char)0x79,  /* [950] */
    (xdc_Char)0x3a,  /* [951] */
    (xdc_Char)0x20,  /* [952] */
    (xdc_Char)0x54,  /* [953] */
    (xdc_Char)0x68,  /* [954] */
    (xdc_Char)0x72,  /* [955] */
    (xdc_Char)0x65,  /* [956] */
    (xdc_Char)0x61,  /* [957] */
    (xdc_Char)0x64,  /* [958] */
    (xdc_Char)0x20,  /* [959] */
    (xdc_Char)0x70,  /* [960] */
    (xdc_Char)0x72,  /* [961] */
    (xdc_Char)0x69,  /* [962] */
    (xdc_Char)0x6f,  /* [963] */
    (xdc_Char)0x72,  /* [964] */
    (xdc_Char)0x69,  /* [965] */
    (xdc_Char)0x74,  /* [966] */
    (xdc_Char)0x79,  /* [967] */
    (xdc_Char)0x20,  /* [968] */
    (xdc_Char)0x69,  /* [969] */
    (xdc_Char)0x73,  /* [970] */
    (xdc_Char)0x20,  /* [971] */
    (xdc_Char)0x69,  /* [972] */
    (xdc_Char)0x6e,  /* [973] */
    (xdc_Char)0x76,  /* [974] */
    (xdc_Char)0x61,  /* [975] */
    (xdc_Char)0x6c,  /* [976] */
    (xdc_Char)0x69,  /* [977] */
    (xdc_Char)0x64,  /* [978] */
    (xdc_Char)0x20,  /* [979] */
    (xdc_Char)0x25,  /* [980] */
    (xdc_Char)0x64,  /* [981] */
    (xdc_Char)0x0,  /* [982] */
    (xdc_Char)0x3c,  /* [983] */
    (xdc_Char)0x2d,  /* [984] */
    (xdc_Char)0x2d,  /* [985] */
    (xdc_Char)0x20,  /* [986] */
    (xdc_Char)0x63,  /* [987] */
    (xdc_Char)0x6f,  /* [988] */
    (xdc_Char)0x6e,  /* [989] */
    (xdc_Char)0x73,  /* [990] */
    (xdc_Char)0x74,  /* [991] */
    (xdc_Char)0x72,  /* [992] */
    (xdc_Char)0x75,  /* [993] */
    (xdc_Char)0x63,  /* [994] */
    (xdc_Char)0x74,  /* [995] */
    (xdc_Char)0x3a,  /* [996] */
    (xdc_Char)0x20,  /* [997] */
    (xdc_Char)0x25,  /* [998] */
    (xdc_Char)0x70,  /* [999] */
    (xdc_Char)0x28,  /* [1000] */
    (xdc_Char)0x27,  /* [1001] */
    (xdc_Char)0x25,  /* [1002] */
    (xdc_Char)0x73,  /* [1003] */
    (xdc_Char)0x27,  /* [1004] */
    (xdc_Char)0x29,  /* [1005] */
    (xdc_Char)0x0,  /* [1006] */
    (xdc_Char)0x3c,  /* [1007] */
    (xdc_Char)0x2d,  /* [1008] */
    (xdc_Char)0x2d,  /* [1009] */
    (xdc_Char)0x20,  /* [1010] */
    (xdc_Char)0x63,  /* [1011] */
    (xdc_Char)0x72,  /* [1012] */
    (xdc_Char)0x65,  /* [1013] */
    (xdc_Char)0x61,  /* [1014] */
    (xdc_Char)0x74,  /* [1015] */
    (xdc_Char)0x65,  /* [1016] */
    (xdc_Char)0x3a,  /* [1017] */
    (xdc_Char)0x20,  /* [1018] */
    (xdc_Char)0x25,  /* [1019] */
    (xdc_Char)0x70,  /* [1020] */
    (xdc_Char)0x28,  /* [1021] */
    (xdc_Char)0x27,  /* [1022] */
    (xdc_Char)0x25,  /* [1023] */
    (xdc_Char)0x73,  /* [1024] */
    (xdc_Char)0x27,  /* [1025] */
    (xdc_Char)0x29,  /* [1026] */
    (xdc_Char)0x0,  /* [1027] */
    (xdc_Char)0x2d,  /* [1028] */
    (xdc_Char)0x2d,  /* [1029] */
    (xdc_Char)0x3e,  /* [1030] */
    (xdc_Char)0x20,  /* [1031] */
    (xdc_Char)0x64,  /* [1032] */
    (xdc_Char)0x65,  /* [1033] */
    (xdc_Char)0x73,  /* [1034] */
    (xdc_Char)0x74,  /* [1035] */
    (xdc_Char)0x72,  /* [1036] */
    (xdc_Char)0x75,  /* [1037] */
    (xdc_Char)0x63,  /* [1038] */
    (xdc_Char)0x74,  /* [1039] */
    (xdc_Char)0x3a,  /* [1040] */
    (xdc_Char)0x20,  /* [1041] */
    (xdc_Char)0x28,  /* [1042] */
    (xdc_Char)0x25,  /* [1043] */
    (xdc_Char)0x70,  /* [1044] */
    (xdc_Char)0x29,  /* [1045] */
    (xdc_Char)0x0,  /* [1046] */
    (xdc_Char)0x2d,  /* [1047] */
    (xdc_Char)0x2d,  /* [1048] */
    (xdc_Char)0x3e,  /* [1049] */
    (xdc_Char)0x20,  /* [1050] */
    (xdc_Char)0x64,  /* [1051] */
    (xdc_Char)0x65,  /* [1052] */
    (xdc_Char)0x6c,  /* [1053] */
    (xdc_Char)0x65,  /* [1054] */
    (xdc_Char)0x74,  /* [1055] */
    (xdc_Char)0x65,  /* [1056] */
    (xdc_Char)0x3a,  /* [1057] */
    (xdc_Char)0x20,  /* [1058] */
    (xdc_Char)0x28,  /* [1059] */
    (xdc_Char)0x25,  /* [1060] */
    (xdc_Char)0x70,  /* [1061] */
    (xdc_Char)0x29,  /* [1062] */
    (xdc_Char)0x0,  /* [1063] */
    (xdc_Char)0x45,  /* [1064] */
    (xdc_Char)0x52,  /* [1065] */
    (xdc_Char)0x52,  /* [1066] */
    (xdc_Char)0x4f,  /* [1067] */
    (xdc_Char)0x52,  /* [1068] */
    (xdc_Char)0x3a,  /* [1069] */
    (xdc_Char)0x20,  /* [1070] */
    (xdc_Char)0x25,  /* [1071] */
    (xdc_Char)0x24,  /* [1072] */
    (xdc_Char)0x46,  /* [1073] */
    (xdc_Char)0x25,  /* [1074] */
    (xdc_Char)0x24,  /* [1075] */
    (xdc_Char)0x53,  /* [1076] */
    (xdc_Char)0x0,  /* [1077] */
    (xdc_Char)0x57,  /* [1078] */
    (xdc_Char)0x41,  /* [1079] */
    (xdc_Char)0x52,  /* [1080] */
    (xdc_Char)0x4e,  /* [1081] */
    (xdc_Char)0x49,  /* [1082] */
    (xdc_Char)0x4e,  /* [1083] */
    (xdc_Char)0x47,  /* [1084] */
    (xdc_Char)0x3a,  /* [1085] */
    (xdc_Char)0x20,  /* [1086] */
    (xdc_Char)0x25,  /* [1087] */
    (xdc_Char)0x24,  /* [1088] */
    (xdc_Char)0x46,  /* [1089] */
    (xdc_Char)0x25,  /* [1090] */
    (xdc_Char)0x24,  /* [1091] */
    (xdc_Char)0x53,  /* [1092] */
    (xdc_Char)0x0,  /* [1093] */
    (xdc_Char)0x25,  /* [1094] */
    (xdc_Char)0x24,  /* [1095] */
    (xdc_Char)0x46,  /* [1096] */
    (xdc_Char)0x25,  /* [1097] */
    (xdc_Char)0x24,  /* [1098] */
    (xdc_Char)0x53,  /* [1099] */
    (xdc_Char)0x0,  /* [1100] */
    (xdc_Char)0x2d,  /* [1101] */
    (xdc_Char)0x2d,  /* [1102] */
    (xdc_Char)0x3e,  /* [1103] */
    (xdc_Char)0x20,  /* [1104] */
    (xdc_Char)0x61,  /* [1105] */
    (xdc_Char)0x64,  /* [1106] */
    (xdc_Char)0x64,  /* [1107] */
    (xdc_Char)0x4d,  /* [1108] */
    (xdc_Char)0x6f,  /* [1109] */
    (xdc_Char)0x64,  /* [1110] */
    (xdc_Char)0x75,  /* [1111] */
    (xdc_Char)0x6c,  /* [1112] */
    (xdc_Char)0x65,  /* [1113] */
    (xdc_Char)0x3a,  /* [1114] */
    (xdc_Char)0x20,  /* [1115] */
    (xdc_Char)0x28,  /* [1116] */
    (xdc_Char)0x25,  /* [1117] */
    (xdc_Char)0x70,  /* [1118] */
    (xdc_Char)0x2c,  /* [1119] */
    (xdc_Char)0x20,  /* [1120] */
    (xdc_Char)0x22,  /* [1121] */
    (xdc_Char)0x25,  /* [1122] */
    (xdc_Char)0x73,  /* [1123] */
    (xdc_Char)0x22,  /* [1124] */
    (xdc_Char)0x29,  /* [1125] */
    (xdc_Char)0x0,  /* [1126] */
    (xdc_Char)0x3c,  /* [1127] */
    (xdc_Char)0x2d,  /* [1128] */
    (xdc_Char)0x2d,  /* [1129] */
    (xdc_Char)0x20,  /* [1130] */
    (xdc_Char)0x61,  /* [1131] */
    (xdc_Char)0x64,  /* [1132] */
    (xdc_Char)0x64,  /* [1133] */
    (xdc_Char)0x4d,  /* [1134] */
    (xdc_Char)0x6f,  /* [1135] */
    (xdc_Char)0x64,  /* [1136] */
    (xdc_Char)0x75,  /* [1137] */
    (xdc_Char)0x6c,  /* [1138] */
    (xdc_Char)0x65,  /* [1139] */
    (xdc_Char)0x3a,  /* [1140] */
    (xdc_Char)0x20,  /* [1141] */
    (xdc_Char)0x25,  /* [1142] */
    (xdc_Char)0x64,  /* [1143] */
    (xdc_Char)0x0,  /* [1144] */
    (xdc_Char)0x2d,  /* [1145] */
    (xdc_Char)0x2d,  /* [1146] */
    (xdc_Char)0x3e,  /* [1147] */
    (xdc_Char)0x20,  /* [1148] */
    (xdc_Char)0x66,  /* [1149] */
    (xdc_Char)0x69,  /* [1150] */
    (xdc_Char)0x6e,  /* [1151] */
    (xdc_Char)0x64,  /* [1152] */
    (xdc_Char)0x42,  /* [1153] */
    (xdc_Char)0x79,  /* [1154] */
    (xdc_Char)0x4e,  /* [1155] */
    (xdc_Char)0x61,  /* [1156] */
    (xdc_Char)0x6d,  /* [1157] */
    (xdc_Char)0x65,  /* [1158] */
    (xdc_Char)0x3a,  /* [1159] */
    (xdc_Char)0x20,  /* [1160] */
    (xdc_Char)0x28,  /* [1161] */
    (xdc_Char)0x22,  /* [1162] */
    (xdc_Char)0x25,  /* [1163] */
    (xdc_Char)0x73,  /* [1164] */
    (xdc_Char)0x22,  /* [1165] */
    (xdc_Char)0x29,  /* [1166] */
    (xdc_Char)0x0,  /* [1167] */
    (xdc_Char)0x3c,  /* [1168] */
    (xdc_Char)0x2d,  /* [1169] */
    (xdc_Char)0x2d,  /* [1170] */
    (xdc_Char)0x20,  /* [1171] */
    (xdc_Char)0x66,  /* [1172] */
    (xdc_Char)0x69,  /* [1173] */
    (xdc_Char)0x6e,  /* [1174] */
    (xdc_Char)0x64,  /* [1175] */
    (xdc_Char)0x42,  /* [1176] */
    (xdc_Char)0x79,  /* [1177] */
    (xdc_Char)0x4e,  /* [1178] */
    (xdc_Char)0x61,  /* [1179] */
    (xdc_Char)0x6d,  /* [1180] */
    (xdc_Char)0x65,  /* [1181] */
    (xdc_Char)0x3a,  /* [1182] */
    (xdc_Char)0x20,  /* [1183] */
    (xdc_Char)0x25,  /* [1184] */
    (xdc_Char)0x70,  /* [1185] */
    (xdc_Char)0x0,  /* [1186] */
    (xdc_Char)0x2d,  /* [1187] */
    (xdc_Char)0x2d,  /* [1188] */
    (xdc_Char)0x3e,  /* [1189] */
    (xdc_Char)0x20,  /* [1190] */
    (xdc_Char)0x66,  /* [1191] */
    (xdc_Char)0x69,  /* [1192] */
    (xdc_Char)0x6e,  /* [1193] */
    (xdc_Char)0x64,  /* [1194] */
    (xdc_Char)0x42,  /* [1195] */
    (xdc_Char)0x79,  /* [1196] */
    (xdc_Char)0x4e,  /* [1197] */
    (xdc_Char)0x61,  /* [1198] */
    (xdc_Char)0x6d,  /* [1199] */
    (xdc_Char)0x65,  /* [1200] */
    (xdc_Char)0x50,  /* [1201] */
    (xdc_Char)0x61,  /* [1202] */
    (xdc_Char)0x74,  /* [1203] */
    (xdc_Char)0x74,  /* [1204] */
    (xdc_Char)0x65,  /* [1205] */
    (xdc_Char)0x72,  /* [1206] */
    (xdc_Char)0x6e,  /* [1207] */
    (xdc_Char)0x3a,  /* [1208] */
    (xdc_Char)0x20,  /* [1209] */
    (xdc_Char)0x28,  /* [1210] */
    (xdc_Char)0x22,  /* [1211] */
    (xdc_Char)0x25,  /* [1212] */
    (xdc_Char)0x73,  /* [1213] */
    (xdc_Char)0x22,  /* [1214] */
    (xdc_Char)0x2c,  /* [1215] */
    (xdc_Char)0x20,  /* [1216] */
    (xdc_Char)0x25,  /* [1217] */
    (xdc_Char)0x64,  /* [1218] */
    (xdc_Char)0x2c,  /* [1219] */
    (xdc_Char)0x20,  /* [1220] */
    (xdc_Char)0x25,  /* [1221] */
    (xdc_Char)0x70,  /* [1222] */
    (xdc_Char)0x29,  /* [1223] */
    (xdc_Char)0x0,  /* [1224] */
    (xdc_Char)0x3c,  /* [1225] */
    (xdc_Char)0x2d,  /* [1226] */
    (xdc_Char)0x2d,  /* [1227] */
    (xdc_Char)0x20,  /* [1228] */
    (xdc_Char)0x66,  /* [1229] */
    (xdc_Char)0x69,  /* [1230] */
    (xdc_Char)0x6e,  /* [1231] */
    (xdc_Char)0x64,  /* [1232] */
    (xdc_Char)0x42,  /* [1233] */
    (xdc_Char)0x79,  /* [1234] */
    (xdc_Char)0x4e,  /* [1235] */
    (xdc_Char)0x61,  /* [1236] */
    (xdc_Char)0x6d,  /* [1237] */
    (xdc_Char)0x65,  /* [1238] */
    (xdc_Char)0x50,  /* [1239] */
    (xdc_Char)0x61,  /* [1240] */
    (xdc_Char)0x74,  /* [1241] */
    (xdc_Char)0x74,  /* [1242] */
    (xdc_Char)0x65,  /* [1243] */
    (xdc_Char)0x72,  /* [1244] */
    (xdc_Char)0x6e,  /* [1245] */
    (xdc_Char)0x3a,  /* [1246] */
    (xdc_Char)0x20,  /* [1247] */
    (xdc_Char)0x25,  /* [1248] */
    (xdc_Char)0x70,  /* [1249] */
    (xdc_Char)0x0,  /* [1250] */
    (xdc_Char)0x2d,  /* [1251] */
    (xdc_Char)0x2d,  /* [1252] */
    (xdc_Char)0x3e,  /* [1253] */
    (xdc_Char)0x20,  /* [1254] */
    (xdc_Char)0x66,  /* [1255] */
    (xdc_Char)0x69,  /* [1256] */
    (xdc_Char)0x6e,  /* [1257] */
    (xdc_Char)0x64,  /* [1258] */
    (xdc_Char)0x42,  /* [1259] */
    (xdc_Char)0x79,  /* [1260] */
    (xdc_Char)0x49,  /* [1261] */
    (xdc_Char)0x64,  /* [1262] */
    (xdc_Char)0x3a,  /* [1263] */
    (xdc_Char)0x20,  /* [1264] */
    (xdc_Char)0x28,  /* [1265] */
    (xdc_Char)0x25,  /* [1266] */
    (xdc_Char)0x64,  /* [1267] */
    (xdc_Char)0x29,  /* [1268] */
    (xdc_Char)0x0,  /* [1269] */
    (xdc_Char)0x3c,  /* [1270] */
    (xdc_Char)0x2d,  /* [1271] */
    (xdc_Char)0x2d,  /* [1272] */
    (xdc_Char)0x20,  /* [1273] */
    (xdc_Char)0x66,  /* [1274] */
    (xdc_Char)0x69,  /* [1275] */
    (xdc_Char)0x6e,  /* [1276] */
    (xdc_Char)0x64,  /* [1277] */
    (xdc_Char)0x42,  /* [1278] */
    (xdc_Char)0x79,  /* [1279] */
    (xdc_Char)0x49,  /* [1280] */
    (xdc_Char)0x64,  /* [1281] */
    (xdc_Char)0x3a,  /* [1282] */
    (xdc_Char)0x20,  /* [1283] */
    (xdc_Char)0x25,  /* [1284] */
    (xdc_Char)0x70,  /* [1285] */
    (xdc_Char)0x0,  /* [1286] */
    (xdc_Char)0x2d,  /* [1287] */
    (xdc_Char)0x2d,  /* [1288] */
    (xdc_Char)0x3e,  /* [1289] */
    (xdc_Char)0x20,  /* [1290] */
    (xdc_Char)0x67,  /* [1291] */
    (xdc_Char)0x65,  /* [1292] */
    (xdc_Char)0x74,  /* [1293] */
    (xdc_Char)0x4d,  /* [1294] */
    (xdc_Char)0x61,  /* [1295] */
    (xdc_Char)0x73,  /* [1296] */
    (xdc_Char)0x6b,  /* [1297] */
    (xdc_Char)0x3a,  /* [1298] */
    (xdc_Char)0x20,  /* [1299] */
    (xdc_Char)0x28,  /* [1300] */
    (xdc_Char)0x22,  /* [1301] */
    (xdc_Char)0x25,  /* [1302] */
    (xdc_Char)0x73,  /* [1303] */
    (xdc_Char)0x22,  /* [1304] */
    (xdc_Char)0x2c,  /* [1305] */
    (xdc_Char)0x20,  /* [1306] */
    (xdc_Char)0x25,  /* [1307] */
    (xdc_Char)0x70,  /* [1308] */
    (xdc_Char)0x29,  /* [1309] */
    (xdc_Char)0x0,  /* [1310] */
    (xdc_Char)0x3c,  /* [1311] */
    (xdc_Char)0x2d,  /* [1312] */
    (xdc_Char)0x2d,  /* [1313] */
    (xdc_Char)0x20,  /* [1314] */
    (xdc_Char)0x67,  /* [1315] */
    (xdc_Char)0x65,  /* [1316] */
    (xdc_Char)0x74,  /* [1317] */
    (xdc_Char)0x4d,  /* [1318] */
    (xdc_Char)0x61,  /* [1319] */
    (xdc_Char)0x73,  /* [1320] */
    (xdc_Char)0x6b,  /* [1321] */
    (xdc_Char)0x3a,  /* [1322] */
    (xdc_Char)0x20,  /* [1323] */
    (xdc_Char)0x25,  /* [1324] */
    (xdc_Char)0x64,  /* [1325] */
    (xdc_Char)0x0,  /* [1326] */
    (xdc_Char)0x2d,  /* [1327] */
    (xdc_Char)0x2d,  /* [1328] */
    (xdc_Char)0x3e,  /* [1329] */
    (xdc_Char)0x20,  /* [1330] */
    (xdc_Char)0x69,  /* [1331] */
    (xdc_Char)0x73,  /* [1332] */
    (xdc_Char)0x4d,  /* [1333] */
    (xdc_Char)0x65,  /* [1334] */
    (xdc_Char)0x6d,  /* [1335] */
    (xdc_Char)0x62,  /* [1336] */
    (xdc_Char)0x65,  /* [1337] */
    (xdc_Char)0x72,  /* [1338] */
    (xdc_Char)0x3a,  /* [1339] */
    (xdc_Char)0x20,  /* [1340] */
    (xdc_Char)0x28,  /* [1341] */
    (xdc_Char)0x25,  /* [1342] */
    (xdc_Char)0x64,  /* [1343] */
    (xdc_Char)0x29,  /* [1344] */
    (xdc_Char)0x0,  /* [1345] */
    (xdc_Char)0x3c,  /* [1346] */
    (xdc_Char)0x2d,  /* [1347] */
    (xdc_Char)0x2d,  /* [1348] */
    (xdc_Char)0x20,  /* [1349] */
    (xdc_Char)0x69,  /* [1350] */
    (xdc_Char)0x73,  /* [1351] */
    (xdc_Char)0x4d,  /* [1352] */
    (xdc_Char)0x65,  /* [1353] */
    (xdc_Char)0x6d,  /* [1354] */
    (xdc_Char)0x62,  /* [1355] */
    (xdc_Char)0x65,  /* [1356] */
    (xdc_Char)0x72,  /* [1357] */
    (xdc_Char)0x3a,  /* [1358] */
    (xdc_Char)0x20,  /* [1359] */
    (xdc_Char)0x25,  /* [1360] */
    (xdc_Char)0x64,  /* [1361] */
    (xdc_Char)0x0,  /* [1362] */
    (xdc_Char)0x2d,  /* [1363] */
    (xdc_Char)0x2d,  /* [1364] */
    (xdc_Char)0x3e,  /* [1365] */
    (xdc_Char)0x20,  /* [1366] */
    (xdc_Char)0x67,  /* [1367] */
    (xdc_Char)0x65,  /* [1368] */
    (xdc_Char)0x74,  /* [1369] */
    (xdc_Char)0x4e,  /* [1370] */
    (xdc_Char)0x65,  /* [1371] */
    (xdc_Char)0x78,  /* [1372] */
    (xdc_Char)0x74,  /* [1373] */
    (xdc_Char)0x4d,  /* [1374] */
    (xdc_Char)0x6f,  /* [1375] */
    (xdc_Char)0x64,  /* [1376] */
    (xdc_Char)0x75,  /* [1377] */
    (xdc_Char)0x6c,  /* [1378] */
    (xdc_Char)0x65,  /* [1379] */
    (xdc_Char)0x3a,  /* [1380] */
    (xdc_Char)0x20,  /* [1381] */
    (xdc_Char)0x28,  /* [1382] */
    (xdc_Char)0x25,  /* [1383] */
    (xdc_Char)0x70,  /* [1384] */
    (xdc_Char)0x29,  /* [1385] */
    (xdc_Char)0x0,  /* [1386] */
    (xdc_Char)0x3c,  /* [1387] */
    (xdc_Char)0x2d,  /* [1388] */
    (xdc_Char)0x2d,  /* [1389] */
    (xdc_Char)0x20,  /* [1390] */
    (xdc_Char)0x67,  /* [1391] */
    (xdc_Char)0x65,  /* [1392] */
    (xdc_Char)0x74,  /* [1393] */
    (xdc_Char)0x4e,  /* [1394] */
    (xdc_Char)0x65,  /* [1395] */
    (xdc_Char)0x78,  /* [1396] */
    (xdc_Char)0x74,  /* [1397] */
    (xdc_Char)0x4d,  /* [1398] */
    (xdc_Char)0x6f,  /* [1399] */
    (xdc_Char)0x64,  /* [1400] */
    (xdc_Char)0x75,  /* [1401] */
    (xdc_Char)0x6c,  /* [1402] */
    (xdc_Char)0x65,  /* [1403] */
    (xdc_Char)0x3a,  /* [1404] */
    (xdc_Char)0x20,  /* [1405] */
    (xdc_Char)0x25,  /* [1406] */
    (xdc_Char)0x70,  /* [1407] */
    (xdc_Char)0x0,  /* [1408] */
    (xdc_Char)0x2d,  /* [1409] */
    (xdc_Char)0x2d,  /* [1410] */
    (xdc_Char)0x3e,  /* [1411] */
    (xdc_Char)0x20,  /* [1412] */
    (xdc_Char)0x67,  /* [1413] */
    (xdc_Char)0x65,  /* [1414] */
    (xdc_Char)0x74,  /* [1415] */
    (xdc_Char)0x4d,  /* [1416] */
    (xdc_Char)0x6f,  /* [1417] */
    (xdc_Char)0x64,  /* [1418] */
    (xdc_Char)0x75,  /* [1419] */
    (xdc_Char)0x6c,  /* [1420] */
    (xdc_Char)0x65,  /* [1421] */
    (xdc_Char)0x4e,  /* [1422] */
    (xdc_Char)0x61,  /* [1423] */
    (xdc_Char)0x6d,  /* [1424] */
    (xdc_Char)0x65,  /* [1425] */
    (xdc_Char)0x3a,  /* [1426] */
    (xdc_Char)0x20,  /* [1427] */
    (xdc_Char)0x28,  /* [1428] */
    (xdc_Char)0x25,  /* [1429] */
    (xdc_Char)0x70,  /* [1430] */
    (xdc_Char)0x29,  /* [1431] */
    (xdc_Char)0x0,  /* [1432] */
    (xdc_Char)0x3c,  /* [1433] */
    (xdc_Char)0x2d,  /* [1434] */
    (xdc_Char)0x2d,  /* [1435] */
    (xdc_Char)0x20,  /* [1436] */
    (xdc_Char)0x67,  /* [1437] */
    (xdc_Char)0x65,  /* [1438] */
    (xdc_Char)0x74,  /* [1439] */
    (xdc_Char)0x4d,  /* [1440] */
    (xdc_Char)0x6f,  /* [1441] */
    (xdc_Char)0x64,  /* [1442] */
    (xdc_Char)0x75,  /* [1443] */
    (xdc_Char)0x6c,  /* [1444] */
    (xdc_Char)0x65,  /* [1445] */
    (xdc_Char)0x4e,  /* [1446] */
    (xdc_Char)0x61,  /* [1447] */
    (xdc_Char)0x6d,  /* [1448] */
    (xdc_Char)0x65,  /* [1449] */
    (xdc_Char)0x3a,  /* [1450] */
    (xdc_Char)0x20,  /* [1451] */
    (xdc_Char)0x22,  /* [1452] */
    (xdc_Char)0x25,  /* [1453] */
    (xdc_Char)0x73,  /* [1454] */
    (xdc_Char)0x22,  /* [1455] */
    (xdc_Char)0x0,  /* [1456] */
    (xdc_Char)0x2d,  /* [1457] */
    (xdc_Char)0x2d,  /* [1458] */
    (xdc_Char)0x3e,  /* [1459] */
    (xdc_Char)0x20,  /* [1460] */
    (xdc_Char)0x67,  /* [1461] */
    (xdc_Char)0x65,  /* [1462] */
    (xdc_Char)0x74,  /* [1463] */
    (xdc_Char)0x4d,  /* [1464] */
    (xdc_Char)0x6f,  /* [1465] */
    (xdc_Char)0x64,  /* [1466] */
    (xdc_Char)0x75,  /* [1467] */
    (xdc_Char)0x6c,  /* [1468] */
    (xdc_Char)0x65,  /* [1469] */
    (xdc_Char)0x49,  /* [1470] */
    (xdc_Char)0x64,  /* [1471] */
    (xdc_Char)0x3a,  /* [1472] */
    (xdc_Char)0x20,  /* [1473] */
    (xdc_Char)0x28,  /* [1474] */
    (xdc_Char)0x25,  /* [1475] */
    (xdc_Char)0x70,  /* [1476] */
    (xdc_Char)0x29,  /* [1477] */
    (xdc_Char)0x0,  /* [1478] */
    (xdc_Char)0x3c,  /* [1479] */
    (xdc_Char)0x2d,  /* [1480] */
    (xdc_Char)0x2d,  /* [1481] */
    (xdc_Char)0x20,  /* [1482] */
    (xdc_Char)0x67,  /* [1483] */
    (xdc_Char)0x65,  /* [1484] */
    (xdc_Char)0x74,  /* [1485] */
    (xdc_Char)0x4d,  /* [1486] */
    (xdc_Char)0x6f,  /* [1487] */
    (xdc_Char)0x64,  /* [1488] */
    (xdc_Char)0x75,  /* [1489] */
    (xdc_Char)0x6c,  /* [1490] */
    (xdc_Char)0x65,  /* [1491] */
    (xdc_Char)0x49,  /* [1492] */
    (xdc_Char)0x64,  /* [1493] */
    (xdc_Char)0x3a,  /* [1494] */
    (xdc_Char)0x20,  /* [1495] */
    (xdc_Char)0x25,  /* [1496] */
    (xdc_Char)0x64,  /* [1497] */
    (xdc_Char)0x0,  /* [1498] */
    (xdc_Char)0x2d,  /* [1499] */
    (xdc_Char)0x2d,  /* [1500] */
    (xdc_Char)0x2d,  /* [1501] */
    (xdc_Char)0x20,  /* [1502] */
    (xdc_Char)0x53,  /* [1503] */
    (xdc_Char)0x65,  /* [1504] */
    (xdc_Char)0x6d,  /* [1505] */
    (xdc_Char)0x50,  /* [1506] */
    (xdc_Char)0x72,  /* [1507] */
    (xdc_Char)0x6f,  /* [1508] */
    (xdc_Char)0x63,  /* [1509] */
    (xdc_Char)0x65,  /* [1510] */
    (xdc_Char)0x73,  /* [1511] */
    (xdc_Char)0x73,  /* [1512] */
    (xdc_Char)0x28,  /* [1513] */
    (xdc_Char)0x25,  /* [1514] */
    (xdc_Char)0x64,  /* [1515] */
    (xdc_Char)0x29,  /* [1516] */
    (xdc_Char)0x20,  /* [1517] */
    (xdc_Char)0x61,  /* [1518] */
    (xdc_Char)0x6c,  /* [1519] */
    (xdc_Char)0x72,  /* [1520] */
    (xdc_Char)0x65,  /* [1521] */
    (xdc_Char)0x61,  /* [1522] */
    (xdc_Char)0x64,  /* [1523] */
    (xdc_Char)0x79,  /* [1524] */
    (xdc_Char)0x20,  /* [1525] */
    (xdc_Char)0x65,  /* [1526] */
    (xdc_Char)0x78,  /* [1527] */
    (xdc_Char)0x69,  /* [1528] */
    (xdc_Char)0x73,  /* [1529] */
    (xdc_Char)0x74,  /* [1530] */
    (xdc_Char)0x73,  /* [1531] */
    (xdc_Char)0x2c,  /* [1532] */
    (xdc_Char)0x20,  /* [1533] */
    (xdc_Char)0x69,  /* [1534] */
    (xdc_Char)0x6e,  /* [1535] */
    (xdc_Char)0x63,  /* [1536] */
    (xdc_Char)0x72,  /* [1537] */
    (xdc_Char)0x65,  /* [1538] */
    (xdc_Char)0x6d,  /* [1539] */
    (xdc_Char)0x65,  /* [1540] */
    (xdc_Char)0x6e,  /* [1541] */
    (xdc_Char)0x74,  /* [1542] */
    (xdc_Char)0x69,  /* [1543] */
    (xdc_Char)0x6e,  /* [1544] */
    (xdc_Char)0x67,  /* [1545] */
    (xdc_Char)0x20,  /* [1546] */
    (xdc_Char)0x72,  /* [1547] */
    (xdc_Char)0x65,  /* [1548] */
    (xdc_Char)0x66,  /* [1549] */
    (xdc_Char)0x65,  /* [1550] */
    (xdc_Char)0x72,  /* [1551] */
    (xdc_Char)0x65,  /* [1552] */
    (xdc_Char)0x6e,  /* [1553] */
    (xdc_Char)0x63,  /* [1554] */
    (xdc_Char)0x65,  /* [1555] */
    (xdc_Char)0x20,  /* [1556] */
    (xdc_Char)0x63,  /* [1557] */
    (xdc_Char)0x6f,  /* [1558] */
    (xdc_Char)0x75,  /* [1559] */
    (xdc_Char)0x6e,  /* [1560] */
    (xdc_Char)0x74,  /* [1561] */
    (xdc_Char)0x0,  /* [1562] */
    (xdc_Char)0x2d,  /* [1563] */
    (xdc_Char)0x2d,  /* [1564] */
    (xdc_Char)0x2d,  /* [1565] */
    (xdc_Char)0x20,  /* [1566] */
    (xdc_Char)0x53,  /* [1567] */
    (xdc_Char)0x65,  /* [1568] */
    (xdc_Char)0x6d,  /* [1569] */
    (xdc_Char)0x50,  /* [1570] */
    (xdc_Char)0x72,  /* [1571] */
    (xdc_Char)0x6f,  /* [1572] */
    (xdc_Char)0x63,  /* [1573] */
    (xdc_Char)0x65,  /* [1574] */
    (xdc_Char)0x73,  /* [1575] */
    (xdc_Char)0x73,  /* [1576] */
    (xdc_Char)0x28,  /* [1577] */
    (xdc_Char)0x25,  /* [1578] */
    (xdc_Char)0x64,  /* [1579] */
    (xdc_Char)0x29,  /* [1580] */
    (xdc_Char)0x20,  /* [1581] */
    (xdc_Char)0x44,  /* [1582] */
    (xdc_Char)0x4e,  /* [1583] */
    (xdc_Char)0x45,  /* [1584] */
    (xdc_Char)0x2c,  /* [1585] */
    (xdc_Char)0x20,  /* [1586] */
    (xdc_Char)0x63,  /* [1587] */
    (xdc_Char)0x72,  /* [1588] */
    (xdc_Char)0x65,  /* [1589] */
    (xdc_Char)0x61,  /* [1590] */
    (xdc_Char)0x74,  /* [1591] */
    (xdc_Char)0x69,  /* [1592] */
    (xdc_Char)0x6e,  /* [1593] */
    (xdc_Char)0x67,  /* [1594] */
    (xdc_Char)0x0,  /* [1595] */
    (xdc_Char)0x3c,  /* [1596] */
    (xdc_Char)0x2d,  /* [1597] */
    (xdc_Char)0x2d,  /* [1598] */
    (xdc_Char)0x20,  /* [1599] */
    (xdc_Char)0x73,  /* [1600] */
    (xdc_Char)0x74,  /* [1601] */
    (xdc_Char)0x61,  /* [1602] */
    (xdc_Char)0x72,  /* [1603] */
    (xdc_Char)0x74,  /* [1604] */
    (xdc_Char)0x3a,  /* [1605] */
    (xdc_Char)0x20,  /* [1606] */
    (xdc_Char)0x28,  /* [1607] */
    (xdc_Char)0x25,  /* [1608] */
    (xdc_Char)0x70,  /* [1609] */
    (xdc_Char)0x29,  /* [1610] */
    (xdc_Char)0x0,  /* [1611] */
    (xdc_Char)0x2d,  /* [1612] */
    (xdc_Char)0x2d,  /* [1613] */
    (xdc_Char)0x3e,  /* [1614] */
    (xdc_Char)0x20,  /* [1615] */
    (xdc_Char)0x66,  /* [1616] */
    (xdc_Char)0x69,  /* [1617] */
    (xdc_Char)0x6e,  /* [1618] */
    (xdc_Char)0x69,  /* [1619] */
    (xdc_Char)0x73,  /* [1620] */
    (xdc_Char)0x68,  /* [1621] */
    (xdc_Char)0x3a,  /* [1622] */
    (xdc_Char)0x20,  /* [1623] */
    (xdc_Char)0x28,  /* [1624] */
    (xdc_Char)0x25,  /* [1625] */
    (xdc_Char)0x70,  /* [1626] */
    (xdc_Char)0x29,  /* [1627] */
    (xdc_Char)0x0,  /* [1628] */
    (xdc_Char)0x2d,  /* [1629] */
    (xdc_Char)0x2d,  /* [1630] */
    (xdc_Char)0x3e,  /* [1631] */
    (xdc_Char)0x20,  /* [1632] */
    (xdc_Char)0x6a,  /* [1633] */
    (xdc_Char)0x6f,  /* [1634] */
    (xdc_Char)0x69,  /* [1635] */
    (xdc_Char)0x6e,  /* [1636] */
    (xdc_Char)0x3a,  /* [1637] */
    (xdc_Char)0x20,  /* [1638] */
    (xdc_Char)0x28,  /* [1639] */
    (xdc_Char)0x25,  /* [1640] */
    (xdc_Char)0x70,  /* [1641] */
    (xdc_Char)0x29,  /* [1642] */
    (xdc_Char)0x0,  /* [1643] */
    (xdc_Char)0x78,  /* [1644] */
    (xdc_Char)0x64,  /* [1645] */
    (xdc_Char)0x63,  /* [1646] */
    (xdc_Char)0x2e,  /* [1647] */
    (xdc_Char)0x0,  /* [1648] */
    (xdc_Char)0x72,  /* [1649] */
    (xdc_Char)0x75,  /* [1650] */
    (xdc_Char)0x6e,  /* [1651] */
    (xdc_Char)0x74,  /* [1652] */
    (xdc_Char)0x69,  /* [1653] */
    (xdc_Char)0x6d,  /* [1654] */
    (xdc_Char)0x65,  /* [1655] */
    (xdc_Char)0x2e,  /* [1656] */
    (xdc_Char)0x0,  /* [1657] */
    (xdc_Char)0x41,  /* [1658] */
    (xdc_Char)0x73,  /* [1659] */
    (xdc_Char)0x73,  /* [1660] */
    (xdc_Char)0x65,  /* [1661] */
    (xdc_Char)0x72,  /* [1662] */
    (xdc_Char)0x74,  /* [1663] */
    (xdc_Char)0x0,  /* [1664] */
    (xdc_Char)0x43,  /* [1665] */
    (xdc_Char)0x6f,  /* [1666] */
    (xdc_Char)0x72,  /* [1667] */
    (xdc_Char)0x65,  /* [1668] */
    (xdc_Char)0x0,  /* [1669] */
    (xdc_Char)0x44,  /* [1670] */
    (xdc_Char)0x65,  /* [1671] */
    (xdc_Char)0x66,  /* [1672] */
    (xdc_Char)0x61,  /* [1673] */
    (xdc_Char)0x75,  /* [1674] */
    (xdc_Char)0x6c,  /* [1675] */
    (xdc_Char)0x74,  /* [1676] */
    (xdc_Char)0x73,  /* [1677] */
    (xdc_Char)0x0,  /* [1678] */
    (xdc_Char)0x44,  /* [1679] */
    (xdc_Char)0x69,  /* [1680] */
    (xdc_Char)0x61,  /* [1681] */
    (xdc_Char)0x67,  /* [1682] */
    (xdc_Char)0x73,  /* [1683] */
    (xdc_Char)0x0,  /* [1684] */
    (xdc_Char)0x45,  /* [1685] */
    (xdc_Char)0x72,  /* [1686] */
    (xdc_Char)0x72,  /* [1687] */
    (xdc_Char)0x6f,  /* [1688] */
    (xdc_Char)0x72,  /* [1689] */
    (xdc_Char)0x0,  /* [1690] */
    (xdc_Char)0x47,  /* [1691] */
    (xdc_Char)0x61,  /* [1692] */
    (xdc_Char)0x74,  /* [1693] */
    (xdc_Char)0x65,  /* [1694] */
    (xdc_Char)0x0,  /* [1695] */
    (xdc_Char)0x4c,  /* [1696] */
    (xdc_Char)0x6f,  /* [1697] */
    (xdc_Char)0x67,  /* [1698] */
    (xdc_Char)0x0,  /* [1699] */
    (xdc_Char)0x4d,  /* [1700] */
    (xdc_Char)0x61,  /* [1701] */
    (xdc_Char)0x69,  /* [1702] */
    (xdc_Char)0x6e,  /* [1703] */
    (xdc_Char)0x0,  /* [1704] */
    (xdc_Char)0x4d,  /* [1705] */
    (xdc_Char)0x65,  /* [1706] */
    (xdc_Char)0x6d,  /* [1707] */
    (xdc_Char)0x6f,  /* [1708] */
    (xdc_Char)0x72,  /* [1709] */
    (xdc_Char)0x79,  /* [1710] */
    (xdc_Char)0x0,  /* [1711] */
    (xdc_Char)0x48,  /* [1712] */
    (xdc_Char)0x65,  /* [1713] */
    (xdc_Char)0x61,  /* [1714] */
    (xdc_Char)0x70,  /* [1715] */
    (xdc_Char)0x53,  /* [1716] */
    (xdc_Char)0x74,  /* [1717] */
    (xdc_Char)0x64,  /* [1718] */
    (xdc_Char)0x0,  /* [1719] */
    (xdc_Char)0x52,  /* [1720] */
    (xdc_Char)0x65,  /* [1721] */
    (xdc_Char)0x67,  /* [1722] */
    (xdc_Char)0x69,  /* [1723] */
    (xdc_Char)0x73,  /* [1724] */
    (xdc_Char)0x74,  /* [1725] */
    (xdc_Char)0x72,  /* [1726] */
    (xdc_Char)0x79,  /* [1727] */
    (xdc_Char)0x0,  /* [1728] */
    (xdc_Char)0x53,  /* [1729] */
    (xdc_Char)0x74,  /* [1730] */
    (xdc_Char)0x61,  /* [1731] */
    (xdc_Char)0x72,  /* [1732] */
    (xdc_Char)0x74,  /* [1733] */
    (xdc_Char)0x75,  /* [1734] */
    (xdc_Char)0x70,  /* [1735] */
    (xdc_Char)0x0,  /* [1736] */
    (xdc_Char)0x53,  /* [1737] */
    (xdc_Char)0x79,  /* [1738] */
    (xdc_Char)0x73,  /* [1739] */
    (xdc_Char)0x74,  /* [1740] */
    (xdc_Char)0x65,  /* [1741] */
    (xdc_Char)0x6d,  /* [1742] */
    (xdc_Char)0x0,  /* [1743] */
    (xdc_Char)0x53,  /* [1744] */
    (xdc_Char)0x79,  /* [1745] */
    (xdc_Char)0x73,  /* [1746] */
    (xdc_Char)0x53,  /* [1747] */
    (xdc_Char)0x74,  /* [1748] */
    (xdc_Char)0x64,  /* [1749] */
    (xdc_Char)0x0,  /* [1750] */
    (xdc_Char)0x54,  /* [1751] */
    (xdc_Char)0x65,  /* [1752] */
    (xdc_Char)0x78,  /* [1753] */
    (xdc_Char)0x74,  /* [1754] */
    (xdc_Char)0x0,  /* [1755] */
    (xdc_Char)0x54,  /* [1756] */
    (xdc_Char)0x69,  /* [1757] */
    (xdc_Char)0x6d,  /* [1758] */
    (xdc_Char)0x65,  /* [1759] */
    (xdc_Char)0x73,  /* [1760] */
    (xdc_Char)0x74,  /* [1761] */
    (xdc_Char)0x61,  /* [1762] */
    (xdc_Char)0x6d,  /* [1763] */
    (xdc_Char)0x70,  /* [1764] */
    (xdc_Char)0x0,  /* [1765] */
    (xdc_Char)0x6b,  /* [1766] */
    (xdc_Char)0x6e,  /* [1767] */
    (xdc_Char)0x6c,  /* [1768] */
    (xdc_Char)0x2e,  /* [1769] */
    (xdc_Char)0x0,  /* [1770] */
    (xdc_Char)0x54,  /* [1771] */
    (xdc_Char)0x68,  /* [1772] */
    (xdc_Char)0x72,  /* [1773] */
    (xdc_Char)0x65,  /* [1774] */
    (xdc_Char)0x61,  /* [1775] */
    (xdc_Char)0x64,  /* [1776] */
    (xdc_Char)0x0,  /* [1777] */
    (xdc_Char)0x47,  /* [1778] */
    (xdc_Char)0x61,  /* [1779] */
    (xdc_Char)0x74,  /* [1780] */
    (xdc_Char)0x65,  /* [1781] */
    (xdc_Char)0x54,  /* [1782] */
    (xdc_Char)0x68,  /* [1783] */
    (xdc_Char)0x72,  /* [1784] */
    (xdc_Char)0x65,  /* [1785] */
    (xdc_Char)0x61,  /* [1786] */
    (xdc_Char)0x64,  /* [1787] */
    (xdc_Char)0x0,  /* [1788] */
    (xdc_Char)0x53,  /* [1789] */
    (xdc_Char)0x65,  /* [1790] */
    (xdc_Char)0x6d,  /* [1791] */
    (xdc_Char)0x54,  /* [1792] */
    (xdc_Char)0x68,  /* [1793] */
    (xdc_Char)0x72,  /* [1794] */
    (xdc_Char)0x65,  /* [1795] */
    (xdc_Char)0x61,  /* [1796] */
    (xdc_Char)0x64,  /* [1797] */
    (xdc_Char)0x0,  /* [1798] */
    (xdc_Char)0x53,  /* [1799] */
    (xdc_Char)0x65,  /* [1800] */
    (xdc_Char)0x6d,  /* [1801] */
    (xdc_Char)0x50,  /* [1802] */
    (xdc_Char)0x72,  /* [1803] */
    (xdc_Char)0x6f,  /* [1804] */
    (xdc_Char)0x63,  /* [1805] */
    (xdc_Char)0x65,  /* [1806] */
    (xdc_Char)0x73,  /* [1807] */
    (xdc_Char)0x73,  /* [1808] */
    (xdc_Char)0x0,  /* [1809] */
    (xdc_Char)0x74,  /* [1810] */
    (xdc_Char)0x69,  /* [1811] */
    (xdc_Char)0x2e,  /* [1812] */
    (xdc_Char)0x0,  /* [1813] */
    (xdc_Char)0x73,  /* [1814] */
    (xdc_Char)0x64,  /* [1815] */
    (xdc_Char)0x6f,  /* [1816] */
    (xdc_Char)0x2e,  /* [1817] */
    (xdc_Char)0x0,  /* [1818] */
    (xdc_Char)0x78,  /* [1819] */
    (xdc_Char)0x64,  /* [1820] */
    (xdc_Char)0x63,  /* [1821] */
    (xdc_Char)0x72,  /* [1822] */
    (xdc_Char)0x75,  /* [1823] */
    (xdc_Char)0x6e,  /* [1824] */
    (xdc_Char)0x74,  /* [1825] */
    (xdc_Char)0x69,  /* [1826] */
    (xdc_Char)0x6d,  /* [1827] */
    (xdc_Char)0x65,  /* [1828] */
    (xdc_Char)0x2e,  /* [1829] */
    (xdc_Char)0x0,  /* [1830] */
    (xdc_Char)0x6c,  /* [1831] */
    (xdc_Char)0x69,  /* [1832] */
    (xdc_Char)0x6e,  /* [1833] */
    (xdc_Char)0x75,  /* [1834] */
    (xdc_Char)0x78,  /* [1835] */
    (xdc_Char)0x2e,  /* [1836] */
    (xdc_Char)0x0,  /* [1837] */
    (xdc_Char)0x47,  /* [1838] */
    (xdc_Char)0x61,  /* [1839] */
    (xdc_Char)0x74,  /* [1840] */
    (xdc_Char)0x65,  /* [1841] */
    (xdc_Char)0x54,  /* [1842] */
    (xdc_Char)0x68,  /* [1843] */
    (xdc_Char)0x72,  /* [1844] */
    (xdc_Char)0x65,  /* [1845] */
    (xdc_Char)0x61,  /* [1846] */
    (xdc_Char)0x64,  /* [1847] */
    (xdc_Char)0x53,  /* [1848] */
    (xdc_Char)0x75,  /* [1849] */
    (xdc_Char)0x70,  /* [1850] */
    (xdc_Char)0x70,  /* [1851] */
    (xdc_Char)0x6f,  /* [1852] */
    (xdc_Char)0x72,  /* [1853] */
    (xdc_Char)0x74,  /* [1854] */
    (xdc_Char)0x0,  /* [1855] */
    (xdc_Char)0x53,  /* [1856] */
    (xdc_Char)0x65,  /* [1857] */
    (xdc_Char)0x6d,  /* [1858] */
    (xdc_Char)0x54,  /* [1859] */
    (xdc_Char)0x68,  /* [1860] */
    (xdc_Char)0x72,  /* [1861] */
    (xdc_Char)0x65,  /* [1862] */
    (xdc_Char)0x61,  /* [1863] */
    (xdc_Char)0x64,  /* [1864] */
    (xdc_Char)0x53,  /* [1865] */
    (xdc_Char)0x75,  /* [1866] */
    (xdc_Char)0x70,  /* [1867] */
    (xdc_Char)0x70,  /* [1868] */
    (xdc_Char)0x6f,  /* [1869] */
    (xdc_Char)0x72,  /* [1870] */
    (xdc_Char)0x74,  /* [1871] */
    (xdc_Char)0x0,  /* [1872] */
    (xdc_Char)0x53,  /* [1873] */
    (xdc_Char)0x65,  /* [1874] */
    (xdc_Char)0x6d,  /* [1875] */
    (xdc_Char)0x50,  /* [1876] */
    (xdc_Char)0x72,  /* [1877] */
    (xdc_Char)0x6f,  /* [1878] */
    (xdc_Char)0x63,  /* [1879] */
    (xdc_Char)0x65,  /* [1880] */
    (xdc_Char)0x73,  /* [1881] */
    (xdc_Char)0x73,  /* [1882] */
    (xdc_Char)0x53,  /* [1883] */
    (xdc_Char)0x75,  /* [1884] */
    (xdc_Char)0x70,  /* [1885] */
    (xdc_Char)0x70,  /* [1886] */
    (xdc_Char)0x6f,  /* [1887] */
    (xdc_Char)0x72,  /* [1888] */
    (xdc_Char)0x74,  /* [1889] */
    (xdc_Char)0x0,  /* [1890] */
    (xdc_Char)0x54,  /* [1891] */
    (xdc_Char)0x68,  /* [1892] */
    (xdc_Char)0x72,  /* [1893] */
    (xdc_Char)0x65,  /* [1894] */
    (xdc_Char)0x61,  /* [1895] */
    (xdc_Char)0x64,  /* [1896] */
    (xdc_Char)0x53,  /* [1897] */
    (xdc_Char)0x75,  /* [1898] */
    (xdc_Char)0x70,  /* [1899] */
    (xdc_Char)0x70,  /* [1900] */
    (xdc_Char)0x6f,  /* [1901] */
    (xdc_Char)0x72,  /* [1902] */
    (xdc_Char)0x74,  /* [1903] */
    (xdc_Char)0x0,  /* [1904] */
    (xdc_Char)0x54,  /* [1905] */
    (xdc_Char)0x69,  /* [1906] */
    (xdc_Char)0x6d,  /* [1907] */
    (xdc_Char)0x65,  /* [1908] */
    (xdc_Char)0x73,  /* [1909] */
    (xdc_Char)0x74,  /* [1910] */
    (xdc_Char)0x61,  /* [1911] */
    (xdc_Char)0x6d,  /* [1912] */
    (xdc_Char)0x70,  /* [1913] */
    (xdc_Char)0x50,  /* [1914] */
    (xdc_Char)0x6f,  /* [1915] */
    (xdc_Char)0x73,  /* [1916] */
    (xdc_Char)0x69,  /* [1917] */
    (xdc_Char)0x78,  /* [1918] */
    (xdc_Char)0x0,  /* [1919] */
    (xdc_Char)0x75,  /* [1920] */
    (xdc_Char)0x74,  /* [1921] */
    (xdc_Char)0x69,  /* [1922] */
    (xdc_Char)0x6c,  /* [1923] */
    (xdc_Char)0x73,  /* [1924] */
    (xdc_Char)0x2e,  /* [1925] */
    (xdc_Char)0x0,  /* [1926] */
    (xdc_Char)0x6c,  /* [1927] */
    (xdc_Char)0x6f,  /* [1928] */
    (xdc_Char)0x67,  /* [1929] */
    (xdc_Char)0x67,  /* [1930] */
    (xdc_Char)0x65,  /* [1931] */
    (xdc_Char)0x72,  /* [1932] */
    (xdc_Char)0x73,  /* [1933] */
    (xdc_Char)0x2e,  /* [1934] */
    (xdc_Char)0x0,  /* [1935] */
    (xdc_Char)0x4c,  /* [1936] */
    (xdc_Char)0x6f,  /* [1937] */
    (xdc_Char)0x67,  /* [1938] */
    (xdc_Char)0x67,  /* [1939] */
    (xdc_Char)0x65,  /* [1940] */
    (xdc_Char)0x72,  /* [1941] */
    (xdc_Char)0x53,  /* [1942] */
    (xdc_Char)0x79,  /* [1943] */
    (xdc_Char)0x73,  /* [1944] */
    (xdc_Char)0x54,  /* [1945] */
    (xdc_Char)0x49,  /* [1946] */
    (xdc_Char)0x44,  /* [1947] */
    (xdc_Char)0x0,  /* [1948] */
    (xdc_Char)0x4c,  /* [1949] */
    (xdc_Char)0x6f,  /* [1950] */
    (xdc_Char)0x67,  /* [1951] */
    (xdc_Char)0x67,  /* [1952] */
    (xdc_Char)0x65,  /* [1953] */
    (xdc_Char)0x72,  /* [1954] */
    (xdc_Char)0x4d,  /* [1955] */
    (xdc_Char)0x46,  /* [1956] */
    (xdc_Char)0x50,  /* [1957] */
    (xdc_Char)0x4e,  /* [1958] */
    (xdc_Char)0x75,  /* [1959] */
    (xdc_Char)0x6c,  /* [1960] */
    (xdc_Char)0x6c,  /* [1961] */
    (xdc_Char)0x0,  /* [1962] */
    (xdc_Char)0x4c,  /* [1963] */
    (xdc_Char)0x6f,  /* [1964] */
    (xdc_Char)0x67,  /* [1965] */
    (xdc_Char)0x4d,  /* [1966] */
    (xdc_Char)0x46,  /* [1967] */
    (xdc_Char)0x50,  /* [1968] */
    (xdc_Char)0x0,  /* [1969] */
};

/* --> xdc_runtime_Text_nodeTab__A */
const __T1_xdc_runtime_Text_nodeTab xdc_runtime_Text_nodeTab__A[36] = {
    {
        (xdc_Bits16)0x0,  /* left */
        (xdc_Bits16)0x0,  /* right */
    },  /* [0] */
    {
        (xdc_Bits16)0x66c,  /* left */
        (xdc_Bits16)0x671,  /* right */
    },  /* [1] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x67a,  /* right */
    },  /* [2] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x681,  /* right */
    },  /* [3] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x686,  /* right */
    },  /* [4] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x68f,  /* right */
    },  /* [5] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x695,  /* right */
    },  /* [6] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x69b,  /* right */
    },  /* [7] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x6a0,  /* right */
    },  /* [8] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x6a4,  /* right */
    },  /* [9] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x6a9,  /* right */
    },  /* [10] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x6b0,  /* right */
    },  /* [11] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x6b8,  /* right */
    },  /* [12] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x6c1,  /* right */
    },  /* [13] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x6c9,  /* right */
    },  /* [14] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x6d0,  /* right */
    },  /* [15] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x6d7,  /* right */
    },  /* [16] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x6dc,  /* right */
    },  /* [17] */
    {
        (xdc_Bits16)0x8001,  /* left */
        (xdc_Bits16)0x6e6,  /* right */
    },  /* [18] */
    {
        (xdc_Bits16)0x8012,  /* left */
        (xdc_Bits16)0x6eb,  /* right */
    },  /* [19] */
    {
        (xdc_Bits16)0x8012,  /* left */
        (xdc_Bits16)0x6f2,  /* right */
    },  /* [20] */
    {
        (xdc_Bits16)0x8012,  /* left */
        (xdc_Bits16)0x6fd,  /* right */
    },  /* [21] */
    {
        (xdc_Bits16)0x8012,  /* left */
        (xdc_Bits16)0x707,  /* right */
    },  /* [22] */
    {
        (xdc_Bits16)0x712,  /* left */
        (xdc_Bits16)0x716,  /* right */
    },  /* [23] */
    {
        (xdc_Bits16)0x8017,  /* left */
        (xdc_Bits16)0x71b,  /* right */
    },  /* [24] */
    {
        (xdc_Bits16)0x8018,  /* left */
        (xdc_Bits16)0x727,  /* right */
    },  /* [25] */
    {
        (xdc_Bits16)0x8019,  /* left */
        (xdc_Bits16)0x72e,  /* right */
    },  /* [26] */
    {
        (xdc_Bits16)0x8019,  /* left */
        (xdc_Bits16)0x740,  /* right */
    },  /* [27] */
    {
        (xdc_Bits16)0x8019,  /* left */
        (xdc_Bits16)0x751,  /* right */
    },  /* [28] */
    {
        (xdc_Bits16)0x8019,  /* left */
        (xdc_Bits16)0x763,  /* right */
    },  /* [29] */
    {
        (xdc_Bits16)0x8019,  /* left */
        (xdc_Bits16)0x771,  /* right */
    },  /* [30] */
    {
        (xdc_Bits16)0x8017,  /* left */
        (xdc_Bits16)0x780,  /* right */
    },  /* [31] */
    {
        (xdc_Bits16)0x801f,  /* left */
        (xdc_Bits16)0x787,  /* right */
    },  /* [32] */
    {
        (xdc_Bits16)0x8020,  /* left */
        (xdc_Bits16)0x790,  /* right */
    },  /* [33] */
    {
        (xdc_Bits16)0x8020,  /* left */
        (xdc_Bits16)0x79d,  /* right */
    },  /* [34] */
    {
        (xdc_Bits16)0x8020,  /* left */
        (xdc_Bits16)0x7ab,  /* right */
    },  /* [35] */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_Text_Module__diagsEnabled xdc_runtime_Text_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_Text_Module__diagsIncluded xdc_runtime_Text_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_Text_Module__diagsMask xdc_runtime_Text_Module__diagsMask__C = ((CT__xdc_runtime_Text_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_Text_Module__gateObj xdc_runtime_Text_Module__gateObj__C = ((CT__xdc_runtime_Text_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_Text_Module__gatePrms xdc_runtime_Text_Module__gatePrms__C = ((CT__xdc_runtime_Text_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_Text_Module__id xdc_runtime_Text_Module__id__C = (xdc_Bits16)0x8010;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_Text_Module__loggerDefined xdc_runtime_Text_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_Text_Module__loggerObj xdc_runtime_Text_Module__loggerObj__C = ((CT__xdc_runtime_Text_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_Text_Module__loggerFxn0 xdc_runtime_Text_Module__loggerFxn0__C = ((CT__xdc_runtime_Text_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_Text_Module__loggerFxn1 xdc_runtime_Text_Module__loggerFxn1__C = ((CT__xdc_runtime_Text_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_Text_Module__loggerFxn2 xdc_runtime_Text_Module__loggerFxn2__C = ((CT__xdc_runtime_Text_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_Text_Module__loggerFxn4 xdc_runtime_Text_Module__loggerFxn4__C = ((CT__xdc_runtime_Text_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_Text_Module__loggerFxn8 xdc_runtime_Text_Module__loggerFxn8__C = ((CT__xdc_runtime_Text_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_Text_Module__startupDoneFxn xdc_runtime_Text_Module__startupDoneFxn__C = ((CT__xdc_runtime_Text_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_Text_Object__count xdc_runtime_Text_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_Text_Object__heap xdc_runtime_Text_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_Text_Object__sizeof xdc_runtime_Text_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_Text_Object__table xdc_runtime_Text_Object__table__C = 0;

/* nameUnknown__C */
__FAR__ const CT__xdc_runtime_Text_nameUnknown xdc_runtime_Text_nameUnknown__C = "{unknown-instance-name}";

/* nameEmpty__C */
__FAR__ const CT__xdc_runtime_Text_nameEmpty xdc_runtime_Text_nameEmpty__C = "{empty-instance-name}";

/* nameStatic__C */
__FAR__ const CT__xdc_runtime_Text_nameStatic xdc_runtime_Text_nameStatic__C = "{static-instance-name}";

/* isLoaded__C */
__FAR__ const CT__xdc_runtime_Text_isLoaded xdc_runtime_Text_isLoaded__C = 1;

/* charTab__C */
__FAR__ const CT__xdc_runtime_Text_charTab xdc_runtime_Text_charTab__C = ((CT__xdc_runtime_Text_charTab)xdc_runtime_Text_charTab__A);

/* nodeTab__C */
__FAR__ const CT__xdc_runtime_Text_nodeTab xdc_runtime_Text_nodeTab__C = ((CT__xdc_runtime_Text_nodeTab)xdc_runtime_Text_nodeTab__A);

/* charCnt__C */
__FAR__ const CT__xdc_runtime_Text_charCnt xdc_runtime_Text_charCnt__C = (xdc_Int16)0x7b2;

/* nodeCnt__C */
__FAR__ const CT__xdc_runtime_Text_nodeCnt xdc_runtime_Text_nodeCnt__C = (xdc_Int16)0x24;

/* unnamedModsLastId__C */
__FAR__ const CT__xdc_runtime_Text_unnamedModsLastId xdc_runtime_Text_unnamedModsLastId__C = (xdc_UInt16)0x4000;

/* registryModsLastId__C */
__FAR__ const CT__xdc_runtime_Text_registryModsLastId xdc_runtime_Text_registryModsLastId__C = (xdc_UInt16)0x7fff;

/* visitRopeFxn__C */
__FAR__ const CT__xdc_runtime_Text_visitRopeFxn xdc_runtime_Text_visitRopeFxn__C = ((CT__xdc_runtime_Text_visitRopeFxn)((xdc_Fxn)xdc_runtime_Text_visitRope__I));

/* visitRopeFxn2__C */
__FAR__ const CT__xdc_runtime_Text_visitRopeFxn2 xdc_runtime_Text_visitRopeFxn2__C = ((CT__xdc_runtime_Text_visitRopeFxn2)((xdc_Fxn)xdc_runtime_Text_visitRope2__I));


/*
 * ======== xdc.runtime.Timestamp INITIALIZERS ========
 */

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__diagsEnabled xdc_runtime_Timestamp_Module__diagsEnabled__C = (xdc_Bits32)0x10;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__diagsIncluded xdc_runtime_Timestamp_Module__diagsIncluded__C = (xdc_Bits32)0x10;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__diagsMask xdc_runtime_Timestamp_Module__diagsMask__C = ((CT__xdc_runtime_Timestamp_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__gateObj xdc_runtime_Timestamp_Module__gateObj__C = ((CT__xdc_runtime_Timestamp_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__gatePrms xdc_runtime_Timestamp_Module__gatePrms__C = ((CT__xdc_runtime_Timestamp_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__id xdc_runtime_Timestamp_Module__id__C = (xdc_Bits16)0x8011;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__loggerDefined xdc_runtime_Timestamp_Module__loggerDefined__C = 0;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__loggerObj xdc_runtime_Timestamp_Module__loggerObj__C = ((CT__xdc_runtime_Timestamp_Module__loggerObj)0);

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__loggerFxn0 xdc_runtime_Timestamp_Module__loggerFxn0__C = ((CT__xdc_runtime_Timestamp_Module__loggerFxn0)0);

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__loggerFxn1 xdc_runtime_Timestamp_Module__loggerFxn1__C = ((CT__xdc_runtime_Timestamp_Module__loggerFxn1)0);

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__loggerFxn2 xdc_runtime_Timestamp_Module__loggerFxn2__C = ((CT__xdc_runtime_Timestamp_Module__loggerFxn2)0);

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__loggerFxn4 xdc_runtime_Timestamp_Module__loggerFxn4__C = ((CT__xdc_runtime_Timestamp_Module__loggerFxn4)0);

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__loggerFxn8 xdc_runtime_Timestamp_Module__loggerFxn8__C = ((CT__xdc_runtime_Timestamp_Module__loggerFxn8)0);

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_Timestamp_Module__startupDoneFxn xdc_runtime_Timestamp_Module__startupDoneFxn__C = ((CT__xdc_runtime_Timestamp_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_Timestamp_Object__count xdc_runtime_Timestamp_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_Timestamp_Object__heap xdc_runtime_Timestamp_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_Timestamp_Object__sizeof xdc_runtime_Timestamp_Object__sizeof__C = 0;

/* Object__table__C */
__FAR__ const CT__xdc_runtime_Timestamp_Object__table xdc_runtime_Timestamp_Object__table__C = 0;


/*
 * ======== xdc.runtime.Timestamp_SupportProxy INITIALIZERS ========
 */


/*
 * ======== xdc.runtime.knl.GateThread INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_knl_GateThread_Object__DESC__C;

/* Object__PARAMS__C */
__FAR__ const xdc_runtime_knl_GateThread_Params xdc_runtime_knl_GateThread_Object__PARAMS__C = {
    sizeof (xdc_runtime_knl_GateThread_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&xdc_runtime_knl_GateThread_Object__PARAMS__C.__iprms, /* instance */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
xdc_runtime_knl_GateThread_Module__ xdc_runtime_knl_GateThread_Module__root__V = {
    {&xdc_runtime_knl_GateThread_Module__root__V.link,  /* link.next */
    &xdc_runtime_knl_GateThread_Module__root__V.link},  /* link.prev */
};

/* Object__table__V */
xdc_runtime_knl_GateThread_Object__ xdc_runtime_knl_GateThread_Object__table__V[1] = {
    {/* instance#0 */
        &xdc_runtime_knl_GateThread_Module__FXNS__C,
        (xdc_runtime_knl_GateThread_Proxy_Handle)&ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__V[1],  /* proxyHandle */
    },
};

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__diagsEnabled xdc_runtime_knl_GateThread_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__diagsIncluded xdc_runtime_knl_GateThread_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__diagsMask xdc_runtime_knl_GateThread_Module__diagsMask__C = ((CT__xdc_runtime_knl_GateThread_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__gateObj xdc_runtime_knl_GateThread_Module__gateObj__C = ((CT__xdc_runtime_knl_GateThread_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__gatePrms xdc_runtime_knl_GateThread_Module__gatePrms__C = ((CT__xdc_runtime_knl_GateThread_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__id xdc_runtime_knl_GateThread_Module__id__C = (xdc_Bits16)0x8014;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__loggerDefined xdc_runtime_knl_GateThread_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__loggerObj xdc_runtime_knl_GateThread_Module__loggerObj__C = ((CT__xdc_runtime_knl_GateThread_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__loggerFxn0 xdc_runtime_knl_GateThread_Module__loggerFxn0__C = ((CT__xdc_runtime_knl_GateThread_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__loggerFxn1 xdc_runtime_knl_GateThread_Module__loggerFxn1__C = ((CT__xdc_runtime_knl_GateThread_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__loggerFxn2 xdc_runtime_knl_GateThread_Module__loggerFxn2__C = ((CT__xdc_runtime_knl_GateThread_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__loggerFxn4 xdc_runtime_knl_GateThread_Module__loggerFxn4__C = ((CT__xdc_runtime_knl_GateThread_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__loggerFxn8 xdc_runtime_knl_GateThread_Module__loggerFxn8__C = ((CT__xdc_runtime_knl_GateThread_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Module__startupDoneFxn xdc_runtime_knl_GateThread_Module__startupDoneFxn__C = ((CT__xdc_runtime_knl_GateThread_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Object__count xdc_runtime_knl_GateThread_Object__count__C = 1;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Object__heap xdc_runtime_knl_GateThread_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Object__sizeof xdc_runtime_knl_GateThread_Object__sizeof__C = sizeof(xdc_runtime_knl_GateThread_Object__);

/* Object__table__C */
__FAR__ const CT__xdc_runtime_knl_GateThread_Object__table xdc_runtime_knl_GateThread_Object__table__C = xdc_runtime_knl_GateThread_Object__table__V;


/*
 * ======== xdc.runtime.knl.GateThread_Proxy INITIALIZERS ========
 */


/*
 * ======== xdc.runtime.knl.SemProcess INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_knl_SemProcess_Object__DESC__C;

/* Object__PARAMS__C */
__FAR__ const xdc_runtime_knl_SemProcess_Params xdc_runtime_knl_SemProcess_Object__PARAMS__C = {
    sizeof (xdc_runtime_knl_SemProcess_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&xdc_runtime_knl_SemProcess_Object__PARAMS__C.__iprms, /* instance */
    xdc_runtime_knl_ISemaphore_Mode_COUNTING,  /* mode */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
xdc_runtime_knl_SemProcess_Module__ xdc_runtime_knl_SemProcess_Module__root__V = {
    {&xdc_runtime_knl_SemProcess_Module__root__V.link,  /* link.next */
    &xdc_runtime_knl_SemProcess_Module__root__V.link},  /* link.prev */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__diagsEnabled xdc_runtime_knl_SemProcess_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__diagsIncluded xdc_runtime_knl_SemProcess_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__diagsMask xdc_runtime_knl_SemProcess_Module__diagsMask__C = ((CT__xdc_runtime_knl_SemProcess_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__gateObj xdc_runtime_knl_SemProcess_Module__gateObj__C = ((CT__xdc_runtime_knl_SemProcess_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__gatePrms xdc_runtime_knl_SemProcess_Module__gatePrms__C = ((CT__xdc_runtime_knl_SemProcess_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__id xdc_runtime_knl_SemProcess_Module__id__C = (xdc_Bits16)0x8016;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__loggerDefined xdc_runtime_knl_SemProcess_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__loggerObj xdc_runtime_knl_SemProcess_Module__loggerObj__C = ((CT__xdc_runtime_knl_SemProcess_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__loggerFxn0 xdc_runtime_knl_SemProcess_Module__loggerFxn0__C = ((CT__xdc_runtime_knl_SemProcess_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__loggerFxn1 xdc_runtime_knl_SemProcess_Module__loggerFxn1__C = ((CT__xdc_runtime_knl_SemProcess_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__loggerFxn2 xdc_runtime_knl_SemProcess_Module__loggerFxn2__C = ((CT__xdc_runtime_knl_SemProcess_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__loggerFxn4 xdc_runtime_knl_SemProcess_Module__loggerFxn4__C = ((CT__xdc_runtime_knl_SemProcess_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__loggerFxn8 xdc_runtime_knl_SemProcess_Module__loggerFxn8__C = ((CT__xdc_runtime_knl_SemProcess_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Module__startupDoneFxn xdc_runtime_knl_SemProcess_Module__startupDoneFxn__C = ((CT__xdc_runtime_knl_SemProcess_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Object__count xdc_runtime_knl_SemProcess_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Object__heap xdc_runtime_knl_SemProcess_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Object__sizeof xdc_runtime_knl_SemProcess_Object__sizeof__C = sizeof(xdc_runtime_knl_SemProcess_Object__);

/* Object__table__C */
__FAR__ const CT__xdc_runtime_knl_SemProcess_Object__table xdc_runtime_knl_SemProcess_Object__table__C = 0;


/*
 * ======== xdc.runtime.knl.SemProcess_Proxy INITIALIZERS ========
 */


/*
 * ======== xdc.runtime.knl.SemThread INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_knl_SemThread_Object__DESC__C;

/* Object__PARAMS__C */
__FAR__ const xdc_runtime_knl_SemThread_Params xdc_runtime_knl_SemThread_Object__PARAMS__C = {
    sizeof (xdc_runtime_knl_SemThread_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&xdc_runtime_knl_SemThread_Object__PARAMS__C.__iprms, /* instance */
    xdc_runtime_knl_ISemaphore_Mode_COUNTING,  /* mode */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
xdc_runtime_knl_SemThread_Module__ xdc_runtime_knl_SemThread_Module__root__V = {
    {&xdc_runtime_knl_SemThread_Module__root__V.link,  /* link.next */
    &xdc_runtime_knl_SemThread_Module__root__V.link},  /* link.prev */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__diagsEnabled xdc_runtime_knl_SemThread_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__diagsIncluded xdc_runtime_knl_SemThread_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__diagsMask xdc_runtime_knl_SemThread_Module__diagsMask__C = ((CT__xdc_runtime_knl_SemThread_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__gateObj xdc_runtime_knl_SemThread_Module__gateObj__C = ((CT__xdc_runtime_knl_SemThread_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__gatePrms xdc_runtime_knl_SemThread_Module__gatePrms__C = ((CT__xdc_runtime_knl_SemThread_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__id xdc_runtime_knl_SemThread_Module__id__C = (xdc_Bits16)0x8015;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerDefined xdc_runtime_knl_SemThread_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerObj xdc_runtime_knl_SemThread_Module__loggerObj__C = ((CT__xdc_runtime_knl_SemThread_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerFxn0 xdc_runtime_knl_SemThread_Module__loggerFxn0__C = ((CT__xdc_runtime_knl_SemThread_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerFxn1 xdc_runtime_knl_SemThread_Module__loggerFxn1__C = ((CT__xdc_runtime_knl_SemThread_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerFxn2 xdc_runtime_knl_SemThread_Module__loggerFxn2__C = ((CT__xdc_runtime_knl_SemThread_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerFxn4 xdc_runtime_knl_SemThread_Module__loggerFxn4__C = ((CT__xdc_runtime_knl_SemThread_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__loggerFxn8 xdc_runtime_knl_SemThread_Module__loggerFxn8__C = ((CT__xdc_runtime_knl_SemThread_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Module__startupDoneFxn xdc_runtime_knl_SemThread_Module__startupDoneFxn__C = ((CT__xdc_runtime_knl_SemThread_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Object__count xdc_runtime_knl_SemThread_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Object__heap xdc_runtime_knl_SemThread_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Object__sizeof xdc_runtime_knl_SemThread_Object__sizeof__C = sizeof(xdc_runtime_knl_SemThread_Object__);

/* Object__table__C */
__FAR__ const CT__xdc_runtime_knl_SemThread_Object__table xdc_runtime_knl_SemThread_Object__table__C = 0;


/*
 * ======== xdc.runtime.knl.SemThread_Proxy INITIALIZERS ========
 */


/*
 * ======== xdc.runtime.knl.Thread INITIALIZERS ========
 */

/* Object__DESC__C */
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_knl_Thread_Object__DESC__C;

/* Object__PARAMS__C */
__FAR__ const xdc_runtime_knl_Thread_Params xdc_runtime_knl_Thread_Object__PARAMS__C = {
    sizeof (xdc_runtime_knl_Thread_Params), /* __size */
    0, /* __self */
    0, /* __fxns */
    (xdc_runtime_IInstance_Params*)&xdc_runtime_knl_Thread_Object__PARAMS__C.__iprms, /* instance */
    ((xdc_IArg)((void*)0x0)),  /* arg */
    xdc_runtime_knl_Thread_Priority_NORMAL,  /* priority */
    (xdc_Int)0x0,  /* osPriority */
    (xdc_SizeT)0x0,  /* stackSize */
    ((xdc_Ptr)0),  /* tls */
    {
        sizeof (xdc_runtime_IInstance_Params), /* __size */
        0,  /* name */
    },  /* instance */
};

/* Module__root__V */
xdc_runtime_knl_Thread_Module__ xdc_runtime_knl_Thread_Module__root__V = {
    {&xdc_runtime_knl_Thread_Module__root__V.link,  /* link.next */
    &xdc_runtime_knl_Thread_Module__root__V.link},  /* link.prev */
};

/* Module__diagsEnabled__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__diagsEnabled xdc_runtime_knl_Thread_Module__diagsEnabled__C = (xdc_Bits32)0x90;

/* Module__diagsIncluded__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__diagsIncluded xdc_runtime_knl_Thread_Module__diagsIncluded__C = (xdc_Bits32)0x90;

/* Module__diagsMask__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__diagsMask xdc_runtime_knl_Thread_Module__diagsMask__C = ((CT__xdc_runtime_knl_Thread_Module__diagsMask)0);

/* Module__gateObj__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__gateObj xdc_runtime_knl_Thread_Module__gateObj__C = ((CT__xdc_runtime_knl_Thread_Module__gateObj)0);

/* Module__gatePrms__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__gatePrms xdc_runtime_knl_Thread_Module__gatePrms__C = ((CT__xdc_runtime_knl_Thread_Module__gatePrms)0);

/* Module__id__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__id xdc_runtime_knl_Thread_Module__id__C = (xdc_Bits16)0x8013;

/* Module__loggerDefined__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__loggerDefined xdc_runtime_knl_Thread_Module__loggerDefined__C = 1;

/* Module__loggerObj__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__loggerObj xdc_runtime_knl_Thread_Module__loggerObj__C = ((CT__xdc_runtime_knl_Thread_Module__loggerObj)((void*)(xdc_runtime_ILogger_Handle)&ti_sdo_utils_loggers_LoggerSysTID_Object__table__V[0]));

/* Module__loggerFxn0__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__loggerFxn0 xdc_runtime_knl_Thread_Module__loggerFxn0__C = ((CT__xdc_runtime_knl_Thread_Module__loggerFxn0)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write0));

/* Module__loggerFxn1__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__loggerFxn1 xdc_runtime_knl_Thread_Module__loggerFxn1__C = ((CT__xdc_runtime_knl_Thread_Module__loggerFxn1)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write1));

/* Module__loggerFxn2__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__loggerFxn2 xdc_runtime_knl_Thread_Module__loggerFxn2__C = ((CT__xdc_runtime_knl_Thread_Module__loggerFxn2)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write2));

/* Module__loggerFxn4__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__loggerFxn4 xdc_runtime_knl_Thread_Module__loggerFxn4__C = ((CT__xdc_runtime_knl_Thread_Module__loggerFxn4)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write4));

/* Module__loggerFxn8__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__loggerFxn8 xdc_runtime_knl_Thread_Module__loggerFxn8__C = ((CT__xdc_runtime_knl_Thread_Module__loggerFxn8)((xdc_Fxn)ti_sdo_utils_loggers_LoggerSysTID_write8));

/* Module__startupDoneFxn__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Module__startupDoneFxn xdc_runtime_knl_Thread_Module__startupDoneFxn__C = ((CT__xdc_runtime_knl_Thread_Module__startupDoneFxn)0);

/* Object__count__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Object__count xdc_runtime_knl_Thread_Object__count__C = 0;

/* Object__heap__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Object__heap xdc_runtime_knl_Thread_Object__heap__C = 0;

/* Object__sizeof__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Object__sizeof xdc_runtime_knl_Thread_Object__sizeof__C = sizeof(xdc_runtime_knl_Thread_Object__);

/* Object__table__C */
__FAR__ const CT__xdc_runtime_knl_Thread_Object__table xdc_runtime_knl_Thread_Object__table__C = 0;

/* A_zeroTimeout__C */
__FAR__ const CT__xdc_runtime_knl_Thread_A_zeroTimeout xdc_runtime_knl_Thread_A_zeroTimeout__C = (((xdc_runtime_Assert_Id)355) << 16 | 16);

/* defaultStackSize__C */
__FAR__ const CT__xdc_runtime_knl_Thread_defaultStackSize xdc_runtime_knl_Thread_defaultStackSize__C = (xdc_SizeT)0x0;


/*
 * ======== xdc.runtime.knl.Thread_Proxy INITIALIZERS ========
 */


/*
 * ======== ti.sdo.utils.loggers.LogMFP FUNCTION STUBS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_utils_loggers_LogMFP_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_utils_loggers_LogMFP_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_utils_loggers_LogMFP_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_utils_loggers_LogMFP_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_utils_loggers_LogMFP_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_utils_loggers_LogMFP_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_utils_loggers_LogMFP_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_utils_loggers_LogMFP_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_utils_loggers_LogMFP_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_utils_loggers_LogMFP_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_utils_loggers_LogMFP_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_utils_loggers_LogMFP_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_utils_loggers_LogMFP_Module_GateProxy_query

/* entry/exit Log events */
#define ti_sdo_utils_loggers_LogMFP_control__ENTRY_EVT 0x0
#define ti_sdo_utils_loggers_LogMFP_control__EXIT_EVT 0x0

/* control__E */
xdc_Void ti_sdo_utils_loggers_LogMFP_control__E( xdc_Int cmd, xdc_UArg cmdArgs ) 
{
    ti_sdo_utils_loggers_LogMFP_control__F(cmd, cmdArgs);
}


/*
 * ======== ti.sdo.utils.loggers.LoggerMFPNull FUNCTION STUBS ========
 */

/* enable__E */
xdc_Bool ti_sdo_utils_loggers_LoggerMFPNull_enable__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle __inst ) 
{
    return ti_sdo_utils_loggers_LoggerMFPNull_enable__F((void*)__inst);
}

/* disable__E */
xdc_Bool ti_sdo_utils_loggers_LoggerMFPNull_disable__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle __inst ) 
{
    return ti_sdo_utils_loggers_LoggerMFPNull_disable__F((void*)__inst);
}

/* write0__E */
xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_write0__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid ) 
{
    ti_sdo_utils_loggers_LoggerMFPNull_write0__F((void*)__inst, evt, mid);
}

/* write1__E */
xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_write1__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1 ) 
{
    ti_sdo_utils_loggers_LoggerMFPNull_write1__F((void*)__inst, evt, mid, a1);
}

/* write2__E */
xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_write2__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2 ) 
{
    ti_sdo_utils_loggers_LoggerMFPNull_write2__F((void*)__inst, evt, mid, a1, a2);
}

/* write4__E */
xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_write4__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4 ) 
{
    ti_sdo_utils_loggers_LoggerMFPNull_write4__F((void*)__inst, evt, mid, a1, a2, a3, a4);
}

/* write8__E */
xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_write8__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8 ) 
{
    ti_sdo_utils_loggers_LoggerMFPNull_write8__F((void*)__inst, evt, mid, a1, a2, a3, a4, a5, a6, a7, a8);
}

/* control__E */
xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_control__E( xdc_Int cmd, xdc_UArg cmdArgs ) 
{
    ti_sdo_utils_loggers_LoggerMFPNull_control__F(cmd, cmdArgs);
}


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID FUNCTION STUBS ========
 */

/* enable__E */
xdc_Bool ti_sdo_utils_loggers_LoggerSysTID_enable__E( ti_sdo_utils_loggers_LoggerSysTID_Handle __inst ) 
{
    return ti_sdo_utils_loggers_LoggerSysTID_enable__F((void*)__inst);
}

/* disable__E */
xdc_Bool ti_sdo_utils_loggers_LoggerSysTID_disable__E( ti_sdo_utils_loggers_LoggerSysTID_Handle __inst ) 
{
    return ti_sdo_utils_loggers_LoggerSysTID_disable__F((void*)__inst);
}

/* write0__E */
xdc_Void ti_sdo_utils_loggers_LoggerSysTID_write0__E( ti_sdo_utils_loggers_LoggerSysTID_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid ) 
{
    ti_sdo_utils_loggers_LoggerSysTID_write0__F((void*)__inst, evt, mid);
}

/* write1__E */
xdc_Void ti_sdo_utils_loggers_LoggerSysTID_write1__E( ti_sdo_utils_loggers_LoggerSysTID_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1 ) 
{
    ti_sdo_utils_loggers_LoggerSysTID_write1__F((void*)__inst, evt, mid, a1);
}

/* write2__E */
xdc_Void ti_sdo_utils_loggers_LoggerSysTID_write2__E( ti_sdo_utils_loggers_LoggerSysTID_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2 ) 
{
    ti_sdo_utils_loggers_LoggerSysTID_write2__F((void*)__inst, evt, mid, a1, a2);
}

/* write4__E */
xdc_Void ti_sdo_utils_loggers_LoggerSysTID_write4__E( ti_sdo_utils_loggers_LoggerSysTID_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4 ) 
{
    ti_sdo_utils_loggers_LoggerSysTID_write4__F((void*)__inst, evt, mid, a1, a2, a3, a4);
}

/* write8__E */
xdc_Void ti_sdo_utils_loggers_LoggerSysTID_write8__E( ti_sdo_utils_loggers_LoggerSysTID_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8 ) 
{
    ti_sdo_utils_loggers_LoggerSysTID_write8__F((void*)__inst, evt, mid, a1, a2, a3, a4, a5, a6, a7, a8);
}

/* control__E */
xdc_Void ti_sdo_utils_loggers_LoggerSysTID_control__E( xdc_Int cmd, xdc_UArg cmdArgs ) 
{
    ti_sdo_utils_loggers_LoggerSysTID_control__F(cmd, cmdArgs);
}

/* Module_startup */
xdc_Int ti_sdo_utils_loggers_LoggerSysTID_Module_startup__E( xdc_Int state )
{
    return ti_sdo_utils_loggers_LoggerSysTID_Module_startup__F(state);
}


/*
 * ======== ti.sdo.xdcruntime.linux.GateThreadSupport FUNCTION STUBS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_xdcruntime_linux_GateThreadSupport_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_xdcruntime_linux_GateThreadSupport_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_xdcruntime_linux_GateThreadSupport_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_xdcruntime_linux_GateThreadSupport_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_xdcruntime_linux_GateThreadSupport_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_xdcruntime_linux_GateThreadSupport_Module_GateProxy_query

/* entry/exit Log events */
#define ti_sdo_xdcruntime_linux_GateThreadSupport_query__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_GateThreadSupport_query__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_GateThreadSupport_enter__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_GateThreadSupport_enter__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_GateThreadSupport_leave__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_GateThreadSupport_leave__EXIT_EVT 0x0

/* query__E */
xdc_Bool ti_sdo_xdcruntime_linux_GateThreadSupport_query__E( xdc_Int qual ) 
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_query__F(qual);
}

/* enter__E */
xdc_IArg ti_sdo_xdcruntime_linux_GateThreadSupport_enter__E( ti_sdo_xdcruntime_linux_GateThreadSupport_Handle __inst ) 
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_enter__F((void*)__inst);
}

/* leave__E */
xdc_Void ti_sdo_xdcruntime_linux_GateThreadSupport_leave__E( ti_sdo_xdcruntime_linux_GateThreadSupport_Handle __inst, xdc_IArg key ) 
{
    ti_sdo_xdcruntime_linux_GateThreadSupport_leave__F((void*)__inst, key);
}

/* Module_startup */
xdc_Int ti_sdo_xdcruntime_linux_GateThreadSupport_Module_startup__E( xdc_Int state )
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_Module_startup__F(state);
}


/*
 * ======== ti.sdo.xdcruntime.linux.SemProcessSupport FUNCTION STUBS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_xdcruntime_linux_SemProcessSupport_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_xdcruntime_linux_SemProcessSupport_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_xdcruntime_linux_SemProcessSupport_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_xdcruntime_linux_SemProcessSupport_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_xdcruntime_linux_SemProcessSupport_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_xdcruntime_linux_SemProcessSupport_Module_GateProxy_query

/* entry/exit Log events */
#define ti_sdo_xdcruntime_linux_SemProcessSupport_pend__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_SemProcessSupport_pend__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_SemProcessSupport_post__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_SemProcessSupport_post__EXIT_EVT 0x0

/* pend__E */
xdc_Int ti_sdo_xdcruntime_linux_SemProcessSupport_pend__E( ti_sdo_xdcruntime_linux_SemProcessSupport_Handle __inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_SemProcessSupport_pend__F((void*)__inst, timeout, eb);
}

/* post__E */
xdc_Bool ti_sdo_xdcruntime_linux_SemProcessSupport_post__E( ti_sdo_xdcruntime_linux_SemProcessSupport_Handle __inst, xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_SemProcessSupport_post__F((void*)__inst, eb);
}

/* Module_startup */
xdc_Int ti_sdo_xdcruntime_linux_SemProcessSupport_Module_startup__E( xdc_Int state )
{
    return ti_sdo_xdcruntime_linux_SemProcessSupport_Module_startup__F(state);
}


/*
 * ======== ti.sdo.xdcruntime.linux.SemThreadSupport FUNCTION STUBS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_xdcruntime_linux_SemThreadSupport_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_xdcruntime_linux_SemThreadSupport_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_xdcruntime_linux_SemThreadSupport_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_xdcruntime_linux_SemThreadSupport_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_xdcruntime_linux_SemThreadSupport_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_xdcruntime_linux_SemThreadSupport_Module_GateProxy_query

/* entry/exit Log events */
#define ti_sdo_xdcruntime_linux_SemThreadSupport_pend__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_SemThreadSupport_pend__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_SemThreadSupport_post__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_SemThreadSupport_post__EXIT_EVT 0x0

/* pend__E */
xdc_Int ti_sdo_xdcruntime_linux_SemThreadSupport_pend__E( ti_sdo_xdcruntime_linux_SemThreadSupport_Handle __inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_SemThreadSupport_pend__F((void*)__inst, timeout, eb);
}

/* post__E */
xdc_Bool ti_sdo_xdcruntime_linux_SemThreadSupport_post__E( ti_sdo_xdcruntime_linux_SemThreadSupport_Handle __inst, xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_SemThreadSupport_post__F((void*)__inst, eb);
}

/* Module_startup */
xdc_Int ti_sdo_xdcruntime_linux_SemThreadSupport_Module_startup__E( xdc_Int state )
{
    return ti_sdo_xdcruntime_linux_SemThreadSupport_Module_startup__F(state);
}


/*
 * ======== ti.sdo.xdcruntime.linux.ThreadSupport FUNCTION STUBS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_xdcruntime_linux_ThreadSupport_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_xdcruntime_linux_ThreadSupport_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_xdcruntime_linux_ThreadSupport_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_xdcruntime_linux_ThreadSupport_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_xdcruntime_linux_ThreadSupport_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_xdcruntime_linux_ThreadSupport_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_xdcruntime_linux_ThreadSupport_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_xdcruntime_linux_ThreadSupport_Module_GateProxy_query

/* entry/exit Log events */
#define ti_sdo_xdcruntime_linux_ThreadSupport_self__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_self__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_start__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_start__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_yield__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_yield__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_compareOsPriorities__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_compareOsPriorities__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_sleep__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_sleep__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_join__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_join__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_getPriority__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_getPriority__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_setPriority__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_setPriority__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_getOsPriority__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_getOsPriority__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_setOsPriority__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_setOsPriority__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_getOsHandle__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_getOsHandle__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_getTls__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_getTls__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_setTls__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_setTls__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_stat__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_ThreadSupport_stat__EXIT_EVT 0x0

/* self__E */
xdc_runtime_knl_IThreadSupport_Handle ti_sdo_xdcruntime_linux_ThreadSupport_self__E( xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_self__F(eb);
}

/* start__E */
xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_start__E( xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_start__F(eb);
}

/* yield__E */
xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_yield__E( xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_yield__F(eb);
}

/* compareOsPriorities__E */
xdc_Int ti_sdo_xdcruntime_linux_ThreadSupport_compareOsPriorities__E( xdc_Int p1, xdc_Int p2, xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_compareOsPriorities__F(p1, p2, eb);
}

/* sleep__E */
xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_sleep__E( xdc_UInt timeout, xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_sleep__F(timeout, eb);
}

/* join__E */
xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_join__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle __inst, xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_join__F((void*)__inst, eb);
}

/* getPriority__E */
xdc_runtime_knl_IThreadSupport_Priority ti_sdo_xdcruntime_linux_ThreadSupport_getPriority__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle __inst, xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_getPriority__F((void*)__inst, eb);
}

/* setPriority__E */
xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_setPriority__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle __inst, xdc_runtime_knl_IThreadSupport_Priority newPri, xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_setPriority__F((void*)__inst, newPri, eb);
}

/* getOsPriority__E */
xdc_Int ti_sdo_xdcruntime_linux_ThreadSupport_getOsPriority__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle __inst, xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_getOsPriority__F((void*)__inst, eb);
}

/* setOsPriority__E */
xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_setOsPriority__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle __inst, xdc_Int newPri, xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_setOsPriority__F((void*)__inst, newPri, eb);
}

/* getOsHandle__E */
xdc_Ptr ti_sdo_xdcruntime_linux_ThreadSupport_getOsHandle__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle __inst ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_getOsHandle__F((void*)__inst);
}

/* getTls__E */
xdc_Ptr ti_sdo_xdcruntime_linux_ThreadSupport_getTls__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle __inst ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_getTls__F((void*)__inst);
}

/* setTls__E */
xdc_Void ti_sdo_xdcruntime_linux_ThreadSupport_setTls__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle __inst, xdc_Ptr tls ) 
{
    ti_sdo_xdcruntime_linux_ThreadSupport_setTls__F((void*)__inst, tls);
}

/* stat__E */
xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_stat__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle __inst, xdc_runtime_knl_IThreadSupport_Stat* buf, xdc_runtime_Error_Block* eb ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_stat__F((void*)__inst, buf, eb);
}

/* Module_startup */
xdc_Int ti_sdo_xdcruntime_linux_ThreadSupport_Module_startup__E( xdc_Int state )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_Module_startup__F(state);
}


/*
 * ======== ti.sdo.xdcruntime.linux.TimestampPosix FUNCTION STUBS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_xdcruntime_linux_TimestampPosix_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_xdcruntime_linux_TimestampPosix_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_xdcruntime_linux_TimestampPosix_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_xdcruntime_linux_TimestampPosix_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_xdcruntime_linux_TimestampPosix_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_xdcruntime_linux_TimestampPosix_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_xdcruntime_linux_TimestampPosix_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_xdcruntime_linux_TimestampPosix_Module_GateProxy_query

/* entry/exit Log events */
#define ti_sdo_xdcruntime_linux_TimestampPosix_get32__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_TimestampPosix_get32__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_TimestampPosix_get64__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_TimestampPosix_get64__EXIT_EVT 0x0
#define ti_sdo_xdcruntime_linux_TimestampPosix_getFreq__ENTRY_EVT 0x0
#define ti_sdo_xdcruntime_linux_TimestampPosix_getFreq__EXIT_EVT 0x0

/* get32__E */
xdc_Bits32 ti_sdo_xdcruntime_linux_TimestampPosix_get32__E( void ) 
{
    return ti_sdo_xdcruntime_linux_TimestampPosix_get32__F();
}

/* get64__E */
xdc_Void ti_sdo_xdcruntime_linux_TimestampPosix_get64__E( xdc_runtime_Types_Timestamp64* result ) 
{
    ti_sdo_xdcruntime_linux_TimestampPosix_get64__F(result);
}

/* getFreq__E */
xdc_Void ti_sdo_xdcruntime_linux_TimestampPosix_getFreq__E( xdc_runtime_Types_FreqHz* freq ) 
{
    ti_sdo_xdcruntime_linux_TimestampPosix_getFreq__F(freq);
}


/*
 * ======== xdc.runtime.Diags FUNCTION STUBS ========
 */

/* setMask__E */
xdc_Void xdc_runtime_Diags_setMask__E( xdc_String control ) 
{
    xdc_runtime_Diags_setMask__F(control);
}


/*
 * ======== xdc.runtime.Error FUNCTION STUBS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_Error_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_Error_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_Error_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_Error_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_Error_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_Error_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_Error_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_Error_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_Error_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_Error_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_Error_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_Error_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_Error_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_Error_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_Error_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_Error_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_Error_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_Error_Module_GateProxy_query

/* entry/exit Log events */
#define xdc_runtime_Error_check__ENTRY_EVT 0x0
#define xdc_runtime_Error_check__EXIT_EVT 0x0
#define xdc_runtime_Error_getData__ENTRY_EVT 0x0
#define xdc_runtime_Error_getData__EXIT_EVT 0x0
#define xdc_runtime_Error_getCode__ENTRY_EVT 0x0
#define xdc_runtime_Error_getCode__EXIT_EVT 0x0
#define xdc_runtime_Error_getId__ENTRY_EVT 0x0
#define xdc_runtime_Error_getId__EXIT_EVT 0x0
#define xdc_runtime_Error_getMsg__ENTRY_EVT 0x0
#define xdc_runtime_Error_getMsg__EXIT_EVT 0x0
#define xdc_runtime_Error_getSite__ENTRY_EVT 0x0
#define xdc_runtime_Error_getSite__EXIT_EVT 0x0
#define xdc_runtime_Error_init__ENTRY_EVT 0x0
#define xdc_runtime_Error_init__EXIT_EVT 0x0
#define xdc_runtime_Error_print__ENTRY_EVT 0x0
#define xdc_runtime_Error_print__EXIT_EVT 0x0
#define xdc_runtime_Error_raiseX__ENTRY_EVT 0x0
#define xdc_runtime_Error_raiseX__EXIT_EVT 0x0

/* check__E */
xdc_Bool xdc_runtime_Error_check__E( xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_Error_check__F(eb);
}

/* getData__E */
xdc_runtime_Error_Data* xdc_runtime_Error_getData__E( xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_Error_getData__F(eb);
}

/* getCode__E */
xdc_UInt16 xdc_runtime_Error_getCode__E( xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_Error_getCode__F(eb);
}

/* getId__E */
xdc_runtime_Error_Id xdc_runtime_Error_getId__E( xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_Error_getId__F(eb);
}

/* getMsg__E */
xdc_String xdc_runtime_Error_getMsg__E( xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_Error_getMsg__F(eb);
}

/* getSite__E */
xdc_runtime_Types_Site* xdc_runtime_Error_getSite__E( xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_Error_getSite__F(eb);
}

/* init__E */
xdc_Void xdc_runtime_Error_init__E( xdc_runtime_Error_Block* eb ) 
{
    xdc_runtime_Error_init__F(eb);
}

/* print__E */
xdc_Void xdc_runtime_Error_print__E( xdc_runtime_Error_Block* eb ) 
{
    xdc_runtime_Error_print__F(eb);
}

/* raiseX__E */
xdc_Void xdc_runtime_Error_raiseX__E( xdc_runtime_Error_Block* eb, xdc_runtime_Types_ModuleId mod, xdc_String file, xdc_Int line, xdc_runtime_Error_Id id, xdc_IArg arg1, xdc_IArg arg2 ) 
{
    xdc_runtime_Error_raiseX__F(eb, mod, file, line, id, arg1, arg2);
}


/*
 * ======== xdc.runtime.Gate FUNCTION STUBS ========
 */

/* enterSystem__E */
xdc_IArg xdc_runtime_Gate_enterSystem__E( void ) 
{
    return xdc_runtime_Gate_enterSystem__F();
}

/* leaveSystem__E */
xdc_Void xdc_runtime_Gate_leaveSystem__E( xdc_IArg key ) 
{
    xdc_runtime_Gate_leaveSystem__F(key);
}


/*
 * ======== xdc.runtime.HeapStd FUNCTION STUBS ========
 */

/* free__E */
xdc_Void xdc_runtime_HeapStd_free__E( xdc_runtime_HeapStd_Handle __inst, xdc_Ptr block, xdc_SizeT size ) 
{
    xdc_runtime_HeapStd_free__F((void*)__inst, block, size);
}

/* getStats__E */
xdc_Void xdc_runtime_HeapStd_getStats__E( xdc_runtime_HeapStd_Handle __inst, xdc_runtime_Memory_Stats* stats ) 
{
    xdc_runtime_HeapStd_getStats__F((void*)__inst, stats);
}

/* alloc__E */
xdc_Ptr xdc_runtime_HeapStd_alloc__E( xdc_runtime_HeapStd_Handle __inst, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_HeapStd_alloc__F((void*)__inst, size, align, eb);
}

/* isBlocking__E */
xdc_Bool xdc_runtime_HeapStd_isBlocking__E( xdc_runtime_HeapStd_Handle __inst ) 
{
    return xdc_runtime_HeapStd_isBlocking__F((void*)__inst);
}


/*
 * ======== xdc.runtime.Log FUNCTION STUBS ========
 */

/* doPrint__E */
xdc_Void xdc_runtime_Log_doPrint__E( xdc_runtime_Log_EventRec* evRec ) 
{
    xdc_runtime_Log_doPrint__F(evRec);
}


/*
 * ======== xdc.runtime.Memory FUNCTION STUBS ========
 */

/* alloc__E */
xdc_Ptr xdc_runtime_Memory_alloc__E( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_Memory_alloc__F(heap, size, align, eb);
}

/* calloc__E */
xdc_Ptr xdc_runtime_Memory_calloc__E( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_Memory_calloc__F(heap, size, align, eb);
}

/* free__E */
xdc_Void xdc_runtime_Memory_free__E( xdc_runtime_IHeap_Handle heap, xdc_Ptr block, xdc_SizeT size ) 
{
    xdc_runtime_Memory_free__F(heap, block, size);
}

/* getStats__E */
xdc_Void xdc_runtime_Memory_getStats__E( xdc_runtime_IHeap_Handle heap, xdc_runtime_Memory_Stats* stats ) 
{
    xdc_runtime_Memory_getStats__F(heap, stats);
}

/* query__E */
xdc_Bool xdc_runtime_Memory_query__E( xdc_runtime_IHeap_Handle heap, xdc_Int qual ) 
{
    return xdc_runtime_Memory_query__F(heap, qual);
}

/* getMaxDefaultTypeAlign__E */
xdc_SizeT xdc_runtime_Memory_getMaxDefaultTypeAlign__E( void ) 
{
    return xdc_runtime_Memory_getMaxDefaultTypeAlign__F();
}

/* valloc__E */
xdc_Ptr xdc_runtime_Memory_valloc__E( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_Char value, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_Memory_valloc__F(heap, size, align, value, eb);
}


/*
 * ======== xdc.runtime.Registry FUNCTION STUBS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_Registry_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_Registry_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_Registry_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_Registry_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_Registry_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_Registry_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_Registry_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_Registry_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_Registry_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_Registry_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_Registry_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_Registry_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_Registry_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_Registry_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_Registry_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_Registry_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_Registry_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_Registry_Module_GateProxy_query

/* entry/exit Log events */
#define xdc_runtime_Registry_addModule__ENTRY_EVT 0x44d0001
#define xdc_runtime_Registry_addModule__EXIT_EVT 0x4670002
#define xdc_runtime_Registry_findByName__ENTRY_EVT 0x4790001
#define xdc_runtime_Registry_findByName__EXIT_EVT 0x4900002
#define xdc_runtime_Registry_findByNamePattern__ENTRY_EVT 0x4a30001
#define xdc_runtime_Registry_findByNamePattern__EXIT_EVT 0x4c90002
#define xdc_runtime_Registry_findById__ENTRY_EVT 0x4e30001
#define xdc_runtime_Registry_findById__EXIT_EVT 0x4f60002
#define xdc_runtime_Registry_getMask__ENTRY_EVT 0x5070001
#define xdc_runtime_Registry_getMask__EXIT_EVT 0x51f0002
#define xdc_runtime_Registry_isMember__ENTRY_EVT 0x52f0001
#define xdc_runtime_Registry_isMember__EXIT_EVT 0x5420002
#define xdc_runtime_Registry_getNextModule__ENTRY_EVT 0x5530001
#define xdc_runtime_Registry_getNextModule__EXIT_EVT 0x56b0002
#define xdc_runtime_Registry_getModuleName__ENTRY_EVT 0x5810001
#define xdc_runtime_Registry_getModuleName__EXIT_EVT 0x5990002
#define xdc_runtime_Registry_getModuleId__ENTRY_EVT 0x5b10001
#define xdc_runtime_Registry_getModuleId__EXIT_EVT 0x5c70002

/* addModule__E */
xdc_runtime_Registry_Result xdc_runtime_Registry_addModule__E( xdc_runtime_Registry_Desc* desc, xdc_String modName ) 
{
    xdc_runtime_Registry_Result __ret;

    xdc_runtime_Log_write2(xdc_runtime_Registry_addModule__ENTRY_EVT, (xdc_IArg)desc, (xdc_IArg)modName);
    __ret = xdc_runtime_Registry_addModule__F(desc, modName);
    xdc_runtime_Log_write1(xdc_runtime_Registry_addModule__EXIT_EVT, (xdc_IArg)__ret);

    return __ret;
}

/* findByName__E */
xdc_runtime_Registry_Desc* xdc_runtime_Registry_findByName__E( xdc_String modName ) 
{
    xdc_runtime_Registry_Desc* __ret;

    xdc_runtime_Log_write1(xdc_runtime_Registry_findByName__ENTRY_EVT, (xdc_IArg)modName);
    __ret = xdc_runtime_Registry_findByName__F(modName);
    xdc_runtime_Log_write1(xdc_runtime_Registry_findByName__EXIT_EVT, (xdc_IArg)__ret);

    return __ret;
}

/* findByNamePattern__E */
xdc_runtime_Registry_Desc* xdc_runtime_Registry_findByNamePattern__E( xdc_String namePat, xdc_Int len, xdc_runtime_Registry_Desc* prev ) 
{
    xdc_runtime_Registry_Desc* __ret;

    xdc_runtime_Log_write3(xdc_runtime_Registry_findByNamePattern__ENTRY_EVT, (xdc_IArg)namePat, (xdc_IArg)len, (xdc_IArg)prev);
    __ret = xdc_runtime_Registry_findByNamePattern__F(namePat, len, prev);
    xdc_runtime_Log_write1(xdc_runtime_Registry_findByNamePattern__EXIT_EVT, (xdc_IArg)__ret);

    return __ret;
}

/* findById__E */
xdc_runtime_Registry_Desc* xdc_runtime_Registry_findById__E( xdc_runtime_Types_ModuleId mid ) 
{
    xdc_runtime_Registry_Desc* __ret;

    xdc_runtime_Log_write1(xdc_runtime_Registry_findById__ENTRY_EVT, (xdc_IArg)mid);
    __ret = xdc_runtime_Registry_findById__F(mid);
    xdc_runtime_Log_write1(xdc_runtime_Registry_findById__EXIT_EVT, (xdc_IArg)__ret);

    return __ret;
}

/* getMask__E */
xdc_Bool xdc_runtime_Registry_getMask__E( xdc_String name, xdc_runtime_Types_DiagsMask* mask ) 
{
    xdc_Bool __ret;

    xdc_runtime_Log_write2(xdc_runtime_Registry_getMask__ENTRY_EVT, (xdc_IArg)name, (xdc_IArg)mask);
    __ret = xdc_runtime_Registry_getMask__F(name, mask);
    xdc_runtime_Log_write1(xdc_runtime_Registry_getMask__EXIT_EVT, (xdc_IArg)__ret);

    return __ret;
}

/* isMember__E */
xdc_Bool xdc_runtime_Registry_isMember__E( xdc_runtime_Types_ModuleId mid ) 
{
    xdc_Bool __ret;

    xdc_runtime_Log_write1(xdc_runtime_Registry_isMember__ENTRY_EVT, (xdc_IArg)mid);
    __ret = xdc_runtime_Registry_isMember__F(mid);
    xdc_runtime_Log_write1(xdc_runtime_Registry_isMember__EXIT_EVT, (xdc_IArg)__ret);

    return __ret;
}

/* getNextModule__E */
xdc_runtime_Registry_Desc* xdc_runtime_Registry_getNextModule__E( xdc_runtime_Registry_Desc* desc ) 
{
    xdc_runtime_Registry_Desc* __ret;

    xdc_runtime_Log_write1(xdc_runtime_Registry_getNextModule__ENTRY_EVT, (xdc_IArg)desc);
    __ret = xdc_runtime_Registry_getNextModule__F(desc);
    xdc_runtime_Log_write1(xdc_runtime_Registry_getNextModule__EXIT_EVT, (xdc_IArg)__ret);

    return __ret;
}

/* getModuleName__E */
xdc_String xdc_runtime_Registry_getModuleName__E( xdc_runtime_Registry_Desc* desc ) 
{
    xdc_String __ret;

    xdc_runtime_Log_write1(xdc_runtime_Registry_getModuleName__ENTRY_EVT, (xdc_IArg)desc);
    __ret = xdc_runtime_Registry_getModuleName__F(desc);
    xdc_runtime_Log_write1(xdc_runtime_Registry_getModuleName__EXIT_EVT, (xdc_IArg)__ret);

    return __ret;
}

/* getModuleId__E */
xdc_runtime_Types_ModuleId xdc_runtime_Registry_getModuleId__E( xdc_runtime_Registry_Desc* desc ) 
{
    xdc_runtime_Types_ModuleId __ret;

    xdc_runtime_Log_write1(xdc_runtime_Registry_getModuleId__ENTRY_EVT, (xdc_IArg)desc);
    __ret = xdc_runtime_Registry_getModuleId__F(desc);
    xdc_runtime_Log_write1(xdc_runtime_Registry_getModuleId__EXIT_EVT, (xdc_IArg)__ret);

    return __ret;
}


/*
 * ======== xdc.runtime.Startup FUNCTION STUBS ========
 */

/* exec__E */
xdc_Void xdc_runtime_Startup_exec__E( void ) 
{
    xdc_runtime_Startup_exec__F();
}

/* rtsDone__E */
xdc_Bool xdc_runtime_Startup_rtsDone__E( void ) 
{
    return xdc_runtime_Startup_rtsDone__F();
}


/*
 * ======== xdc.runtime.SysStd FUNCTION STUBS ========
 */

/* abort__E */
xdc_Void xdc_runtime_SysStd_abort__E( xdc_String str ) 
{
    xdc_runtime_SysStd_abort__F(str);
}

/* exit__E */
xdc_Void xdc_runtime_SysStd_exit__E( xdc_Int stat ) 
{
    xdc_runtime_SysStd_exit__F(stat);
}

/* flush__E */
xdc_Void xdc_runtime_SysStd_flush__E( void ) 
{
    xdc_runtime_SysStd_flush__F();
}

/* putch__E */
xdc_Void xdc_runtime_SysStd_putch__E( xdc_Char ch ) 
{
    xdc_runtime_SysStd_putch__F(ch);
}

/* ready__E */
xdc_Bool xdc_runtime_SysStd_ready__E( void ) 
{
    return xdc_runtime_SysStd_ready__F();
}


/*
 * ======== xdc.runtime.System FUNCTION STUBS ========
 */

/* abort__E */
xdc_Void xdc_runtime_System_abort__E( xdc_String str ) 
{
    xdc_runtime_System_abort__F(str);
}

/* atexit__E */
xdc_Bool xdc_runtime_System_atexit__E( xdc_runtime_System_AtexitHandler handler ) 
{
    return xdc_runtime_System_atexit__F(handler);
}

/* exit__E */
xdc_Void xdc_runtime_System_exit__E( xdc_Int stat ) 
{
    xdc_runtime_System_exit__F(stat);
}

/* putch__E */
xdc_Void xdc_runtime_System_putch__E( xdc_Char ch ) 
{
    xdc_runtime_System_putch__F(ch);
}

/* flush__E */
xdc_Void xdc_runtime_System_flush__E( void ) 
{
    xdc_runtime_System_flush__F();
}

/* printf_va__E */
xdc_Int xdc_runtime_System_printf_va__E( xdc_String fmt, va_list __va ) 
{
    return xdc_runtime_System_printf_va__F(fmt, __va);
}

/* printf__E */
xdc_Int xdc_runtime_System_printf__E( xdc_String fmt, ... ) 
{
    xdc_Int __ret;

    va_list __va; va_start(__va, fmt);
    __ret = xdc_runtime_System_printf_va__F(fmt, __va);

    va_end(__va);
    return __ret;
}

/* aprintf_va__E */
xdc_Int xdc_runtime_System_aprintf_va__E( xdc_String fmt, va_list __va ) 
{
    return xdc_runtime_System_aprintf_va__F(fmt, __va);
}

/* aprintf__E */
xdc_Int xdc_runtime_System_aprintf__E( xdc_String fmt, ... ) 
{
    xdc_Int __ret;

    va_list __va; va_start(__va, fmt);
    __ret = xdc_runtime_System_aprintf_va__F(fmt, __va);

    va_end(__va);
    return __ret;
}

/* sprintf_va__E */
xdc_Int xdc_runtime_System_sprintf_va__E( xdc_Char buf[], xdc_String fmt, va_list __va ) 
{
    return xdc_runtime_System_sprintf_va__F(buf, fmt, __va);
}

/* sprintf__E */
xdc_Int xdc_runtime_System_sprintf__E( xdc_Char buf[], xdc_String fmt, ... ) 
{
    xdc_Int __ret;

    va_list __va; va_start(__va, fmt);
    __ret = xdc_runtime_System_sprintf_va__F(buf, fmt, __va);

    va_end(__va);
    return __ret;
}

/* asprintf_va__E */
xdc_Int xdc_runtime_System_asprintf_va__E( xdc_Char buf[], xdc_String fmt, va_list __va ) 
{
    return xdc_runtime_System_asprintf_va__F(buf, fmt, __va);
}

/* asprintf__E */
xdc_Int xdc_runtime_System_asprintf__E( xdc_Char buf[], xdc_String fmt, ... ) 
{
    xdc_Int __ret;

    va_list __va; va_start(__va, fmt);
    __ret = xdc_runtime_System_asprintf_va__F(buf, fmt, __va);

    va_end(__va);
    return __ret;
}

/* vprintf__E */
xdc_Int xdc_runtime_System_vprintf__E( xdc_String fmt, xdc_VaList va ) 
{
    return xdc_runtime_System_vprintf__F(fmt, va);
}

/* avprintf__E */
xdc_Int xdc_runtime_System_avprintf__E( xdc_String fmt, xdc_VaList va ) 
{
    return xdc_runtime_System_avprintf__F(fmt, va);
}

/* vsprintf__E */
xdc_Int xdc_runtime_System_vsprintf__E( xdc_Char buf[], xdc_String fmt, xdc_VaList va ) 
{
    return xdc_runtime_System_vsprintf__F(buf, fmt, va);
}

/* avsprintf__E */
xdc_Int xdc_runtime_System_avsprintf__E( xdc_Char buf[], xdc_String fmt, xdc_VaList va ) 
{
    return xdc_runtime_System_avsprintf__F(buf, fmt, va);
}

/* Module_startup */
xdc_Int xdc_runtime_System_Module_startup__E( xdc_Int state )
{
    return xdc_runtime_System_Module_startup__F(state);
}


/*
 * ======== xdc.runtime.Text FUNCTION STUBS ========
 */

/* cordText__E */
xdc_String xdc_runtime_Text_cordText__E( xdc_runtime_Text_CordAddr cord ) 
{
    return xdc_runtime_Text_cordText__F(cord);
}

/* ropeText__E */
xdc_String xdc_runtime_Text_ropeText__E( xdc_runtime_Text_RopeId rope ) 
{
    return xdc_runtime_Text_ropeText__F(rope);
}

/* matchRope__E */
xdc_Int xdc_runtime_Text_matchRope__E( xdc_runtime_Text_RopeId rope, xdc_String pat, xdc_Int* lenp ) 
{
    return xdc_runtime_Text_matchRope__F(rope, pat, lenp);
}

/* putLab__E */
xdc_Int xdc_runtime_Text_putLab__E( xdc_runtime_Types_Label* lab, xdc_Char** bufp, xdc_Int len ) 
{
    return xdc_runtime_Text_putLab__F(lab, bufp, len);
}

/* putMod__E */
xdc_Int xdc_runtime_Text_putMod__E( xdc_runtime_Types_ModuleId mid, xdc_Char** bufp, xdc_Int len ) 
{
    return xdc_runtime_Text_putMod__F(mid, bufp, len);
}

/* putSite__E */
xdc_Int xdc_runtime_Text_putSite__E( xdc_runtime_Types_Site* site, xdc_Char** bufp, xdc_Int len ) 
{
    return xdc_runtime_Text_putSite__F(site, bufp, len);
}


/*
 * ======== xdc.runtime.Timestamp FUNCTION STUBS ========
 */

/* get32__E */
xdc_Bits32 xdc_runtime_Timestamp_get32__E( void ) 
{
    return xdc_runtime_Timestamp_get32__F();
}

/* get64__E */
xdc_Void xdc_runtime_Timestamp_get64__E( xdc_runtime_Types_Timestamp64* result ) 
{
    xdc_runtime_Timestamp_get64__F(result);
}

/* getFreq__E */
xdc_Void xdc_runtime_Timestamp_getFreq__E( xdc_runtime_Types_FreqHz* freq ) 
{
    xdc_runtime_Timestamp_getFreq__F(freq);
}


/*
 * ======== xdc.runtime.knl.GateThread FUNCTION STUBS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_knl_GateThread_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_knl_GateThread_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_knl_GateThread_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_knl_GateThread_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_knl_GateThread_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_knl_GateThread_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_knl_GateThread_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_knl_GateThread_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_knl_GateThread_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_knl_GateThread_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_knl_GateThread_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_knl_GateThread_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_knl_GateThread_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_knl_GateThread_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_knl_GateThread_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_knl_GateThread_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_knl_GateThread_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_knl_GateThread_Module_GateProxy_query

/* entry/exit Log events */
#define xdc_runtime_knl_GateThread_query__ENTRY_EVT 0x0
#define xdc_runtime_knl_GateThread_query__EXIT_EVT 0x0
#define xdc_runtime_knl_GateThread_enter__ENTRY_EVT 0x0
#define xdc_runtime_knl_GateThread_enter__EXIT_EVT 0x0
#define xdc_runtime_knl_GateThread_leave__ENTRY_EVT 0x0
#define xdc_runtime_knl_GateThread_leave__EXIT_EVT 0x0

/* query__E */
xdc_Bool xdc_runtime_knl_GateThread_query__E( xdc_Int qual ) 
{
    return xdc_runtime_knl_GateThread_query__F(qual);
}

/* enter__E */
xdc_IArg xdc_runtime_knl_GateThread_enter__E( xdc_runtime_knl_GateThread_Handle __inst ) 
{
    return xdc_runtime_knl_GateThread_enter__F((void*)__inst);
}

/* leave__E */
xdc_Void xdc_runtime_knl_GateThread_leave__E( xdc_runtime_knl_GateThread_Handle __inst, xdc_IArg key ) 
{
    xdc_runtime_knl_GateThread_leave__F((void*)__inst, key);
}


/*
 * ======== xdc.runtime.knl.SemProcess FUNCTION STUBS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_knl_SemProcess_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_knl_SemProcess_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_knl_SemProcess_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_knl_SemProcess_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_knl_SemProcess_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_knl_SemProcess_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_knl_SemProcess_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_knl_SemProcess_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_knl_SemProcess_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_knl_SemProcess_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_knl_SemProcess_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_knl_SemProcess_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_knl_SemProcess_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_knl_SemProcess_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_knl_SemProcess_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_knl_SemProcess_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_knl_SemProcess_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_knl_SemProcess_Module_GateProxy_query

/* entry/exit Log events */
#define xdc_runtime_knl_SemProcess_pend__ENTRY_EVT 0x0
#define xdc_runtime_knl_SemProcess_pend__EXIT_EVT 0x0
#define xdc_runtime_knl_SemProcess_post__ENTRY_EVT 0x0
#define xdc_runtime_knl_SemProcess_post__EXIT_EVT 0x0

/* pend__E */
xdc_Int xdc_runtime_knl_SemProcess_pend__E( xdc_runtime_knl_SemProcess_Handle __inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_SemProcess_pend__F((void*)__inst, timeout, eb);
}

/* post__E */
xdc_Bool xdc_runtime_knl_SemProcess_post__E( xdc_runtime_knl_SemProcess_Handle __inst, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_SemProcess_post__F((void*)__inst, eb);
}


/*
 * ======== xdc.runtime.knl.SemThread FUNCTION STUBS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_knl_SemThread_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_knl_SemThread_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_knl_SemThread_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_knl_SemThread_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_knl_SemThread_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_knl_SemThread_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_knl_SemThread_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_knl_SemThread_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_knl_SemThread_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_knl_SemThread_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_knl_SemThread_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_knl_SemThread_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_knl_SemThread_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_knl_SemThread_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_knl_SemThread_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_knl_SemThread_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_knl_SemThread_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_knl_SemThread_Module_GateProxy_query

/* entry/exit Log events */
#define xdc_runtime_knl_SemThread_pend__ENTRY_EVT 0x0
#define xdc_runtime_knl_SemThread_pend__EXIT_EVT 0x0
#define xdc_runtime_knl_SemThread_post__ENTRY_EVT 0x0
#define xdc_runtime_knl_SemThread_post__EXIT_EVT 0x0

/* pend__E */
xdc_Int xdc_runtime_knl_SemThread_pend__E( xdc_runtime_knl_SemThread_Handle __inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_SemThread_pend__F((void*)__inst, timeout, eb);
}

/* post__E */
xdc_Bool xdc_runtime_knl_SemThread_post__E( xdc_runtime_knl_SemThread_Handle __inst, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_SemThread_post__F((void*)__inst, eb);
}


/*
 * ======== xdc.runtime.knl.Thread FUNCTION STUBS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_knl_Thread_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_knl_Thread_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_knl_Thread_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_knl_Thread_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_knl_Thread_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_knl_Thread_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_knl_Thread_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_knl_Thread_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_knl_Thread_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_knl_Thread_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_knl_Thread_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_knl_Thread_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_knl_Thread_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_knl_Thread_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_knl_Thread_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_knl_Thread_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_knl_Thread_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_knl_Thread_Module_GateProxy_query

/* entry/exit Log events */
#define xdc_runtime_knl_Thread_start__ENTRY_EVT 0x0
#define xdc_runtime_knl_Thread_start__EXIT_EVT 0x0
#define xdc_runtime_knl_Thread_yield__ENTRY_EVT 0x0
#define xdc_runtime_knl_Thread_yield__EXIT_EVT 0x0
#define xdc_runtime_knl_Thread_compareOsPriorities__ENTRY_EVT 0x0
#define xdc_runtime_knl_Thread_compareOsPriorities__EXIT_EVT 0x0
#define xdc_runtime_knl_Thread_sleep__ENTRY_EVT 0x0
#define xdc_runtime_knl_Thread_sleep__EXIT_EVT 0x0
#define xdc_runtime_knl_Thread_join__ENTRY_EVT 0x0
#define xdc_runtime_knl_Thread_join__EXIT_EVT 0x0
#define xdc_runtime_knl_Thread_getPriority__ENTRY_EVT 0x0
#define xdc_runtime_knl_Thread_getPriority__EXIT_EVT 0x0
#define xdc_runtime_knl_Thread_setPriority__ENTRY_EVT 0x0
#define xdc_runtime_knl_Thread_setPriority__EXIT_EVT 0x0
#define xdc_runtime_knl_Thread_getOsPriority__ENTRY_EVT 0x0
#define xdc_runtime_knl_Thread_getOsPriority__EXIT_EVT 0x0
#define xdc_runtime_knl_Thread_setOsPriority__ENTRY_EVT 0x0
#define xdc_runtime_knl_Thread_setOsPriority__EXIT_EVT 0x0
#define xdc_runtime_knl_Thread_getOsHandle__ENTRY_EVT 0x0
#define xdc_runtime_knl_Thread_getOsHandle__EXIT_EVT 0x0
#define xdc_runtime_knl_Thread_getTls__ENTRY_EVT 0x0
#define xdc_runtime_knl_Thread_getTls__EXIT_EVT 0x0
#define xdc_runtime_knl_Thread_setTls__ENTRY_EVT 0x0
#define xdc_runtime_knl_Thread_setTls__EXIT_EVT 0x0
#define xdc_runtime_knl_Thread_stat__ENTRY_EVT 0x0
#define xdc_runtime_knl_Thread_stat__EXIT_EVT 0x0

/* start__E */
xdc_Bool xdc_runtime_knl_Thread_start__E( xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_Thread_start__F(eb);
}

/* yield__E */
xdc_Bool xdc_runtime_knl_Thread_yield__E( xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_Thread_yield__F(eb);
}

/* compareOsPriorities__E */
xdc_Int xdc_runtime_knl_Thread_compareOsPriorities__E( xdc_Int p1, xdc_Int p2, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_Thread_compareOsPriorities__F(p1, p2, eb);
}

/* sleep__E */
xdc_Bool xdc_runtime_knl_Thread_sleep__E( xdc_UInt timeout, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_Thread_sleep__F(timeout, eb);
}

/* join__E */
xdc_Bool xdc_runtime_knl_Thread_join__E( xdc_runtime_knl_Thread_Handle __inst, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_Thread_join__F((void*)__inst, eb);
}

/* getPriority__E */
xdc_runtime_knl_Thread_Priority xdc_runtime_knl_Thread_getPriority__E( xdc_runtime_knl_Thread_Handle __inst, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_Thread_getPriority__F((void*)__inst, eb);
}

/* setPriority__E */
xdc_Bool xdc_runtime_knl_Thread_setPriority__E( xdc_runtime_knl_Thread_Handle __inst, xdc_runtime_knl_Thread_Priority newPri, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_Thread_setPriority__F((void*)__inst, newPri, eb);
}

/* getOsPriority__E */
xdc_Int xdc_runtime_knl_Thread_getOsPriority__E( xdc_runtime_knl_Thread_Handle __inst, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_Thread_getOsPriority__F((void*)__inst, eb);
}

/* setOsPriority__E */
xdc_Bool xdc_runtime_knl_Thread_setOsPriority__E( xdc_runtime_knl_Thread_Handle __inst, xdc_Int newPri, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_Thread_setOsPriority__F((void*)__inst, newPri, eb);
}

/* getOsHandle__E */
xdc_Ptr xdc_runtime_knl_Thread_getOsHandle__E( xdc_runtime_knl_Thread_Handle __inst ) 
{
    return xdc_runtime_knl_Thread_getOsHandle__F((void*)__inst);
}

/* getTls__E */
xdc_Ptr xdc_runtime_knl_Thread_getTls__E( xdc_runtime_knl_Thread_Handle __inst ) 
{
    return xdc_runtime_knl_Thread_getTls__F((void*)__inst);
}

/* setTls__E */
xdc_Void xdc_runtime_knl_Thread_setTls__E( xdc_runtime_knl_Thread_Handle __inst, xdc_Ptr tls ) 
{
    xdc_runtime_knl_Thread_setTls__F((void*)__inst, tls);
}

/* stat__E */
xdc_Bool xdc_runtime_knl_Thread_stat__E( xdc_runtime_knl_Thread_Handle __inst, xdc_runtime_knl_Thread_Stat* buf, xdc_runtime_Error_Block* eb ) 
{
    return xdc_runtime_knl_Thread_stat__F((void*)__inst, buf, eb);
}


/*
 * ======== ti.sdo.utils.loggers.LogMFP_Proxy PROXY BODY ========
 */

/* DELEGATES TO ti.sdo.utils.loggers.LoggerMFPNull */

/* Module__startupDone__S */
xdc_Bool ti_sdo_utils_loggers_LogMFP_Proxy_Module__startupDone__S( void ) 
{
    return ti_sdo_utils_loggers_LoggerMFPNull_Module__startupDone__S();
}

/* Object__create__S */
xdc_Ptr ti_sdo_utils_loggers_LogMFP_Proxy_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const ti_sdo_utils_loggers_LogMFP_Proxy___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    return ti_sdo_utils_loggers_LoggerMFPNull_Object__create__S(oa, osz, aa, (ti_sdo_utils_loggers_LoggerMFPNull___ParamsPtr)pa, sizeof(ti_sdo_utils_loggers_ILoggerMFP_Params), eb);
}

/* Object__delete__S */
void ti_sdo_utils_loggers_LogMFP_Proxy_Object__delete__S( Ptr instp ) 
{
    ti_sdo_utils_loggers_LoggerMFPNull_Object__delete__S(instp);
}

/* Params__init__S */
void ti_sdo_utils_loggers_LogMFP_Proxy_Params__init__S( xdc_Ptr dst, const xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz )
{
    ti_sdo_utils_loggers_LoggerMFPNull_Params__init__S(dst, src, psz, isz);
}

/* Handle__label__S */
xdc_runtime_Types_Label* ti_sdo_utils_loggers_LogMFP_Proxy_Handle__label__S( Ptr obj, xdc_runtime_Types_Label* lab )
{
    return ti_sdo_utils_loggers_LoggerMFPNull_Handle__label__S(obj, lab);
}

/* enable__E */
xdc_Bool ti_sdo_utils_loggers_LogMFP_Proxy_enable__E( ti_sdo_utils_loggers_LogMFP_Proxy_Handle __inst )
{
    return ti_sdo_utils_loggers_LoggerMFPNull_enable((ti_sdo_utils_loggers_LoggerMFPNull_Handle)__inst);
}

/* disable__E */
xdc_Bool ti_sdo_utils_loggers_LogMFP_Proxy_disable__E( ti_sdo_utils_loggers_LogMFP_Proxy_Handle __inst )
{
    return ti_sdo_utils_loggers_LoggerMFPNull_disable((ti_sdo_utils_loggers_LoggerMFPNull_Handle)__inst);
}

/* write0__E */
xdc_Void ti_sdo_utils_loggers_LogMFP_Proxy_write0__E( ti_sdo_utils_loggers_LogMFP_Proxy_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid )
{
    ti_sdo_utils_loggers_LoggerMFPNull_write0((ti_sdo_utils_loggers_LoggerMFPNull_Handle)__inst, evt, mid);
}

/* write1__E */
xdc_Void ti_sdo_utils_loggers_LogMFP_Proxy_write1__E( ti_sdo_utils_loggers_LogMFP_Proxy_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1 )
{
    ti_sdo_utils_loggers_LoggerMFPNull_write1((ti_sdo_utils_loggers_LoggerMFPNull_Handle)__inst, evt, mid, a1);
}

/* write2__E */
xdc_Void ti_sdo_utils_loggers_LogMFP_Proxy_write2__E( ti_sdo_utils_loggers_LogMFP_Proxy_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2 )
{
    ti_sdo_utils_loggers_LoggerMFPNull_write2((ti_sdo_utils_loggers_LoggerMFPNull_Handle)__inst, evt, mid, a1, a2);
}

/* write4__E */
xdc_Void ti_sdo_utils_loggers_LogMFP_Proxy_write4__E( ti_sdo_utils_loggers_LogMFP_Proxy_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4 )
{
    ti_sdo_utils_loggers_LoggerMFPNull_write4((ti_sdo_utils_loggers_LoggerMFPNull_Handle)__inst, evt, mid, a1, a2, a3, a4);
}

/* write8__E */
xdc_Void ti_sdo_utils_loggers_LogMFP_Proxy_write8__E( ti_sdo_utils_loggers_LogMFP_Proxy_Handle __inst, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8 )
{
    ti_sdo_utils_loggers_LoggerMFPNull_write8((ti_sdo_utils_loggers_LoggerMFPNull_Handle)__inst, evt, mid, a1, a2, a3, a4, a5, a6, a7, a8);
}

/* control__E */
xdc_Void ti_sdo_utils_loggers_LogMFP_Proxy_control__E( xdc_Int cmd, xdc_UArg cmdArgs )
{
    ti_sdo_utils_loggers_LoggerMFPNull_control(cmd, cmdArgs);
}


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID_Module_GateProxy PROXY BODY ========
 */

/* DELEGATES TO xdc.runtime.knl.GateThread */

/* Module__startupDone__S */
xdc_Bool ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__startupDone__S( void ) 
{
    return xdc_runtime_knl_GateThread_Module__startupDone__S();
}

/* Object__create__S */
xdc_Ptr ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    return xdc_runtime_knl_GateThread_Object__create__S(oa, osz, aa, (xdc_runtime_knl_GateThread___ParamsPtr)pa, sizeof(xdc_runtime_IGateProvider_Params), eb);
}

/* Object__delete__S */
void ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Object__delete__S( Ptr instp ) 
{
    xdc_runtime_knl_GateThread_Object__delete__S(instp);
}

/* Params__init__S */
void ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Params__init__S( xdc_Ptr dst, const xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz )
{
    xdc_runtime_knl_GateThread_Params__init__S(dst, src, psz, isz);
}

/* Handle__label__S */
xdc_runtime_Types_Label* ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Handle__label__S( Ptr obj, xdc_runtime_Types_Label* lab )
{
    return xdc_runtime_knl_GateThread_Handle__label__S(obj, lab);
}

/* query__E */
xdc_Bool ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_query__E( xdc_Int qual )
{
    return xdc_runtime_knl_GateThread_query(qual);
}

/* enter__E */
xdc_IArg ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_enter__E( ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Handle __inst )
{
    return xdc_runtime_knl_GateThread_enter((xdc_runtime_knl_GateThread_Handle)__inst);
}

/* leave__E */
xdc_Void ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_leave__E( ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Handle __inst, xdc_IArg key )
{
    xdc_runtime_knl_GateThread_leave((xdc_runtime_knl_GateThread_Handle)__inst, key);
}


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID_TimestampProxy PROXY BODY ========
 */

/* DELEGATES TO ti.sdo.xdcruntime.linux.TimestampPosix */

/* Module__startupDone__S */
xdc_Bool ti_sdo_utils_loggers_LoggerSysTID_TimestampProxy_Module__startupDone__S( void ) 
{
    return ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDone__S();
}

/* get32__E */
xdc_Bits32 ti_sdo_utils_loggers_LoggerSysTID_TimestampProxy_get32__E( void )
{
    return ti_sdo_xdcruntime_linux_TimestampPosix_get32();
}

/* get64__E */
xdc_Void ti_sdo_utils_loggers_LoggerSysTID_TimestampProxy_get64__E( xdc_runtime_Types_Timestamp64* result )
{
    ti_sdo_xdcruntime_linux_TimestampPosix_get64(result);
}

/* getFreq__E */
xdc_Void ti_sdo_utils_loggers_LoggerSysTID_TimestampProxy_getFreq__E( xdc_runtime_Types_FreqHz* freq )
{
    ti_sdo_xdcruntime_linux_TimestampPosix_getFreq(freq);
}


/*
 * ======== xdc.runtime.Main_Module_GateProxy PROXY BODY ========
 */

/* DELEGATES TO ti.sdo.xdcruntime.linux.GateThreadSupport */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Main_Module_GateProxy_Module__startupDone__S( void ) 
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDone__S();
}

/* Object__create__S */
xdc_Ptr xdc_runtime_Main_Module_GateProxy_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const xdc_runtime_Main_Module_GateProxy___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_Object__create__S(oa, osz, aa, (ti_sdo_xdcruntime_linux_GateThreadSupport___ParamsPtr)pa, sizeof(xdc_runtime_IGateProvider_Params), eb);
}

/* Object__delete__S */
void xdc_runtime_Main_Module_GateProxy_Object__delete__S( Ptr instp ) 
{
    ti_sdo_xdcruntime_linux_GateThreadSupport_Object__delete__S(instp);
}

/* Params__init__S */
void xdc_runtime_Main_Module_GateProxy_Params__init__S( xdc_Ptr dst, const xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz )
{
    ti_sdo_xdcruntime_linux_GateThreadSupport_Params__init__S(dst, src, psz, isz);
}

/* Handle__label__S */
xdc_runtime_Types_Label* xdc_runtime_Main_Module_GateProxy_Handle__label__S( Ptr obj, xdc_runtime_Types_Label* lab )
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_Handle__label__S(obj, lab);
}

/* query__E */
xdc_Bool xdc_runtime_Main_Module_GateProxy_query__E( xdc_Int qual )
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_query(qual);
}

/* enter__E */
xdc_IArg xdc_runtime_Main_Module_GateProxy_enter__E( xdc_runtime_Main_Module_GateProxy_Handle __inst )
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_enter((ti_sdo_xdcruntime_linux_GateThreadSupport_Handle)__inst);
}

/* leave__E */
xdc_Void xdc_runtime_Main_Module_GateProxy_leave__E( xdc_runtime_Main_Module_GateProxy_Handle __inst, xdc_IArg key )
{
    ti_sdo_xdcruntime_linux_GateThreadSupport_leave((ti_sdo_xdcruntime_linux_GateThreadSupport_Handle)__inst, key);
}


/*
 * ======== xdc.runtime.Memory_HeapProxy PROXY BODY ========
 */

/* DELEGATES TO xdc.runtime.HeapStd */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Memory_HeapProxy_Module__startupDone__S( void ) 
{
    return xdc_runtime_HeapStd_Module__startupDone__S();
}

/* Object__create__S */
xdc_Ptr xdc_runtime_Memory_HeapProxy_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const xdc_runtime_Memory_HeapProxy___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    return xdc_runtime_HeapStd_Object__create__S(oa, osz, aa, (xdc_runtime_HeapStd___ParamsPtr)pa, sizeof(xdc_runtime_IHeap_Params), eb);
}

/* Object__delete__S */
void xdc_runtime_Memory_HeapProxy_Object__delete__S( Ptr instp ) 
{
    xdc_runtime_HeapStd_Object__delete__S(instp);
}

/* Params__init__S */
void xdc_runtime_Memory_HeapProxy_Params__init__S( xdc_Ptr dst, const xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz )
{
    xdc_runtime_HeapStd_Params__init__S(dst, src, psz, isz);
}

/* Handle__label__S */
xdc_runtime_Types_Label* xdc_runtime_Memory_HeapProxy_Handle__label__S( Ptr obj, xdc_runtime_Types_Label* lab )
{
    return xdc_runtime_HeapStd_Handle__label__S(obj, lab);
}

/* alloc__E */
xdc_Ptr xdc_runtime_Memory_HeapProxy_alloc__E( xdc_runtime_Memory_HeapProxy_Handle __inst, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb )
{
    return xdc_runtime_IHeap_alloc((xdc_runtime_IHeap_Handle)__inst, size, align, eb);
}

/* free__E */
xdc_Void xdc_runtime_Memory_HeapProxy_free__E( xdc_runtime_Memory_HeapProxy_Handle __inst, xdc_Ptr block, xdc_SizeT size )
{
    xdc_runtime_IHeap_free((xdc_runtime_IHeap_Handle)__inst, block, size);
}

/* isBlocking__E */
xdc_Bool xdc_runtime_Memory_HeapProxy_isBlocking__E( xdc_runtime_Memory_HeapProxy_Handle __inst )
{
    return xdc_runtime_IHeap_isBlocking((xdc_runtime_IHeap_Handle)__inst);
}

/* getStats__E */
xdc_Void xdc_runtime_Memory_HeapProxy_getStats__E( xdc_runtime_Memory_HeapProxy_Handle __inst, xdc_runtime_Memory_Stats* stats )
{
    xdc_runtime_IHeap_getStats((xdc_runtime_IHeap_Handle)__inst, stats);
}


/*
 * ======== xdc.runtime.System_Module_GateProxy PROXY BODY ========
 */

/* DELEGATES TO ti.sdo.xdcruntime.linux.GateThreadSupport */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_System_Module_GateProxy_Module__startupDone__S( void ) 
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDone__S();
}

/* Object__create__S */
xdc_Ptr xdc_runtime_System_Module_GateProxy_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const xdc_runtime_System_Module_GateProxy___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_Object__create__S(oa, osz, aa, (ti_sdo_xdcruntime_linux_GateThreadSupport___ParamsPtr)pa, sizeof(xdc_runtime_IGateProvider_Params), eb);
}

/* Object__delete__S */
void xdc_runtime_System_Module_GateProxy_Object__delete__S( Ptr instp ) 
{
    ti_sdo_xdcruntime_linux_GateThreadSupport_Object__delete__S(instp);
}

/* Params__init__S */
void xdc_runtime_System_Module_GateProxy_Params__init__S( xdc_Ptr dst, const xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz )
{
    ti_sdo_xdcruntime_linux_GateThreadSupport_Params__init__S(dst, src, psz, isz);
}

/* Handle__label__S */
xdc_runtime_Types_Label* xdc_runtime_System_Module_GateProxy_Handle__label__S( Ptr obj, xdc_runtime_Types_Label* lab )
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_Handle__label__S(obj, lab);
}

/* query__E */
xdc_Bool xdc_runtime_System_Module_GateProxy_query__E( xdc_Int qual )
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_query(qual);
}

/* enter__E */
xdc_IArg xdc_runtime_System_Module_GateProxy_enter__E( xdc_runtime_System_Module_GateProxy_Handle __inst )
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_enter((ti_sdo_xdcruntime_linux_GateThreadSupport_Handle)__inst);
}

/* leave__E */
xdc_Void xdc_runtime_System_Module_GateProxy_leave__E( xdc_runtime_System_Module_GateProxy_Handle __inst, xdc_IArg key )
{
    ti_sdo_xdcruntime_linux_GateThreadSupport_leave((ti_sdo_xdcruntime_linux_GateThreadSupport_Handle)__inst, key);
}


/*
 * ======== xdc.runtime.System_SupportProxy PROXY BODY ========
 */

/* DELEGATES TO xdc.runtime.SysStd */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_System_SupportProxy_Module__startupDone__S( void ) 
{
    return xdc_runtime_SysStd_Module__startupDone__S();
}

/* abort__E */
xdc_Void xdc_runtime_System_SupportProxy_abort__E( xdc_String str )
{
    xdc_runtime_SysStd_abort(str);
}

/* exit__E */
xdc_Void xdc_runtime_System_SupportProxy_exit__E( xdc_Int stat )
{
    xdc_runtime_SysStd_exit(stat);
}

/* flush__E */
xdc_Void xdc_runtime_System_SupportProxy_flush__E( void )
{
    xdc_runtime_SysStd_flush();
}

/* putch__E */
xdc_Void xdc_runtime_System_SupportProxy_putch__E( xdc_Char ch )
{
    xdc_runtime_SysStd_putch(ch);
}

/* ready__E */
xdc_Bool xdc_runtime_System_SupportProxy_ready__E( void )
{
    return xdc_runtime_SysStd_ready();
}


/*
 * ======== xdc.runtime.Timestamp_SupportProxy PROXY BODY ========
 */

/* DELEGATES TO ti.sdo.xdcruntime.linux.TimestampPosix */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Timestamp_SupportProxy_Module__startupDone__S( void ) 
{
    return ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDone__S();
}

/* get32__E */
xdc_Bits32 xdc_runtime_Timestamp_SupportProxy_get32__E( void )
{
    return ti_sdo_xdcruntime_linux_TimestampPosix_get32();
}

/* get64__E */
xdc_Void xdc_runtime_Timestamp_SupportProxy_get64__E( xdc_runtime_Types_Timestamp64* result )
{
    ti_sdo_xdcruntime_linux_TimestampPosix_get64(result);
}

/* getFreq__E */
xdc_Void xdc_runtime_Timestamp_SupportProxy_getFreq__E( xdc_runtime_Types_FreqHz* freq )
{
    ti_sdo_xdcruntime_linux_TimestampPosix_getFreq(freq);
}


/*
 * ======== xdc.runtime.knl.GateThread_Proxy PROXY BODY ========
 */

/* DELEGATES TO ti.sdo.xdcruntime.linux.GateThreadSupport */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_knl_GateThread_Proxy_Module__startupDone__S( void ) 
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDone__S();
}

/* Object__create__S */
xdc_Ptr xdc_runtime_knl_GateThread_Proxy_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const xdc_runtime_knl_GateThread_Proxy___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_Object__create__S(oa, osz, aa, (ti_sdo_xdcruntime_linux_GateThreadSupport___ParamsPtr)pa, sizeof(xdc_runtime_knl_IGateThreadSupport_Params), eb);
}

/* Object__delete__S */
void xdc_runtime_knl_GateThread_Proxy_Object__delete__S( Ptr instp ) 
{
    ti_sdo_xdcruntime_linux_GateThreadSupport_Object__delete__S(instp);
}

/* Params__init__S */
void xdc_runtime_knl_GateThread_Proxy_Params__init__S( xdc_Ptr dst, const xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz )
{
    ti_sdo_xdcruntime_linux_GateThreadSupport_Params__init__S(dst, src, psz, isz);
}

/* Handle__label__S */
xdc_runtime_Types_Label* xdc_runtime_knl_GateThread_Proxy_Handle__label__S( Ptr obj, xdc_runtime_Types_Label* lab )
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_Handle__label__S(obj, lab);
}

/* query__E */
xdc_Bool xdc_runtime_knl_GateThread_Proxy_query__E( xdc_Int qual )
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_query(qual);
}

/* enter__E */
xdc_IArg xdc_runtime_knl_GateThread_Proxy_enter__E( xdc_runtime_knl_GateThread_Proxy_Handle __inst )
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_enter((ti_sdo_xdcruntime_linux_GateThreadSupport_Handle)__inst);
}

/* leave__E */
xdc_Void xdc_runtime_knl_GateThread_Proxy_leave__E( xdc_runtime_knl_GateThread_Proxy_Handle __inst, xdc_IArg key )
{
    ti_sdo_xdcruntime_linux_GateThreadSupport_leave((ti_sdo_xdcruntime_linux_GateThreadSupport_Handle)__inst, key);
}


/*
 * ======== xdc.runtime.knl.SemProcess_Proxy PROXY BODY ========
 */

/* DELEGATES TO ti.sdo.xdcruntime.linux.SemProcessSupport */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_knl_SemProcess_Proxy_Module__startupDone__S( void ) 
{
    return ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDone__S();
}

/* Object__create__S */
xdc_Ptr xdc_runtime_knl_SemProcess_Proxy_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const xdc_runtime_knl_SemProcess_Proxy___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_SemProcessSupport_Object__create__S(oa, osz, aa, (ti_sdo_xdcruntime_linux_SemProcessSupport___ParamsPtr)pa, sizeof(xdc_runtime_knl_ISemProcessSupport_Params), eb);
}

/* Object__delete__S */
void xdc_runtime_knl_SemProcess_Proxy_Object__delete__S( Ptr instp ) 
{
    ti_sdo_xdcruntime_linux_SemProcessSupport_Object__delete__S(instp);
}

/* Params__init__S */
void xdc_runtime_knl_SemProcess_Proxy_Params__init__S( xdc_Ptr dst, const xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz )
{
    ti_sdo_xdcruntime_linux_SemProcessSupport_Params__init__S(dst, src, psz, isz);
}

/* Handle__label__S */
xdc_runtime_Types_Label* xdc_runtime_knl_SemProcess_Proxy_Handle__label__S( Ptr obj, xdc_runtime_Types_Label* lab )
{
    return ti_sdo_xdcruntime_linux_SemProcessSupport_Handle__label__S(obj, lab);
}

/* pend__E */
xdc_Int xdc_runtime_knl_SemProcess_Proxy_pend__E( xdc_runtime_knl_SemProcess_Proxy_Handle __inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_SemProcessSupport_pend((ti_sdo_xdcruntime_linux_SemProcessSupport_Handle)__inst, timeout, eb);
}

/* post__E */
xdc_Bool xdc_runtime_knl_SemProcess_Proxy_post__E( xdc_runtime_knl_SemProcess_Proxy_Handle __inst, xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_SemProcessSupport_post((ti_sdo_xdcruntime_linux_SemProcessSupport_Handle)__inst, eb);
}


/*
 * ======== xdc.runtime.knl.SemThread_Proxy PROXY BODY ========
 */

/* DELEGATES TO ti.sdo.xdcruntime.linux.SemThreadSupport */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_knl_SemThread_Proxy_Module__startupDone__S( void ) 
{
    return ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDone__S();
}

/* Object__create__S */
xdc_Ptr xdc_runtime_knl_SemThread_Proxy_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const xdc_runtime_knl_SemThread_Proxy___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_SemThreadSupport_Object__create__S(oa, osz, aa, (ti_sdo_xdcruntime_linux_SemThreadSupport___ParamsPtr)pa, sizeof(xdc_runtime_knl_ISemThreadSupport_Params), eb);
}

/* Object__delete__S */
void xdc_runtime_knl_SemThread_Proxy_Object__delete__S( Ptr instp ) 
{
    ti_sdo_xdcruntime_linux_SemThreadSupport_Object__delete__S(instp);
}

/* Params__init__S */
void xdc_runtime_knl_SemThread_Proxy_Params__init__S( xdc_Ptr dst, const xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz )
{
    ti_sdo_xdcruntime_linux_SemThreadSupport_Params__init__S(dst, src, psz, isz);
}

/* Handle__label__S */
xdc_runtime_Types_Label* xdc_runtime_knl_SemThread_Proxy_Handle__label__S( Ptr obj, xdc_runtime_Types_Label* lab )
{
    return ti_sdo_xdcruntime_linux_SemThreadSupport_Handle__label__S(obj, lab);
}

/* pend__E */
xdc_Int xdc_runtime_knl_SemThread_Proxy_pend__E( xdc_runtime_knl_SemThread_Proxy_Handle __inst, xdc_UInt timeout, xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_SemThreadSupport_pend((ti_sdo_xdcruntime_linux_SemThreadSupport_Handle)__inst, timeout, eb);
}

/* post__E */
xdc_Bool xdc_runtime_knl_SemThread_Proxy_post__E( xdc_runtime_knl_SemThread_Proxy_Handle __inst, xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_SemThreadSupport_post((ti_sdo_xdcruntime_linux_SemThreadSupport_Handle)__inst, eb);
}


/*
 * ======== xdc.runtime.knl.Thread_Proxy PROXY BODY ========
 */

/* DELEGATES TO ti.sdo.xdcruntime.linux.ThreadSupport */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_knl_Thread_Proxy_Module__startupDone__S( void ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDone__S();
}

/* Object__create__S */
xdc_Ptr xdc_runtime_knl_Thread_Proxy_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const xdc_runtime_knl_Thread_Proxy___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_Object__create__S(oa, osz, aa, (ti_sdo_xdcruntime_linux_ThreadSupport___ParamsPtr)pa, sizeof(xdc_runtime_knl_IThreadSupport_Params), eb);
}

/* Object__delete__S */
void xdc_runtime_knl_Thread_Proxy_Object__delete__S( Ptr instp ) 
{
    ti_sdo_xdcruntime_linux_ThreadSupport_Object__delete__S(instp);
}

/* Params__init__S */
void xdc_runtime_knl_Thread_Proxy_Params__init__S( xdc_Ptr dst, const xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz )
{
    ti_sdo_xdcruntime_linux_ThreadSupport_Params__init__S(dst, src, psz, isz);
}

/* Handle__label__S */
xdc_runtime_Types_Label* xdc_runtime_knl_Thread_Proxy_Handle__label__S( Ptr obj, xdc_runtime_Types_Label* lab )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_Handle__label__S(obj, lab);
}

/* self__E */
xdc_runtime_knl_IThreadSupport_Handle xdc_runtime_knl_Thread_Proxy_self__E( xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_self(eb);
}

/* start__E */
xdc_Bool xdc_runtime_knl_Thread_Proxy_start__E( xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_start(eb);
}

/* yield__E */
xdc_Bool xdc_runtime_knl_Thread_Proxy_yield__E( xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_yield(eb);
}

/* compareOsPriorities__E */
xdc_Int xdc_runtime_knl_Thread_Proxy_compareOsPriorities__E( xdc_Int p1, xdc_Int p2, xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_compareOsPriorities(p1, p2, eb);
}

/* sleep__E */
xdc_Bool xdc_runtime_knl_Thread_Proxy_sleep__E( xdc_UInt timeout, xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_sleep(timeout, eb);
}

/* join__E */
xdc_Bool xdc_runtime_knl_Thread_Proxy_join__E( xdc_runtime_knl_Thread_Proxy_Handle __inst, xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_join((ti_sdo_xdcruntime_linux_ThreadSupport_Handle)__inst, eb);
}

/* getPriority__E */
xdc_runtime_knl_IThreadSupport_Priority xdc_runtime_knl_Thread_Proxy_getPriority__E( xdc_runtime_knl_Thread_Proxy_Handle __inst, xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_getPriority((ti_sdo_xdcruntime_linux_ThreadSupport_Handle)__inst, eb);
}

/* setPriority__E */
xdc_Bool xdc_runtime_knl_Thread_Proxy_setPriority__E( xdc_runtime_knl_Thread_Proxy_Handle __inst, xdc_runtime_knl_IThreadSupport_Priority newPri, xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_setPriority((ti_sdo_xdcruntime_linux_ThreadSupport_Handle)__inst, newPri, eb);
}

/* getOsPriority__E */
xdc_Int xdc_runtime_knl_Thread_Proxy_getOsPriority__E( xdc_runtime_knl_Thread_Proxy_Handle __inst, xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_getOsPriority((ti_sdo_xdcruntime_linux_ThreadSupport_Handle)__inst, eb);
}

/* setOsPriority__E */
xdc_Bool xdc_runtime_knl_Thread_Proxy_setOsPriority__E( xdc_runtime_knl_Thread_Proxy_Handle __inst, xdc_Int newPri, xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_setOsPriority((ti_sdo_xdcruntime_linux_ThreadSupport_Handle)__inst, newPri, eb);
}

/* getOsHandle__E */
xdc_Ptr xdc_runtime_knl_Thread_Proxy_getOsHandle__E( xdc_runtime_knl_Thread_Proxy_Handle __inst )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_getOsHandle((ti_sdo_xdcruntime_linux_ThreadSupport_Handle)__inst);
}

/* getTls__E */
xdc_Ptr xdc_runtime_knl_Thread_Proxy_getTls__E( xdc_runtime_knl_Thread_Proxy_Handle __inst )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_getTls((ti_sdo_xdcruntime_linux_ThreadSupport_Handle)__inst);
}

/* setTls__E */
xdc_Void xdc_runtime_knl_Thread_Proxy_setTls__E( xdc_runtime_knl_Thread_Proxy_Handle __inst, xdc_Ptr tls )
{
    ti_sdo_xdcruntime_linux_ThreadSupport_setTls((ti_sdo_xdcruntime_linux_ThreadSupport_Handle)__inst, tls);
}

/* stat__E */
xdc_Bool xdc_runtime_knl_Thread_Proxy_stat__E( xdc_runtime_knl_Thread_Proxy_Handle __inst, xdc_runtime_knl_IThreadSupport_Stat* buf, xdc_runtime_Error_Block* eb )
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_stat((ti_sdo_xdcruntime_linux_ThreadSupport_Handle)__inst, buf, eb);
}


/*
 * ======== ti.sdo.utils.loggers.LoggerMFPNull OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { ti_sdo_utils_loggers_LoggerMFPNull_Object2__ s0; char c; } ti_sdo_utils_loggers_LoggerMFPNull___S1;
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_utils_loggers_LoggerMFPNull_Object__DESC__C = {
    (Ptr)&ti_sdo_utils_loggers_LoggerMFPNull_Module__FXNS__C, /* fxnTab */
    &ti_sdo_utils_loggers_LoggerMFPNull_Module__root__V.link, /* modLink */
    sizeof(ti_sdo_utils_loggers_LoggerMFPNull___S1) - sizeof(ti_sdo_utils_loggers_LoggerMFPNull_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(ti_sdo_utils_loggers_LoggerMFPNull_Object2__), /* objSize */
    (Ptr)&ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C, /* prmsInit */
    sizeof(ti_sdo_utils_loggers_LoggerMFPNull_Params), /* prmsSize */
};



/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { ti_sdo_utils_loggers_LoggerSysTID_Object2__ s0; char c; } ti_sdo_utils_loggers_LoggerSysTID___S1;
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_utils_loggers_LoggerSysTID_Object__DESC__C = {
    (Ptr)&ti_sdo_utils_loggers_LoggerSysTID_Module__FXNS__C, /* fxnTab */
    &ti_sdo_utils_loggers_LoggerSysTID_Module__root__V.link, /* modLink */
    sizeof(ti_sdo_utils_loggers_LoggerSysTID___S1) - sizeof(ti_sdo_utils_loggers_LoggerSysTID_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(ti_sdo_utils_loggers_LoggerSysTID_Object2__), /* objSize */
    (Ptr)&ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C, /* prmsInit */
    sizeof(ti_sdo_utils_loggers_LoggerSysTID_Params), /* prmsSize */
};



/*
 * ======== ti.sdo.xdcruntime.linux.GateThreadSupport OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { ti_sdo_xdcruntime_linux_GateThreadSupport_Object2__ s0; char c; } ti_sdo_xdcruntime_linux_GateThreadSupport___S1;
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_xdcruntime_linux_GateThreadSupport_Object__DESC__C = {
    (Ptr)0, /* fxnTab */
    &ti_sdo_xdcruntime_linux_GateThreadSupport_Module__root__V.link, /* modLink */
    sizeof(ti_sdo_xdcruntime_linux_GateThreadSupport___S1) - sizeof(ti_sdo_xdcruntime_linux_GateThreadSupport_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(ti_sdo_xdcruntime_linux_GateThreadSupport_Object2__), /* objSize */
    (Ptr)&ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C, /* prmsInit */
    sizeof(ti_sdo_xdcruntime_linux_GateThreadSupport_Params), /* prmsSize */
};



/*
 * ======== ti.sdo.xdcruntime.linux.SemProcessSupport OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { ti_sdo_xdcruntime_linux_SemProcessSupport_Object2__ s0; char c; } ti_sdo_xdcruntime_linux_SemProcessSupport___S1;
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_xdcruntime_linux_SemProcessSupport_Object__DESC__C = {
    (Ptr)0, /* fxnTab */
    &ti_sdo_xdcruntime_linux_SemProcessSupport_Module__root__V.link, /* modLink */
    sizeof(ti_sdo_xdcruntime_linux_SemProcessSupport___S1) - sizeof(ti_sdo_xdcruntime_linux_SemProcessSupport_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(ti_sdo_xdcruntime_linux_SemProcessSupport_Object2__), /* objSize */
    (Ptr)&ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C, /* prmsInit */
    sizeof(ti_sdo_xdcruntime_linux_SemProcessSupport_Params), /* prmsSize */
};



/*
 * ======== ti.sdo.xdcruntime.linux.SemThreadSupport OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { ti_sdo_xdcruntime_linux_SemThreadSupport_Object2__ s0; char c; } ti_sdo_xdcruntime_linux_SemThreadSupport___S1;
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_xdcruntime_linux_SemThreadSupport_Object__DESC__C = {
    (Ptr)0, /* fxnTab */
    &ti_sdo_xdcruntime_linux_SemThreadSupport_Module__root__V.link, /* modLink */
    sizeof(ti_sdo_xdcruntime_linux_SemThreadSupport___S1) - sizeof(ti_sdo_xdcruntime_linux_SemThreadSupport_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(ti_sdo_xdcruntime_linux_SemThreadSupport_Object2__), /* objSize */
    (Ptr)&ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C, /* prmsInit */
    sizeof(ti_sdo_xdcruntime_linux_SemThreadSupport_Params), /* prmsSize */
};



/*
 * ======== ti.sdo.xdcruntime.linux.ThreadSupport OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { ti_sdo_xdcruntime_linux_ThreadSupport_Object2__ s0; char c; } ti_sdo_xdcruntime_linux_ThreadSupport___S1;
__FAR__ const xdc_runtime_Core_ObjDesc ti_sdo_xdcruntime_linux_ThreadSupport_Object__DESC__C = {
    (Ptr)0, /* fxnTab */
    &ti_sdo_xdcruntime_linux_ThreadSupport_Module__root__V.link, /* modLink */
    sizeof(ti_sdo_xdcruntime_linux_ThreadSupport___S1) - sizeof(ti_sdo_xdcruntime_linux_ThreadSupport_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(ti_sdo_xdcruntime_linux_ThreadSupport_Object2__), /* objSize */
    (Ptr)&ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C, /* prmsInit */
    sizeof(ti_sdo_xdcruntime_linux_ThreadSupport_Params), /* prmsSize */
};



/*
 * ======== xdc.runtime.HeapStd OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { xdc_runtime_HeapStd_Object2__ s0; char c; } xdc_runtime_HeapStd___S1;
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_HeapStd_Object__DESC__C = {
    (Ptr)&xdc_runtime_HeapStd_Module__FXNS__C, /* fxnTab */
    &xdc_runtime_HeapStd_Module__root__V.link, /* modLink */
    sizeof(xdc_runtime_HeapStd___S1) - sizeof(xdc_runtime_HeapStd_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(xdc_runtime_HeapStd_Object2__), /* objSize */
    (Ptr)&xdc_runtime_HeapStd_Object__PARAMS__C, /* prmsInit */
    sizeof(xdc_runtime_HeapStd_Params), /* prmsSize */
};



/*
 * ======== xdc.runtime.knl.GateThread OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { xdc_runtime_knl_GateThread_Object2__ s0; char c; } xdc_runtime_knl_GateThread___S1;
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_knl_GateThread_Object__DESC__C = {
    (Ptr)&xdc_runtime_knl_GateThread_Module__FXNS__C, /* fxnTab */
    &xdc_runtime_knl_GateThread_Module__root__V.link, /* modLink */
    sizeof(xdc_runtime_knl_GateThread___S1) - sizeof(xdc_runtime_knl_GateThread_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(xdc_runtime_knl_GateThread_Object2__), /* objSize */
    (Ptr)&xdc_runtime_knl_GateThread_Object__PARAMS__C, /* prmsInit */
    sizeof(xdc_runtime_knl_GateThread_Params), /* prmsSize */
};



/*
 * ======== xdc.runtime.knl.SemProcess OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { xdc_runtime_knl_SemProcess_Object2__ s0; char c; } xdc_runtime_knl_SemProcess___S1;
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_knl_SemProcess_Object__DESC__C = {
    (Ptr)&xdc_runtime_knl_SemProcess_Module__FXNS__C, /* fxnTab */
    &xdc_runtime_knl_SemProcess_Module__root__V.link, /* modLink */
    sizeof(xdc_runtime_knl_SemProcess___S1) - sizeof(xdc_runtime_knl_SemProcess_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(xdc_runtime_knl_SemProcess_Object2__), /* objSize */
    (Ptr)&xdc_runtime_knl_SemProcess_Object__PARAMS__C, /* prmsInit */
    sizeof(xdc_runtime_knl_SemProcess_Params), /* prmsSize */
};



/*
 * ======== xdc.runtime.knl.SemThread OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { xdc_runtime_knl_SemThread_Object2__ s0; char c; } xdc_runtime_knl_SemThread___S1;
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_knl_SemThread_Object__DESC__C = {
    (Ptr)&xdc_runtime_knl_SemThread_Module__FXNS__C, /* fxnTab */
    &xdc_runtime_knl_SemThread_Module__root__V.link, /* modLink */
    sizeof(xdc_runtime_knl_SemThread___S1) - sizeof(xdc_runtime_knl_SemThread_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(xdc_runtime_knl_SemThread_Object2__), /* objSize */
    (Ptr)&xdc_runtime_knl_SemThread_Object__PARAMS__C, /* prmsInit */
    sizeof(xdc_runtime_knl_SemThread_Params), /* prmsSize */
};



/*
 * ======== xdc.runtime.knl.Thread OBJECT DESCRIPTOR ========
 */

/* Object__DESC__C */
typedef struct { xdc_runtime_knl_Thread_Object2__ s0; char c; } xdc_runtime_knl_Thread___S1;
__FAR__ const xdc_runtime_Core_ObjDesc xdc_runtime_knl_Thread_Object__DESC__C = {
    (Ptr)-1, /* fxnTab */
    &xdc_runtime_knl_Thread_Module__root__V.link, /* modLink */
    sizeof(xdc_runtime_knl_Thread___S1) - sizeof(xdc_runtime_knl_Thread_Object2__), /* objAlign */
    0, /* objHeap */
    0, /* objName */
    sizeof(xdc_runtime_knl_Thread_Object2__), /* objSize */
    (Ptr)&xdc_runtime_knl_Thread_Object__PARAMS__C, /* prmsInit */
    sizeof(xdc_runtime_knl_Thread_Params), /* prmsSize */
};



/*
 * ======== ti.sdo.utils.loggers.LogMFP SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool ti_sdo_utils_loggers_LogMFP_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== ti.sdo.utils.loggers.LogMFP_Proxy SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_utils_loggers_LogMFP_Proxy_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_utils_loggers_LogMFP_Proxy_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_utils_loggers_LogMFP_Proxy_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_utils_loggers_LogMFP_Proxy_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_utils_loggers_LogMFP_Proxy_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_utils_loggers_LogMFP_Proxy_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_utils_loggers_LogMFP_Proxy_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_utils_loggers_LogMFP_Proxy_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_utils_loggers_LogMFP_Proxy_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_utils_loggers_LogMFP_Proxy_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_utils_loggers_LogMFP_Proxy_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_utils_loggers_LogMFP_Proxy_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_utils_loggers_LogMFP_Proxy_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_utils_loggers_LogMFP_Proxy_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_utils_loggers_LogMFP_Proxy_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_utils_loggers_LogMFP_Proxy_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_utils_loggers_LogMFP_Proxy_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_utils_loggers_LogMFP_Proxy_Module_GateProxy_query
xdc_Bool ti_sdo_utils_loggers_LogMFP_Proxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr ti_sdo_utils_loggers_LogMFP_Proxy_Proxy__delegate__S( void )
{
    return (xdc_Ptr)&ti_sdo_utils_loggers_LoggerMFPNull_Module__FXNS__C;
}



/*
 * ======== ti.sdo.utils.loggers.LoggerMFPNull SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_utils_loggers_LoggerMFPNull_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_utils_loggers_LoggerMFPNull_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_utils_loggers_LoggerMFPNull_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_utils_loggers_LoggerMFPNull_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_utils_loggers_LoggerMFPNull_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_utils_loggers_LoggerMFPNull_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_utils_loggers_LoggerMFPNull_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_utils_loggers_LoggerMFPNull_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool ti_sdo_utils_loggers_LoggerMFPNull_Module__startupDone__S( void ) 
{
    return 1;
}

/* Handle__label__S */
xdc_runtime_Types_Label* ti_sdo_utils_loggers_LoggerMFPNull_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) 
{
    lab->handle = obj;
    lab->modId = 32802;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_Params__init__S( xdc_Ptr prms, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr ti_sdo_utils_loggers_LoggerMFPNull_Object__get__S( xdc_Ptr oa, xdc_Int i ) 
{
    if (oa) {
        return ((ti_sdo_utils_loggers_LoggerMFPNull_Object__*)oa) + i;
    }

    if (ti_sdo_utils_loggers_LoggerMFPNull_Object__count__C == 0) {
        return NULL;
    }

    return ((ti_sdo_utils_loggers_LoggerMFPNull_Object__*)ti_sdo_utils_loggers_LoggerMFPNull_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr ti_sdo_utils_loggers_LoggerMFPNull_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)ti_sdo_utils_loggers_LoggerMFPNull_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&ti_sdo_utils_loggers_LoggerMFPNull_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr ti_sdo_utils_loggers_LoggerMFPNull_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&ti_sdo_utils_loggers_LoggerMFPNull_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr ti_sdo_utils_loggers_LoggerMFPNull_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const ti_sdo_utils_loggers_LoggerMFPNull___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    ti_sdo_utils_loggers_LoggerMFPNull_Params prms;
    ti_sdo_utils_loggers_LoggerMFPNull_Object* obj;

    /* common instance initialization */
    obj = xdc_runtime_Core_createObject__I(&ti_sdo_utils_loggers_LoggerMFPNull_Object__DESC__C, oa, osz, &prms, (xdc_Ptr)pa, psz, eb);
    if (obj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    ti_sdo_utils_loggers_LoggerMFPNull_Instance_init__F(obj, &prms);
    return obj;
}

/* Object__destruct__S */
xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_utils_loggers_LoggerMFPNull_Object__DESC__C, obj, NULL, -1, TRUE);
}

/* Object__delete__S */
xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_utils_loggers_LoggerMFPNull_Object__DESC__C, *((ti_sdo_utils_loggers_LoggerMFPNull_Object**)instp), NULL, -1, FALSE);
    *((ti_sdo_utils_loggers_LoggerMFPNull_Handle*)instp) = NULL;
}


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_utils_loggers_LoggerSysTID_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_utils_loggers_LoggerSysTID_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_utils_loggers_LoggerSysTID_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_utils_loggers_LoggerSysTID_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_utils_loggers_LoggerSysTID_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_utils_loggers_LoggerSysTID_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_utils_loggers_LoggerSysTID_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_utils_loggers_LoggerSysTID_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool ti_sdo_utils_loggers_LoggerSysTID_Module__startupDone__S( void ) 
{
    return ti_sdo_utils_loggers_LoggerSysTID_Module__startupDone__F();
}

/* Handle__label__S */
xdc_runtime_Types_Label* ti_sdo_utils_loggers_LoggerSysTID_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) 
{
    lab->handle = obj;
    lab->modId = 32801;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void ti_sdo_utils_loggers_LoggerSysTID_Params__init__S( xdc_Ptr prms, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr ti_sdo_utils_loggers_LoggerSysTID_Object__get__S( xdc_Ptr oa, xdc_Int i ) 
{
    if (oa) {
        return ((ti_sdo_utils_loggers_LoggerSysTID_Object__*)oa) + i;
    }

    if (ti_sdo_utils_loggers_LoggerSysTID_Object__count__C == 0) {
        return NULL;
    }

    return ((ti_sdo_utils_loggers_LoggerSysTID_Object__*)ti_sdo_utils_loggers_LoggerSysTID_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr ti_sdo_utils_loggers_LoggerSysTID_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)ti_sdo_utils_loggers_LoggerSysTID_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&ti_sdo_utils_loggers_LoggerSysTID_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr ti_sdo_utils_loggers_LoggerSysTID_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&ti_sdo_utils_loggers_LoggerSysTID_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr ti_sdo_utils_loggers_LoggerSysTID_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const ti_sdo_utils_loggers_LoggerSysTID___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    ti_sdo_utils_loggers_LoggerSysTID_Params prms;
    ti_sdo_utils_loggers_LoggerSysTID_Object* obj;

    /* common instance initialization */
    obj = xdc_runtime_Core_createObject__I(&ti_sdo_utils_loggers_LoggerSysTID_Object__DESC__C, oa, osz, &prms, (xdc_Ptr)pa, psz, eb);
    if (obj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    ti_sdo_utils_loggers_LoggerSysTID_Instance_init__F(obj, &prms);
    return obj;
}

/* Object__destruct__S */
xdc_Void ti_sdo_utils_loggers_LoggerSysTID_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_utils_loggers_LoggerSysTID_Object__DESC__C, obj, NULL, -1, TRUE);
}

/* Object__delete__S */
xdc_Void ti_sdo_utils_loggers_LoggerSysTID_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_utils_loggers_LoggerSysTID_Object__DESC__C, *((ti_sdo_utils_loggers_LoggerSysTID_Object**)instp), NULL, -1, FALSE);
    *((ti_sdo_utils_loggers_LoggerSysTID_Handle*)instp) = NULL;
}


/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID_Module_GateProxy SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Module_GateProxy_query
xdc_Bool ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr ti_sdo_utils_loggers_LoggerSysTID_Module_GateProxy_Proxy__delegate__S( void )
{
    return (xdc_Ptr)&xdc_runtime_knl_GateThread_Module__FXNS__C;
}



/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID_TimestampProxy SYSTEM FUNCTIONS ========
 */

xdc_Bool ti_sdo_utils_loggers_LoggerSysTID_TimestampProxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr ti_sdo_utils_loggers_LoggerSysTID_TimestampProxy_Proxy__delegate__S( void )
{
    return (xdc_Ptr)&ti_sdo_xdcruntime_linux_TimestampPosix_Module__FXNS__C;
}


/*
 * ======== ti.sdo.xdcruntime.linux.GateThreadSupport SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_xdcruntime_linux_GateThreadSupport_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_xdcruntime_linux_GateThreadSupport_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_xdcruntime_linux_GateThreadSupport_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_xdcruntime_linux_GateThreadSupport_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_xdcruntime_linux_GateThreadSupport_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_xdcruntime_linux_GateThreadSupport_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDone__S( void ) 
{
    return ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDone__F();
}

/* Handle__label__S */
xdc_runtime_Types_Label* ti_sdo_xdcruntime_linux_GateThreadSupport_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) 
{
    lab->handle = obj;
    lab->modId = 32794;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void ti_sdo_xdcruntime_linux_GateThreadSupport_Params__init__S( xdc_Ptr prms, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr ti_sdo_xdcruntime_linux_GateThreadSupport_Object__get__S( xdc_Ptr oa, xdc_Int i ) 
{
    if (oa) {
        return ((ti_sdo_xdcruntime_linux_GateThreadSupport_Object__*)oa) + i;
    }

    if (ti_sdo_xdcruntime_linux_GateThreadSupport_Object__count__C == 0) {
        return NULL;
    }

    return ((ti_sdo_xdcruntime_linux_GateThreadSupport_Object__*)ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr ti_sdo_xdcruntime_linux_GateThreadSupport_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)ti_sdo_xdcruntime_linux_GateThreadSupport_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&ti_sdo_xdcruntime_linux_GateThreadSupport_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr ti_sdo_xdcruntime_linux_GateThreadSupport_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&ti_sdo_xdcruntime_linux_GateThreadSupport_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr ti_sdo_xdcruntime_linux_GateThreadSupport_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const ti_sdo_xdcruntime_linux_GateThreadSupport___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    ti_sdo_xdcruntime_linux_GateThreadSupport_Params prms;
    ti_sdo_xdcruntime_linux_GateThreadSupport_Object* obj;
    int iStat;

    /* common instance initialization */
    obj = xdc_runtime_Core_createObject__I(&ti_sdo_xdcruntime_linux_GateThreadSupport_Object__DESC__C, oa, osz, &prms, (xdc_Ptr)pa, psz, eb);
    if (obj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    iStat = ti_sdo_xdcruntime_linux_GateThreadSupport_Instance_init__F(obj, &prms, eb);
    if (xdc_runtime_Error_check(eb)) {
        xdc_runtime_Core_deleteObject__I(&ti_sdo_xdcruntime_linux_GateThreadSupport_Object__DESC__C, obj, (xdc_Fxn)ti_sdo_xdcruntime_linux_GateThreadSupport_Instance_finalize__F, iStat, (xdc_Bool)(oa != NULL));
        return NULL;
    }

    return obj;
}

/* Object__destruct__S */
xdc_Void ti_sdo_xdcruntime_linux_GateThreadSupport_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_xdcruntime_linux_GateThreadSupport_Object__DESC__C, obj, (xdc_Fxn)ti_sdo_xdcruntime_linux_GateThreadSupport_Instance_finalize__F, 0, TRUE);
}

/* Object__delete__S */
xdc_Void ti_sdo_xdcruntime_linux_GateThreadSupport_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_xdcruntime_linux_GateThreadSupport_Object__DESC__C, *((ti_sdo_xdcruntime_linux_GateThreadSupport_Object**)instp), (xdc_Fxn)ti_sdo_xdcruntime_linux_GateThreadSupport_Instance_finalize__F, 0, FALSE);
    *((ti_sdo_xdcruntime_linux_GateThreadSupport_Handle*)instp) = NULL;
}


/*
 * ======== ti.sdo.xdcruntime.linux.SemProcessSupport SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_xdcruntime_linux_SemProcessSupport_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_xdcruntime_linux_SemProcessSupport_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_xdcruntime_linux_SemProcessSupport_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_xdcruntime_linux_SemProcessSupport_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_xdcruntime_linux_SemProcessSupport_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_xdcruntime_linux_SemProcessSupport_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDone__S( void ) 
{
    return ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDone__F();
}

/* Handle__label__S */
xdc_runtime_Types_Label* ti_sdo_xdcruntime_linux_SemProcessSupport_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) 
{
    lab->handle = obj;
    lab->modId = 32796;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void ti_sdo_xdcruntime_linux_SemProcessSupport_Params__init__S( xdc_Ptr prms, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr ti_sdo_xdcruntime_linux_SemProcessSupport_Object__get__S( xdc_Ptr oa, xdc_Int i ) 
{
    if (oa) {
        return ((ti_sdo_xdcruntime_linux_SemProcessSupport_Object__*)oa) + i;
    }

    if (ti_sdo_xdcruntime_linux_SemProcessSupport_Object__count__C == 0) {
        return NULL;
    }

    return ((ti_sdo_xdcruntime_linux_SemProcessSupport_Object__*)ti_sdo_xdcruntime_linux_SemProcessSupport_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr ti_sdo_xdcruntime_linux_SemProcessSupport_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)ti_sdo_xdcruntime_linux_SemProcessSupport_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&ti_sdo_xdcruntime_linux_SemProcessSupport_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr ti_sdo_xdcruntime_linux_SemProcessSupport_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&ti_sdo_xdcruntime_linux_SemProcessSupport_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr ti_sdo_xdcruntime_linux_SemProcessSupport_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const ti_sdo_xdcruntime_linux_SemProcessSupport___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    ti_sdo_xdcruntime_linux_SemProcessSupport_Params prms;
    ti_sdo_xdcruntime_linux_SemProcessSupport_Object* obj;
    int iStat;

    ti_sdo_xdcruntime_linux_SemProcessSupport_Args__create* args = aa;
    /* common instance initialization */
    obj = xdc_runtime_Core_createObject__I(&ti_sdo_xdcruntime_linux_SemProcessSupport_Object__DESC__C, oa, osz, &prms, (xdc_Ptr)pa, psz, eb);
    if (obj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    iStat = ti_sdo_xdcruntime_linux_SemProcessSupport_Instance_init__F(obj, args->count, args->key, &prms, eb);
    if (xdc_runtime_Error_check(eb)) {
        xdc_runtime_Core_deleteObject__I(&ti_sdo_xdcruntime_linux_SemProcessSupport_Object__DESC__C, obj, (xdc_Fxn)ti_sdo_xdcruntime_linux_SemProcessSupport_Instance_finalize__F, iStat, (xdc_Bool)(oa != NULL));
        return NULL;
    }

    return obj;
}

/* Object__destruct__S */
xdc_Void ti_sdo_xdcruntime_linux_SemProcessSupport_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_xdcruntime_linux_SemProcessSupport_Object__DESC__C, obj, (xdc_Fxn)ti_sdo_xdcruntime_linux_SemProcessSupport_Instance_finalize__F, 0, TRUE);
}

/* Object__delete__S */
xdc_Void ti_sdo_xdcruntime_linux_SemProcessSupport_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_xdcruntime_linux_SemProcessSupport_Object__DESC__C, *((ti_sdo_xdcruntime_linux_SemProcessSupport_Object**)instp), (xdc_Fxn)ti_sdo_xdcruntime_linux_SemProcessSupport_Instance_finalize__F, 0, FALSE);
    *((ti_sdo_xdcruntime_linux_SemProcessSupport_Handle*)instp) = NULL;
}


/*
 * ======== ti.sdo.xdcruntime.linux.SemThreadSupport SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_xdcruntime_linux_SemThreadSupport_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_xdcruntime_linux_SemThreadSupport_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_xdcruntime_linux_SemThreadSupport_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_xdcruntime_linux_SemThreadSupport_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_xdcruntime_linux_SemThreadSupport_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_xdcruntime_linux_SemThreadSupport_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDone__S( void ) 
{
    return ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDone__F();
}

/* Handle__label__S */
xdc_runtime_Types_Label* ti_sdo_xdcruntime_linux_SemThreadSupport_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) 
{
    lab->handle = obj;
    lab->modId = 32795;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void ti_sdo_xdcruntime_linux_SemThreadSupport_Params__init__S( xdc_Ptr prms, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr ti_sdo_xdcruntime_linux_SemThreadSupport_Object__get__S( xdc_Ptr oa, xdc_Int i ) 
{
    if (oa) {
        return ((ti_sdo_xdcruntime_linux_SemThreadSupport_Object__*)oa) + i;
    }

    if (ti_sdo_xdcruntime_linux_SemThreadSupport_Object__count__C == 0) {
        return NULL;
    }

    return ((ti_sdo_xdcruntime_linux_SemThreadSupport_Object__*)ti_sdo_xdcruntime_linux_SemThreadSupport_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr ti_sdo_xdcruntime_linux_SemThreadSupport_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)ti_sdo_xdcruntime_linux_SemThreadSupport_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&ti_sdo_xdcruntime_linux_SemThreadSupport_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr ti_sdo_xdcruntime_linux_SemThreadSupport_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&ti_sdo_xdcruntime_linux_SemThreadSupport_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr ti_sdo_xdcruntime_linux_SemThreadSupport_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const ti_sdo_xdcruntime_linux_SemThreadSupport___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    ti_sdo_xdcruntime_linux_SemThreadSupport_Params prms;
    ti_sdo_xdcruntime_linux_SemThreadSupport_Object* obj;
    int iStat;

    ti_sdo_xdcruntime_linux_SemThreadSupport_Args__create* args = aa;
    /* common instance initialization */
    obj = xdc_runtime_Core_createObject__I(&ti_sdo_xdcruntime_linux_SemThreadSupport_Object__DESC__C, oa, osz, &prms, (xdc_Ptr)pa, psz, eb);
    if (obj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    iStat = ti_sdo_xdcruntime_linux_SemThreadSupport_Instance_init__F(obj, args->count, &prms, eb);
    if (xdc_runtime_Error_check(eb)) {
        xdc_runtime_Core_deleteObject__I(&ti_sdo_xdcruntime_linux_SemThreadSupport_Object__DESC__C, obj, (xdc_Fxn)ti_sdo_xdcruntime_linux_SemThreadSupport_Instance_finalize__F, iStat, (xdc_Bool)(oa != NULL));
        return NULL;
    }

    return obj;
}

/* Object__destruct__S */
xdc_Void ti_sdo_xdcruntime_linux_SemThreadSupport_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_xdcruntime_linux_SemThreadSupport_Object__DESC__C, obj, (xdc_Fxn)ti_sdo_xdcruntime_linux_SemThreadSupport_Instance_finalize__F, 0, TRUE);
}

/* Object__delete__S */
xdc_Void ti_sdo_xdcruntime_linux_SemThreadSupport_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_xdcruntime_linux_SemThreadSupport_Object__DESC__C, *((ti_sdo_xdcruntime_linux_SemThreadSupport_Object**)instp), (xdc_Fxn)ti_sdo_xdcruntime_linux_SemThreadSupport_Instance_finalize__F, 0, FALSE);
    *((ti_sdo_xdcruntime_linux_SemThreadSupport_Handle*)instp) = NULL;
}


/*
 * ======== ti.sdo.xdcruntime.linux.ThreadSupport SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID ti_sdo_xdcruntime_linux_ThreadSupport_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ ti_sdo_xdcruntime_linux_ThreadSupport_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS ti_sdo_xdcruntime_linux_ThreadSupport_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create ti_sdo_xdcruntime_linux_ThreadSupport_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete ti_sdo_xdcruntime_linux_ThreadSupport_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter ti_sdo_xdcruntime_linux_ThreadSupport_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave ti_sdo_xdcruntime_linux_ThreadSupport_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query ti_sdo_xdcruntime_linux_ThreadSupport_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDone__S( void ) 
{
    return ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDone__F();
}

/* Handle__label__S */
xdc_runtime_Types_Label* ti_sdo_xdcruntime_linux_ThreadSupport_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) 
{
    lab->handle = obj;
    lab->modId = 32797;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void ti_sdo_xdcruntime_linux_ThreadSupport_Params__init__S( xdc_Ptr prms, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr ti_sdo_xdcruntime_linux_ThreadSupport_Object__get__S( xdc_Ptr oa, xdc_Int i ) 
{
    if (oa) {
        return ((ti_sdo_xdcruntime_linux_ThreadSupport_Object__*)oa) + i;
    }

    if (ti_sdo_xdcruntime_linux_ThreadSupport_Object__count__C == 0) {
        return NULL;
    }

    return ((ti_sdo_xdcruntime_linux_ThreadSupport_Object__*)ti_sdo_xdcruntime_linux_ThreadSupport_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr ti_sdo_xdcruntime_linux_ThreadSupport_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)ti_sdo_xdcruntime_linux_ThreadSupport_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&ti_sdo_xdcruntime_linux_ThreadSupport_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr ti_sdo_xdcruntime_linux_ThreadSupport_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&ti_sdo_xdcruntime_linux_ThreadSupport_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr ti_sdo_xdcruntime_linux_ThreadSupport_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const ti_sdo_xdcruntime_linux_ThreadSupport___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    ti_sdo_xdcruntime_linux_ThreadSupport_Params prms;
    ti_sdo_xdcruntime_linux_ThreadSupport_Object* obj;
    int iStat;

    ti_sdo_xdcruntime_linux_ThreadSupport_Args__create* args = aa;
    /* common instance initialization */
    obj = xdc_runtime_Core_createObject__I(&ti_sdo_xdcruntime_linux_ThreadSupport_Object__DESC__C, oa, osz, &prms, (xdc_Ptr)pa, psz, eb);
    if (obj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    iStat = ti_sdo_xdcruntime_linux_ThreadSupport_Instance_init__F(obj, args->fxn, &prms, eb);
    if (xdc_runtime_Error_check(eb)) {
        xdc_runtime_Core_deleteObject__I(&ti_sdo_xdcruntime_linux_ThreadSupport_Object__DESC__C, obj, (xdc_Fxn)ti_sdo_xdcruntime_linux_ThreadSupport_Instance_finalize__F, iStat, (xdc_Bool)(oa != NULL));
        return NULL;
    }

    return obj;
}

/* Object__destruct__S */
xdc_Void ti_sdo_xdcruntime_linux_ThreadSupport_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_xdcruntime_linux_ThreadSupport_Object__DESC__C, obj, (xdc_Fxn)ti_sdo_xdcruntime_linux_ThreadSupport_Instance_finalize__F, 0, TRUE);
}

/* Object__delete__S */
xdc_Void ti_sdo_xdcruntime_linux_ThreadSupport_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&ti_sdo_xdcruntime_linux_ThreadSupport_Object__DESC__C, *((ti_sdo_xdcruntime_linux_ThreadSupport_Object**)instp), (xdc_Fxn)ti_sdo_xdcruntime_linux_ThreadSupport_Instance_finalize__F, 0, FALSE);
    *((ti_sdo_xdcruntime_linux_ThreadSupport_Handle*)instp) = NULL;
}


/*
 * ======== ti.sdo.xdcruntime.linux.TimestampPosix SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.Assert SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Assert_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.Core SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Core_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.Defaults SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Defaults_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.Diags SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Diags_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.Error SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Error_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.Gate SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Gate_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.HeapStd SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_HeapStd_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_HeapStd_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_HeapStd_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_HeapStd_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_HeapStd_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_HeapStd_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_HeapStd_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_HeapStd_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_HeapStd_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_HeapStd_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_HeapStd_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_HeapStd_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_HeapStd_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_HeapStd_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_HeapStd_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_HeapStd_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_HeapStd_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_HeapStd_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool xdc_runtime_HeapStd_Module__startupDone__S( void ) 
{
    return 1;
}

/* Handle__label__S */
xdc_runtime_Types_Label* xdc_runtime_HeapStd_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) 
{
    lab->handle = obj;
    lab->modId = 32779;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void xdc_runtime_HeapStd_Params__init__S( xdc_Ptr prms, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &xdc_runtime_HeapStd_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr xdc_runtime_HeapStd_Object__get__S( xdc_Ptr oa, xdc_Int i ) 
{
    if (oa) {
        return ((xdc_runtime_HeapStd_Object__*)oa) + i;
    }

    if (xdc_runtime_HeapStd_Object__count__C == 0) {
        return NULL;
    }

    return ((xdc_runtime_HeapStd_Object__*)xdc_runtime_HeapStd_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr xdc_runtime_HeapStd_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)xdc_runtime_HeapStd_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&xdc_runtime_HeapStd_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr xdc_runtime_HeapStd_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&xdc_runtime_HeapStd_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr xdc_runtime_HeapStd_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const xdc_runtime_HeapStd___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    xdc_runtime_HeapStd_Params prms;
    xdc_runtime_HeapStd_Object* obj;
    int iStat;

    /* common instance initialization */
    obj = xdc_runtime_Core_createObject__I(&xdc_runtime_HeapStd_Object__DESC__C, oa, osz, &prms, (xdc_Ptr)pa, psz, eb);
    if (obj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    iStat = xdc_runtime_HeapStd_Instance_init__F(obj, &prms, eb);
    if (xdc_runtime_Error_check(eb)) {
        xdc_runtime_Core_deleteObject__I(&xdc_runtime_HeapStd_Object__DESC__C, obj, NULL, iStat, (xdc_Bool)(oa != NULL));
        return NULL;
    }

    return obj;
}

/* Object__destruct__S */
xdc_Void xdc_runtime_HeapStd_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_HeapStd_Object__DESC__C, obj, NULL, 0, TRUE);
}

/* Object__delete__S */
xdc_Void xdc_runtime_HeapStd_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_HeapStd_Object__DESC__C, *((xdc_runtime_HeapStd_Object**)instp), NULL, 0, FALSE);
    *((xdc_runtime_HeapStd_Handle*)instp) = NULL;
}


/*
 * ======== xdc.runtime.Log SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Log_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.Main SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Main_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.Main_Module_GateProxy SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_Main_Module_GateProxy_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_Main_Module_GateProxy_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_Main_Module_GateProxy_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_Main_Module_GateProxy_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_Main_Module_GateProxy_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_Main_Module_GateProxy_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_Main_Module_GateProxy_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_Main_Module_GateProxy_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_Main_Module_GateProxy_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_Main_Module_GateProxy_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_Main_Module_GateProxy_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_Main_Module_GateProxy_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_Main_Module_GateProxy_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_Main_Module_GateProxy_Module_GateProxy_query
xdc_Bool xdc_runtime_Main_Module_GateProxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr xdc_runtime_Main_Module_GateProxy_Proxy__delegate__S( void )
{
    return 0;
}



/*
 * ======== xdc.runtime.Memory SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Memory_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.Memory_HeapProxy SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_Memory_HeapProxy_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_Memory_HeapProxy_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_Memory_HeapProxy_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_Memory_HeapProxy_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_Memory_HeapProxy_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_Memory_HeapProxy_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_Memory_HeapProxy_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_Memory_HeapProxy_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_Memory_HeapProxy_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_Memory_HeapProxy_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_Memory_HeapProxy_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_Memory_HeapProxy_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_Memory_HeapProxy_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_Memory_HeapProxy_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_Memory_HeapProxy_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_Memory_HeapProxy_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_Memory_HeapProxy_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_Memory_HeapProxy_Module_GateProxy_query
xdc_Bool xdc_runtime_Memory_HeapProxy_Proxy__abstract__S( void )
{
    return 1;
}
xdc_Ptr xdc_runtime_Memory_HeapProxy_Proxy__delegate__S( void )
{
    return (xdc_Ptr)&xdc_runtime_HeapStd_Module__FXNS__C;
}



/*
 * ======== xdc.runtime.Registry SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Registry_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.Startup SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Startup_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.SysStd SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_SysStd_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.System SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_System_Module__startupDone__S( void ) 
{
    return xdc_runtime_System_Module__startupDone__F();
}



/*
 * ======== xdc.runtime.System_Module_GateProxy SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_System_Module_GateProxy_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_System_Module_GateProxy_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_System_Module_GateProxy_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_System_Module_GateProxy_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_System_Module_GateProxy_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_System_Module_GateProxy_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_System_Module_GateProxy_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_System_Module_GateProxy_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_System_Module_GateProxy_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_System_Module_GateProxy_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_System_Module_GateProxy_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_System_Module_GateProxy_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_System_Module_GateProxy_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_System_Module_GateProxy_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_System_Module_GateProxy_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_System_Module_GateProxy_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_System_Module_GateProxy_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_System_Module_GateProxy_Module_GateProxy_query
xdc_Bool xdc_runtime_System_Module_GateProxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr xdc_runtime_System_Module_GateProxy_Proxy__delegate__S( void )
{
    return 0;
}



/*
 * ======== xdc.runtime.System_SupportProxy SYSTEM FUNCTIONS ========
 */

xdc_Bool xdc_runtime_System_SupportProxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr xdc_runtime_System_SupportProxy_Proxy__delegate__S( void )
{
    return (xdc_Ptr)&xdc_runtime_SysStd_Module__FXNS__C;
}


/*
 * ======== xdc.runtime.Text SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Text_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.Timestamp SYSTEM FUNCTIONS ========
 */

/* Module__startupDone__S */
xdc_Bool xdc_runtime_Timestamp_Module__startupDone__S( void ) 
{
    return 1;
}



/*
 * ======== xdc.runtime.Timestamp_SupportProxy SYSTEM FUNCTIONS ========
 */

xdc_Bool xdc_runtime_Timestamp_SupportProxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr xdc_runtime_Timestamp_SupportProxy_Proxy__delegate__S( void )
{
    return (xdc_Ptr)&ti_sdo_xdcruntime_linux_TimestampPosix_Module__FXNS__C;
}


/*
 * ======== xdc.runtime.knl.GateThread SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_knl_GateThread_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_knl_GateThread_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_knl_GateThread_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_knl_GateThread_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_knl_GateThread_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_knl_GateThread_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_knl_GateThread_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_knl_GateThread_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_knl_GateThread_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_knl_GateThread_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_knl_GateThread_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_knl_GateThread_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_knl_GateThread_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_knl_GateThread_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_knl_GateThread_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_knl_GateThread_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_knl_GateThread_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_knl_GateThread_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool xdc_runtime_knl_GateThread_Module__startupDone__S( void ) 
{
    return 1;
}

/* Handle__label__S */
xdc_runtime_Types_Label* xdc_runtime_knl_GateThread_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) 
{
    lab->handle = obj;
    lab->modId = 32788;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void xdc_runtime_knl_GateThread_Params__init__S( xdc_Ptr prms, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &xdc_runtime_knl_GateThread_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr xdc_runtime_knl_GateThread_Object__get__S( xdc_Ptr oa, xdc_Int i ) 
{
    if (oa) {
        return ((xdc_runtime_knl_GateThread_Object__*)oa) + i;
    }

    if (xdc_runtime_knl_GateThread_Object__count__C == 0) {
        return NULL;
    }

    return ((xdc_runtime_knl_GateThread_Object__*)xdc_runtime_knl_GateThread_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr xdc_runtime_knl_GateThread_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)xdc_runtime_knl_GateThread_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&xdc_runtime_knl_GateThread_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr xdc_runtime_knl_GateThread_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&xdc_runtime_knl_GateThread_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr xdc_runtime_knl_GateThread_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const xdc_runtime_knl_GateThread___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    xdc_runtime_knl_GateThread_Params prms;
    xdc_runtime_knl_GateThread_Object* obj;
    int iStat;

    /* common instance initialization */
    obj = xdc_runtime_Core_createObject__I(&xdc_runtime_knl_GateThread_Object__DESC__C, oa, osz, &prms, (xdc_Ptr)pa, psz, eb);
    if (obj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    iStat = xdc_runtime_knl_GateThread_Instance_init__F(obj, &prms, eb);
    if (xdc_runtime_Error_check(eb)) {
        xdc_runtime_Core_deleteObject__I(&xdc_runtime_knl_GateThread_Object__DESC__C, obj, (xdc_Fxn)xdc_runtime_knl_GateThread_Instance_finalize__F, iStat, (xdc_Bool)(oa != NULL));
        return NULL;
    }

    return obj;
}

/* Object__destruct__S */
xdc_Void xdc_runtime_knl_GateThread_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_knl_GateThread_Object__DESC__C, obj, (xdc_Fxn)xdc_runtime_knl_GateThread_Instance_finalize__F, 0, TRUE);
}

/* Object__delete__S */
xdc_Void xdc_runtime_knl_GateThread_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_knl_GateThread_Object__DESC__C, *((xdc_runtime_knl_GateThread_Object**)instp), (xdc_Fxn)xdc_runtime_knl_GateThread_Instance_finalize__F, 0, FALSE);
    *((xdc_runtime_knl_GateThread_Handle*)instp) = NULL;
}


/*
 * ======== xdc.runtime.knl.GateThread_Proxy SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_knl_GateThread_Proxy_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_knl_GateThread_Proxy_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_knl_GateThread_Proxy_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_knl_GateThread_Proxy_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_knl_GateThread_Proxy_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_knl_GateThread_Proxy_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_knl_GateThread_Proxy_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_knl_GateThread_Proxy_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_knl_GateThread_Proxy_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_knl_GateThread_Proxy_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_knl_GateThread_Proxy_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_knl_GateThread_Proxy_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_knl_GateThread_Proxy_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_knl_GateThread_Proxy_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_knl_GateThread_Proxy_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_knl_GateThread_Proxy_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_knl_GateThread_Proxy_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_knl_GateThread_Proxy_Module_GateProxy_query
xdc_Bool xdc_runtime_knl_GateThread_Proxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr xdc_runtime_knl_GateThread_Proxy_Proxy__delegate__S( void )
{
    return 0;
}



/*
 * ======== xdc.runtime.knl.SemProcess SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_knl_SemProcess_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_knl_SemProcess_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_knl_SemProcess_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_knl_SemProcess_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_knl_SemProcess_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_knl_SemProcess_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_knl_SemProcess_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_knl_SemProcess_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_knl_SemProcess_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_knl_SemProcess_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_knl_SemProcess_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_knl_SemProcess_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_knl_SemProcess_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_knl_SemProcess_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_knl_SemProcess_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_knl_SemProcess_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_knl_SemProcess_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_knl_SemProcess_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool xdc_runtime_knl_SemProcess_Module__startupDone__S( void ) 
{
    return 1;
}

/* Handle__label__S */
xdc_runtime_Types_Label* xdc_runtime_knl_SemProcess_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) 
{
    lab->handle = obj;
    lab->modId = 32790;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void xdc_runtime_knl_SemProcess_Params__init__S( xdc_Ptr prms, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &xdc_runtime_knl_SemProcess_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr xdc_runtime_knl_SemProcess_Object__get__S( xdc_Ptr oa, xdc_Int i ) 
{
    if (oa) {
        return ((xdc_runtime_knl_SemProcess_Object__*)oa) + i;
    }

    if (xdc_runtime_knl_SemProcess_Object__count__C == 0) {
        return NULL;
    }

    return ((xdc_runtime_knl_SemProcess_Object__*)xdc_runtime_knl_SemProcess_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr xdc_runtime_knl_SemProcess_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)xdc_runtime_knl_SemProcess_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&xdc_runtime_knl_SemProcess_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr xdc_runtime_knl_SemProcess_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&xdc_runtime_knl_SemProcess_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr xdc_runtime_knl_SemProcess_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const xdc_runtime_knl_SemProcess___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    xdc_runtime_knl_SemProcess_Params prms;
    xdc_runtime_knl_SemProcess_Object* obj;
    int iStat;

    xdc_runtime_knl_SemProcess_Args__create* args = aa;
    /* common instance initialization */
    obj = xdc_runtime_Core_createObject__I(&xdc_runtime_knl_SemProcess_Object__DESC__C, oa, osz, &prms, (xdc_Ptr)pa, psz, eb);
    if (obj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    iStat = xdc_runtime_knl_SemProcess_Instance_init__F(obj, args->count, args->key, &prms, eb);
    if (xdc_runtime_Error_check(eb)) {
        xdc_runtime_Core_deleteObject__I(&xdc_runtime_knl_SemProcess_Object__DESC__C, obj, (xdc_Fxn)xdc_runtime_knl_SemProcess_Instance_finalize__F, iStat, (xdc_Bool)(oa != NULL));
        return NULL;
    }

    return obj;
}

/* Object__destruct__S */
xdc_Void xdc_runtime_knl_SemProcess_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_knl_SemProcess_Object__DESC__C, obj, (xdc_Fxn)xdc_runtime_knl_SemProcess_Instance_finalize__F, 0, TRUE);
}

/* Object__delete__S */
xdc_Void xdc_runtime_knl_SemProcess_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_knl_SemProcess_Object__DESC__C, *((xdc_runtime_knl_SemProcess_Object**)instp), (xdc_Fxn)xdc_runtime_knl_SemProcess_Instance_finalize__F, 0, FALSE);
    *((xdc_runtime_knl_SemProcess_Handle*)instp) = NULL;
}


/*
 * ======== xdc.runtime.knl.SemProcess_Proxy SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_knl_SemProcess_Proxy_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_knl_SemProcess_Proxy_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_knl_SemProcess_Proxy_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_knl_SemProcess_Proxy_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_knl_SemProcess_Proxy_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_knl_SemProcess_Proxy_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_knl_SemProcess_Proxy_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_knl_SemProcess_Proxy_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_knl_SemProcess_Proxy_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_knl_SemProcess_Proxy_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_knl_SemProcess_Proxy_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_knl_SemProcess_Proxy_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_knl_SemProcess_Proxy_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_knl_SemProcess_Proxy_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_knl_SemProcess_Proxy_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_knl_SemProcess_Proxy_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_knl_SemProcess_Proxy_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_knl_SemProcess_Proxy_Module_GateProxy_query
xdc_Bool xdc_runtime_knl_SemProcess_Proxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr xdc_runtime_knl_SemProcess_Proxy_Proxy__delegate__S( void )
{
    return 0;
}



/*
 * ======== xdc.runtime.knl.SemThread SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_knl_SemThread_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_knl_SemThread_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_knl_SemThread_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_knl_SemThread_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_knl_SemThread_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_knl_SemThread_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_knl_SemThread_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_knl_SemThread_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_knl_SemThread_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_knl_SemThread_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_knl_SemThread_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_knl_SemThread_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_knl_SemThread_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_knl_SemThread_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_knl_SemThread_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_knl_SemThread_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_knl_SemThread_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_knl_SemThread_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool xdc_runtime_knl_SemThread_Module__startupDone__S( void ) 
{
    return 1;
}

/* Handle__label__S */
xdc_runtime_Types_Label* xdc_runtime_knl_SemThread_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) 
{
    lab->handle = obj;
    lab->modId = 32789;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void xdc_runtime_knl_SemThread_Params__init__S( xdc_Ptr prms, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &xdc_runtime_knl_SemThread_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr xdc_runtime_knl_SemThread_Object__get__S( xdc_Ptr oa, xdc_Int i ) 
{
    if (oa) {
        return ((xdc_runtime_knl_SemThread_Object__*)oa) + i;
    }

    if (xdc_runtime_knl_SemThread_Object__count__C == 0) {
        return NULL;
    }

    return ((xdc_runtime_knl_SemThread_Object__*)xdc_runtime_knl_SemThread_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr xdc_runtime_knl_SemThread_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)xdc_runtime_knl_SemThread_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&xdc_runtime_knl_SemThread_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr xdc_runtime_knl_SemThread_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&xdc_runtime_knl_SemThread_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr xdc_runtime_knl_SemThread_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const xdc_runtime_knl_SemThread___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    xdc_runtime_knl_SemThread_Params prms;
    xdc_runtime_knl_SemThread_Object* obj;
    int iStat;

    xdc_runtime_knl_SemThread_Args__create* args = aa;
    /* common instance initialization */
    obj = xdc_runtime_Core_createObject__I(&xdc_runtime_knl_SemThread_Object__DESC__C, oa, osz, &prms, (xdc_Ptr)pa, psz, eb);
    if (obj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    iStat = xdc_runtime_knl_SemThread_Instance_init__F(obj, args->count, &prms, eb);
    if (xdc_runtime_Error_check(eb)) {
        xdc_runtime_Core_deleteObject__I(&xdc_runtime_knl_SemThread_Object__DESC__C, obj, (xdc_Fxn)xdc_runtime_knl_SemThread_Instance_finalize__F, iStat, (xdc_Bool)(oa != NULL));
        return NULL;
    }

    return obj;
}

/* Object__destruct__S */
xdc_Void xdc_runtime_knl_SemThread_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_knl_SemThread_Object__DESC__C, obj, (xdc_Fxn)xdc_runtime_knl_SemThread_Instance_finalize__F, 0, TRUE);
}

/* Object__delete__S */
xdc_Void xdc_runtime_knl_SemThread_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_knl_SemThread_Object__DESC__C, *((xdc_runtime_knl_SemThread_Object**)instp), (xdc_Fxn)xdc_runtime_knl_SemThread_Instance_finalize__F, 0, FALSE);
    *((xdc_runtime_knl_SemThread_Handle*)instp) = NULL;
}


/*
 * ======== xdc.runtime.knl.SemThread_Proxy SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_knl_SemThread_Proxy_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_knl_SemThread_Proxy_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_knl_SemThread_Proxy_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_knl_SemThread_Proxy_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_knl_SemThread_Proxy_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_knl_SemThread_Proxy_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_knl_SemThread_Proxy_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_knl_SemThread_Proxy_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_knl_SemThread_Proxy_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_knl_SemThread_Proxy_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_knl_SemThread_Proxy_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_knl_SemThread_Proxy_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_knl_SemThread_Proxy_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_knl_SemThread_Proxy_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_knl_SemThread_Proxy_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_knl_SemThread_Proxy_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_knl_SemThread_Proxy_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_knl_SemThread_Proxy_Module_GateProxy_query
xdc_Bool xdc_runtime_knl_SemThread_Proxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr xdc_runtime_knl_SemThread_Proxy_Proxy__delegate__S( void )
{
    return 0;
}



/*
 * ======== xdc.runtime.knl.Thread SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_knl_Thread_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_knl_Thread_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_knl_Thread_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_knl_Thread_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_knl_Thread_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_knl_Thread_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_knl_Thread_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_knl_Thread_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_knl_Thread_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_knl_Thread_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_knl_Thread_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_knl_Thread_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_knl_Thread_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_knl_Thread_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_knl_Thread_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_knl_Thread_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_knl_Thread_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_knl_Thread_Module_GateProxy_query

/* Module__startupDone__S */
xdc_Bool xdc_runtime_knl_Thread_Module__startupDone__S( void ) 
{
    return 1;
}

/* Handle__label__S */
xdc_runtime_Types_Label* xdc_runtime_knl_Thread_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) 
{
    lab->handle = obj;
    lab->modId = 32787;
    xdc_runtime_Core_assignLabel(lab, 0, 0);

    return lab;
}

/* Params__init__S */
xdc_Void xdc_runtime_knl_Thread_Params__init__S( xdc_Ptr prms, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) 
{
    xdc_runtime_Core_assignParams__I(prms, (xdc_Ptr)(src ? src : &xdc_runtime_knl_Thread_Object__PARAMS__C), psz, isz);
}

/* Object__get__S */
xdc_Ptr xdc_runtime_knl_Thread_Object__get__S( xdc_Ptr oa, xdc_Int i ) 
{
    if (oa) {
        return ((xdc_runtime_knl_Thread_Object__*)oa) + i;
    }

    if (xdc_runtime_knl_Thread_Object__count__C == 0) {
        return NULL;
    }

    return ((xdc_runtime_knl_Thread_Object__*)xdc_runtime_knl_Thread_Object__table__C) + i;
}

/* Object__first__S */
xdc_Ptr xdc_runtime_knl_Thread_Object__first__S( void ) 
{
    xdc_runtime_Types_InstHdr *iHdr = (xdc_runtime_Types_InstHdr *)xdc_runtime_knl_Thread_Module__root__V.link.next;

    if (iHdr != (xdc_runtime_Types_InstHdr *)&xdc_runtime_knl_Thread_Module__root__V.link) {
        return iHdr + 1;
    }
    else {
        return NULL;
    }
}

/* Object__next__S */
xdc_Ptr xdc_runtime_knl_Thread_Object__next__S( xdc_Ptr obj ) 
{
    xdc_runtime_Types_InstHdr *iHdr = ((xdc_runtime_Types_InstHdr *)obj) - 1;

    if (iHdr->link.next != (xdc_runtime_Types_Link *)&xdc_runtime_knl_Thread_Module__root__V.link) {
        return (xdc_runtime_Types_InstHdr *)(iHdr->link.next) + 1;
    }
    else {
        return NULL;
    }
}

/* Object__create__S */
xdc_Ptr xdc_runtime_knl_Thread_Object__create__S (
    xdc_Ptr oa,
    xdc_SizeT osz,
    const xdc_Ptr aa,
    const xdc_runtime_knl_Thread___ParamsPtr pa,
    xdc_SizeT psz,
    xdc_runtime_Error_Block* eb )
{
    xdc_runtime_knl_Thread_Params prms;
    xdc_runtime_knl_Thread_Object* obj;
    int iStat;

    xdc_runtime_knl_Thread_Args__create* args = aa;
    /* common instance initialization */
    obj = xdc_runtime_Core_createObject__I(&xdc_runtime_knl_Thread_Object__DESC__C, oa, osz, &prms, (xdc_Ptr)pa, psz, eb);
    if (obj == NULL) {
        return NULL;
    }

    /* module-specific initialization */
    iStat = xdc_runtime_knl_Thread_Instance_init__F(obj, args->fxn, &prms, eb);
    if (xdc_runtime_Error_check(eb)) {
        xdc_runtime_Core_deleteObject__I(&xdc_runtime_knl_Thread_Object__DESC__C, obj, (xdc_Fxn)xdc_runtime_knl_Thread_Instance_finalize__F, iStat, (xdc_Bool)(oa != NULL));
        return NULL;
    }

    return obj;
}

/* Object__destruct__S */
xdc_Void xdc_runtime_knl_Thread_Object__destruct__S( xdc_Ptr obj ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_knl_Thread_Object__DESC__C, obj, (xdc_Fxn)xdc_runtime_knl_Thread_Instance_finalize__F, 0, TRUE);
}

/* Object__delete__S */
xdc_Void xdc_runtime_knl_Thread_Object__delete__S( xdc_Ptr instp ) 
{
    xdc_runtime_Core_deleteObject__I(&xdc_runtime_knl_Thread_Object__DESC__C, *((xdc_runtime_knl_Thread_Object**)instp), (xdc_Fxn)xdc_runtime_knl_Thread_Instance_finalize__F, 0, FALSE);
    *((xdc_runtime_knl_Thread_Handle*)instp) = NULL;
}


/*
 * ======== xdc.runtime.knl.Thread_Proxy SYSTEM FUNCTIONS ========
 */

/* per-module runtime symbols */
#undef Module__MID
#define Module__MID xdc_runtime_knl_Thread_Proxy_Module__id__C
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_knl_Thread_Proxy_Module__diagsIncluded__C
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_knl_Thread_Proxy_Module__diagsEnabled__C
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_knl_Thread_Proxy_Module__diagsMask__C
#undef Module__LOGDEF
#define Module__LOGDEF xdc_runtime_knl_Thread_Proxy_Module__loggerDefined__C
#undef Module__LOGOBJ
#define Module__LOGOBJ xdc_runtime_knl_Thread_Proxy_Module__loggerObj__C
#undef Module__LOGFXN0
#define Module__LOGFXN0 xdc_runtime_knl_Thread_Proxy_Module__loggerFxn0__C
#undef Module__LOGFXN1
#define Module__LOGFXN1 xdc_runtime_knl_Thread_Proxy_Module__loggerFxn1__C
#undef Module__LOGFXN2
#define Module__LOGFXN2 xdc_runtime_knl_Thread_Proxy_Module__loggerFxn2__C
#undef Module__LOGFXN4
#define Module__LOGFXN4 xdc_runtime_knl_Thread_Proxy_Module__loggerFxn4__C
#undef Module__LOGFXN8
#define Module__LOGFXN8 xdc_runtime_knl_Thread_Proxy_Module__loggerFxn8__C
#undef Module__G_OBJ
#define Module__G_OBJ xdc_runtime_knl_Thread_Proxy_Module__gateObj__C
#undef Module__G_PRMS
#define Module__G_PRMS xdc_runtime_knl_Thread_Proxy_Module__gatePrms__C
#undef Module__GP_create
#define Module__GP_create xdc_runtime_knl_Thread_Proxy_Module_GateProxy_create
#undef Module__GP_delete
#define Module__GP_delete xdc_runtime_knl_Thread_Proxy_Module_GateProxy_delete
#undef Module__GP_enter
#define Module__GP_enter xdc_runtime_knl_Thread_Proxy_Module_GateProxy_enter
#undef Module__GP_leave
#define Module__GP_leave xdc_runtime_knl_Thread_Proxy_Module_GateProxy_leave
#undef Module__GP_query
#define Module__GP_query xdc_runtime_knl_Thread_Proxy_Module_GateProxy_query
xdc_Bool xdc_runtime_knl_Thread_Proxy_Proxy__abstract__S( void )
{
    return 0;
}
xdc_Ptr xdc_runtime_knl_Thread_Proxy_Proxy__delegate__S( void )
{
    return 0;
}



/*
 * ======== ti.sdo.utils.loggers.LogMFP PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__ti_sdo_utils_loggers_LogMFP_Module__diagsEnabled ti_sdo_utils_loggers_LogMFP_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Module__diagsIncluded ti_sdo_utils_loggers_LogMFP_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Module__diagsMask ti_sdo_utils_loggers_LogMFP_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Module__gateObj ti_sdo_utils_loggers_LogMFP_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Module__gatePrms ti_sdo_utils_loggers_LogMFP_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Module__id ti_sdo_utils_loggers_LogMFP_Module__id__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerDefined ti_sdo_utils_loggers_LogMFP_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerObj ti_sdo_utils_loggers_LogMFP_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn0 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn1 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn2 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn4 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Module__loggerFxn8 ti_sdo_utils_loggers_LogMFP_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Module__startupDoneFxn ti_sdo_utils_loggers_LogMFP_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Object__count ti_sdo_utils_loggers_LogMFP_Object__count__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Object__heap ti_sdo_utils_loggers_LogMFP_Object__heap__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Object__sizeof ti_sdo_utils_loggers_LogMFP_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LogMFP_Object__table ti_sdo_utils_loggers_LogMFP_Object__table__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* ti_sdo_utils_loggers_LogMFP_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_utils_loggers_LogMFP_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LogMFP_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LogMFP_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LogMFP_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LogMFP_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LogMFP_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LogMFP_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LogMFP_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_utils_loggers_LogMFP_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LogMFP_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LogMFP_control__E( xdc_Int cmd, xdc_UArg cmdArgs ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== ti.sdo.utils.loggers.LoggerMFPNull PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsEnabled ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsIncluded ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsMask ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__gateObj ti_sdo_utils_loggers_LoggerMFPNull_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__gatePrms ti_sdo_utils_loggers_LoggerMFPNull_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__id ti_sdo_utils_loggers_LoggerMFPNull_Module__id__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerDefined ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerObj ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn0 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn1 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn2 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn4 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn8 ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Module__startupDoneFxn ti_sdo_utils_loggers_LoggerMFPNull_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Object__count ti_sdo_utils_loggers_LoggerMFPNull_Object__count__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Object__heap ti_sdo_utils_loggers_LoggerMFPNull_Object__heap__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Object__sizeof ti_sdo_utils_loggers_LoggerMFPNull_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerMFPNull_Object__table ti_sdo_utils_loggers_LoggerMFPNull_Object__table__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* ti_sdo_utils_loggers_LoggerMFPNull_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_utils_loggers_LoggerMFPNull_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LoggerMFPNull_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LoggerMFPNull_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LoggerMFPNull_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LoggerMFPNull_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_utils_loggers_LoggerMFPNull_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LoggerMFPNull_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_utils_loggers_LoggerMFPNull_enable__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_utils_loggers_LoggerMFPNull_disable__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_write0__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_write1__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1 ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_write2__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2 ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_write4__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4 ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_write8__E( ti_sdo_utils_loggers_LoggerMFPNull_Handle, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8 ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerMFPNull_control__E( xdc_Int cmd, xdc_UArg cmdArgs ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== ti.sdo.utils.loggers.LoggerSysTID PRAGMAS ========
 */


#ifdef __ti__
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_Module__startupDone__S);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_Handle__label__S);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_Object__create__S);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_Object__delete__S);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_Object__destruct__S);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_Object__get__S);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_Object__first__S);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_Object__next__S);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_Params__init__S);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_Module_startup__E);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_enable__E);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_disable__E);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_write0__E);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_write1__E);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_write2__E);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_write4__E);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_write8__E);
    #pragma FUNC_EXT_CALLED(ti_sdo_utils_loggers_LoggerSysTID_control__E);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__diagsEnabled ti_sdo_utils_loggers_LoggerSysTID_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__diagsIncluded ti_sdo_utils_loggers_LoggerSysTID_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__diagsMask ti_sdo_utils_loggers_LoggerSysTID_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__gateObj ti_sdo_utils_loggers_LoggerSysTID_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__gatePrms ti_sdo_utils_loggers_LoggerSysTID_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__id ti_sdo_utils_loggers_LoggerSysTID_Module__id__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerDefined ti_sdo_utils_loggers_LoggerSysTID_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerObj ti_sdo_utils_loggers_LoggerSysTID_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn0 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn1 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn2 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn4 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn8 ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Module__startupDoneFxn ti_sdo_utils_loggers_LoggerSysTID_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Object__count ti_sdo_utils_loggers_LoggerSysTID_Object__count__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Object__heap ti_sdo_utils_loggers_LoggerSysTID_Object__heap__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Object__sizeof ti_sdo_utils_loggers_LoggerSysTID_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_Object__table ti_sdo_utils_loggers_LoggerSysTID_Object__table__C __attribute__ ((externally_visible));
    const CT__ti_sdo_utils_loggers_LoggerSysTID_gate ti_sdo_utils_loggers_LoggerSysTID_gate__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* ti_sdo_utils_loggers_LoggerSysTID_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_utils_loggers_LoggerSysTID_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LoggerSysTID_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerSysTID_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerSysTID_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LoggerSysTID_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LoggerSysTID_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LoggerSysTID_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerSysTID_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_utils_loggers_LoggerSysTID_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_utils_loggers_LoggerSysTID_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_utils_loggers_LoggerSysTID_enable__E( ti_sdo_utils_loggers_LoggerSysTID_Handle ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_utils_loggers_LoggerSysTID_disable__E( ti_sdo_utils_loggers_LoggerSysTID_Handle ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerSysTID_write0__E( ti_sdo_utils_loggers_LoggerSysTID_Handle, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerSysTID_write1__E( ti_sdo_utils_loggers_LoggerSysTID_Handle, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1 ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerSysTID_write2__E( ti_sdo_utils_loggers_LoggerSysTID_Handle, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2 ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerSysTID_write4__E( ti_sdo_utils_loggers_LoggerSysTID_Handle, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4 ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerSysTID_write8__E( ti_sdo_utils_loggers_LoggerSysTID_Handle, xdc_runtime_Log_Event evt, xdc_runtime_Types_ModuleId mid, xdc_IArg a1, xdc_IArg a2, xdc_IArg a3, xdc_IArg a4, xdc_IArg a5, xdc_IArg a6, xdc_IArg a7, xdc_IArg a8 ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_utils_loggers_LoggerSysTID_control__E( xdc_Int cmd, xdc_UArg cmdArgs ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== ti.sdo.xdcruntime.linux.GateThreadSupport PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsEnabled ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsIncluded ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsMask ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gateObj ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gatePrms ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__id ti_sdo_xdcruntime_linux_GateThreadSupport_Module__id__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerDefined ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerObj ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn0 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn1 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn2 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn4 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn8 ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDoneFxn ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Object__count ti_sdo_xdcruntime_linux_GateThreadSupport_Object__count__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Object__heap ti_sdo_xdcruntime_linux_GateThreadSupport_Object__heap__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Object__sizeof ti_sdo_xdcruntime_linux_GateThreadSupport_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_A_POSIX_Error ti_sdo_xdcruntime_linux_GateThreadSupport_A_POSIX_Error__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_GateThreadSupport_E_POSIX_Error ti_sdo_xdcruntime_linux_GateThreadSupport_E_POSIX_Error__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* ti_sdo_xdcruntime_linux_GateThreadSupport_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_GateThreadSupport_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_GateThreadSupport_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_GateThreadSupport_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_GateThreadSupport_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_GateThreadSupport_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_GateThreadSupport_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_GateThreadSupport_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_GateThreadSupport_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_GateThreadSupport_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_GateThreadSupport_query__E( xdc_Int qual ) __attribute__ ((externally_visible));
    xdc_IArg ti_sdo_xdcruntime_linux_GateThreadSupport_enter__E( ti_sdo_xdcruntime_linux_GateThreadSupport_Handle ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_GateThreadSupport_leave__E( ti_sdo_xdcruntime_linux_GateThreadSupport_Handle, xdc_IArg key ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== ti.sdo.xdcruntime.linux.SemProcessSupport PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsEnabled ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsIncluded ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsMask ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gateObj ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gatePrms ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__id ti_sdo_xdcruntime_linux_SemProcessSupport_Module__id__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerDefined ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerObj ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn0 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn1 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn2 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn4 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn8 ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDoneFxn ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Object__count ti_sdo_xdcruntime_linux_SemProcessSupport_Object__count__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Object__heap ti_sdo_xdcruntime_linux_SemProcessSupport_Object__heap__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Object__sizeof ti_sdo_xdcruntime_linux_SemProcessSupport_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_Object__table ti_sdo_xdcruntime_linux_SemProcessSupport_Object__table__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_A_unsupportedTimeout ti_sdo_xdcruntime_linux_SemProcessSupport_A_unsupportedTimeout__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_A_invalidKey ti_sdo_xdcruntime_linux_SemProcessSupport_A_invalidKey__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_A_POSIX_Error ti_sdo_xdcruntime_linux_SemProcessSupport_A_POSIX_Error__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_E_POSIX_Error ti_sdo_xdcruntime_linux_SemProcessSupport_E_POSIX_Error__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_L_extant ti_sdo_xdcruntime_linux_SemProcessSupport_L_extant__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_L_create ti_sdo_xdcruntime_linux_SemProcessSupport_L_create__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemProcessSupport_perms ti_sdo_xdcruntime_linux_SemProcessSupport_perms__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* ti_sdo_xdcruntime_linux_SemProcessSupport_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_SemProcessSupport_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_SemProcessSupport_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_SemProcessSupport_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_SemProcessSupport_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_SemProcessSupport_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_SemProcessSupport_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_SemProcessSupport_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_SemProcessSupport_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_SemProcessSupport_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Int ti_sdo_xdcruntime_linux_SemProcessSupport_pend__E( ti_sdo_xdcruntime_linux_SemProcessSupport_Handle, xdc_UInt timeout, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_SemProcessSupport_post__E( ti_sdo_xdcruntime_linux_SemProcessSupport_Handle, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== ti.sdo.xdcruntime.linux.SemThreadSupport PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsEnabled ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsIncluded ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsMask ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gateObj ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gatePrms ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__id ti_sdo_xdcruntime_linux_SemThreadSupport_Module__id__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerDefined ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerObj ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn0 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn1 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn2 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn4 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn8 ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDoneFxn ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Object__count ti_sdo_xdcruntime_linux_SemThreadSupport_Object__count__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Object__heap ti_sdo_xdcruntime_linux_SemThreadSupport_Object__heap__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Object__sizeof ti_sdo_xdcruntime_linux_SemThreadSupport_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_Object__table ti_sdo_xdcruntime_linux_SemThreadSupport_Object__table__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_A_POSIX_Error ti_sdo_xdcruntime_linux_SemThreadSupport_A_POSIX_Error__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_E_POSIX_Error ti_sdo_xdcruntime_linux_SemThreadSupport_E_POSIX_Error__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_SemThreadSupport_E_resetError ti_sdo_xdcruntime_linux_SemThreadSupport_E_resetError__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* ti_sdo_xdcruntime_linux_SemThreadSupport_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_SemThreadSupport_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_SemThreadSupport_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_SemThreadSupport_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_SemThreadSupport_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_SemThreadSupport_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_SemThreadSupport_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_SemThreadSupport_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_SemThreadSupport_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_SemThreadSupport_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Int ti_sdo_xdcruntime_linux_SemThreadSupport_pend__E( ti_sdo_xdcruntime_linux_SemThreadSupport_Handle, xdc_UInt timeout, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_SemThreadSupport_post__E( ti_sdo_xdcruntime_linux_SemThreadSupport_Handle, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== ti.sdo.xdcruntime.linux.ThreadSupport PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsEnabled ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsIncluded ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsMask ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__gateObj ti_sdo_xdcruntime_linux_ThreadSupport_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__gatePrms ti_sdo_xdcruntime_linux_ThreadSupport_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__id ti_sdo_xdcruntime_linux_ThreadSupport_Module__id__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerDefined ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerObj ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn0 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn1 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn2 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn4 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn8 ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDoneFxn ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Object__count ti_sdo_xdcruntime_linux_ThreadSupport_Object__count__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Object__heap ti_sdo_xdcruntime_linux_ThreadSupport_Object__heap__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Object__sizeof ti_sdo_xdcruntime_linux_ThreadSupport_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_Object__table ti_sdo_xdcruntime_linux_ThreadSupport_Object__table__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_E_priority ti_sdo_xdcruntime_linux_ThreadSupport_E_priority__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_A_POSIX_Error ti_sdo_xdcruntime_linux_ThreadSupport_A_POSIX_Error__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_E_POSIX_Error ti_sdo_xdcruntime_linux_ThreadSupport_E_POSIX_Error__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_L_start ti_sdo_xdcruntime_linux_ThreadSupport_L_start__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_L_finish ti_sdo_xdcruntime_linux_ThreadSupport_L_finish__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_ThreadSupport_L_join ti_sdo_xdcruntime_linux_ThreadSupport_L_join__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* ti_sdo_xdcruntime_linux_ThreadSupport_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_ThreadSupport_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_ThreadSupport_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_ThreadSupport_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_ThreadSupport_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_ThreadSupport_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_ThreadSupport_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_ThreadSupport_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_ThreadSupport_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_runtime_knl_IThreadSupport_Handle ti_sdo_xdcruntime_linux_ThreadSupport_self__E( xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_start__E( xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_yield__E( xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Int ti_sdo_xdcruntime_linux_ThreadSupport_compareOsPriorities__E( xdc_Int p1, xdc_Int p2, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_sleep__E( xdc_UInt timeout, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_join__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_runtime_knl_IThreadSupport_Priority ti_sdo_xdcruntime_linux_ThreadSupport_getPriority__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_setPriority__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle, xdc_runtime_knl_IThreadSupport_Priority newPri, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Int ti_sdo_xdcruntime_linux_ThreadSupport_getOsPriority__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_setOsPriority__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle, xdc_Int newPri, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_ThreadSupport_getOsHandle__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_ThreadSupport_getTls__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_ThreadSupport_setTls__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle, xdc_Ptr tls ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_ThreadSupport_stat__E( ti_sdo_xdcruntime_linux_ThreadSupport_Handle, xdc_runtime_knl_IThreadSupport_Stat* buf, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== ti.sdo.xdcruntime.linux.TimestampPosix PRAGMAS ========
 */


#ifdef __ti__
    #pragma FUNC_EXT_CALLED(ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDone__S);
    #pragma FUNC_EXT_CALLED(ti_sdo_xdcruntime_linux_TimestampPosix_get32__E);
    #pragma FUNC_EXT_CALLED(ti_sdo_xdcruntime_linux_TimestampPosix_get64__E);
    #pragma FUNC_EXT_CALLED(ti_sdo_xdcruntime_linux_TimestampPosix_getFreq__E);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsEnabled ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsIncluded ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsMask ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__gateObj ti_sdo_xdcruntime_linux_TimestampPosix_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__gatePrms ti_sdo_xdcruntime_linux_TimestampPosix_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__id ti_sdo_xdcruntime_linux_TimestampPosix_Module__id__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerDefined ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerObj ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn0 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn1 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn2 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn4 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn8 ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDoneFxn ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Object__count ti_sdo_xdcruntime_linux_TimestampPosix_Object__count__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Object__heap ti_sdo_xdcruntime_linux_TimestampPosix_Object__heap__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Object__sizeof ti_sdo_xdcruntime_linux_TimestampPosix_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__ti_sdo_xdcruntime_linux_TimestampPosix_Object__table ti_sdo_xdcruntime_linux_TimestampPosix_Object__table__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* ti_sdo_xdcruntime_linux_TimestampPosix_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_TimestampPosix_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_TimestampPosix_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_TimestampPosix_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_TimestampPosix_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_TimestampPosix_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_TimestampPosix_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_TimestampPosix_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool ti_sdo_xdcruntime_linux_TimestampPosix_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr ti_sdo_xdcruntime_linux_TimestampPosix_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Bits32 ti_sdo_xdcruntime_linux_TimestampPosix_get32__E( void ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_TimestampPosix_get64__E( xdc_runtime_Types_Timestamp64* result ) __attribute__ ((externally_visible));
    xdc_Void ti_sdo_xdcruntime_linux_TimestampPosix_getFreq__E( xdc_runtime_Types_FreqHz* freq ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.Assert PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_Assert_Module__diagsEnabled xdc_runtime_Assert_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Module__diagsIncluded xdc_runtime_Assert_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Module__diagsMask xdc_runtime_Assert_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Module__gateObj xdc_runtime_Assert_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Module__gatePrms xdc_runtime_Assert_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Module__id xdc_runtime_Assert_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Module__loggerDefined xdc_runtime_Assert_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Module__loggerObj xdc_runtime_Assert_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Module__loggerFxn0 xdc_runtime_Assert_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Module__loggerFxn1 xdc_runtime_Assert_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Module__loggerFxn2 xdc_runtime_Assert_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Module__loggerFxn4 xdc_runtime_Assert_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Module__loggerFxn8 xdc_runtime_Assert_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Module__startupDoneFxn xdc_runtime_Assert_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Object__count xdc_runtime_Assert_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Object__heap xdc_runtime_Assert_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Object__sizeof xdc_runtime_Assert_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_Object__table xdc_runtime_Assert_Object__table__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Assert_E_assertFailed xdc_runtime_Assert_E_assertFailed__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_Assert_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Assert_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Assert_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Assert_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Assert_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Assert_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Assert_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Assert_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Assert_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Assert_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Assert_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.Core PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_Core_Module__diagsEnabled xdc_runtime_Core_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Module__diagsIncluded xdc_runtime_Core_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Module__diagsMask xdc_runtime_Core_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Module__gateObj xdc_runtime_Core_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Module__gatePrms xdc_runtime_Core_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Module__id xdc_runtime_Core_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Module__loggerDefined xdc_runtime_Core_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Module__loggerObj xdc_runtime_Core_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Module__loggerFxn0 xdc_runtime_Core_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Module__loggerFxn1 xdc_runtime_Core_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Module__loggerFxn2 xdc_runtime_Core_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Module__loggerFxn4 xdc_runtime_Core_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Module__loggerFxn8 xdc_runtime_Core_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Module__startupDoneFxn xdc_runtime_Core_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Object__count xdc_runtime_Core_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Object__heap xdc_runtime_Core_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Object__sizeof xdc_runtime_Core_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_Object__table xdc_runtime_Core_Object__table__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Core_A_initializedParams xdc_runtime_Core_A_initializedParams__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_Core_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Core_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Core_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Core_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Core_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Core_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Core_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Core_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Core_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Core_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Core_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.Defaults PRAGMAS ========
 */


#ifdef __ti__
    #pragma FUNC_EXT_CALLED(xdc_runtime_Defaults_Module__startupDone__S);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_Defaults_Module__diagsEnabled xdc_runtime_Defaults_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Module__diagsIncluded xdc_runtime_Defaults_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Module__diagsMask xdc_runtime_Defaults_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Module__gateObj xdc_runtime_Defaults_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Module__gatePrms xdc_runtime_Defaults_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Module__id xdc_runtime_Defaults_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Module__loggerDefined xdc_runtime_Defaults_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Module__loggerObj xdc_runtime_Defaults_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Module__loggerFxn0 xdc_runtime_Defaults_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Module__loggerFxn1 xdc_runtime_Defaults_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Module__loggerFxn2 xdc_runtime_Defaults_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Module__loggerFxn4 xdc_runtime_Defaults_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Module__loggerFxn8 xdc_runtime_Defaults_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Module__startupDoneFxn xdc_runtime_Defaults_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Object__count xdc_runtime_Defaults_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Object__heap xdc_runtime_Defaults_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Object__sizeof xdc_runtime_Defaults_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Defaults_Object__table xdc_runtime_Defaults_Object__table__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_Defaults_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Defaults_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Defaults_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Defaults_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Defaults_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Defaults_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Defaults_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Defaults_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Defaults_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Defaults_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Defaults_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.Diags PRAGMAS ========
 */


#ifdef __ti__
    #pragma FUNC_EXT_CALLED(xdc_runtime_Diags_Module__startupDone__S);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Diags_setMask__E);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_Diags_Module__diagsEnabled xdc_runtime_Diags_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Module__diagsIncluded xdc_runtime_Diags_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Module__diagsMask xdc_runtime_Diags_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Module__gateObj xdc_runtime_Diags_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Module__gatePrms xdc_runtime_Diags_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Module__id xdc_runtime_Diags_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Module__loggerDefined xdc_runtime_Diags_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Module__loggerObj xdc_runtime_Diags_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Module__loggerFxn0 xdc_runtime_Diags_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Module__loggerFxn1 xdc_runtime_Diags_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Module__loggerFxn2 xdc_runtime_Diags_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Module__loggerFxn4 xdc_runtime_Diags_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Module__loggerFxn8 xdc_runtime_Diags_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Module__startupDoneFxn xdc_runtime_Diags_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Object__count xdc_runtime_Diags_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Object__heap xdc_runtime_Diags_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Object__sizeof xdc_runtime_Diags_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_Object__table xdc_runtime_Diags_Object__table__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_setMaskEnabled xdc_runtime_Diags_setMaskEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Diags_dictBase xdc_runtime_Diags_dictBase__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_Diags_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Diags_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Diags_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Diags_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Diags_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Diags_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Diags_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Diags_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Diags_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Diags_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Diags_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Diags_setMask__E( xdc_String control ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.Error PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_Error_Module__diagsEnabled xdc_runtime_Error_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Module__diagsIncluded xdc_runtime_Error_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Module__diagsMask xdc_runtime_Error_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Module__gateObj xdc_runtime_Error_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Module__gatePrms xdc_runtime_Error_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Module__id xdc_runtime_Error_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Module__loggerDefined xdc_runtime_Error_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Module__loggerObj xdc_runtime_Error_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Module__loggerFxn0 xdc_runtime_Error_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Module__loggerFxn1 xdc_runtime_Error_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Module__loggerFxn2 xdc_runtime_Error_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Module__loggerFxn4 xdc_runtime_Error_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Module__loggerFxn8 xdc_runtime_Error_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Module__startupDoneFxn xdc_runtime_Error_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Object__count xdc_runtime_Error_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Object__heap xdc_runtime_Error_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Object__sizeof xdc_runtime_Error_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_Object__table xdc_runtime_Error_Object__table__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_E_generic xdc_runtime_Error_E_generic__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_E_memory xdc_runtime_Error_E_memory__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_E_msgCode xdc_runtime_Error_E_msgCode__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_policy xdc_runtime_Error_policy__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_raiseHook xdc_runtime_Error_raiseHook__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Error_maxDepth xdc_runtime_Error_maxDepth__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_Error_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Error_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Error_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Error_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Error_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Error_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Error_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Error_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Error_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Error_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Error_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Error_check__E( xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_runtime_Error_Data* xdc_runtime_Error_getData__E( xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_UInt16 xdc_runtime_Error_getCode__E( xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_runtime_Error_Id xdc_runtime_Error_getId__E( xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_String xdc_runtime_Error_getMsg__E( xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_runtime_Types_Site* xdc_runtime_Error_getSite__E( xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Error_init__E( xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Error_print__E( xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Error_raiseX__E( xdc_runtime_Error_Block* eb, xdc_runtime_Types_ModuleId mod, xdc_String file, xdc_Int line, xdc_runtime_Error_Id id, xdc_IArg arg1, xdc_IArg arg2 ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.Gate PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_Gate_Module__diagsEnabled xdc_runtime_Gate_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Module__diagsIncluded xdc_runtime_Gate_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Module__diagsMask xdc_runtime_Gate_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Module__gateObj xdc_runtime_Gate_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Module__gatePrms xdc_runtime_Gate_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Module__id xdc_runtime_Gate_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Module__loggerDefined xdc_runtime_Gate_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Module__loggerObj xdc_runtime_Gate_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Module__loggerFxn0 xdc_runtime_Gate_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Module__loggerFxn1 xdc_runtime_Gate_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Module__loggerFxn2 xdc_runtime_Gate_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Module__loggerFxn4 xdc_runtime_Gate_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Module__loggerFxn8 xdc_runtime_Gate_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Module__startupDoneFxn xdc_runtime_Gate_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Object__count xdc_runtime_Gate_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Object__heap xdc_runtime_Gate_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Object__sizeof xdc_runtime_Gate_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Gate_Object__table xdc_runtime_Gate_Object__table__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_Gate_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Gate_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Gate_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Gate_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Gate_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Gate_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Gate_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Gate_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Gate_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Gate_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Gate_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_IArg xdc_runtime_Gate_enterSystem__E( void ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Gate_leaveSystem__E( xdc_IArg key ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.HeapStd PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_HeapStd_Module__diagsEnabled xdc_runtime_HeapStd_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Module__diagsIncluded xdc_runtime_HeapStd_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Module__diagsMask xdc_runtime_HeapStd_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Module__gateObj xdc_runtime_HeapStd_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Module__gatePrms xdc_runtime_HeapStd_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Module__id xdc_runtime_HeapStd_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Module__loggerDefined xdc_runtime_HeapStd_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Module__loggerObj xdc_runtime_HeapStd_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Module__loggerFxn0 xdc_runtime_HeapStd_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Module__loggerFxn1 xdc_runtime_HeapStd_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Module__loggerFxn2 xdc_runtime_HeapStd_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Module__loggerFxn4 xdc_runtime_HeapStd_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Module__loggerFxn8 xdc_runtime_HeapStd_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Module__startupDoneFxn xdc_runtime_HeapStd_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Object__count xdc_runtime_HeapStd_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Object__heap xdc_runtime_HeapStd_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Object__sizeof xdc_runtime_HeapStd_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_Object__table xdc_runtime_HeapStd_Object__table__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_E_noRTSMemory xdc_runtime_HeapStd_E_noRTSMemory__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_A_zeroSize xdc_runtime_HeapStd_A_zeroSize__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_A_invalidTotalFreeSize xdc_runtime_HeapStd_A_invalidTotalFreeSize__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_HeapStd_A_invalidAlignment xdc_runtime_HeapStd_A_invalidAlignment__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_HeapStd_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_HeapStd_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_HeapStd_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_HeapStd_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_HeapStd_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_HeapStd_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_HeapStd_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_HeapStd_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_HeapStd_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_HeapStd_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_HeapStd_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_HeapStd_free__E( xdc_runtime_HeapStd_Handle, xdc_Ptr block, xdc_SizeT size ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_HeapStd_getStats__E( xdc_runtime_HeapStd_Handle, xdc_runtime_Memory_Stats* stats ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_HeapStd_alloc__E( xdc_runtime_HeapStd_Handle, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_HeapStd_isBlocking__E( xdc_runtime_HeapStd_Handle ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.Log PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_Log_Module__diagsEnabled xdc_runtime_Log_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Module__diagsIncluded xdc_runtime_Log_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Module__diagsMask xdc_runtime_Log_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Module__gateObj xdc_runtime_Log_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Module__gatePrms xdc_runtime_Log_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Module__id xdc_runtime_Log_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Module__loggerDefined xdc_runtime_Log_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Module__loggerObj xdc_runtime_Log_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Module__loggerFxn0 xdc_runtime_Log_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Module__loggerFxn1 xdc_runtime_Log_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Module__loggerFxn2 xdc_runtime_Log_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Module__loggerFxn4 xdc_runtime_Log_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Module__loggerFxn8 xdc_runtime_Log_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Module__startupDoneFxn xdc_runtime_Log_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Object__count xdc_runtime_Log_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Object__heap xdc_runtime_Log_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Object__sizeof xdc_runtime_Log_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_Object__table xdc_runtime_Log_Object__table__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_L_construct xdc_runtime_Log_L_construct__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_L_create xdc_runtime_Log_L_create__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_L_destruct xdc_runtime_Log_L_destruct__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_L_delete xdc_runtime_Log_L_delete__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_L_error xdc_runtime_Log_L_error__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_L_warning xdc_runtime_Log_L_warning__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Log_L_info xdc_runtime_Log_L_info__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_Log_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Log_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Log_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Log_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Log_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Log_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Log_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Log_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Log_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Log_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Log_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Log_doPrint__E( xdc_runtime_Log_EventRec* evRec ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.Main PRAGMAS ========
 */


#ifdef __ti__
    #pragma FUNC_EXT_CALLED(xdc_runtime_Main_Module__startupDone__S);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_Main_Module__diagsEnabled xdc_runtime_Main_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Module__diagsIncluded xdc_runtime_Main_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Module__diagsMask xdc_runtime_Main_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Module__gateObj xdc_runtime_Main_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Module__gatePrms xdc_runtime_Main_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Module__id xdc_runtime_Main_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Module__loggerDefined xdc_runtime_Main_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Module__loggerObj xdc_runtime_Main_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Module__loggerFxn0 xdc_runtime_Main_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Module__loggerFxn1 xdc_runtime_Main_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Module__loggerFxn2 xdc_runtime_Main_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Module__loggerFxn4 xdc_runtime_Main_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Module__loggerFxn8 xdc_runtime_Main_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Module__startupDoneFxn xdc_runtime_Main_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Object__count xdc_runtime_Main_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Object__heap xdc_runtime_Main_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Object__sizeof xdc_runtime_Main_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Main_Object__table xdc_runtime_Main_Object__table__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_Main_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Main_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Main_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Main_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Main_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Main_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Main_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Main_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Main_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Main_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Main_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.Memory PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_Memory_Module__diagsEnabled xdc_runtime_Memory_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Module__diagsIncluded xdc_runtime_Memory_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Module__diagsMask xdc_runtime_Memory_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Module__gateObj xdc_runtime_Memory_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Module__gatePrms xdc_runtime_Memory_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Module__id xdc_runtime_Memory_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Module__loggerDefined xdc_runtime_Memory_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Module__loggerObj xdc_runtime_Memory_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Module__loggerFxn0 xdc_runtime_Memory_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Module__loggerFxn1 xdc_runtime_Memory_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Module__loggerFxn2 xdc_runtime_Memory_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Module__loggerFxn4 xdc_runtime_Memory_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Module__loggerFxn8 xdc_runtime_Memory_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Module__startupDoneFxn xdc_runtime_Memory_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Object__count xdc_runtime_Memory_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Object__heap xdc_runtime_Memory_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Object__sizeof xdc_runtime_Memory_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_Object__table xdc_runtime_Memory_Object__table__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Memory_defaultHeapInstance xdc_runtime_Memory_defaultHeapInstance__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_Memory_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Memory_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Memory_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Memory_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Memory_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Memory_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Memory_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Memory_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Memory_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Memory_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Memory_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Memory_alloc__E( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Memory_calloc__E( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Memory_free__E( xdc_runtime_IHeap_Handle heap, xdc_Ptr block, xdc_SizeT size ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Memory_getStats__E( xdc_runtime_IHeap_Handle heap, xdc_runtime_Memory_Stats* stats ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Memory_query__E( xdc_runtime_IHeap_Handle heap, xdc_Int qual ) __attribute__ ((externally_visible));
    xdc_SizeT xdc_runtime_Memory_getMaxDefaultTypeAlign__E( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Memory_valloc__E( xdc_runtime_IHeap_Handle heap, xdc_SizeT size, xdc_SizeT align, xdc_Char value, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.Registry PRAGMAS ========
 */


#ifdef __ti__
    #pragma FUNC_EXT_CALLED(xdc_runtime_Registry_Module__startupDone__S);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Registry_addModule__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Registry_findByName__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Registry_findByNamePattern__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Registry_findById__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Registry_getMask__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Registry_isMember__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Registry_getNextModule__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Registry_getModuleName__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Registry_getModuleId__E);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_Registry_Module__diagsEnabled xdc_runtime_Registry_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Module__diagsIncluded xdc_runtime_Registry_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Module__diagsMask xdc_runtime_Registry_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Module__gateObj xdc_runtime_Registry_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Module__gatePrms xdc_runtime_Registry_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Module__id xdc_runtime_Registry_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Module__loggerDefined xdc_runtime_Registry_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Module__loggerObj xdc_runtime_Registry_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Module__loggerFxn0 xdc_runtime_Registry_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Module__loggerFxn1 xdc_runtime_Registry_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Module__loggerFxn2 xdc_runtime_Registry_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Module__loggerFxn4 xdc_runtime_Registry_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Module__loggerFxn8 xdc_runtime_Registry_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Module__startupDoneFxn xdc_runtime_Registry_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Object__count xdc_runtime_Registry_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Object__heap xdc_runtime_Registry_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Object__sizeof xdc_runtime_Registry_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Registry_Object__table xdc_runtime_Registry_Object__table__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_Registry_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Registry_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Registry_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Registry_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Registry_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Registry_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Registry_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Registry_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Registry_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Registry_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Registry_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_runtime_Registry_Result xdc_runtime_Registry_addModule__E( xdc_runtime_Registry_Desc* desc, xdc_String modName ) __attribute__ ((externally_visible));
    xdc_runtime_Registry_Desc* xdc_runtime_Registry_findByName__E( xdc_String modName ) __attribute__ ((externally_visible));
    xdc_runtime_Registry_Desc* xdc_runtime_Registry_findByNamePattern__E( xdc_String namePat, xdc_Int len, xdc_runtime_Registry_Desc* prev ) __attribute__ ((externally_visible));
    xdc_runtime_Registry_Desc* xdc_runtime_Registry_findById__E( xdc_runtime_Types_ModuleId mid ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Registry_getMask__E( xdc_String name, xdc_runtime_Types_DiagsMask* mask ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Registry_isMember__E( xdc_runtime_Types_ModuleId mid ) __attribute__ ((externally_visible));
    xdc_runtime_Registry_Desc* xdc_runtime_Registry_getNextModule__E( xdc_runtime_Registry_Desc* desc ) __attribute__ ((externally_visible));
    xdc_String xdc_runtime_Registry_getModuleName__E( xdc_runtime_Registry_Desc* desc ) __attribute__ ((externally_visible));
    xdc_runtime_Types_ModuleId xdc_runtime_Registry_getModuleId__E( xdc_runtime_Registry_Desc* desc ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.Startup PRAGMAS ========
 */


#ifdef __ti__
    #pragma FUNC_EXT_CALLED(xdc_runtime_Startup_Module__startupDone__S);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Startup_exec__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Startup_rtsDone__E);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_Startup_Module__diagsEnabled xdc_runtime_Startup_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Module__diagsIncluded xdc_runtime_Startup_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Module__diagsMask xdc_runtime_Startup_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Module__gateObj xdc_runtime_Startup_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Module__gatePrms xdc_runtime_Startup_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Module__id xdc_runtime_Startup_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Module__loggerDefined xdc_runtime_Startup_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Module__loggerObj xdc_runtime_Startup_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Module__loggerFxn0 xdc_runtime_Startup_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Module__loggerFxn1 xdc_runtime_Startup_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Module__loggerFxn2 xdc_runtime_Startup_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Module__loggerFxn4 xdc_runtime_Startup_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Module__loggerFxn8 xdc_runtime_Startup_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Module__startupDoneFxn xdc_runtime_Startup_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Object__count xdc_runtime_Startup_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Object__heap xdc_runtime_Startup_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Object__sizeof xdc_runtime_Startup_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_Object__table xdc_runtime_Startup_Object__table__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_maxPasses xdc_runtime_Startup_maxPasses__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_firstFxns xdc_runtime_Startup_firstFxns__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_lastFxns xdc_runtime_Startup_lastFxns__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_startModsFxn xdc_runtime_Startup_startModsFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_execImpl xdc_runtime_Startup_execImpl__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_sfxnTab xdc_runtime_Startup_sfxnTab__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Startup_sfxnRts xdc_runtime_Startup_sfxnRts__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_Startup_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Startup_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Startup_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Startup_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Startup_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Startup_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Startup_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Startup_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Startup_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Startup_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Startup_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Startup_exec__E( void ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Startup_rtsDone__E( void ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.SysStd PRAGMAS ========
 */


#ifdef __ti__
    #pragma FUNC_EXT_CALLED(xdc_runtime_SysStd_Module__startupDone__S);
    #pragma FUNC_EXT_CALLED(xdc_runtime_SysStd_abort__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_SysStd_exit__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_SysStd_flush__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_SysStd_putch__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_SysStd_ready__E);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_SysStd_Module__diagsEnabled xdc_runtime_SysStd_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Module__diagsIncluded xdc_runtime_SysStd_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Module__diagsMask xdc_runtime_SysStd_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Module__gateObj xdc_runtime_SysStd_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Module__gatePrms xdc_runtime_SysStd_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Module__id xdc_runtime_SysStd_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Module__loggerDefined xdc_runtime_SysStd_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Module__loggerObj xdc_runtime_SysStd_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Module__loggerFxn0 xdc_runtime_SysStd_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Module__loggerFxn1 xdc_runtime_SysStd_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Module__loggerFxn2 xdc_runtime_SysStd_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Module__loggerFxn4 xdc_runtime_SysStd_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Module__loggerFxn8 xdc_runtime_SysStd_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Module__startupDoneFxn xdc_runtime_SysStd_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Object__count xdc_runtime_SysStd_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Object__heap xdc_runtime_SysStd_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Object__sizeof xdc_runtime_SysStd_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_SysStd_Object__table xdc_runtime_SysStd_Object__table__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_SysStd_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_SysStd_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_SysStd_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_SysStd_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_SysStd_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_SysStd_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_SysStd_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_SysStd_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_SysStd_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_SysStd_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_SysStd_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_SysStd_abort__E( xdc_String str ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_SysStd_exit__E( xdc_Int stat ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_SysStd_flush__E( void ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_SysStd_putch__E( xdc_Char ch ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_SysStd_ready__E( void ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.System PRAGMAS ========
 */


#ifdef __ti__
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_Module__startupDone__S);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_Module_startup__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_abort__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_atexit__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_exit__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_putch__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_flush__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_printf__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_aprintf__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_sprintf__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_asprintf__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_vprintf__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_avprintf__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_vsprintf__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_System_avsprintf__E);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_System_Module__diagsEnabled xdc_runtime_System_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Module__diagsIncluded xdc_runtime_System_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Module__diagsMask xdc_runtime_System_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Module__gateObj xdc_runtime_System_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Module__gatePrms xdc_runtime_System_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Module__id xdc_runtime_System_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Module__loggerDefined xdc_runtime_System_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Module__loggerObj xdc_runtime_System_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Module__loggerFxn0 xdc_runtime_System_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Module__loggerFxn1 xdc_runtime_System_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Module__loggerFxn2 xdc_runtime_System_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Module__loggerFxn4 xdc_runtime_System_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Module__loggerFxn8 xdc_runtime_System_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Module__startupDoneFxn xdc_runtime_System_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Object__count xdc_runtime_System_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Object__heap xdc_runtime_System_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Object__sizeof xdc_runtime_System_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_Object__table xdc_runtime_System_Object__table__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_A_cannotFitIntoArg xdc_runtime_System_A_cannotFitIntoArg__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_maxAtexitHandlers xdc_runtime_System_maxAtexitHandlers__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_System_extendFxn xdc_runtime_System_extendFxn__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_System_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_System_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_System_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_System_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_System_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_System_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_System_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_System_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_System_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_System_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_System_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_System_abort__E( xdc_String str ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_System_atexit__E( xdc_runtime_System_AtexitHandler handler ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_System_exit__E( xdc_Int stat ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_System_putch__E( xdc_Char ch ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_System_flush__E( void ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_System_printf__E( xdc_String fmt, ... ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_System_aprintf__E( xdc_String fmt, ... ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_System_sprintf__E( xdc_Char buf[], xdc_String fmt, ... ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_System_asprintf__E( xdc_Char buf[], xdc_String fmt, ... ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_System_vprintf__E( xdc_String fmt, xdc_VaList va ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_System_avprintf__E( xdc_String fmt, xdc_VaList va ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_System_vsprintf__E( xdc_Char buf[], xdc_String fmt, xdc_VaList va ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_System_avsprintf__E( xdc_Char buf[], xdc_String fmt, xdc_VaList va ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.Text PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_Text_Module__diagsEnabled xdc_runtime_Text_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Module__diagsIncluded xdc_runtime_Text_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Module__diagsMask xdc_runtime_Text_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Module__gateObj xdc_runtime_Text_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Module__gatePrms xdc_runtime_Text_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Module__id xdc_runtime_Text_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Module__loggerDefined xdc_runtime_Text_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Module__loggerObj xdc_runtime_Text_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Module__loggerFxn0 xdc_runtime_Text_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Module__loggerFxn1 xdc_runtime_Text_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Module__loggerFxn2 xdc_runtime_Text_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Module__loggerFxn4 xdc_runtime_Text_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Module__loggerFxn8 xdc_runtime_Text_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Module__startupDoneFxn xdc_runtime_Text_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Object__count xdc_runtime_Text_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Object__heap xdc_runtime_Text_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Object__sizeof xdc_runtime_Text_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_Object__table xdc_runtime_Text_Object__table__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_nameUnknown xdc_runtime_Text_nameUnknown__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_nameEmpty xdc_runtime_Text_nameEmpty__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_nameStatic xdc_runtime_Text_nameStatic__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_isLoaded xdc_runtime_Text_isLoaded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_charTab xdc_runtime_Text_charTab__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_nodeTab xdc_runtime_Text_nodeTab__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_charCnt xdc_runtime_Text_charCnt__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_nodeCnt xdc_runtime_Text_nodeCnt__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_unnamedModsLastId xdc_runtime_Text_unnamedModsLastId__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_registryModsLastId xdc_runtime_Text_registryModsLastId__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_visitRopeFxn xdc_runtime_Text_visitRopeFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Text_visitRopeFxn2 xdc_runtime_Text_visitRopeFxn2__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_Text_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Text_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Text_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Text_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Text_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Text_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Text_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Text_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Text_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Text_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Text_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_String xdc_runtime_Text_cordText__E( xdc_runtime_Text_CordAddr cord ) __attribute__ ((externally_visible));
    xdc_String xdc_runtime_Text_ropeText__E( xdc_runtime_Text_RopeId rope ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_Text_matchRope__E( xdc_runtime_Text_RopeId rope, xdc_String pat, xdc_Int* lenp ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_Text_putLab__E( xdc_runtime_Types_Label* lab, xdc_Char** bufp, xdc_Int len ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_Text_putMod__E( xdc_runtime_Types_ModuleId mid, xdc_Char** bufp, xdc_Int len ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_Text_putSite__E( xdc_runtime_Types_Site* site, xdc_Char** bufp, xdc_Int len ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.Timestamp PRAGMAS ========
 */


#ifdef __ti__
    #pragma FUNC_EXT_CALLED(xdc_runtime_Timestamp_Module__startupDone__S);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Timestamp_get32__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Timestamp_get64__E);
    #pragma FUNC_EXT_CALLED(xdc_runtime_Timestamp_getFreq__E);
#endif

#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_Timestamp_Module__diagsEnabled xdc_runtime_Timestamp_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Module__diagsIncluded xdc_runtime_Timestamp_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Module__diagsMask xdc_runtime_Timestamp_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Module__gateObj xdc_runtime_Timestamp_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Module__gatePrms xdc_runtime_Timestamp_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Module__id xdc_runtime_Timestamp_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Module__loggerDefined xdc_runtime_Timestamp_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Module__loggerObj xdc_runtime_Timestamp_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Module__loggerFxn0 xdc_runtime_Timestamp_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Module__loggerFxn1 xdc_runtime_Timestamp_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Module__loggerFxn2 xdc_runtime_Timestamp_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Module__loggerFxn4 xdc_runtime_Timestamp_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Module__loggerFxn8 xdc_runtime_Timestamp_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Module__startupDoneFxn xdc_runtime_Timestamp_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Object__count xdc_runtime_Timestamp_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Object__heap xdc_runtime_Timestamp_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Object__sizeof xdc_runtime_Timestamp_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_Timestamp_Object__table xdc_runtime_Timestamp_Object__table__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_Timestamp_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Timestamp_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Timestamp_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Timestamp_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Timestamp_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Timestamp_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Timestamp_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Timestamp_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Timestamp_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_Timestamp_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_Timestamp_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Bits32 xdc_runtime_Timestamp_get32__E( void ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Timestamp_get64__E( xdc_runtime_Types_Timestamp64* result ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_Timestamp_getFreq__E( xdc_runtime_Types_FreqHz* freq ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.knl.GateThread PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_knl_GateThread_Module__diagsEnabled xdc_runtime_knl_GateThread_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Module__diagsIncluded xdc_runtime_knl_GateThread_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Module__diagsMask xdc_runtime_knl_GateThread_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Module__gateObj xdc_runtime_knl_GateThread_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Module__gatePrms xdc_runtime_knl_GateThread_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Module__id xdc_runtime_knl_GateThread_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Module__loggerDefined xdc_runtime_knl_GateThread_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Module__loggerObj xdc_runtime_knl_GateThread_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Module__loggerFxn0 xdc_runtime_knl_GateThread_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Module__loggerFxn1 xdc_runtime_knl_GateThread_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Module__loggerFxn2 xdc_runtime_knl_GateThread_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Module__loggerFxn4 xdc_runtime_knl_GateThread_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Module__loggerFxn8 xdc_runtime_knl_GateThread_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Module__startupDoneFxn xdc_runtime_knl_GateThread_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Object__count xdc_runtime_knl_GateThread_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Object__heap xdc_runtime_knl_GateThread_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Object__sizeof xdc_runtime_knl_GateThread_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_GateThread_Object__table xdc_runtime_knl_GateThread_Object__table__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_knl_GateThread_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_GateThread_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_GateThread_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_GateThread_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_GateThread_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_GateThread_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_GateThread_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_GateThread_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_GateThread_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_GateThread_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_GateThread_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_GateThread_query__E( xdc_Int qual ) __attribute__ ((externally_visible));
    xdc_IArg xdc_runtime_knl_GateThread_enter__E( xdc_runtime_knl_GateThread_Handle ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_GateThread_leave__E( xdc_runtime_knl_GateThread_Handle, xdc_IArg key ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.knl.SemProcess PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_knl_SemProcess_Module__diagsEnabled xdc_runtime_knl_SemProcess_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Module__diagsIncluded xdc_runtime_knl_SemProcess_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Module__diagsMask xdc_runtime_knl_SemProcess_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Module__gateObj xdc_runtime_knl_SemProcess_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Module__gatePrms xdc_runtime_knl_SemProcess_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Module__id xdc_runtime_knl_SemProcess_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Module__loggerDefined xdc_runtime_knl_SemProcess_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Module__loggerObj xdc_runtime_knl_SemProcess_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Module__loggerFxn0 xdc_runtime_knl_SemProcess_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Module__loggerFxn1 xdc_runtime_knl_SemProcess_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Module__loggerFxn2 xdc_runtime_knl_SemProcess_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Module__loggerFxn4 xdc_runtime_knl_SemProcess_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Module__loggerFxn8 xdc_runtime_knl_SemProcess_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Module__startupDoneFxn xdc_runtime_knl_SemProcess_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Object__count xdc_runtime_knl_SemProcess_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Object__heap xdc_runtime_knl_SemProcess_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Object__sizeof xdc_runtime_knl_SemProcess_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemProcess_Object__table xdc_runtime_knl_SemProcess_Object__table__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_knl_SemProcess_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_SemProcess_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_SemProcess_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_SemProcess_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_SemProcess_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_SemProcess_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_SemProcess_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_SemProcess_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_SemProcess_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_SemProcess_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_SemProcess_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_knl_SemProcess_pend__E( xdc_runtime_knl_SemProcess_Handle, xdc_UInt timeout, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_SemProcess_post__E( xdc_runtime_knl_SemProcess_Handle, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.knl.SemThread PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_knl_SemThread_Module__diagsEnabled xdc_runtime_knl_SemThread_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Module__diagsIncluded xdc_runtime_knl_SemThread_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Module__diagsMask xdc_runtime_knl_SemThread_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Module__gateObj xdc_runtime_knl_SemThread_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Module__gatePrms xdc_runtime_knl_SemThread_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Module__id xdc_runtime_knl_SemThread_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Module__loggerDefined xdc_runtime_knl_SemThread_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Module__loggerObj xdc_runtime_knl_SemThread_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Module__loggerFxn0 xdc_runtime_knl_SemThread_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Module__loggerFxn1 xdc_runtime_knl_SemThread_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Module__loggerFxn2 xdc_runtime_knl_SemThread_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Module__loggerFxn4 xdc_runtime_knl_SemThread_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Module__loggerFxn8 xdc_runtime_knl_SemThread_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Module__startupDoneFxn xdc_runtime_knl_SemThread_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Object__count xdc_runtime_knl_SemThread_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Object__heap xdc_runtime_knl_SemThread_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Object__sizeof xdc_runtime_knl_SemThread_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_SemThread_Object__table xdc_runtime_knl_SemThread_Object__table__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_knl_SemThread_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_SemThread_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_SemThread_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_SemThread_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_SemThread_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_SemThread_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_SemThread_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_SemThread_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_SemThread_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_SemThread_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_SemThread_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_knl_SemThread_pend__E( xdc_runtime_knl_SemThread_Handle, xdc_UInt timeout, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_SemThread_post__E( xdc_runtime_knl_SemThread_Handle, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== xdc.runtime.knl.Thread PRAGMAS ========
 */


#ifdef __GNUC__
#if __GNUC__ >= 4
    const CT__xdc_runtime_knl_Thread_Module__diagsEnabled xdc_runtime_knl_Thread_Module__diagsEnabled__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Module__diagsIncluded xdc_runtime_knl_Thread_Module__diagsIncluded__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Module__diagsMask xdc_runtime_knl_Thread_Module__diagsMask__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Module__gateObj xdc_runtime_knl_Thread_Module__gateObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Module__gatePrms xdc_runtime_knl_Thread_Module__gatePrms__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Module__id xdc_runtime_knl_Thread_Module__id__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Module__loggerDefined xdc_runtime_knl_Thread_Module__loggerDefined__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Module__loggerObj xdc_runtime_knl_Thread_Module__loggerObj__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Module__loggerFxn0 xdc_runtime_knl_Thread_Module__loggerFxn0__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Module__loggerFxn1 xdc_runtime_knl_Thread_Module__loggerFxn1__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Module__loggerFxn2 xdc_runtime_knl_Thread_Module__loggerFxn2__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Module__loggerFxn4 xdc_runtime_knl_Thread_Module__loggerFxn4__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Module__loggerFxn8 xdc_runtime_knl_Thread_Module__loggerFxn8__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Module__startupDoneFxn xdc_runtime_knl_Thread_Module__startupDoneFxn__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Object__count xdc_runtime_knl_Thread_Object__count__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Object__heap xdc_runtime_knl_Thread_Object__heap__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Object__sizeof xdc_runtime_knl_Thread_Object__sizeof__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_Object__table xdc_runtime_knl_Thread_Object__table__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_A_zeroTimeout xdc_runtime_knl_Thread_A_zeroTimeout__C __attribute__ ((externally_visible));
    const CT__xdc_runtime_knl_Thread_defaultStackSize xdc_runtime_knl_Thread_defaultStackSize__C __attribute__ ((externally_visible));
    xdc_runtime_Types_Label* xdc_runtime_knl_Thread_Handle__label__S( xdc_Ptr obj, xdc_runtime_Types_Label* lab ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_Thread_Module__startupDone__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_Thread_Object__create__S( xdc_Ptr __oa, xdc_SizeT __osz, xdc_Ptr __aa, const xdc_UChar* __pa, xdc_SizeT __psz, xdc_runtime_Error_Block* __eb ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_Thread_Object__delete__S( xdc_Ptr instp ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_Thread_Object__destruct__S( xdc_Ptr objp ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_Thread_Object__get__S( xdc_Ptr oarr, xdc_Int i ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_Thread_Object__first__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_Thread_Object__next__S( xdc_Ptr obj ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_Thread_Params__init__S( xdc_Ptr dst, xdc_Ptr src, xdc_SizeT psz, xdc_SizeT isz ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_Thread_Proxy__abstract__S( void ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_Thread_Proxy__delegate__S( void ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_Thread_start__E( xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_Thread_yield__E( xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_knl_Thread_compareOsPriorities__E( xdc_Int p1, xdc_Int p2, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_Thread_sleep__E( xdc_UInt timeout, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_Thread_join__E( xdc_runtime_knl_Thread_Handle, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_runtime_knl_Thread_Priority xdc_runtime_knl_Thread_getPriority__E( xdc_runtime_knl_Thread_Handle, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_Thread_setPriority__E( xdc_runtime_knl_Thread_Handle, xdc_runtime_knl_Thread_Priority newPri, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Int xdc_runtime_knl_Thread_getOsPriority__E( xdc_runtime_knl_Thread_Handle, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_Thread_setOsPriority__E( xdc_runtime_knl_Thread_Handle, xdc_Int newPri, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_Thread_getOsHandle__E( xdc_runtime_knl_Thread_Handle ) __attribute__ ((externally_visible));
    xdc_Ptr xdc_runtime_knl_Thread_getTls__E( xdc_runtime_knl_Thread_Handle ) __attribute__ ((externally_visible));
    xdc_Void xdc_runtime_knl_Thread_setTls__E( xdc_runtime_knl_Thread_Handle, xdc_Ptr tls ) __attribute__ ((externally_visible));
    xdc_Bool xdc_runtime_knl_Thread_stat__E( xdc_runtime_knl_Thread_Handle, xdc_runtime_knl_Thread_Stat* buf, xdc_runtime_Error_Block* eb ) __attribute__ ((externally_visible));
#endif
#endif

/*
 * ======== INITIALIZATION ENTRY POINT ========
 */

extern int __xdc__init(void);
#ifdef __GNUC__
#if __GNUC__ >= 4
    __attribute__ ((externally_visible))
#endif
#endif
__FAR__ int (* volatile __xdc__init__addr)(void) = &__xdc__init;


/*
 * ======== PROGRAM GLOBALS ========
 */


/*
 * ======== CLINK DIRECTIVES ========
 */

#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_IModule_Interface__BASE__C, ".const:xdc_runtime_IModule_Interface__BASE__C");
    asm("	.sect \".const:xdc_runtime_IModule_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_IModule_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_IModule_Interface__BASE__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_ILogger_Interface__BASE__C, ".const:xdc_runtime_ILogger_Interface__BASE__C");
    asm("	.sect \".const:xdc_runtime_ILogger_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_ILogger_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_ILogger_Interface__BASE__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_ILoggerMFP_Interface__BASE__C, ".const:ti_sdo_utils_loggers_ILoggerMFP_Interface__BASE__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_ILoggerMFP_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_ILoggerMFP_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_ILoggerMFP_Interface__BASE__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_ITimestampClient_Interface__BASE__C, ".const:xdc_runtime_ITimestampClient_Interface__BASE__C");
    asm("	.sect \".const:xdc_runtime_ITimestampClient_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_ITimestampClient_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_ITimestampClient_Interface__BASE__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_ITimestampProvider_Interface__BASE__C, ".const:xdc_runtime_ITimestampProvider_Interface__BASE__C");
    asm("	.sect \".const:xdc_runtime_ITimestampProvider_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_ITimestampProvider_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_ITimestampProvider_Interface__BASE__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_IHeap_Interface__BASE__C, ".const:xdc_runtime_IHeap_Interface__BASE__C");
    asm("	.sect \".const:xdc_runtime_IHeap_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_IHeap_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_IHeap_Interface__BASE__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_ISystemSupport_Interface__BASE__C, ".const:xdc_runtime_ISystemSupport_Interface__BASE__C");
    asm("	.sect \".const:xdc_runtime_ISystemSupport_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_ISystemSupport_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_ISystemSupport_Interface__BASE__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_IGateProvider_Interface__BASE__C, ".const:xdc_runtime_IGateProvider_Interface__BASE__C");
    asm("	.sect \".const:xdc_runtime_IGateProvider_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_IGateProvider_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_IGateProvider_Interface__BASE__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_ISemaphore_Interface__BASE__C, ".const:xdc_runtime_knl_ISemaphore_Interface__BASE__C");
    asm("	.sect \".const:xdc_runtime_knl_ISemaphore_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_ISemaphore_Interface__BASE__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_ISemaphore_Interface__BASE__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__FXNS__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__FXNS__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__FXNS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__FXNS__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__FXNS__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__FXNS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__FXNS__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__FXNS__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__FXNS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__FXNS__C, ".const:xdc_runtime_HeapStd_Module__FXNS__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__FXNS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__FXNS__C, ".const:xdc_runtime_SysStd_Module__FXNS__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__FXNS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__FXNS__C, ".const:xdc_runtime_Timestamp_Module__FXNS__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__FXNS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__FXNS__C, ".const:xdc_runtime_knl_GateThread_Module__FXNS__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__FXNS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__FXNS__C, ".const:xdc_runtime_knl_SemProcess_Module__FXNS__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__FXNS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__FXNS__C, ".const:xdc_runtime_knl_SemThread_Module__FXNS__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__FXNS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__FXNS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Object__PARAMS__C, ".const:xdc_runtime_HeapStd_Object__PARAMS__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Object__PARAMS__C, ".const:xdc_runtime_knl_GateThread_Object__PARAMS__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Object__PARAMS__C, ".const:xdc_runtime_knl_SemProcess_Object__PARAMS__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Object__PARAMS__C, ".const:xdc_runtime_knl_SemThread_Object__PARAMS__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Object__PARAMS__C, ".const:xdc_runtime_knl_Thread_Object__PARAMS__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__diagsEnabled__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__diagsEnabled__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__diagsIncluded__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__diagsIncluded__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__diagsMask__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__diagsMask__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__gateObj__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__gateObj__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__gatePrms__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__gatePrms__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__id__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__id__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__loggerDefined__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__loggerDefined__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__loggerObj__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__loggerObj__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__loggerFxn0__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn0__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__loggerFxn1__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn1__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__loggerFxn2__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn2__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__loggerFxn4__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn4__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__loggerFxn8__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn8__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Module__startupDoneFxn__C, ".const:ti_sdo_utils_loggers_LogMFP_Module__startupDoneFxn__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Object__count__C, ".const:ti_sdo_utils_loggers_LogMFP_Object__count__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Object__heap__C, ".const:ti_sdo_utils_loggers_LogMFP_Object__heap__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Object__sizeof__C, ".const:ti_sdo_utils_loggers_LogMFP_Object__sizeof__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LogMFP_Object__table__C, ".const:ti_sdo_utils_loggers_LogMFP_Object__table__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LogMFP_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LogMFP_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LogMFP_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Object__DESC__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__DESC__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__DESC__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsEnabled__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsEnabled__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsIncluded__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsIncluded__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsMask__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsMask__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__gateObj__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__gateObj__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__gatePrms__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__gatePrms__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__id__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__id__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerDefined__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerDefined__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerObj__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerObj__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn0__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn0__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn1__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn1__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn2__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn2__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn4__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn4__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn8__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn8__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Module__startupDoneFxn__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__startupDoneFxn__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Object__count__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__count__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Object__heap__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__heap__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Object__sizeof__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__sizeof__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerMFPNull_Object__table__C, ".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__table__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerMFPNull_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerMFPNull_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Object__DESC__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Object__DESC__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Object__DESC__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__diagsEnabled__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__diagsEnabled__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__diagsIncluded__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__diagsIncluded__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__diagsMask__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__diagsMask__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__gateObj__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__gateObj__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__gatePrms__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__gatePrms__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__id__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__id__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__loggerDefined__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerDefined__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__loggerObj__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerObj__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn0__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn0__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn1__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn1__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn2__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn2__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn4__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn4__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn8__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn8__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Module__startupDoneFxn__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Module__startupDoneFxn__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Object__count__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Object__count__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Object__heap__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Object__heap__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Object__sizeof__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Object__sizeof__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_Object__table__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_Object__table__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_utils_loggers_LoggerSysTID_gate__C, ".const:ti_sdo_utils_loggers_LoggerSysTID_gate__C");
    asm("	.sect \".const:ti_sdo_utils_loggers_LoggerSysTID_gate__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_utils_loggers_LoggerSysTID_gate__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_utils_loggers_LoggerSysTID_gate__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Object__DESC__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__DESC__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__DESC__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsEnabled__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsEnabled__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsIncluded__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsIncluded__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsMask__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsMask__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gateObj__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gateObj__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gatePrms__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gatePrms__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__id__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__id__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerDefined__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerDefined__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerObj__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerObj__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn0__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn0__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn1__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn1__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn2__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn2__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn4__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn4__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn8__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn8__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDoneFxn__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDoneFxn__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Object__count__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__count__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Object__heap__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__heap__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Object__sizeof__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__sizeof__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_A_POSIX_Error__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_A_POSIX_Error__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_A_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_A_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_A_POSIX_Error__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_GateThreadSupport_E_POSIX_Error__C, ".const:ti_sdo_xdcruntime_linux_GateThreadSupport_E_POSIX_Error__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_GateThreadSupport_E_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_GateThreadSupport_E_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_GateThreadSupport_E_POSIX_Error__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Object__DESC__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__DESC__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__DESC__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsEnabled__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsEnabled__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsIncluded__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsIncluded__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsMask__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsMask__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gateObj__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gateObj__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gatePrms__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gatePrms__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__id__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__id__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerDefined__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerDefined__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerObj__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerObj__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn0__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn0__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn1__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn1__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn2__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn2__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn4__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn4__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn8__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn8__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDoneFxn__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDoneFxn__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Object__count__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__count__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Object__heap__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__heap__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Object__sizeof__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__sizeof__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_Object__table__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__table__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_A_unsupportedTimeout__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_A_unsupportedTimeout__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_A_unsupportedTimeout__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_A_unsupportedTimeout__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_A_unsupportedTimeout__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_A_invalidKey__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_A_invalidKey__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_A_invalidKey__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_A_invalidKey__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_A_invalidKey__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_A_POSIX_Error__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_A_POSIX_Error__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_A_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_A_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_A_POSIX_Error__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_E_POSIX_Error__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_E_POSIX_Error__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_E_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_E_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_E_POSIX_Error__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_L_extant__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_L_extant__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_L_extant__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_L_extant__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_L_extant__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_L_create__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_L_create__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_L_create__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_L_create__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_L_create__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemProcessSupport_perms__C, ".const:ti_sdo_xdcruntime_linux_SemProcessSupport_perms__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemProcessSupport_perms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemProcessSupport_perms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemProcessSupport_perms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Object__DESC__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__DESC__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__DESC__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsEnabled__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsEnabled__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsIncluded__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsIncluded__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsMask__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsMask__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gateObj__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gateObj__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gatePrms__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gatePrms__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__id__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__id__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerDefined__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerDefined__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerObj__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerObj__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn0__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn0__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn1__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn1__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn2__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn2__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn4__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn4__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn8__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn8__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDoneFxn__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDoneFxn__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Object__count__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__count__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Object__heap__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__heap__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Object__sizeof__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__sizeof__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_Object__table__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__table__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_A_POSIX_Error__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_A_POSIX_Error__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_A_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_A_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_A_POSIX_Error__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_E_POSIX_Error__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_E_POSIX_Error__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_E_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_E_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_E_POSIX_Error__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_SemThreadSupport_E_resetError__C, ".const:ti_sdo_xdcruntime_linux_SemThreadSupport_E_resetError__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_SemThreadSupport_E_resetError__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_SemThreadSupport_E_resetError__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_SemThreadSupport_E_resetError__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Object__DESC__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__DESC__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__DESC__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsEnabled__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsEnabled__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsIncluded__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsIncluded__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsMask__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsMask__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__gateObj__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__gateObj__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__gatePrms__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__gatePrms__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__id__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__id__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerDefined__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerDefined__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerObj__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerObj__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn0__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn0__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn1__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn1__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn2__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn2__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn4__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn4__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn8__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn8__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDoneFxn__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDoneFxn__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Object__count__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__count__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Object__heap__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__heap__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Object__sizeof__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__sizeof__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_Object__table__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__table__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_E_priority__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_E_priority__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_E_priority__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_E_priority__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_E_priority__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_A_POSIX_Error__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_A_POSIX_Error__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_A_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_A_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_A_POSIX_Error__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_E_POSIX_Error__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_E_POSIX_Error__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_E_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_E_POSIX_Error__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_E_POSIX_Error__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_L_start__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_L_start__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_L_start__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_L_start__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_L_start__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_L_finish__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_L_finish__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_L_finish__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_L_finish__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_L_finish__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_ThreadSupport_L_join__C, ".const:ti_sdo_xdcruntime_linux_ThreadSupport_L_join__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_ThreadSupport_L_join__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_ThreadSupport_L_join__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_ThreadSupport_L_join__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsEnabled__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsEnabled__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsIncluded__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsIncluded__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsMask__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsMask__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__gateObj__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__gateObj__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__gatePrms__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__gatePrms__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__id__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__id__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerDefined__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerDefined__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerObj__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerObj__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn0__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn0__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn1__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn1__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn2__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn2__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn4__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn4__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn8__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn8__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDoneFxn__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDoneFxn__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Object__count__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__count__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Object__heap__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__heap__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Object__sizeof__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__sizeof__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(ti_sdo_xdcruntime_linux_TimestampPosix_Object__table__C, ".const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__table__C");
    asm("	.sect \".const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:ti_sdo_xdcruntime_linux_TimestampPosix_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__diagsEnabled__C, ".const:xdc_runtime_Assert_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__diagsIncluded__C, ".const:xdc_runtime_Assert_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__diagsMask__C, ".const:xdc_runtime_Assert_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__gateObj__C, ".const:xdc_runtime_Assert_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__gatePrms__C, ".const:xdc_runtime_Assert_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__id__C, ".const:xdc_runtime_Assert_Module__id__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerDefined__C, ".const:xdc_runtime_Assert_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerObj__C, ".const:xdc_runtime_Assert_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerFxn0__C, ".const:xdc_runtime_Assert_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerFxn1__C, ".const:xdc_runtime_Assert_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerFxn2__C, ".const:xdc_runtime_Assert_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerFxn4__C, ".const:xdc_runtime_Assert_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__loggerFxn8__C, ".const:xdc_runtime_Assert_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Module__startupDoneFxn__C, ".const:xdc_runtime_Assert_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_Assert_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Object__count__C, ".const:xdc_runtime_Assert_Object__count__C");
    asm("	.sect \".const:xdc_runtime_Assert_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Object__heap__C, ".const:xdc_runtime_Assert_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_Assert_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Object__sizeof__C, ".const:xdc_runtime_Assert_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_Assert_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_Object__table__C, ".const:xdc_runtime_Assert_Object__table__C");
    asm("	.sect \".const:xdc_runtime_Assert_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Assert_E_assertFailed__C, ".const:xdc_runtime_Assert_E_assertFailed__C");
    asm("	.sect \".const:xdc_runtime_Assert_E_assertFailed__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Assert_E_assertFailed__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Assert_E_assertFailed__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__diagsEnabled__C, ".const:xdc_runtime_Core_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__diagsIncluded__C, ".const:xdc_runtime_Core_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__diagsMask__C, ".const:xdc_runtime_Core_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__gateObj__C, ".const:xdc_runtime_Core_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__gatePrms__C, ".const:xdc_runtime_Core_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__id__C, ".const:xdc_runtime_Core_Module__id__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__loggerDefined__C, ".const:xdc_runtime_Core_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__loggerObj__C, ".const:xdc_runtime_Core_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__loggerFxn0__C, ".const:xdc_runtime_Core_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__loggerFxn1__C, ".const:xdc_runtime_Core_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__loggerFxn2__C, ".const:xdc_runtime_Core_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__loggerFxn4__C, ".const:xdc_runtime_Core_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__loggerFxn8__C, ".const:xdc_runtime_Core_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Module__startupDoneFxn__C, ".const:xdc_runtime_Core_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_Core_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Object__count__C, ".const:xdc_runtime_Core_Object__count__C");
    asm("	.sect \".const:xdc_runtime_Core_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Object__heap__C, ".const:xdc_runtime_Core_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_Core_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Object__sizeof__C, ".const:xdc_runtime_Core_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_Core_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_Object__table__C, ".const:xdc_runtime_Core_Object__table__C");
    asm("	.sect \".const:xdc_runtime_Core_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Core_A_initializedParams__C, ".const:xdc_runtime_Core_A_initializedParams__C");
    asm("	.sect \".const:xdc_runtime_Core_A_initializedParams__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Core_A_initializedParams__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Core_A_initializedParams__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__diagsEnabled__C, ".const:xdc_runtime_Defaults_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__diagsIncluded__C, ".const:xdc_runtime_Defaults_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__diagsMask__C, ".const:xdc_runtime_Defaults_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__gateObj__C, ".const:xdc_runtime_Defaults_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__gatePrms__C, ".const:xdc_runtime_Defaults_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__id__C, ".const:xdc_runtime_Defaults_Module__id__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerDefined__C, ".const:xdc_runtime_Defaults_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerObj__C, ".const:xdc_runtime_Defaults_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerFxn0__C, ".const:xdc_runtime_Defaults_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerFxn1__C, ".const:xdc_runtime_Defaults_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerFxn2__C, ".const:xdc_runtime_Defaults_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerFxn4__C, ".const:xdc_runtime_Defaults_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__loggerFxn8__C, ".const:xdc_runtime_Defaults_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Module__startupDoneFxn__C, ".const:xdc_runtime_Defaults_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Object__count__C, ".const:xdc_runtime_Defaults_Object__count__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Object__heap__C, ".const:xdc_runtime_Defaults_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Object__sizeof__C, ".const:xdc_runtime_Defaults_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Defaults_Object__table__C, ".const:xdc_runtime_Defaults_Object__table__C");
    asm("	.sect \".const:xdc_runtime_Defaults_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Defaults_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Defaults_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__diagsEnabled__C, ".const:xdc_runtime_Diags_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__diagsIncluded__C, ".const:xdc_runtime_Diags_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__diagsMask__C, ".const:xdc_runtime_Diags_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__gateObj__C, ".const:xdc_runtime_Diags_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__gatePrms__C, ".const:xdc_runtime_Diags_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__id__C, ".const:xdc_runtime_Diags_Module__id__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerDefined__C, ".const:xdc_runtime_Diags_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerObj__C, ".const:xdc_runtime_Diags_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerFxn0__C, ".const:xdc_runtime_Diags_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerFxn1__C, ".const:xdc_runtime_Diags_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerFxn2__C, ".const:xdc_runtime_Diags_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerFxn4__C, ".const:xdc_runtime_Diags_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__loggerFxn8__C, ".const:xdc_runtime_Diags_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Module__startupDoneFxn__C, ".const:xdc_runtime_Diags_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_Diags_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Object__count__C, ".const:xdc_runtime_Diags_Object__count__C");
    asm("	.sect \".const:xdc_runtime_Diags_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Object__heap__C, ".const:xdc_runtime_Diags_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_Diags_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Object__sizeof__C, ".const:xdc_runtime_Diags_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_Diags_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_Object__table__C, ".const:xdc_runtime_Diags_Object__table__C");
    asm("	.sect \".const:xdc_runtime_Diags_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_setMaskEnabled__C, ".const:xdc_runtime_Diags_setMaskEnabled__C");
    asm("	.sect \".const:xdc_runtime_Diags_setMaskEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_setMaskEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_setMaskEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Diags_dictBase__C, ".const:xdc_runtime_Diags_dictBase__C");
    asm("	.sect \".const:xdc_runtime_Diags_dictBase__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Diags_dictBase__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Diags_dictBase__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__diagsEnabled__C, ".const:xdc_runtime_Error_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__diagsIncluded__C, ".const:xdc_runtime_Error_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__diagsMask__C, ".const:xdc_runtime_Error_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__gateObj__C, ".const:xdc_runtime_Error_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__gatePrms__C, ".const:xdc_runtime_Error_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__id__C, ".const:xdc_runtime_Error_Module__id__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__loggerDefined__C, ".const:xdc_runtime_Error_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__loggerObj__C, ".const:xdc_runtime_Error_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__loggerFxn0__C, ".const:xdc_runtime_Error_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__loggerFxn1__C, ".const:xdc_runtime_Error_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__loggerFxn2__C, ".const:xdc_runtime_Error_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__loggerFxn4__C, ".const:xdc_runtime_Error_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__loggerFxn8__C, ".const:xdc_runtime_Error_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Module__startupDoneFxn__C, ".const:xdc_runtime_Error_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_Error_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Object__count__C, ".const:xdc_runtime_Error_Object__count__C");
    asm("	.sect \".const:xdc_runtime_Error_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Object__heap__C, ".const:xdc_runtime_Error_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_Error_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Object__sizeof__C, ".const:xdc_runtime_Error_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_Error_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_Object__table__C, ".const:xdc_runtime_Error_Object__table__C");
    asm("	.sect \".const:xdc_runtime_Error_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_E_generic__C, ".const:xdc_runtime_Error_E_generic__C");
    asm("	.sect \".const:xdc_runtime_Error_E_generic__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_E_generic__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_E_generic__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_E_memory__C, ".const:xdc_runtime_Error_E_memory__C");
    asm("	.sect \".const:xdc_runtime_Error_E_memory__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_E_memory__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_E_memory__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_E_msgCode__C, ".const:xdc_runtime_Error_E_msgCode__C");
    asm("	.sect \".const:xdc_runtime_Error_E_msgCode__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_E_msgCode__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_E_msgCode__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_policy__C, ".const:xdc_runtime_Error_policy__C");
    asm("	.sect \".const:xdc_runtime_Error_policy__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_policy__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_policy__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_raiseHook__C, ".const:xdc_runtime_Error_raiseHook__C");
    asm("	.sect \".const:xdc_runtime_Error_raiseHook__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_raiseHook__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_raiseHook__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Error_maxDepth__C, ".const:xdc_runtime_Error_maxDepth__C");
    asm("	.sect \".const:xdc_runtime_Error_maxDepth__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Error_maxDepth__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Error_maxDepth__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__diagsEnabled__C, ".const:xdc_runtime_Gate_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__diagsIncluded__C, ".const:xdc_runtime_Gate_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__diagsMask__C, ".const:xdc_runtime_Gate_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__gateObj__C, ".const:xdc_runtime_Gate_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__gatePrms__C, ".const:xdc_runtime_Gate_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__id__C, ".const:xdc_runtime_Gate_Module__id__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerDefined__C, ".const:xdc_runtime_Gate_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerObj__C, ".const:xdc_runtime_Gate_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerFxn0__C, ".const:xdc_runtime_Gate_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerFxn1__C, ".const:xdc_runtime_Gate_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerFxn2__C, ".const:xdc_runtime_Gate_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerFxn4__C, ".const:xdc_runtime_Gate_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__loggerFxn8__C, ".const:xdc_runtime_Gate_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Module__startupDoneFxn__C, ".const:xdc_runtime_Gate_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_Gate_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Object__count__C, ".const:xdc_runtime_Gate_Object__count__C");
    asm("	.sect \".const:xdc_runtime_Gate_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Object__heap__C, ".const:xdc_runtime_Gate_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_Gate_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Object__sizeof__C, ".const:xdc_runtime_Gate_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_Gate_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Gate_Object__table__C, ".const:xdc_runtime_Gate_Object__table__C");
    asm("	.sect \".const:xdc_runtime_Gate_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Gate_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Gate_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Object__DESC__C, ".const:xdc_runtime_HeapStd_Object__DESC__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Object__DESC__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Object__PARAMS__C, ".const:xdc_runtime_HeapStd_Object__PARAMS__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__diagsEnabled__C, ".const:xdc_runtime_HeapStd_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__diagsIncluded__C, ".const:xdc_runtime_HeapStd_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__diagsMask__C, ".const:xdc_runtime_HeapStd_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__gateObj__C, ".const:xdc_runtime_HeapStd_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__gatePrms__C, ".const:xdc_runtime_HeapStd_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__id__C, ".const:xdc_runtime_HeapStd_Module__id__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerDefined__C, ".const:xdc_runtime_HeapStd_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerObj__C, ".const:xdc_runtime_HeapStd_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerFxn0__C, ".const:xdc_runtime_HeapStd_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerFxn1__C, ".const:xdc_runtime_HeapStd_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerFxn2__C, ".const:xdc_runtime_HeapStd_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerFxn4__C, ".const:xdc_runtime_HeapStd_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__loggerFxn8__C, ".const:xdc_runtime_HeapStd_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Module__startupDoneFxn__C, ".const:xdc_runtime_HeapStd_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Object__count__C, ".const:xdc_runtime_HeapStd_Object__count__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Object__heap__C, ".const:xdc_runtime_HeapStd_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Object__sizeof__C, ".const:xdc_runtime_HeapStd_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_Object__table__C, ".const:xdc_runtime_HeapStd_Object__table__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_E_noRTSMemory__C, ".const:xdc_runtime_HeapStd_E_noRTSMemory__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_E_noRTSMemory__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_E_noRTSMemory__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_E_noRTSMemory__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_A_zeroSize__C, ".const:xdc_runtime_HeapStd_A_zeroSize__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_A_zeroSize__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_A_zeroSize__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_A_zeroSize__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_A_invalidTotalFreeSize__C, ".const:xdc_runtime_HeapStd_A_invalidTotalFreeSize__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_A_invalidTotalFreeSize__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_A_invalidTotalFreeSize__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_A_invalidTotalFreeSize__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_HeapStd_A_invalidAlignment__C, ".const:xdc_runtime_HeapStd_A_invalidAlignment__C");
    asm("	.sect \".const:xdc_runtime_HeapStd_A_invalidAlignment__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_HeapStd_A_invalidAlignment__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_HeapStd_A_invalidAlignment__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__diagsEnabled__C, ".const:xdc_runtime_Log_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__diagsIncluded__C, ".const:xdc_runtime_Log_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__diagsMask__C, ".const:xdc_runtime_Log_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__gateObj__C, ".const:xdc_runtime_Log_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__gatePrms__C, ".const:xdc_runtime_Log_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__id__C, ".const:xdc_runtime_Log_Module__id__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__loggerDefined__C, ".const:xdc_runtime_Log_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__loggerObj__C, ".const:xdc_runtime_Log_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__loggerFxn0__C, ".const:xdc_runtime_Log_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__loggerFxn1__C, ".const:xdc_runtime_Log_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__loggerFxn2__C, ".const:xdc_runtime_Log_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__loggerFxn4__C, ".const:xdc_runtime_Log_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__loggerFxn8__C, ".const:xdc_runtime_Log_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Module__startupDoneFxn__C, ".const:xdc_runtime_Log_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_Log_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Object__count__C, ".const:xdc_runtime_Log_Object__count__C");
    asm("	.sect \".const:xdc_runtime_Log_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Object__heap__C, ".const:xdc_runtime_Log_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_Log_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Object__sizeof__C, ".const:xdc_runtime_Log_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_Log_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_Object__table__C, ".const:xdc_runtime_Log_Object__table__C");
    asm("	.sect \".const:xdc_runtime_Log_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_L_construct__C, ".const:xdc_runtime_Log_L_construct__C");
    asm("	.sect \".const:xdc_runtime_Log_L_construct__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_L_construct__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_L_construct__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_L_create__C, ".const:xdc_runtime_Log_L_create__C");
    asm("	.sect \".const:xdc_runtime_Log_L_create__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_L_create__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_L_create__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_L_destruct__C, ".const:xdc_runtime_Log_L_destruct__C");
    asm("	.sect \".const:xdc_runtime_Log_L_destruct__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_L_destruct__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_L_destruct__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_L_delete__C, ".const:xdc_runtime_Log_L_delete__C");
    asm("	.sect \".const:xdc_runtime_Log_L_delete__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_L_delete__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_L_delete__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_L_error__C, ".const:xdc_runtime_Log_L_error__C");
    asm("	.sect \".const:xdc_runtime_Log_L_error__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_L_error__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_L_error__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_L_warning__C, ".const:xdc_runtime_Log_L_warning__C");
    asm("	.sect \".const:xdc_runtime_Log_L_warning__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_L_warning__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_L_warning__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Log_L_info__C, ".const:xdc_runtime_Log_L_info__C");
    asm("	.sect \".const:xdc_runtime_Log_L_info__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Log_L_info__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Log_L_info__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__diagsEnabled__C, ".const:xdc_runtime_Main_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__diagsIncluded__C, ".const:xdc_runtime_Main_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__diagsMask__C, ".const:xdc_runtime_Main_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__gateObj__C, ".const:xdc_runtime_Main_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__gatePrms__C, ".const:xdc_runtime_Main_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__id__C, ".const:xdc_runtime_Main_Module__id__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__loggerDefined__C, ".const:xdc_runtime_Main_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__loggerObj__C, ".const:xdc_runtime_Main_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__loggerFxn0__C, ".const:xdc_runtime_Main_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__loggerFxn1__C, ".const:xdc_runtime_Main_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__loggerFxn2__C, ".const:xdc_runtime_Main_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__loggerFxn4__C, ".const:xdc_runtime_Main_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__loggerFxn8__C, ".const:xdc_runtime_Main_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Module__startupDoneFxn__C, ".const:xdc_runtime_Main_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_Main_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Object__count__C, ".const:xdc_runtime_Main_Object__count__C");
    asm("	.sect \".const:xdc_runtime_Main_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Object__heap__C, ".const:xdc_runtime_Main_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_Main_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Object__sizeof__C, ".const:xdc_runtime_Main_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_Main_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Main_Object__table__C, ".const:xdc_runtime_Main_Object__table__C");
    asm("	.sect \".const:xdc_runtime_Main_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Main_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Main_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__diagsEnabled__C, ".const:xdc_runtime_Memory_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__diagsIncluded__C, ".const:xdc_runtime_Memory_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__diagsMask__C, ".const:xdc_runtime_Memory_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__gateObj__C, ".const:xdc_runtime_Memory_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__gatePrms__C, ".const:xdc_runtime_Memory_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__id__C, ".const:xdc_runtime_Memory_Module__id__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerDefined__C, ".const:xdc_runtime_Memory_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerObj__C, ".const:xdc_runtime_Memory_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerFxn0__C, ".const:xdc_runtime_Memory_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerFxn1__C, ".const:xdc_runtime_Memory_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerFxn2__C, ".const:xdc_runtime_Memory_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerFxn4__C, ".const:xdc_runtime_Memory_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__loggerFxn8__C, ".const:xdc_runtime_Memory_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Module__startupDoneFxn__C, ".const:xdc_runtime_Memory_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_Memory_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Object__count__C, ".const:xdc_runtime_Memory_Object__count__C");
    asm("	.sect \".const:xdc_runtime_Memory_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Object__heap__C, ".const:xdc_runtime_Memory_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_Memory_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Object__sizeof__C, ".const:xdc_runtime_Memory_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_Memory_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_Object__table__C, ".const:xdc_runtime_Memory_Object__table__C");
    asm("	.sect \".const:xdc_runtime_Memory_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Memory_defaultHeapInstance__C, ".const:xdc_runtime_Memory_defaultHeapInstance__C");
    asm("	.sect \".const:xdc_runtime_Memory_defaultHeapInstance__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Memory_defaultHeapInstance__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Memory_defaultHeapInstance__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__diagsEnabled__C, ".const:xdc_runtime_Registry_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__diagsIncluded__C, ".const:xdc_runtime_Registry_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__diagsMask__C, ".const:xdc_runtime_Registry_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__gateObj__C, ".const:xdc_runtime_Registry_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__gatePrms__C, ".const:xdc_runtime_Registry_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__id__C, ".const:xdc_runtime_Registry_Module__id__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerDefined__C, ".const:xdc_runtime_Registry_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerObj__C, ".const:xdc_runtime_Registry_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerFxn0__C, ".const:xdc_runtime_Registry_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerFxn1__C, ".const:xdc_runtime_Registry_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerFxn2__C, ".const:xdc_runtime_Registry_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerFxn4__C, ".const:xdc_runtime_Registry_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__loggerFxn8__C, ".const:xdc_runtime_Registry_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Module__startupDoneFxn__C, ".const:xdc_runtime_Registry_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_Registry_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Object__count__C, ".const:xdc_runtime_Registry_Object__count__C");
    asm("	.sect \".const:xdc_runtime_Registry_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Object__heap__C, ".const:xdc_runtime_Registry_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_Registry_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Object__sizeof__C, ".const:xdc_runtime_Registry_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_Registry_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Registry_Object__table__C, ".const:xdc_runtime_Registry_Object__table__C");
    asm("	.sect \".const:xdc_runtime_Registry_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Registry_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Registry_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_sfxnTab__A, ".const:xdc_runtime_Startup_sfxnTab__A");
    asm("	.sect \".const:xdc_runtime_Startup_sfxnTab__A\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_sfxnTab__A\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_sfxnTab__A\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_sfxnRts__A, ".const:xdc_runtime_Startup_sfxnRts__A");
    asm("	.sect \".const:xdc_runtime_Startup_sfxnRts__A\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_sfxnRts__A\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_sfxnRts__A\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__diagsEnabled__C, ".const:xdc_runtime_Startup_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__diagsIncluded__C, ".const:xdc_runtime_Startup_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__diagsMask__C, ".const:xdc_runtime_Startup_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__gateObj__C, ".const:xdc_runtime_Startup_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__gatePrms__C, ".const:xdc_runtime_Startup_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__id__C, ".const:xdc_runtime_Startup_Module__id__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerDefined__C, ".const:xdc_runtime_Startup_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerObj__C, ".const:xdc_runtime_Startup_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerFxn0__C, ".const:xdc_runtime_Startup_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerFxn1__C, ".const:xdc_runtime_Startup_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerFxn2__C, ".const:xdc_runtime_Startup_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerFxn4__C, ".const:xdc_runtime_Startup_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__loggerFxn8__C, ".const:xdc_runtime_Startup_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Module__startupDoneFxn__C, ".const:xdc_runtime_Startup_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_Startup_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Object__count__C, ".const:xdc_runtime_Startup_Object__count__C");
    asm("	.sect \".const:xdc_runtime_Startup_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Object__heap__C, ".const:xdc_runtime_Startup_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_Startup_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Object__sizeof__C, ".const:xdc_runtime_Startup_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_Startup_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_Object__table__C, ".const:xdc_runtime_Startup_Object__table__C");
    asm("	.sect \".const:xdc_runtime_Startup_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_maxPasses__C, ".const:xdc_runtime_Startup_maxPasses__C");
    asm("	.sect \".const:xdc_runtime_Startup_maxPasses__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_maxPasses__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_maxPasses__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_firstFxns__C, ".const:xdc_runtime_Startup_firstFxns__C");
    asm("	.sect \".const:xdc_runtime_Startup_firstFxns__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_firstFxns__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_firstFxns__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_lastFxns__C, ".const:xdc_runtime_Startup_lastFxns__C");
    asm("	.sect \".const:xdc_runtime_Startup_lastFxns__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_lastFxns__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_lastFxns__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_startModsFxn__C, ".const:xdc_runtime_Startup_startModsFxn__C");
    asm("	.sect \".const:xdc_runtime_Startup_startModsFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_startModsFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_startModsFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_execImpl__C, ".const:xdc_runtime_Startup_execImpl__C");
    asm("	.sect \".const:xdc_runtime_Startup_execImpl__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_execImpl__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_execImpl__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_sfxnTab__C, ".const:xdc_runtime_Startup_sfxnTab__C");
    asm("	.sect \".const:xdc_runtime_Startup_sfxnTab__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_sfxnTab__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_sfxnTab__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Startup_sfxnRts__C, ".const:xdc_runtime_Startup_sfxnRts__C");
    asm("	.sect \".const:xdc_runtime_Startup_sfxnRts__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Startup_sfxnRts__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Startup_sfxnRts__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__diagsEnabled__C, ".const:xdc_runtime_SysStd_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__diagsIncluded__C, ".const:xdc_runtime_SysStd_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__diagsMask__C, ".const:xdc_runtime_SysStd_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__gateObj__C, ".const:xdc_runtime_SysStd_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__gatePrms__C, ".const:xdc_runtime_SysStd_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__id__C, ".const:xdc_runtime_SysStd_Module__id__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__loggerDefined__C, ".const:xdc_runtime_SysStd_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__loggerObj__C, ".const:xdc_runtime_SysStd_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__loggerFxn0__C, ".const:xdc_runtime_SysStd_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__loggerFxn1__C, ".const:xdc_runtime_SysStd_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__loggerFxn2__C, ".const:xdc_runtime_SysStd_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__loggerFxn4__C, ".const:xdc_runtime_SysStd_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__loggerFxn8__C, ".const:xdc_runtime_SysStd_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Module__startupDoneFxn__C, ".const:xdc_runtime_SysStd_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Object__count__C, ".const:xdc_runtime_SysStd_Object__count__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Object__heap__C, ".const:xdc_runtime_SysStd_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Object__sizeof__C, ".const:xdc_runtime_SysStd_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_SysStd_Object__table__C, ".const:xdc_runtime_SysStd_Object__table__C");
    asm("	.sect \".const:xdc_runtime_SysStd_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_SysStd_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_SysStd_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__diagsEnabled__C, ".const:xdc_runtime_System_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_System_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__diagsIncluded__C, ".const:xdc_runtime_System_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_System_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__diagsMask__C, ".const:xdc_runtime_System_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_System_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__gateObj__C, ".const:xdc_runtime_System_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_System_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__gatePrms__C, ".const:xdc_runtime_System_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_System_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__id__C, ".const:xdc_runtime_System_Module__id__C");
    asm("	.sect \".const:xdc_runtime_System_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__loggerDefined__C, ".const:xdc_runtime_System_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_System_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__loggerObj__C, ".const:xdc_runtime_System_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_System_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__loggerFxn0__C, ".const:xdc_runtime_System_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_System_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__loggerFxn1__C, ".const:xdc_runtime_System_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_System_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__loggerFxn2__C, ".const:xdc_runtime_System_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_System_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__loggerFxn4__C, ".const:xdc_runtime_System_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_System_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__loggerFxn8__C, ".const:xdc_runtime_System_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_System_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Module__startupDoneFxn__C, ".const:xdc_runtime_System_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_System_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Object__count__C, ".const:xdc_runtime_System_Object__count__C");
    asm("	.sect \".const:xdc_runtime_System_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Object__heap__C, ".const:xdc_runtime_System_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_System_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Object__sizeof__C, ".const:xdc_runtime_System_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_System_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_Object__table__C, ".const:xdc_runtime_System_Object__table__C");
    asm("	.sect \".const:xdc_runtime_System_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_A_cannotFitIntoArg__C, ".const:xdc_runtime_System_A_cannotFitIntoArg__C");
    asm("	.sect \".const:xdc_runtime_System_A_cannotFitIntoArg__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_A_cannotFitIntoArg__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_A_cannotFitIntoArg__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_maxAtexitHandlers__C, ".const:xdc_runtime_System_maxAtexitHandlers__C");
    asm("	.sect \".const:xdc_runtime_System_maxAtexitHandlers__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_maxAtexitHandlers__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_maxAtexitHandlers__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_System_extendFxn__C, ".const:xdc_runtime_System_extendFxn__C");
    asm("	.sect \".const:xdc_runtime_System_extendFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_System_extendFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_System_extendFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_charTab__A, ".const:xdc_runtime_Text_charTab__A");
    asm("	.sect \".const:xdc_runtime_Text_charTab__A\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_charTab__A\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_charTab__A\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_nodeTab__A, ".const:xdc_runtime_Text_nodeTab__A");
    asm("	.sect \".const:xdc_runtime_Text_nodeTab__A\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_nodeTab__A\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_nodeTab__A\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__diagsEnabled__C, ".const:xdc_runtime_Text_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__diagsIncluded__C, ".const:xdc_runtime_Text_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__diagsMask__C, ".const:xdc_runtime_Text_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__gateObj__C, ".const:xdc_runtime_Text_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__gatePrms__C, ".const:xdc_runtime_Text_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__id__C, ".const:xdc_runtime_Text_Module__id__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__loggerDefined__C, ".const:xdc_runtime_Text_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__loggerObj__C, ".const:xdc_runtime_Text_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__loggerFxn0__C, ".const:xdc_runtime_Text_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__loggerFxn1__C, ".const:xdc_runtime_Text_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__loggerFxn2__C, ".const:xdc_runtime_Text_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__loggerFxn4__C, ".const:xdc_runtime_Text_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__loggerFxn8__C, ".const:xdc_runtime_Text_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Module__startupDoneFxn__C, ".const:xdc_runtime_Text_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_Text_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Object__count__C, ".const:xdc_runtime_Text_Object__count__C");
    asm("	.sect \".const:xdc_runtime_Text_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Object__heap__C, ".const:xdc_runtime_Text_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_Text_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Object__sizeof__C, ".const:xdc_runtime_Text_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_Text_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_Object__table__C, ".const:xdc_runtime_Text_Object__table__C");
    asm("	.sect \".const:xdc_runtime_Text_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_nameUnknown__C, ".const:xdc_runtime_Text_nameUnknown__C");
    asm("	.sect \".const:xdc_runtime_Text_nameUnknown__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_nameUnknown__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_nameUnknown__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_nameEmpty__C, ".const:xdc_runtime_Text_nameEmpty__C");
    asm("	.sect \".const:xdc_runtime_Text_nameEmpty__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_nameEmpty__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_nameEmpty__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_nameStatic__C, ".const:xdc_runtime_Text_nameStatic__C");
    asm("	.sect \".const:xdc_runtime_Text_nameStatic__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_nameStatic__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_nameStatic__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_isLoaded__C, ".const:xdc_runtime_Text_isLoaded__C");
    asm("	.sect \".const:xdc_runtime_Text_isLoaded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_isLoaded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_isLoaded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_charTab__C, ".const:xdc_runtime_Text_charTab__C");
    asm("	.sect \".const:xdc_runtime_Text_charTab__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_charTab__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_charTab__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_nodeTab__C, ".const:xdc_runtime_Text_nodeTab__C");
    asm("	.sect \".const:xdc_runtime_Text_nodeTab__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_nodeTab__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_nodeTab__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_charCnt__C, ".const:xdc_runtime_Text_charCnt__C");
    asm("	.sect \".const:xdc_runtime_Text_charCnt__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_charCnt__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_charCnt__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_nodeCnt__C, ".const:xdc_runtime_Text_nodeCnt__C");
    asm("	.sect \".const:xdc_runtime_Text_nodeCnt__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_nodeCnt__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_nodeCnt__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_unnamedModsLastId__C, ".const:xdc_runtime_Text_unnamedModsLastId__C");
    asm("	.sect \".const:xdc_runtime_Text_unnamedModsLastId__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_unnamedModsLastId__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_unnamedModsLastId__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_registryModsLastId__C, ".const:xdc_runtime_Text_registryModsLastId__C");
    asm("	.sect \".const:xdc_runtime_Text_registryModsLastId__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_registryModsLastId__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_registryModsLastId__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_visitRopeFxn__C, ".const:xdc_runtime_Text_visitRopeFxn__C");
    asm("	.sect \".const:xdc_runtime_Text_visitRopeFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_visitRopeFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_visitRopeFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Text_visitRopeFxn2__C, ".const:xdc_runtime_Text_visitRopeFxn2__C");
    asm("	.sect \".const:xdc_runtime_Text_visitRopeFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Text_visitRopeFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Text_visitRopeFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__diagsEnabled__C, ".const:xdc_runtime_Timestamp_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__diagsIncluded__C, ".const:xdc_runtime_Timestamp_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__diagsMask__C, ".const:xdc_runtime_Timestamp_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__gateObj__C, ".const:xdc_runtime_Timestamp_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__gatePrms__C, ".const:xdc_runtime_Timestamp_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__id__C, ".const:xdc_runtime_Timestamp_Module__id__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__loggerDefined__C, ".const:xdc_runtime_Timestamp_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__loggerObj__C, ".const:xdc_runtime_Timestamp_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__loggerFxn0__C, ".const:xdc_runtime_Timestamp_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__loggerFxn1__C, ".const:xdc_runtime_Timestamp_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__loggerFxn2__C, ".const:xdc_runtime_Timestamp_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__loggerFxn4__C, ".const:xdc_runtime_Timestamp_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__loggerFxn8__C, ".const:xdc_runtime_Timestamp_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Module__startupDoneFxn__C, ".const:xdc_runtime_Timestamp_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Object__count__C, ".const:xdc_runtime_Timestamp_Object__count__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Object__heap__C, ".const:xdc_runtime_Timestamp_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Object__sizeof__C, ".const:xdc_runtime_Timestamp_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_Timestamp_Object__table__C, ".const:xdc_runtime_Timestamp_Object__table__C");
    asm("	.sect \".const:xdc_runtime_Timestamp_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_Timestamp_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_Timestamp_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Object__DESC__C, ".const:xdc_runtime_knl_GateThread_Object__DESC__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Object__DESC__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Object__PARAMS__C, ".const:xdc_runtime_knl_GateThread_Object__PARAMS__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__diagsEnabled__C, ".const:xdc_runtime_knl_GateThread_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__diagsIncluded__C, ".const:xdc_runtime_knl_GateThread_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__diagsMask__C, ".const:xdc_runtime_knl_GateThread_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__gateObj__C, ".const:xdc_runtime_knl_GateThread_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__gatePrms__C, ".const:xdc_runtime_knl_GateThread_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__id__C, ".const:xdc_runtime_knl_GateThread_Module__id__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__loggerDefined__C, ".const:xdc_runtime_knl_GateThread_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__loggerObj__C, ".const:xdc_runtime_knl_GateThread_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__loggerFxn0__C, ".const:xdc_runtime_knl_GateThread_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__loggerFxn1__C, ".const:xdc_runtime_knl_GateThread_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__loggerFxn2__C, ".const:xdc_runtime_knl_GateThread_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__loggerFxn4__C, ".const:xdc_runtime_knl_GateThread_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__loggerFxn8__C, ".const:xdc_runtime_knl_GateThread_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Module__startupDoneFxn__C, ".const:xdc_runtime_knl_GateThread_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Object__count__C, ".const:xdc_runtime_knl_GateThread_Object__count__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Object__heap__C, ".const:xdc_runtime_knl_GateThread_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Object__sizeof__C, ".const:xdc_runtime_knl_GateThread_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_GateThread_Object__table__C, ".const:xdc_runtime_knl_GateThread_Object__table__C");
    asm("	.sect \".const:xdc_runtime_knl_GateThread_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_GateThread_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_GateThread_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Object__DESC__C, ".const:xdc_runtime_knl_SemProcess_Object__DESC__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Object__DESC__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Object__PARAMS__C, ".const:xdc_runtime_knl_SemProcess_Object__PARAMS__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__diagsEnabled__C, ".const:xdc_runtime_knl_SemProcess_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__diagsIncluded__C, ".const:xdc_runtime_knl_SemProcess_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__diagsMask__C, ".const:xdc_runtime_knl_SemProcess_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__gateObj__C, ".const:xdc_runtime_knl_SemProcess_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__gatePrms__C, ".const:xdc_runtime_knl_SemProcess_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__id__C, ".const:xdc_runtime_knl_SemProcess_Module__id__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__loggerDefined__C, ".const:xdc_runtime_knl_SemProcess_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__loggerObj__C, ".const:xdc_runtime_knl_SemProcess_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__loggerFxn0__C, ".const:xdc_runtime_knl_SemProcess_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__loggerFxn1__C, ".const:xdc_runtime_knl_SemProcess_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__loggerFxn2__C, ".const:xdc_runtime_knl_SemProcess_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__loggerFxn4__C, ".const:xdc_runtime_knl_SemProcess_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__loggerFxn8__C, ".const:xdc_runtime_knl_SemProcess_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Module__startupDoneFxn__C, ".const:xdc_runtime_knl_SemProcess_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Object__count__C, ".const:xdc_runtime_knl_SemProcess_Object__count__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Object__heap__C, ".const:xdc_runtime_knl_SemProcess_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Object__sizeof__C, ".const:xdc_runtime_knl_SemProcess_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemProcess_Object__table__C, ".const:xdc_runtime_knl_SemProcess_Object__table__C");
    asm("	.sect \".const:xdc_runtime_knl_SemProcess_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemProcess_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemProcess_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Object__DESC__C, ".const:xdc_runtime_knl_SemThread_Object__DESC__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Object__DESC__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Object__PARAMS__C, ".const:xdc_runtime_knl_SemThread_Object__PARAMS__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__diagsEnabled__C, ".const:xdc_runtime_knl_SemThread_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__diagsIncluded__C, ".const:xdc_runtime_knl_SemThread_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__diagsMask__C, ".const:xdc_runtime_knl_SemThread_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__gateObj__C, ".const:xdc_runtime_knl_SemThread_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__gatePrms__C, ".const:xdc_runtime_knl_SemThread_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__id__C, ".const:xdc_runtime_knl_SemThread_Module__id__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__loggerDefined__C, ".const:xdc_runtime_knl_SemThread_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__loggerObj__C, ".const:xdc_runtime_knl_SemThread_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__loggerFxn0__C, ".const:xdc_runtime_knl_SemThread_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__loggerFxn1__C, ".const:xdc_runtime_knl_SemThread_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__loggerFxn2__C, ".const:xdc_runtime_knl_SemThread_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__loggerFxn4__C, ".const:xdc_runtime_knl_SemThread_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__loggerFxn8__C, ".const:xdc_runtime_knl_SemThread_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Module__startupDoneFxn__C, ".const:xdc_runtime_knl_SemThread_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Object__count__C, ".const:xdc_runtime_knl_SemThread_Object__count__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Object__heap__C, ".const:xdc_runtime_knl_SemThread_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Object__sizeof__C, ".const:xdc_runtime_knl_SemThread_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_SemThread_Object__table__C, ".const:xdc_runtime_knl_SemThread_Object__table__C");
    asm("	.sect \".const:xdc_runtime_knl_SemThread_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_SemThread_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_SemThread_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Object__DESC__C, ".const:xdc_runtime_knl_Thread_Object__DESC__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Object__DESC__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Object__DESC__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Object__PARAMS__C, ".const:xdc_runtime_knl_Thread_Object__PARAMS__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Object__PARAMS__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Object__PARAMS__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__diagsEnabled__C, ".const:xdc_runtime_knl_Thread_Module__diagsEnabled__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__diagsEnabled__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__diagsEnabled__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__diagsIncluded__C, ".const:xdc_runtime_knl_Thread_Module__diagsIncluded__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__diagsIncluded__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__diagsIncluded__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__diagsMask__C, ".const:xdc_runtime_knl_Thread_Module__diagsMask__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__diagsMask__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__diagsMask__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__gateObj__C, ".const:xdc_runtime_knl_Thread_Module__gateObj__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__gateObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__gateObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__gatePrms__C, ".const:xdc_runtime_knl_Thread_Module__gatePrms__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__gatePrms__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__gatePrms__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__id__C, ".const:xdc_runtime_knl_Thread_Module__id__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__id__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__id__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__loggerDefined__C, ".const:xdc_runtime_knl_Thread_Module__loggerDefined__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__loggerDefined__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__loggerDefined__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__loggerObj__C, ".const:xdc_runtime_knl_Thread_Module__loggerObj__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__loggerObj__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__loggerObj__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__loggerFxn0__C, ".const:xdc_runtime_knl_Thread_Module__loggerFxn0__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__loggerFxn0__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__loggerFxn0__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__loggerFxn1__C, ".const:xdc_runtime_knl_Thread_Module__loggerFxn1__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__loggerFxn1__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__loggerFxn1__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__loggerFxn2__C, ".const:xdc_runtime_knl_Thread_Module__loggerFxn2__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__loggerFxn2__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__loggerFxn2__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__loggerFxn4__C, ".const:xdc_runtime_knl_Thread_Module__loggerFxn4__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__loggerFxn4__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__loggerFxn4__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__loggerFxn8__C, ".const:xdc_runtime_knl_Thread_Module__loggerFxn8__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__loggerFxn8__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__loggerFxn8__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Module__startupDoneFxn__C, ".const:xdc_runtime_knl_Thread_Module__startupDoneFxn__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Module__startupDoneFxn__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Module__startupDoneFxn__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Object__count__C, ".const:xdc_runtime_knl_Thread_Object__count__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Object__count__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Object__count__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Object__heap__C, ".const:xdc_runtime_knl_Thread_Object__heap__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Object__heap__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Object__heap__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Object__sizeof__C, ".const:xdc_runtime_knl_Thread_Object__sizeof__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Object__sizeof__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Object__sizeof__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_Object__table__C, ".const:xdc_runtime_knl_Thread_Object__table__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_Object__table__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_Object__table__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_A_zeroTimeout__C, ".const:xdc_runtime_knl_Thread_A_zeroTimeout__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_A_zeroTimeout__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_A_zeroTimeout__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_A_zeroTimeout__C\"");
    asm("	 .clink");
#endif
#ifdef __ti__
    #pragma DATA_SECTION(xdc_runtime_knl_Thread_defaultStackSize__C, ".const:xdc_runtime_knl_Thread_defaultStackSize__C");
    asm("	.sect \".const:xdc_runtime_knl_Thread_defaultStackSize__C\"");
    asm("	 .clink");
    asm("	.sect \"[0].const:xdc_runtime_knl_Thread_defaultStackSize__C\"");
    asm("	 .clink");
    asm("	.sect \"[1].const:xdc_runtime_knl_Thread_defaultStackSize__C\"");
    asm("	 .clink");
#endif
