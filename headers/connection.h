/**
* Constants and functions for managing a connection to the SMART Response software service in the
* SMART Response SDK V1.
* Copyright (C) 2009 SMART Technologies ULC. All rights reserved.
*/
#ifndef SMARTRESPONSE_V1_CONNECTION_H
#define SMARTRESPONSE_V1_CONNECTION_H

#include "types.h"

/**
* Definition for Clicker mode. This is the Response Senteo mode 
*/
#define SMARTRESPONSE_MODE_SENTEO 1

/**
* Definition for Clicker mode. This is the Response CE mode 
*/
#define SMARTRESPONSE_MODE_CE 2

/**
* Definition for Clicker mode. This is the Response LE mode 
*/
#define SMARTRESPONSE_MODE_LE 1 << 2

/**
* Definition for Clicker mode. This is the Response PE mode 
*/
#define SMARTRESPONSE_MODE_PE 1 << 3

/**
* Definition for Clicker mode. This is the Response XE mode 
*/
#define SMARTRESPONSE_MODE_XE 1 << 4

/**
* Definition for Clicker mode. This is the Response VE mode 
*/
#define SMARTRESPONSE_MODE_VE 1 << 5

/**
* Definition for Clicker mode. This is the Response Mixed mode 
*/
#define SMARTRESPONSE_MODE_MIXED 1 << 6

/**
* Definition for Clicker mode. This is the Response Mixed mode with VE support
*/
#define SMARTRESPONSE_MODE_MIXEDVE 1 << 7

/**
* Definition for Clicker mode. This is the Response Mixed mode with Text support
*/
#define SMARTRESPONSE_MODE_MIXEDTEXT 1 << 8

/**
* Definition for Clicker mode. This is the Response Mixed mode with VE and Text support
*/
#define SMARTRESPONSE_MODE_MIXEDVETEXT 1 << 9

/**
* Definition for Web Assessment Id minimum buffer size
*/
#define SMARTRESPONSE_WEBID_LENGTH 80

