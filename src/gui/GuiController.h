/****************************************************************************
 * Copyright (C) 2015 Dimok
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 ****************************************************************************/
#ifndef GUI_CONTROLLER_H_
#define GUI_CONTROLLER_H_

#include <string.h>
#include <padscore/kpad.h>
#include <vpad/input.h>
#include "GuiTrigger.h"

class GuiController
{
public:
    //!Constructor
    GuiController(s32 channel)
        : chan(channel)
    {
        memset(&lastData, 0, sizeof(lastData));
        memset(&data, 0, sizeof(data));

        switch(chan)
        {
        default:
        case GuiTrigger::CHANNEL_1:
            vpadChanIdx = VPAD_CHAN_0;
            break;
        case GuiTrigger::CHANNEL_2:
            wpadChanIdx = WPAD_CHAN_0;
            break;
        case GuiTrigger::CHANNEL_3:
            wpadChanIdx = WPAD_CHAN_1;
            break;
        case GuiTrigger::CHANNEL_4:
            wpadChanIdx = WPAD_CHAN_2;
            break;
        case GuiTrigger::CHANNEL_5:
            wpadChanIdx = WPAD_CHAN_3;
            break;
        }
    }

    //!Destructor
    virtual ~GuiController()  {}

    virtual bool update(s32 width, s32 height) = 0;

    typedef struct
    {
        u32 buttons_h;
        u32 buttons_d;
        u32 buttons_r;
        bool validPointer;
        bool touched;
        f32 pointerAngle;
        s32 x;
        s32 y;
    } PadData;

    s32 chan;
    VPADChan vpadChanIdx;
    WPADChan wpadChanIdx;
    PadData data;
    PadData lastData;

};

#endif
