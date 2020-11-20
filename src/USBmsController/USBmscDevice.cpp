
#include "USBMSCDevice.h"
#include "USBmscInfo.h"

#ifdef HAS_USB_MSC_CLASS
const uint32_t BUSY_TIMEOUT_MICROS = 1000000;

static bool yieldTimeout(bool (*fcn)());
static bool waitTimeout(bool (*fcn)());
static bool m_initDone = false;
static bool (*m_busyFcn)() = 0;
static uint8_t m_errorCode = MS_NO_MEDIA_ERR;
static uint32_t m_errorLine = 0;
static msController *thisDrive = nullptr;
static bool isBusyRead();
static bool isBusyWrite();

//==============================================================================
// Error function and macro.
#define sdError(code) setSdErrorCode(code, __LINE__)
inline bool setSdErrorCode(uint8_t code, uint32_t line) {
  m_errorCode = code;
  m_errorLine = line;
  return false;
}

//------------------------------------------------------------------------------
// Return true if timeout occurs.
static bool yieldTimeout(bool (*fcn)()) {
  m_busyFcn = fcn;
  uint32_t m = micros();
  while (fcn()) {
    if ((micros() - m) > BUSY_TIMEOUT_MICROS) {
      m_busyFcn = 0;
      return true;
    }
    SysCall::yield();
  }
  m_busyFcn = 0;
  return false;  // Caller will set errorCode.
}
//------------------------------------------------------------------------------
// Return true if timeout occurs.
static bool waitTimeout(bool (*fcn)()) {
  uint32_t m = micros();
  while (fcn()) {
    if ((micros() - m) > BUSY_TIMEOUT_MICROS) {
      return true;
    }
  }
  return false;  // Caller will set errorCode.
}

static bool isBusyRead() {
	return thisDrive->mscTransferComplete;
}

static bool isBusyWrite() {
	return thisDrive->mscTransferComplete;
}

//------------------------------------------------------------------------------
uint8_t USBMSCDevice::errorCode() const {
  return m_errorCode;
}
//------------------------------------------------------------------------------
uint32_t USBMSCDevice::errorData() const {
  return 0;
}
//------------------------------------------------------------------------------
uint32_t USBMSCDevice::errorLine() const {
  return m_errorLine;
}

//------------------------------------------------------------------------------
bool USBMSCDevice::isBusy() {
  return m_busyFcn ? m_busyFcn() : m_initDone && thisDrive->mscTransferComplete;
}

//------------------------------------------------------------------------------
bool USBMSCDevice::syncDevice() {
  return true;
}

//------------------------------------------------------------------------------
uint32_t USBMSCDevice::status() {
  return m_errorCode;
}

//------------------------------------------------------------------------------
uint32_t USBMSCDevice::sectorCount() {
  return thisDrive->msDriveInfo.capacity.Blocks;
}

//==============================================================================
// Start of USBMSCDevice member functions.
//==============================================================================
bool USBMSCDevice::begin(msController *pDrive) {
	m_errorCode = MS_CBW_PASS;
	thisDrive = pDrive;
	pDrive->mscInit(); // Do initial init of each instance of a MSC object.
	if((m_errorCode = pDrive->checkConnectedInitialized())) // Check for Connected USB drive.
		m_initDone = false;
	else
		m_initDone = true;
	return m_errorCode;
}

//------------------------------------------------------------------------------
bool USBMSCDevice::readSector(uint32_t sector, uint8_t* dst) {
  return readSectors(sector, dst, 1);
}
//------------------------------------------------------------------------------
bool USBMSCDevice::readSectors(uint32_t sector, uint8_t* dst, size_t n) {
//Serial.printf("readSectors()\n");
	m_errorCode = thisDrive->msReadBlocks(sector, n, (uint16_t)512, dst);
//Serial.printf("m_errorCode = %d\n",m_errorCode);	
	if(m_errorCode) {
		return false;
	}
	return true;
}
//------------------------------------------------------------------------------
bool USBMSCDevice::writeSector(uint32_t sector, const uint8_t* src) {
  return writeSectors(sector, src, 1);
}
//------------------------------------------------------------------------------
bool USBMSCDevice::writeSectors(uint32_t sector, const uint8_t* src, size_t n) {
//Serial.printf("writeSectors()\n");
	m_errorCode = thisDrive->msWriteBlocks(sector, n, (uint16_t)512, src);
//Serial.printf("m_errorCode = %d\n",m_errorCode);	
	if(m_errorCode) {
		return false;
	}
  return true;
}
#endif // HAS_USB_MSC_CLASS
