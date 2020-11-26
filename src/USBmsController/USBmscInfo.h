/**
 * Copyright (c) 2011-2019 Bill Greiman
 * This file is part of the SdFat library for SD memory cards.
 *
 * Modified 2020 for use with SdFat and MSC. By Warren Watson.
 * 
 * MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef USBmscInfo_h
#define USBmscInfo_h
#include <stdint.h>
#include "../common/SysCall.h"

//---- Added For MSC --------------
#ifdef HAS_USB_MSC_CLASS
//#include "msc.h"
#include "USBHost_t36.h"
#endif  // HAS_USB_MSC_CLASS
//---------------------------------

// USB MSC errors TODO: Complete error code list!
#define USB_MSC_ERROR_CODE_LIST\
  USB_MSC_ERROR(NONE, "No error")

enum {
#define  USB_MSC_ERROR(e, m) USB_MSC_ERROR_##e,
  USB_MSC_ERROR_CODE_LIST
#undef USB_MSC_ERROR
  USB_MSC_ERROR_UNKNOWN
};
void printUSBErrorSymbol(print_t* pr, uint8_t code);
void printUSBErrorText(print_t* pr, uint8_t code);

const uint8_t SD_CARD_TYPE_USB = 4;
//-----------------------------------------------------------------------------

//---- Added For MSC --------------
#ifdef HAS_USB_MSC_CLASS
inline uint32_t USBmscCapacity(msController *pDrv) {
	return (pDrv->msDriveInfo.capacity.Blocks); 
}
#endif  // HAS_USB_MSC_CLASS
//---------------------------------

#endif  // USBmscInfo_h
