#ifndef USBmscDevice_h
#define USBmscDevice_h
#include "../common/SysCall.h"

#ifdef HAS_USB_MSC_CLASS
#include "USBmscInterface.h"
#include "msc.h"
//class msController;

/**
 * \class SdioConfig
 * \brief SDIO card configuration.
 */
//class MSCConfig {
// public:
//  MSCConfig() :  m_pDrive(NULL) {};
  /**
   * SdioConfig constructor.
   * \param[in] opt SDIO options.
   */
//  explicit MSCConfig(msController *pDrive) : m_pDrive(pDrive) {}
  /** \return SDIO card options. */
//  msController *pDrive() {return m_pDrive;}
//  uint8_t options() {return m_options;}
  /** \return true if DMA_SDIO. */
//  bool useDma() {return m_options & DMA_SDIO;}
// private:
//  msController *m_pDrive;
//};

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/**
 * \class USBMSCDevice
 * \brief Raw USB Drive accesss.
 */
class USBMSCDevice : public USBmscInterface {
 public:
  /** Initialize the USB MSC device.
   * \param[in] Pointer to an instance of msc.
   * \return true for success or false for failure.
   */
  bool begin(msController *pDrive);
  uint32_t sectorCount();
  /**
   * \return code for the last error. See SdCardInfo.h for a list of error codes.
   */
  uint8_t errorCode() const;
  /** \return error data for last error. */
  uint32_t errorData() const;
  /** \return error line for last error. Tmp function for debug. */
  uint32_t errorLine() const;
  /**
   * Check for busy with CMD13.
   *
   * \return true if busy else false.
   */
  bool isBusy();
  /**
   * Read a 512 byte sector from an SD card.
   *
   * \param[in] sector Logical sector to be read.
   * \param[out] dst Pointer to the location that will receive the data.
   * \return true for success or false for failure.
   */
  bool readSector(uint32_t sector, uint8_t* dst);
  /**
   * Read multiple 512 byte sectors from an SD card.
   *
   * \param[in] sector Logical sector to be read.
   * \param[in] ns Number of sectors to be read.
   * \param[out] dst Pointer to the location that will receive the data.
   * \return true for success or false for failure.
   */
  bool readSectors(uint32_t sector, uint8_t* dst, size_t ns);
  /** \return SDIO card status. */
  uint32_t status();
  /** \return success if sync successful. Not for user apps. */
  bool syncDevice();
  /**
   * Writes a 512 byte sector to an SD card.
   *
   * \param[in] sector Logical sector to be written.
   * \param[in] src Pointer to the location of the data to be written.
   * \return true for success or false for failure.
   */
  bool writeSector(uint32_t sector, const uint8_t* src);
  /**
   * Write multiple 512 byte sectors to an SD card.
   *
   * \param[in] sector Logical sector to be written.
   * \param[in] ns Number of sectors to be written.
   * \param[in] src Pointer to the location of the data to be written.
   * \return true for success or false for failure.
   */
  bool writeSectors(uint32_t sector, const uint8_t* src, size_t ns);
// private:
//	MSCConfig m_mscConfig;

};
#endif // HAS_USB_MSC_CLASS
#endif  // USBmscDevice_h
