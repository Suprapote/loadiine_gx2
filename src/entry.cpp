#include <string.h>
#include "common/gx2_ext.h"

#include "utils/function_patcher.h"
#include "common/common.h"
#include "common/retain_vars.h"
#include "utils/utils.h"
#include "utils/logger.h"
#include "video/CursorDrawer.h"
#include "main.h"
#include <sys/socket.h>
#include <padscore/kpad.h>


extern "C" int main(int argc, char **argv)
{
    //! *********************************************************************
	//! *                        Initialize Kpad                            *
	//! *********************************************************************
	KPADInit();
	WPADEnableURCC(1);

    log_init();

    //!*******************************************************************
    //!                        Initialize HID Config                     *
    //!*******************************************************************
    //mount_sd_fat("sd");
    //ControllerPatcher::Init(CONTROLLER_PATCHER_PATH);
    //unmount_sd_fat("sd");
   // ControllerPatcher::disableControllerMapping();
    //if(gHIDPADNetwork){ ControllerPatcher::startNetworkServer(); }
    //ControllerPatcher::setRumbleActivated(gHIDPADRumble);

    //!*******************************************************************
    //!                        Dynamic Patching                          *
    //!*******************************************************************

    if(GAME_LAUNCHED){
         //ApplyPatches();
    }

    //! *******************************************************************
    //! *              Check if our application is started                *
    //! *******************************************************************
    /*if (OSGetTitleID != 0 &&
        OSGetTitleID() != 0x000500101004A200 && // mii maker eur
        OSGetTitleID() != 0x000500101004A100 && // mii maker usa
        OSGetTitleID() != 0x000500101004A000 && // mii maker jpn
        OSGetTitleID() != 0x0005000013374842)   // hbl channel
    {
        return 0;
    }*/

    //!*******************************************************************
    //!                       Check game launch                          *
    //!*******************************************************************
    // check if game is launched, if yes continue coreinit process
    if (GAME_LAUNCHED == 1) //&& (LOADIINE_MODE == LOADIINE_MODE_MII_MAKER))
        return 0;

    //! *******************************************************************
    //! *                     Setup EABI registers                        *
    //! *******************************************************************
    /*register int old_sdata_start, old_sdata2_start;
    asm volatile(
        "mr %0, 13\n"
        "mr %1, 2\n"
        "lis 2, __sdata2_start@h\n"
        "ori 2, 2,__sdata2_start@l\n"  // Set the Small Data 2 (Read Only) base register.
        "lis 13, __sdata_start@h\n"
        "ori 13, 13, __sdata_start@l\n"// # Set the Small Data (Read\Write) base register.
        : "=r" (old_sdata_start), "=r" (old_sdata2_start)
    );*/

    //!*******************************************************************
    //!                    Initialize BSS sections                       *
    //!*******************************************************************
    /*asm volatile(
        "lis 3, __bss_start@h\n"
        "ori 3, 3,__bss_start@l\n"
        "lis 5, __bss_end@h\n"
        "ori 5, 5, __bss_end@l\n"
        "subf 5, 3, 5\n"
        "li 4, 0\n"
        "bl memset\n"
    );*/

    //! *******************************************************************
    //! *                        Call our Main                            *
    //! *******************************************************************
    Menu_Main();

    //! *******************************************************************
    //! *                    Restore EABI registers                       *
    //! *******************************************************************
    /*asm volatile("mr 13, %0" : : "r" (old_sdata_start));
    asm volatile("mr 2,  %0" : : "r" (old_sdata2_start));*/

    if(GAME_LAUNCHED)
    {

        //! TODO: add auto launch with SYSLaunchTitle for Karaoke and Art Atelier Modes

        //! *******************************************************************
        //! *                 Jump to original application                    *
        //! *******************************************************************
        return 0;
    }

    //RestoreAllInstructions();

    CursorDrawer::destroyInstance();

    //! *******************************************************************
    //! *                 Jump to homebrew launcher                       *
    //! *******************************************************************
    return 0;
}
