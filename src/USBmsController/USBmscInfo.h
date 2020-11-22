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

// SD card errors
// See the SD Specification for command info.
// USB MSC errors
#define USB_MSC_ERROR_CODE_LIST\
  USB_MSC_ERROR(NONE, "No error")\
  USB_MSC_ERROR(CMD0, "Card reset failed")\
  USB_MSC_ERROR(CMD2, "SDIO read CID")\
  USB_MSC_ERROR(CMD3, "SDIO publish RCA")\
  USB_MSC_ERROR(CMD6, "Switch card function")\
  USB_MSC_ERROR(CMD7, "SDIO card select")\
  USB_MSC_ERROR(CMD8, "Send and check interface settings")\
  USB_MSC_ERROR(CMD9, "Read CSD data")\
  USB_MSC_ERROR(CMD10, "Read CID data")\
  USB_MSC_ERROR(CMD12, "Stop multiple block read")\
  USB_MSC_ERROR(CMD13, "Read card status")\
  USB_MSC_ERROR(CMD17, "Read single block")\
  USB_MSC_ERROR(CMD18, "Read multiple blocks")\
  USB_MSC_ERROR(CMD24, "Write single block")\
  USB_MSC_ERROR(CMD25, "Write multiple blocks")\
  USB_MSC_ERROR(CMD32, "Set first erase block")\
  USB_MSC_ERROR(CMD33, "Set last erase block")\
  USB_MSC_ERROR(CMD38, "Erase selected blocks")\
  USB_MSC_ERROR(CMD58, "Read OCR register")\
  USB_MSC_ERROR(CMD59, "Set CRC mode")\
  USB_MSC_ERROR(ACMD6, "Set SDIO bus width")\
  USB_MSC_ERROR(ACMD13, "Read extended status")\
  USB_MSC_ERROR(ACMD23, "Set pre-erased count")\
  USB_MSC_ERROR(ACMD41, "Activate card initialization")\
  USB_MSC_ERROR(READ_TOKEN, "Bad read data token")\
  USB_MSC_ERROR(READ_CRC, "Read CRC error")\
  USB_MSC_ERROR(READ_FIFO, "SDIO fifo read timeout")\
  USB_MSC_ERROR(READ_REG, "Read CID or CSD failed.")\
  USB_MSC_ERROR(READ_START, "Bad readStart argument")\
  USB_MSC_ERROR(READ_TIMEOUT, "Read data timeout")\
  USB_MSC_ERROR(STOP_TRAN, "Multiple block stop failed")\
  USB_MSC_ERROR(WRITE_DATA, "Write data not accepted")\
  USB_MSC_ERROR(WRITE_FIFO, "SDIO fifo write timeout")\
  USB_MSC_ERROR(WRITE_START, "Bad writeStart argument")\
  USB_MSC_ERROR(WRITE_PROGRAMMING, "Flash programming")\
  USB_MSC_ERROR(WRITE_TIMEOUT, "Write timeout")\
  USB_MSC_ERROR(DMA, "DMA transfer failed")\
  USB_MSC_ERROR(ERASE, "Card did not accept erase commands")\
  USB_MSC_ERROR(ERASE_SINGLE_SECTOR, "Card does not support erase")\
  USB_MSC_ERROR(ERASE_TIMEOUT, "Erase command timeout")\
  USB_MSC_ERROR(INIT_NOT_CALLED, "Card has not been initialized")\
  USB_MSC_ERROR(INVALID_CARD_CONFIG, "Invalid card config")\
  USB_MSC_ERROR(FUNCTION_NOT_SUPPORTED, "Unsupported SDIO command")

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
inline uint32_t USBmscCapacity() {
    return 0;
}
//-----------------------------------------------------------------------------
// fields are big endian
typedef struct USBmscStatus {
} USBmscStatus_t;
#endif  // USBmscInfo_h
