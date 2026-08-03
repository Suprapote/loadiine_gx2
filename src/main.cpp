//#include <string>
#include <nsysnet/_socket.h>
#include "utils/logger.h"
#include "Application.h"
#include "fs/fs_utils.h"
#include "settings/CSettings.h"
#include "system/exception_handler.h"
#include "system/memory.h"
#include "utils/strings.h"
#include "utils/logger.h"
#include "utils/utils.h"
#include "utils/xml.h"
#include "common/common.h"
#include "main.h"

/* Entry point */
extern "C" int Menu_Main(void)
{
    //!*******************************************************************
    //!                   Initialize function pointers                   *
    //!*******************************************************************
    //! do OS (for acquire) and sockets first so we got logging
    //InitOSFunctionPointers();
    socket_lib_init();

    log_init();
    log_printf("Starting Loadiine GX2 " LOADIINE_VERSION "\n");

    /*InitFSFunctionPointers();
    InitGX2FunctionPointers();
    InitSysFunctionPointers();
    InitVPadFunctionPointers();
    InitPadScoreFunctionPointers();
    InitAXFunctionPointers();
    InitCurlFunctionPointers();

    InitAocFunctionPointers();
    InitACPFunctionPointers();*/

    log_printf("Function exports loaded\n");

    //!*******************************************************************
    //!                Initialize our kernel variables                   *
    //!*******************************************************************
    log_printf("Setup kernel variables\n");
    //SetupKernelCallback();
    //!*******************************************************************
    //!                    Initialize heap memory                        *
    //!*******************************************************************
    log_printf("Initialize memory management\n");
    memoryInitialize();

    //!*******************************************************************
    //!                        Initialize FS                             *
    //!*******************************************************************
    log_printf("Mount SD partition\n");
    //mount_sd_fat("sd");

    //!*******************************************************************
    //!                       Patch Functions                            *
    //!*******************************************************************
    log_printf("Patch FS and loader functions\n");
    //ApplyPatches();
    //PatchSDK();

    //!*******************************************************************
    //!                    Setup exception handler                       *
    //!*******************************************************************
    log_printf("Setup exception handler\n");
    setup_os_exceptions();

    //!*******************************************************************
    //!                    Enter main application                        *
    //!*******************************************************************
    log_printf("Start main application\n");
    Application::instance()->exec();
    log_printf("Main application stopped\n");

    Application::destroyInstance();

    log_printf("Unmount SD\n");
    //unmount_sd_fat("sd");
    log_printf("Release memory\n");
    memoryRelease();
    //! Shut down the socket library that was initialized on startup
    socket_lib_finish();
    log_printf("Loadiine peace out...\n");
    //log_deinit();

    return 0;
}

/*void ApplyPatches(){
    log_printf("Patching FS functions\n");
    PatchInvidualMethodHooks(method_hooks_fs,                   method_hooks_size_fs,               method_calls_fs);
    log_printf("Patching functions for AOC support\n");
    PatchInvidualMethodHooks(method_hooks_aoc,                  method_hooks_size_aoc,              method_calls_aoc);
    log_printf("Patching more FS functions (SD)\n");
    PatchInvidualMethodHooks(method_hooks_fs_sd,                method_hooks_size_fs_sd,            method_calls_fs_sd);
    log_printf("Patching functions for RPX/RPL loading\n");
    PatchInvidualMethodHooks(method_hooks_rplrpx,               method_hooks_size_rplrpx,           method_calls_rplrpx);
    log_printf("Patching extra log functions\n");
    PatchInvidualMethodHooks(method_hooks_extra_log,            method_hooks_size_extra_log,        method_calls_extra_log);
    log_printf("Patching controller_patcher (HID to VPAD)\n");
    PatchInvidualMethodHooks(method_hooks_hid_controller,       method_hooks_size_hid_controller,   method_calls_hid_controller);
}

void RestoreAllInstructions(){
    log_printf("Restoring FS functions\n");
    RestoreInvidualInstructions(method_hooks_fs,                method_hooks_size_fs);
    log_printf("Restoring functions for AOC support\n");
    RestoreInvidualInstructions(method_hooks_aoc,               method_hooks_size_aoc);
    log_printf("Restoring more FS functions (SD)\n");
    RestoreInvidualInstructions(method_hooks_fs_sd,             method_hooks_size_fs_sd);
    log_printf("Restoring functions for RPX/RPL loading\n");
    RestoreInvidualInstructions(method_hooks_rplrpx,            method_hooks_size_rplrpx);
    log_printf("Restoring extra log functions\n");
    RestoreInvidualInstructions(method_hooks_extra_log,         method_hooks_size_extra_log);
    log_printf("Restoring controller_patcher (HID to VPAD)\n");
    RestoreInvidualInstructions(method_hooks_hid_controller,    method_hooks_size_hid_controller);
}*/

