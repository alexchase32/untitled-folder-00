/**
* Constants and functions for working with single questions in the SMART Response SDK V1.
* Copyright (C) 2009 SMART Technologies ULC. All rights reserved.
*/
#ifndef SMARTRESPONSE_V1_QUESTIONSET_H
#define SMARTRESPONSE_V1_QUESTIONSET_H
#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* Create a question set description. 
* @return A question set description.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_questionsetV1_t* SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionsetV1_create();

/**
* Destroys a question set created with smartresponse_questionsetV1_create. Releasing question set before question is stopped may cause unexpected behaviors.
* @param[in] aQuestionSet Question set instance.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionsetV1_release(smartresponse_questionsetV1_t* aQuestionSet);

/**
* Gets the (optional) question set's points.
* @param[in] aQuestionSet Question set instance.
* @return the question set 's points.
*/
SMARTRESPONSE_SDK_DECLSPEC double SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionsetV1_points(smartresponse_questionsetV1_t* aQuestionSet);

/**
* Gets the (optional) question set's name.
* @param[in] aQuestionSet Question set instance.
* @param[in] aBuffer Buffer to hold returned string; NULL to query for required length of buffer.
* @param[in] theBufferSize Size of aBuffer.
* @return The required length of buffer to hold the entire string, not including the terminating
* NUL byte.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionsetV1_name(smartresponse_questionsetV1_t* aQuestionSet, char *aBuffer, int theBufferSize);

/**
* Gets the (optional) question set's name.
* @param[in] aQuestionSet Question set instance.
* @param[in] aString New value to set.
* @param[in] theStringLength The length of aString, or -1 if aString is NUL terminated.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionsetV1_setname(smartresponse_questionsetV1_t* aQuestionSet, char *aString, int theStringLength);

/**
* Gets the (optional) the number of questions in the question set
* @param[in] aQuestionSet Question set instance.
* @return the number of questions in the question set
*
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionsetV1_questioncount(smartresponse_questionsetV1_t* aQuestionSet);

/**
* Set the question with specific index.
* @param[in] aQuestionSet Question set instance.
* @param[in] aQuestion Question instance to be added to the question set
* @param[in] anIndex Question index, a value between [0, number of questions). if anIndex == -1, aQuestion will be appended to the aQuestionset. It is highly recommended to use the automatic appending when creating a new set of questions.
*
* All the questions added to the question set must be released later by using smartresponse_questionv1_release; 
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionsetV1_setquestion(smartresponse_questionsetV1_t* aQuestionSet, smartresponse_questionV1_t* aQuestion, int anIndex);

/**
* Gets the (optional) question from a given question set.
* @param[in] aQuestionSet Question instance.
* @param[in] anIndex question index, a value between [0, number of questions).
* @return a Reference to the question or NULL if there is no question associated with the given index
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_questionV1_t* SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionsetV1_question(smartresponse_questionsetV1_t* aQuestionSet, int anIndex);
#ifdef __cplusplus
}
#endif

#endif