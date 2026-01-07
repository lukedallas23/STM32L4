#include "deslib.h"

/*
    Get the Unique Device ID

    @param   Unique Device ID structure pointer

*/
void desGetUdid(DES_UDID *udid) {

    ((uint32_t*)udid)[0] = getRegVal(R_DES_UDID_BASE, 0, 32);
    ((uint32_t*)udid)[1] = getRegVal(R_DES_UDID_BASE+4, 0, 32);
    ((uint32_t*)udid)[2] = getRegVal(R_DES_UDID_BASE+4, 0, 32);

}


/*
    Get the flash size in KB

    @returns Flash size in KBytes

*/
uint16_t desGetFlashSizeKb() {

    return getRegVal16(R_DES_FSDR_BASE, N_FLASH_SIZE, S_FLASH_SIZE);
}


/*
    Get the package type

    @returns Package type

*/
DES_PKG_TYPE desGetPkgType() {

    return getRegVal16(R_DES_PDR_BASE, N_PKG, S_PKG);
}
