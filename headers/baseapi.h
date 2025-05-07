/**
* Essential data types, constants and functions for the SMART Response SDK V1.
* Copyright (C) 2009 SMART Technologies ULC. All rights reserved.
*/

#ifndef SMARTRESPONSE_BASEAPI_H
#define SMARTRESPONSE_BASEAPI_H

#ifndef SMARTRESPONSE_SDK_DECLSPEC
#ifdef _WIN32
#define SMARTRESPONSE_SDK_DECLSPEC __declspec(dllimport)
#else
#define SMARTRESPONSE_SDK_DECLSPEC __attribute__((visibility("default")))
#endif
#endif

#ifndef SMARTRESPONSE_SDK_CALLSPEC
#ifdef _WIN32
#define SMARTRESPONSE_SDK_CALLSPEC __stdcall
#else
#define SMARTRESPONSE_SDK_CALLSPEC 
#endif
#endif

/**
* Constant that defines the current SDK version.
*/


#ifndef SMARTRESPONSE_SDK_CALLBACK_DEFINED
#define SMARTRESPONSE_SDK_CALLBACK_DEFINED
#ifdef _WIN32
/**
* Common typedef for all smartresponse_abc_listenonxyz callbacks.
* @param[in] aContext The context parameter specified in the smartresponse_abc_listenonxyz function call.
*/
typedef void (__stdcall * SMARTRESPONSE_SDK_CALLBACK)(void *aContext);
/**
* Common typedef for all clicker state change related smartresponse_abc_listenonxyz callbacks.
* @param[in] id The id of the clicker or student. It is a null terminated string.  In the anonymous class, it is the mac address of the clicker. In the sign-in class, it is the student sign-in id.
* @param[in] aContext The context parameter specified in the smartresponse_abc_listenonxyz function call.
*/
typedef void (__stdcall * SMARTRESPONSE_SDK_CLICKER_STATE_CHANGE_CALLBACK)(char* id, void* aContext);



/**
* Common typedef for all clicker responded related smartresponse_abc_listenonxyz callbacks.
* @param[in] id The id of the clicker or student. It is a null terminated string.  In the anonymous class, it is the mac address of the clicker. In the sign-in class, it is the student sign-in id.
* @param[in] studentId a null terminated string, the student ID of a clicker.
* @param[in] questionID The question ID of the question that the student just answered.
* @param[in] answer the answer that the clicker just typed in. It is a null terminated string. 
* The answer is a string with a different format depending on the question type:
*
*    multiple choice: "A", "B", "C", ... "J"
*             yes/no: "Y", "N"
*         true/false: "T", "F"
*    multiple answer: "ABCDEF"
*            decimal: "-12.345"
*         fractional: "-12 34/57"
*
* @param[in] aContext The context parameter specified in the smartresponse_abc_listenonxyz function call.
*/
typedef void (__stdcall * SMARTRESPONSE_SDK_CLICKER_RESPONDED_CALLBACK)(char* id, char* questionId, char* response, void* aContext);

#else


/**
 * Common typedef for all smartresponse_abc_listenonxyz callbacks.
 * @param[in] aContext The context parameter specified in the smartresponse_abc_listenonxyz function call.
 */
typedef void (* SMARTRESPONSE_SDK_CALLBACK)(void *aContext);

/**
 * Common typedef for all clicker state change related smartresponse_abc_listenonxyz callbacks.
 * @param[in] id The id of the clicker or student. It is a null terminated string.  In the anonymous class, it is the mac address of the clicker. In the sign-in class, it is the student sign-in id.
 * @param[in] aContext The context parameter specified in the smartresponse_abc_listenonxyz function call.
 */
typedef void (* SMARTRESPONSE_SDK_CLICKER_STATE_CHANGE_CALLBACK)(char* id, void* aContext);


/**
 * Common typedef for all clicker responded related smartresponse_abc_listenonxyz callbacks.
 * @param[in] id The id of the clicker or student. It is a null terminated string.  In the anonymous class, it is the mac address of the clicker. In the sign-in class, it is the student sign-in id.
 * @param[in] studentId a null terminated string, the student ID of a clicker.
 * @param[in] questionID The question ID of the question that the student just answered.
 * @param[in] answer the answer that the clicker just typed in. It is a null terminated string. 
 * The answer is a string with a different format depending on the question type:
 *
 *    multiple choice: "A", "B", "C", ... "J"
 *             yes/no: "Y", "N"
 *         true/false: "T", "F"
 *    multiple answer: "ABCDEF"
 *            decimal: "-12.345"
 *         fractional: "-12 34/57"
 *
 * @param[in] aContext The context parameter specified in the smartresponse_abc_listenonxyz function call.
 */
