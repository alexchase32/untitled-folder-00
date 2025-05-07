/**
* Definitions of opaque handle types for SMART Response SDK V1.
* Copyright (C) 2009 SMART Technologies ULC. All rights reserved.
*/
#ifndef SMARTRESPONSE_V1_TYPES_H
#define SMARTRESPONSE_V1_TYPES_H

#include "baseapi.h"

#ifndef SMARTRESPONSE_SDK_CONNECTIONV1_DEFINED
/**
* Opaque handle type for a connection to the SMART Response software service.
*/
typedef struct _smartresponse_connectionV1
{
	virtual ~_smartresponse_connectionV1(){}
} smartresponse_connectionV1_t;
#define SMARTRESPONSE_SDK_CONNECTIONV1_DEFINED
#endif

#ifndef SMARTRESPONSE_SDK_STUDENT_DEFINED
/**
* Opaque handle type for a SMART Response student.
*/
typedef struct _sr_student
{
	virtual ~_sr_student(){}
}sr_student_t;
#define SMARTRESPONSE_SDK_STUDENT_DEFINED
#endif

#ifndef SMARTRESPONSE_SDK_CLASSV1_DEFINED
/**
* Opaque handle type for a SMART Response class.
*/
typedef struct _smartresponse_classV1
{
	virtual ~_smartresponse_classV1(){}
}smartresponse_classV1_t;
#define SMARTRESPONSE_SDK_CLASSV1_DEFINED
#endif

#ifndef SMARTRESPONSE_SDK_QUESTIONSETV1_DEFINED
/**
* Opaque handle type for a SMART Response question set.
*/
typedef struct _smartresponse_questionsetV1
{
	virtual ~_smartresponse_questionsetV1(){}
}smartresponse_questionsetV1_t;
#endif 


#ifndef SMARTRESPONSE_SDK_QUESTIONV1_DEFINED
/**
* Opaque handle type for a SMART Response single question.
*/
typedef struct _smartresponse_questionV1
{
	virtual ~_smartresponse_questionV1(){}
} smartresponse_questionV1_t;
#define SMARTRESPONSE_SDK_QUESTIONV1_DEFINED
#endif

#ifndef SMARTRESPONSE_SDK_ERRORINFOV1_DEFINED
/**
* Opaque handle type for information about an asynchronous error in SMART Response.
*/
typedef struct _smartresponse_errorinfoV1
{
	virtual ~_smartresponse_errorinfoV1(){}
} smartresponse_errorinfoV1_t;
#define SMARTRESPONSE_SDK_QUESTIONV1_DEFINED
#endif

#ifndef SMARTRESPONSE_SDK_ADD_STUDENT_STATUS
namespace SR
{
	enum ADD_STUDENT_STATUS
	{
		OK = 0,
		ID_IN_USE,
		CLASS_OR_STUDENT_IS_NULL
	};
};
#define SMARTRESPONSE_SDK_ADD_STUDENT_STATUS
#endif

#endif
