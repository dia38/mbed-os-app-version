/**
********************************************************************************
* @file averVersion.h
* @author ItsMe
* @brief  Module Version
* @note   Manger the current version of this application version follow
*         SemVer 2.0 <major>.<minor>.<patch>-<pre-release>+<build>
********************************************************************************
*/
#ifndef __AVER_VERSION_H
#define __AVER_VERSION_H

/******************************************************************************\
* INCLUSIONS                                                                   *
\******************************************************************************/
#include <stdint.h>
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************\
* PUBLIC SYMBOLIC CONSTANTS and MACROS                                         *
\******************************************************************************/

/**
* Maximal Size of Pre-Release Field
*/
#define averPRE_RELEASE_SIZE     (50U)

/******************************************************************************\
* PUBLIC TYPES, STRUCTURES, UNIONS and ENUMS                                   *
\******************************************************************************/


/******************************************************************************\
* PUBLIC VARIABLES                                                             *
\******************************************************************************/

/**
* Public variable description.
*/
extern const uint8_t averMajorVersion;

/**
 * MinorVersion Number
*/
extern const uint8_t averMinorVersion;

/**
 * Patch Version Number
*/
extern const uint8_t averPatchVersion;

/**
 * Pre-release Version 
 * @note Empty String Means Official Version
*/
extern const char     averPreReleaseVersion[averPRE_RELEASE_SIZE];

/**
 * Build Version Number
*/
extern const uint32_t averBuildVersion;


/******************************************************************************\
* PUBLIC FUNCTION PROTOTYPES                                                   *
\******************************************************************************/


/**
 * 
*/
void averPrintVersion(FILE * parOut);



#ifdef __cplusplus
}
#endif

/******************************************************************************\
* END OF FILE                                                                  *
\******************************************************************************/
#endif /*__AVER_VERSION_H*/