typedef void (* SMARTRESPONSE_SDK_CLICKER_RESPONDED_CALLBACK)(char* id, char* questionId, char* answer, void* aContext);



#endif
#endif


#ifndef SMARTRESPONSE_SDK_LISTENER_DEFINED
#define SMARTRESPONSE_SDK_LISTENER_DEFINED
/**
* Opaque handle for a callback bound in a smartresponse_abc_listenonxyz function call.
*/
typedef struct _smartresponse_listener
{
	virtual ~_smartresponse_listener(){}
}smartresponse_listener_t;
#endif

#ifndef SMARTRESPONSE_SDK_CONDITION_DEFINED
#define SMARTRESPONSE_SDK_CONDITION_DEFINED
/**
* Opaque handle for a GUI-safe condition variable.
*/
typedef struct _smartresponse_condition
{
	virtual ~_smartresponse_condition(){}
} smartresponse_condition_t;
#endif

#ifdef __cplusplus
extern "C" {
#endif



/**
* Return the length of a null-terminated UTF8 char*
*
* @param[in] aString null-terminated aString
* @return Length of this string
*/
SMARTRESPONSE_SDK_DECLSPEC
	int SMARTRESPONSE_SDK_CALLSPEC smartresponse_sdk_stringlength(char* aString);


/**
* Initialize the SMART Response SDK ensuring that the minimum version requested is supported.
*
* @param[in] aVersion Pass SMARTRESPONSE_SDK_VERSION here.
* @return Non-zero current version number if successful; zero if failure. 
*/
SMARTRESPONSE_SDK_DECLSPEC
int SMARTRESPONSE_SDK_CALLSPEC smartresponse_sdk_initialize(int aVersion);

/**
* Undo the result of a successful call to smartresponse_sdk_initialize.
*/
SMARTRESPONSE_SDK_DECLSPEC
void SMARTRESPONSE_SDK_CALLSPEC smartresponse_sdk_terminate();

/**
* Release an SDK listener reference returned by a smartresponse_abc_listenonxyz function.
* @param[in] aListener Result returned by a smartresponse_abc_listenonxyz function call.
*/
SMARTRESPONSE_SDK_DECLSPEC
void SMARTRESPONSE_SDK_CALLSPEC smartresponse_listener_release(smartresponse_listener_t *aListener);


/**
* Creates a SMART Response condition variable, which lets you synchronize things in a GUI-safe way.
*/
SMARTRESPONSE_SDK_DECLSPEC
smartresponse_condition_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_condition_create();

/**
* Waits on a condition variable. The calling thread is blocked in a GUI-safe way until 
* smartresponse_condition_notify is called with the given condition.
* @param[in] aCondition Condition variable.
* @param[in] aTimeout A maximum time to wait, or smartresponse_infinity() to wait forever.
* @return true if the wait completed because smartresponse_condition_notify was called; false
*         if the wait operation timed out.
*
* A GUI event loop is executed if this function is being called from the main thread.
*/
SMARTRESPONSE_SDK_DECLSPEC
bool SMARTRESPONSE_SDK_CALLSPEC smartresponse_condition_wait(smartresponse_condition_t *aCondition, double aTimeout);

/**
* Notifies a condition variable, releasing any waiting threads.
* @param[in] aCondition Condition variable.
*/
SMARTRESPONSE_SDK_DECLSPEC
void SMARTRESPONSE_SDK_CALLSPEC smartresponse_condition_notify(smartresponse_condition_t *aCondition);

/**
* Deletes a condition variable instance.
* @param[in] aCondition Condition variable returned by smartresponse_condition_create.
*/
SMARTRESPONSE_SDK_DECLSPEC
void SMARTRESPONSE_SDK_CALLSPEC smartresponse_condition_release(smartresponse_condition_t *aCondition);

#ifdef __cplusplus
}
#endif

#endif
