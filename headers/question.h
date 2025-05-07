/**
* Constants and functions for working with single questions in the SMART Response SDK V1.
* Copyright (C) 2009 SMART Technologies ULC. All rights reserved.
*/
#ifndef SMARTRESPONSE_V1_QUESTION_H
#define SMARTRESPONSE_V1_QUESTION_H

#include "types.h"

/**
* Specifies a ABCD-style multiple choice-type question. This is a closed question. There are
* between two and ten choices possible (each labeled A, B, C, D et cetera). Students may choose one
* choice for their responses.
*/
#define SMARTRESPONSE_QUESTIONTYPE_MULTIPLECHOICE 1

/**
* Specifies an ABCD-style multiple answer-type question. This is a closed question. There are
* between two and ten choices possible (each labeled A, B, C, D et cetera). Students may pick up
* to six choices for their responses. A correct answer must include ALL of the required choices.
*/
#define SMARTRESPONSE_QUESTIONTYPE_MULTIPLEANSWER 2

/**
* Specifies a Yes/No-style multiple choice-type question. This is a closed question. There are
* exactly two choices possible (labeled Yes and No). Students may choose one or the other choice for
* their responses.
*/
#define SMARTRESPONSE_QUESTIONTYPE_YESNO 3

/**
* Specifies a True/False-style multiple choice-type question. This is a closed question. There
* are exactly two choices possible (True and False). Students may choose one choice or the other for
* their responses.
*/
#define SMARTRESPONSE_QUESTIONTYPE_TRUEFALSE 4

/**
* Specifies a decimal-format numeric response-type question. This is an open question. Students may
* enter a positive or negative decimal value up to 11 characters in length for their responses.
* A correct answer must match exactly.
*/
#define SMARTRESPONSE_QUESTIONTYPE_DECIMAL 5

/**
* Specifies a fractional-format numeric response-type question. This is an open question. Students
* may enter a positive or negative mixed, unreduced, or improper fraction up to 11 characters in
* length for their responses. Fractions have a single space character separating a whole number
* part from a fraction part and a single solidus (U+002F) character separating a numerator for
* a denominator. A correct answer must match exactly.
*/
#define SMARTRESPONSE_QUESTIONTYPE_FRACTIONAL 6

/**
* Specifies a short text response-type question. This is an open question. Students may enter any 
* characters provided on the keypad. The current maximal number of characters they can enter is 20. 
*/
#define SMARTRESPONSE_QUESTIONTYPE_SHORTTEXT 7

/**
* Indicates the question was never started.
*/
#define SMARTRESPONSE_QUESTIONSTATUS_NEVERSTARTED 0

/**
* Indicates the question is in the process of starting.
*/
#define SMARTRESPONSE_QUESTIONSTATUS_STARTING 1

/**
* Indicates the question is started. Students may submit responses.
*/
#define SMARTRESPONSE_QUESTIONSTATUS_STARTED 2

/**
* Indicates the question is being stopped.
*/
#define SMARTRESPONSE_QUESTIONSTATUS_STOPPING 3

/**
* Indicates the question is stopped and is in review mode.
*/
#define SMARTRESPONSE_QUESTIONSTATUS_STOPPED 4

