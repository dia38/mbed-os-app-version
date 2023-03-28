/**
********************************************************************************
* @file   TemplateFileCode.c
* @author ItsMe
* @brief  write here a short description of the file on a single ligne.
* @note   Here start a longer description for the file on multiple lignes as you 
*         like. Write whatever you believe important for using this file.
********************************************************************************
*/

/******************************************************************************\
* INCLUSIONS                                                                   *
\******************************************************************************/

// global types and constants declaration file
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <inttypes.h>

// include the header of this code file
#include "averVersion.h"

// include an interface file
#include "averUserVersion.h"

/******************************************************************************\
* PRIVATE SYMBOLIC CONSTANTS and MACROS                                        *
\******************************************************************************/

#if defined(MBED_CONF_APP_VERSION_MAJOR)
#define VERSION_MAJOR   (MBED_CONF_APP_VERSION_MAJOR)
#else
#error Not Define "App_Version.MAJOR" : xxxx  in mbed_app.json
#endif

#if defined(MBED_CONF_APP_VERSION_MINOR)
#define VERSION_MINOR   (MBED_CONF_APP_VERSION_MINOR)
#else
#error Not Define "App_Version.MINOR" : xxxx  in mbed_app.json.
#endif

#if defined(MBED_CONF_APP_VERSION_PATCH)
#define VERSION_PATCH   (MBED_CONF_APP_VERSION_PATCH)
#else
#error Not Define "App_Version.PATCH" : xxxx in mbed_app.json.
#endif

#if !defined(USER_VERSION_PRE_RELEASE)
#error Not Define Pre-Release identifier.
#endif

#if !defined(USER_VERSION_BUILD)
#error Not Define Pre-Release identifier.
#endif

/******************************************************************************\
* PRIVATE TYPES, STRUCTURES, UNIONS ans ENUMS                                  *
\******************************************************************************/

/******************************************************************************\
* PRIVATE MEMBER VARIABLES                                                     *
\******************************************************************************/


/**
* Public variable description.
*/
const uint8_t averMajorVersion = VERSION_MAJOR;

/**
 * MinorVersion Number
*/
const uint8_t averMinorVersion = VERSION_MINOR;

/**
 * Patch Version Number
*/
const uint8_t averPatchVersion = VERSION_PATCH;

/**
 * Pre-release Version 
 * @note Empty String Means Official Version
*/
const char     averPreReleaseVersion[averPRE_RELEASE_SIZE] = USER_VERSION_PRE_RELEASE;

/**
 * Build Version Number
*/
const uint32_t averBuildVersion = USER_VERSION_BUILD;

/******************************************************************************\
* PRIVATE FUNCTION PROTOTYPES                                                  *
\******************************************************************************/
 
/******************************************************************************\
* PRIVATE FUNCTION CODE                                                        *
\******************************************************************************/

/******************************************************************************\
* PUBLIC FUNCTION CODE                                                         *
\******************************************************************************/

/**
 * 
*/
void averPrintVersion(FILE * parOut)
{

    fprintf(parOut, "Version : "
                    "%" PRIu8      // Major
                    ".%" PRIu8     // Minor
                    ".%" PRIu8     // Build
                    , averMajorVersion, averMinorVersion, averPatchVersion);
    if (averPreReleaseVersion[0] != '\0')
    {
        fprintf(parOut, "-%s", averPreReleaseVersion);
    }

    fprintf(parOut, "+%" PRIu32     // Build
                    "\n", averBuildVersion);
}


/******************************************************************************\
* END OF FILE                                                                  *
\******************************************************************************/

