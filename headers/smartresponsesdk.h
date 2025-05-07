/** 
* Main include header for the SMART Response SDK.
* Copyright (C) 2009 SMART Technologies ULC. All rights reserved.
*
* The "connection" object is the starting point for most applications that use the SMART Response
* SDK. It manages a connection to the software service, which coordinates the activities of all
* hardware and software operating in the SMART Response ecosystem.
*
* To use the SMART Response SDK, initialize the SDK with a call to smartresponse_sdk_initialize,
* then create a connection instance with a call to smartresponse_connectionV1_create. Bind your own
* functions to the events that are raised by the connection instance by calling the various
* smartresponse_connectionV1_listenonxyz functions. The call the smartresponse_connectionV1_connect
* function to begin.
*
* When your onconnected callback is invoked, you can query the class list, the currently started
* class or question. While the connection is established, you can start or stop classes and
* questions. Certain query operations must happen inside a locked context: see the individual
* function descriptions for additional information.
*
* Must requests proceed asynchronously. If the request is refused or an error occurs an event
* handler you bind is notified. You can query for more information about the error or refusal by
* calling the smartresponse_connectionV1_copyerrorinfo function.
*
* When finished, call smartresponse_connectionV1_release to release the connection to the SMART
* Response software service, then call smartresponse_sdk_terminate to clean up all use of the
* SMART Response SDK.
*/
#ifndef SMARTRESPONSE_SDK_H
#define SMARTRESPONSE_SDK_H

#include "baseapi.h"
#include "types.h"
#include "errorinfo.h"
#include "connection.h"
#include "class.h"
#include "question.h"
#include "questionset.h"
#include "features.h"
#include "smartresponseapiversioning.h"
#endif