/**
* Indicates the question is stopped and there were no responses submitted.
*/
#define SMARTRESPONSE_QUESTIONSTATUS_CANCELLED 5
#ifdef __cplusplus
extern "C" {
#endif

/**
* Create a question description for the specified type. The question has no answer defined (i.e.,
* it is an opinion question).
* @param[in] aQuestionType One of the SMARTRESPONSE_QUESTIONTYPE_XYZ constants.
* @param[in] aChoiceCount The number of choices when aQuestionType is
*                        SMARTRESPONSE_QUESTIONTYPE_MULTIPLECHOICE or
*                        SMARTRESPONSE_QUESTIONTYPE_MULTIPLEANSWER.
* @return A question description or NULL if aChoiceCount is not valid.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_questionV1_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionV1_create(int aQuestionType, int aChoiceCount);

/**
* Destroys a question created with smartresponse_questionV1_create. Releasing question before question is stopped may cause unexpected behaviors.
* @param[in] aQuestion Question instance.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionV1_release(smartresponse_questionV1_t *aQuestion);

/**
* Gets the type of the question.
* @param[in] aQuestion Question instance.
* @return One of the SMARTRESPONSE_QUESTIONTYPE_XYZ constants.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionV1_type(smartresponse_questionV1_t *aQuestion);

/**
* Gets the (optional) question text as a plaintext UTF-8 encoded string.
* @param[in] aQuestion Question instance.
* @param[in] aBuffer Buffer to hold UTF-8 encoded bytes or NULL to query for the required size of
*                   buffer.
* @param[in] theBufferSize Size of aBuffer in bytes or zero to query for the required size of buffer.
* @return The size of buffer needed to hold the entire string not including a terminating NUL byte.
*
* The returned string includes a terminating NUL byte if aBuffer has sufficient space for it.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionV1_questiontext(smartresponse_questionV1_t *aQuestion, char *aBuffer, int theBufferSize);

/**
* Sets the (optional) question text as a plaintext UTF-8 encoded string.
* @param[in] aQuestion Question instance.
* @param[in] aString UTF-8 encoded string for the platintext question.
* @param[in] theStringLength Number of bytes in aString, or -1 if it is NUL terminated.
*
* This function will trigger an exception if it is called with the return result of smartresponse_connectionV1_currentquestion.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionV1_setquestiontext(smartresponse_questionV1_t *aQuestion, char *aString, int theStringLength);

/**
* Gets the correct answer of a question as a UTF-8 encoded string.
* @param[in] aQuestion Question instance.
* @param[in] aBuffer Buffer to hold UTF-8 encoded bytes or NULL to query for the required size of
*                   buffer.
* @param[in] theBufferSize Size of aBuffer in bytes or zero to query for the rquired size of buffer.
* @return The size of buffer needed to hold the entire string, not including the terminating NUL
*         byte.
*
* The returned string is NUL terminated if there is sufficient space available.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionV1_answer(smartresponse_questionV1_t *aQuestion, char *aBuffer, int theBufferSize);

/**
* Sets the correct answer for the question as a UTF-8 encoded string.
* @param[in] aQuestion Question instance.
* @param[in] aString Answer text.
* @param[in] theStringLength The length of aString in bytes, or -1 if aString is NUL terminated.
*
* The answer is a string with a different format depending on the question type:
*
*    multiple choice: "A", "B", "C", ... "J"
*             yes/no: "Y", "N"
*         true/false: "T", "F"
*    multiple answer: "ABCDEF"
*            decimal: "-12.345"
*         fractional: "-12 34/57"
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionV1_setanswer(smartresponse_questionV1_t *aQuestion, char *aString, int theStringLength);

/**
* Gets the number of choices in a closed question.
* @param[in] aQuestion Question instance.
* @return Zero if aQuestion is an open question; non-zero integer in the range [2, 10] otherwise.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionV1_choicecount(smartresponse_questionV1_t *aQuestion);

/**
* Gets the (optional) text associated with a choice as a plaintext UTF-8 encoded string.
* @param[in] aQuestion Question instance.
* @param[in] anIndex Choice index, a value between [0, number of choices).
* @param[in] aBuffer Buffer to hold returned string; NULL to query for required length of buffer.
* @param[in] theBufferSize Size of aBuffer.
* @return The required length of buffer to hold the entire string, not including the terminating
* NUL byte.
*
* The string returned is NUL terminated if there is sufficient space in aBuffer.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionV1_choicetext(smartresponse_questionV1_t *aQuestion, int anIndex, char *aBuffer, int theBufferSize);

/**
* Sets the (optional) text associated with a choice as a plaintext UTF-8 encoded string.
* @param[in] aQuestion Question instance.
* @param[in] anIndex Choice index, a value between [0, number of choice).
* @param[in] aString New value to set.
* @param[in] theStringLength The length of aString, or -1 if aString is NUL terminated.
* 
* If the question type is Yes/No, True/False or Numeric/fractional question, this function is not mandatory. 
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionV1_setchoicetext(smartresponse_questionV1_t *aQuestion, int anIndex, char *aString, int theStringLength);

/**
* Gets the (optional) question's points.
* @param[in] aQuestion Question instance.
* @return the question's points.
*/
SMARTRESPONSE_SDK_DECLSPEC double SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionV1_questionpoints(smartresponse_questionV1_t *aQuestion);

/**
* Sets the (optional) text associated with a choice as a plaintext UTF-8 encoded string.
* @param[in] aQuestion Question instance.
* @param[in] points the question's points.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_questionV1_setquestionpoints(smartresponse_questionV1_t *aQuestion, double points);

/**
* Gets the (optional) choice label associated with a choice as a plaintext UTF-8 encoded string.
* @param[in] aQuestion Question instance.
* @param[in] anIndex Choice index, a value between [0, number of choices).
* @param[in] aBuffer Buffer to hold returned string; NULL to query for required length of buffer.
* @param[in] theBufferSize Size of aBuffer.
* @return The required length of buffer to hold the entire string, not including the terminating
* NUL byte.
*
* The string returned is NUL terminated if there is sufficient space in aBuffer.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC sr_question_choicelabel(smartresponse_questionV1_t *aQuestion, int anIndex, char *aBuffer, int theBufferSize);

/**
* Sets the (optional) choice label associated with a choice as a plaintext UTF-8 encoded string.
* @param[in] aQuestion Question instance.
* @param[in] anIndex Choice index, a value between [0, number of choice).
* @param[in] aString New value to set.
* @param[in] theStringLength The length of aString, or -1 if aString is NUL terminated.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC sr_question_setchoicelabel(smartresponse_questionV1_t *aQuestion, int anIndex, char *aString, int theStringLength);

#ifdef __cplusplus
}
#endif

#endif
