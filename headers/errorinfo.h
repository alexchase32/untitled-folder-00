/**
* Constants and functions for dealing with asynchronous errors in the SMART Response SDK V1.
* Copyright (C) 2009 SMART Technologies ULC. All rights reserved.
*/
#ifndef SMARTRESPONSE_V1_ERRORINFO_H
#define SMARTRESPONSE_V1_ERRORINFO_H

#include "types.h"

#define UNSUPPORTED_QUESTION_TYPE_CODE			700
#define EXCEED_CHOICE_OR_SELECTION_COUNT_CODE	701
#define BOTH_700_AND_701_ERROR					702
#define NOT_CONNECTED_TO_RESPONSE				703     // Not connected to Response services
#define UNSUPPORTED_FEATURE						704		// In some mode, some features cannot be supported
#define NO_QUESTION                             705
#define CLASS_RUNNING							706		// A class is running

#define UNDEFINED_MODE							707		// Undefined hardware/virtual mode
#define RESPONSE_APPS_RUNNING					708		// Cannot switch mode while Response applications running
#define ERROR_WRITING_REGISTRY					710		// Cannot write to the registry

#ifdef __cplusplus
extern "C" {
#endif

/**
* Releases a reference returned by a successful call to smartresponse_connectionV1_copyerrorinfo.
* @param[in] anError Error info reference.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_errorinfoV1_release(smartresponse_errorinfoV1_t *anError);

/**
* Gets the HTTP status code returned for the failed request, or -1 if the request failed because of
* a software service connection failure.
* @param[in] anError Error info reference.
* @return HTTP status code (3xx, 4xx, or 5xx) if the request was refused by the software service or
*         -1 if the connection to the software service failed
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_errorinfoV1_statuscode(smartresponse_errorinfoV1_t *anError);

/**
* Gets a short human-readable UTF-8 encoded string describing the error.
* @param[in] anError Error info reference.
* @param[in] aBuffer Buffer to hold UTF-8 encoded characters or NULL to query for the length of
*                   buffer required.                    
* @param[in] theBufferSize Size of aBuffer in bytes or zero to query for the length of buffer
*                         required.
* @return The size of a buffer big enough to hold the entire text (not including terminating NUL
*         byte. The string returned in aBuffer is NUL terminated if there is room for it.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_errorinfoV1_statustext(smartresponse_errorinfoV1_t *anError, char *aBuffer, int theBufferSize);

/**
* Gets a string giving full details about the HTTP transaction for the error.
* @param[in] anError Error info reference.
* @param[in] aBuffer Buffer to hold UTF-8 encoded characters or NULL to query for the length of
*                   buffer required.                    
* @param[in] theBufferSize Size of aBuffer in bytes or zero to query for the length of buffer
*                         required.
* @return The size of a buffer big enough to hold the entire text (not including terminating NUL
*         byte. The string returned in aBuffer is NUL terminated if there is room for it.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_errorinfoV1_fulldetails(smartresponse_errorinfoV1_t *anError, char *aBuffer, int theBufferSize);

/**
* Return an array of questionIDs that are not supported under current mode
* @param[in] anError Error info reference.
* @param[in] question_numbers an array to hold the unsupported questions' ids.                   
* @param[in] theBufferSize Size of question_numbers in bytes or zero to query for the size of buffer
*                         required.
* @return The size of a buffer big enough to hold the entire array 
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_errorinfoV1_unsupportedquestions(smartresponse_errorinfoV1_t *anError, int *question_numbers, int theBufferSize);

#ifdef __cplusplus
}
#endif

#endif