#ifdef __cplusplus
extern "C" {
#endif

/**
* Specifies when creating a SMART Response connection instance that smartresponse_connectionV1_listenonxyz callbacks must always be invoked on the main thread. The main thread must run an event loop in order to properly dispatch the callbacks.
*/
#define SMARTRESPONSE_INVOKE_CALLBACKS_ON_MAIN_THREAD_ONLY 0

/**
* Specifies when creating a SMART Response connection instance that smartresponse_connectionV1_listenonxyz callbacks can be invoked on background threads.
*/
#define SMARTRESPONSE_INVOKE_CALLBACKS_ON_BACKGROUND_THREADS 1

/**
* Create a SMART Response SDK connection instance.
* @param[in] aThreadingStyle Pass SMARTRESPONSE_INVOKE_CALLBACKS_ON_MAIN_THREAD_ONLY or SMARTRESPONSE_INVOKE_CALLBACKS_ON_BACKGROUND_THREADS. GUI applications typically specify SMARTRESPONSE_INVOKE_CALLBACKS_ON_MAIN_THREAD_ONLY.
* @return A non-zero SMART Response SDK connection instance, or zero if failure.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_connectionV1_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_create(int aThreadingStyle);

/**
* Release a SMART Response SDK connection instance returned in a successful call to smartresponse_connectionV1_create.
* @param[in] aConnection Connection instance to release.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_release(smartresponse_connectionV1_t *aConnection);

/**
* Gets a copy of the information describe an error that occurred during completion of an asynchronous request. The caller owns the copy and must release it passing it in a call to smartresponse_errorinfoV1_release.
* @param[in] aConnection Connection instance.
* @return A copy of error information about the most recently failed asynchronous request, or NULL if the most recent request did not fail.
*
* Error information is generally available only inside a smartresponse_connectionV1_listenonxyz callback.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_errorinfoV1_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_copyerrorinfo(smartresponse_connectionV1_t *aConnection);

/**
* Bind a callback which will be called when the connection to the SMART Response software service is established and the internal connection state is made to match that of the software service.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonconnected(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aContext);

/**
* Bind a callback which will be called when the connection to the SMART Response software service is unexpectedly broken.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*
* Call smartresponse_connectionV1_errorinfo to obtain information about the error.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonconnectiondidfail(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aContext);

/**
* Establish a connection to the SMART Response software service asynchronously. Event handlers listening for onconnected or onconnectiondidfail events may be called.
* @param[in] aConnection Connection instance.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_connect(smartresponse_connectionV1_t *aConnection);

/**
* Bind a callback which will be called when the connection to the SMART Response software service is disconnected gracefully.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aFunctionArgument A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenondisconnected(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aFunctionArgument);

/**
* Gracefully terminate a connection to the SMART Response SDK. It is not necessary to call this function before calling smartresponse_connectionv1_release.
* @param[in] aConnection Connection instance.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_disconnect(smartresponse_connectionV1_t *aConnection);


/**
* Bind a callback which will be called when a class is started.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aFunctionArgument A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonclassstarted(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aFunctionArgument);

/**
* Bind a callback which will be called when a request to start a class (made over this connection) was refused.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aFunctionArgument A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonclassfailtostart(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aFunctionArgument);

/**
* Start an anonymous class (or switch to a different class.
* @param[in] aConnection Connection instance.
*
* Calls to this function must occur in a locked context bounded by calls to smartresponse_connectionV1_lockclasses and smartresponse_lock_release.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_startclass(smartresponse_connectionV1_t *aConnection);

/**
* Start a class (or switch to a different class.
* @param[in] aConnection Connection instance.
* @param[in] aClass - class containing a list of students
*
* Calls to this function must occur in a locked context bounded by calls to smartresponse_connectionV1_lockclasses and smartresponse_lock_release.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV2_startclass(smartresponse_connectionV1_t *aConnection, smartresponse_classV1_t *aClass);

/**
* Get information about the currently started class.
* @param[in] aConnection Connection instance.
* @return Reference to the currently started class or NULL if no class is started.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_classV1_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_currentclass(smartresponse_connectionV1_t *aConnection);

/**
* Bind a callback which will be called when a class is stopped gracefully
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aFunctionArgument A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonclassstopped(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aFunctionArgument);

/**
* Bind a callback which will be called when a request to stop a class (made over this connection) was refused.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aFunctionArgument A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonclassfailtostop(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aFunctionArgument);

/**
* Stop the anonymous class.
* @param[in] aConnection Connection instance.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_stopclass(smartresponse_connectionV1_t *aConnection);
/**
* Bind a callback which will be called when a single question is started.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aFunctionArgument A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonquestionstarted(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aFunctionArgument);

/**
* Bind a callback which will be called when a request to start a single question was refused.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonquestionfailtostart(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aContext);

/**
* Starts a question.
* @param[in] aConnection Connection instance.
* @param[in] aQuestion Question details, created with a call to smartresponse_questionV1_create.
*
* The contents of the aQuestion are copied internally. Callers must call smartresponse_questionV1_release on aQuestion when finished. Callbacks bound to the
* onquestionstarted or onquestionfailtostart will be invoked asynchronously.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_startquestion(smartresponse_connectionV1_t *aConnection, smartresponse_questionV1_t *aQuestion);

/**
* Obtain a reference to the currently started single question.
* @param[in] aConnection Connection instance.
* @return A reference to the question, or NULL if no question started.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_questionV1_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_currentquestion(smartresponse_connectionV1_t *aConnection);

/**
* Bind a callback which will be called when the current question is stopped.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonquestionstopped(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aContext);

/**
* Bind a callback which will be called when the current question fails to be stopped.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonquestionfailtostop(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aContext);


/**
* Stops the current question.
* @param[in] aConnection Connection instance.
*
* If a question was started it is stopped, the final set of responses are obtained and then onquestionstopped event listeners are notified.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_stopquestion(smartresponse_connectionV1_t *aConnection);

/**
* Ends review mode.
* @param[in] aConnection Connection instance.
*
* If a question was started, it is stopped.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_endreviewmode(smartresponse_connectionV1_t*aConnection);


/**
* Bind a callback which will be called when the receiver is plugged in.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonreceiverpluggedin(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aContext );

/**
* Bind a callback which will be called when the receiver is ready for use.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonreceiverready(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aContext );

/**
* Bind a callback which will be called when the receiver is unplugged.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonreceiverunplugged(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aContext );

/**
* Bind a callback which will be called when a clicker is connected.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called. This function is must be a SMARTRESPONSE_SDK_CALLBACK type. 
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonclickerconnected(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CLICKER_STATE_CHANGE_CALLBACK aFunction, void *aContext );

/**
* Bind a callback which will be called when a clicker is disconnected.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called. This function is must be a SMARTRESPONSE_SDK_CALLBACK type.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonclickerdisconnected(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CLICKER_STATE_CHANGE_CALLBACK aFunction, void *aContext);

/**
* Bind a callback which will be called when a clicker pressed question button.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called. This function is must be a SMARTRESPONSE_SDK_CALLBACK type.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonclickerquestioned(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CLICKER_STATE_CHANGE_CALLBACK aFunction, void *aContext);

/**
* Bind a callback which will be called when a clicker pressed question button second time to cancel the question.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called. This function is must be a SMARTRESPONSE_SDK_CALLBACK type.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonclickerquestioncanceled(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CLICKER_STATE_CHANGE_CALLBACK aFunction, void *aContext);

/**
*
* Bind a callback which will be called when a clicker responded question.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called. This function is must be a SMARTRESPONSE_SDK_CLICKER_RESPONDED_CALLBACK type.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonclickerresponded(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CLICKER_RESPONDED_CALLBACK aFunction, void *aContext);

/**
* Bind a callback which will be called when a student submits the whole assessment.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonclickersubmitted(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CLICKER_STATE_CHANGE_CALLBACK aFunction, void *aContext);


/**
* Bind a callback which will be called when a question set is started.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonquestionsetstarted(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aContext);

/**
* Bind a callback which will be called when request to start a question set refused.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonquestionsetfailtostart(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aContext);

/**
* Start a question set 
* @param[in] aConnection Connection instance.
* @param[in] aQuestionSet Question set instance
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_startquestionset(smartresponse_connectionV1_t *aConnection, smartresponse_questionsetV1_t* aQuestionSet);

/**
* Bind a callback which will be called when a question set is stopped.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonquestionsetstopped(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aContext);

/**
* Bind a callback which will be called when request to stop a question set refused.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_listenonquestionsetfailtostop(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aContext);

/**
* Stop a question set 
* @param[in] aConnection Connection instance.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_stopquestionset(smartresponse_connectionV1_t *aConnection);


/**
* Get information about the currently activated question set.
* @param[in] aConnection Connection instance.
* @return Reference to the currently activated question set or NULL if no question set is activated.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_questionsetV1_t* SMARTRESPONSE_SDK_CALLSPEC  smartresponse_connectionV1_currentquestionset(smartresponse_connectionV1_t *aConnection);

/**
* Get information about if the receiver is ready to use
* @param[in] aConnection Connection instance.
* @return true if the receiver is ready to use or false if it is not.
*/
SMARTRESPONSE_SDK_DECLSPEC bool SMARTRESPONSE_SDK_CALLSPEC smartresponse_connectionV1_isreceiverready(smartresponse_connectionV1_t *aConnection);

/**
* Get the number of students that have signed in the currently started class.
* @param[in] aConnection a pointer to the Connection instance.
* @return value integer type, the number of signed in students.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC sr_connection_get_number_signedin_students(smartresponse_connectionV1_t *aConnection);

/**
* Get the currently configured reponse mode.
* @param[in] aConnection, a pointer to the Connection instance.
* @return value, integer type, the mode as defined in SENTEO_CLASS SuiteFeatures.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC sr_connection_get_current_mode(smartresponse_connectionV1_t *aConnection);


/**
* Get the web assessment id (VE mode)
* @param[in] aConnection, a pointer to the Connection instance.
* @param[in] aBuffer Buffer to hold UTF-8 encoded characters
* @param[in] theBufferSize Size of aBuffer in bytes. Use SMARTRESPONSE_WEBID_LENGTH
* @return The size of a buffer big enough to hold the web assessment id.
		  The string returned in aBuffer is NUL terminated if there is room for it.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC sr_connection_get_web_assessment_id(smartresponse_connectionV1_t *aConnection, char *aBuffer, int theBufferSize);

/**
* Bind a callback which will be called when switch mode is called.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aFunctionArgument A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC sr_connection_listenonmodeswitched(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aFunctionArgument);

/**
* Bind a callback which will be called when a request to switch mode (made over this connection) was refused.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called.
* @param[in] aFunctionArgument A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC sr_connection_listenonmodeswitchfailed(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CALLBACK aFunction, void *aFunctionArgument);

/**
* Switch to a different setup mode
* @param[in] aConnection Connection instance.
* @param[in] theMode, integer type, using the defines at the top of this file.
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC sr_connection_switch_mode(smartresponse_connectionV1_t *aConnection, int theMode);

/**
* Bind a callback which will be called when a student signed in to a VE assessment.
* @param[in] aConnection Connection instance.
* @param[in] aFunction Function to be called. This function is must be a SMARTRESPONSE_SDK_CALLBACK type. 
* @param[in] aContext A value that will be passed to aFunction.
* @return A SMART Response SDK listener object. Call smartresponse_listener_release to stop listening.
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_listener_t * SMARTRESPONSE_SDK_CALLSPEC sr_connection_listenonvesignedin(smartresponse_connectionV1_t *aConnection, SMARTRESPONSE_SDK_CLICKER_STATE_CHANGE_CALLBACK aFunction, void *aContext );

#ifdef __cplusplus
}
#endif

#endif
