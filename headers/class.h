/**
* Constants and functions for deal with classes in the SMART Response SDK V1.
* Copyright (C) 2009 SMART Technologies ULC. All rights reserved.
*/
#ifndef SMARTRESPONSE_V1_CLASS_H
#define SMARTRESPONSE_V1_CLASS_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
* Creates a class.
* @param[in] aBuffer Buffer to hold UTF-8 encoded string to be used as classroom name.
*   The total number of the chacters can not exceed 8 and only following characters are allowed: ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz0123456789`-=!@#$%&*()_+[];':\",./<?
* @param[in] theBufferSize Count of bytes in aBuffer
* @param[in] isAnonymous A bool which is false if the class has a list of named students
*/
SMARTRESPONSE_SDK_DECLSPEC smartresponse_classV1_t * SMARTRESPONSE_SDK_CALLSPEC sr_class_create(char *aBuffer, int theBufferSize, bool isAnonymous);

/**
* Delete a class and free it's memory.
* @param[in] aClass - the class to free memory
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC sr_class_release(smartresponse_classV1_t *aClass);

/**
* Creates a student.
* @param[in] lastName Buffer to hold UTF-8 encoded student's last name
* @param[in] lastNameSize Count of bytes in lastName
* @param[in] firstName Buffer to hold UTF-8 encoded student's first name
* @param[in] firstNameSize Count of bytes in firstName
* @param[in] studentId The id the student uses to sign in
* @param[in] idsize The string length of the studentId
*
* The structure return holds all the student info
*/
SMARTRESPONSE_SDK_DECLSPEC sr_student_t * SMARTRESPONSE_SDK_CALLSPEC sr_student_create(
	const char *lastName, int lastNameSize, const char *firstName, int firstNameSize, const char * studentId, int idsize); 

/**
* Delete a student and free it's memory
* @param[in] aStudent - student to delete
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC sr_student_release(sr_student_t *aStudent);

/**
* Adds a student to a class.
* @param[in] studentClass pointer from smartresponseV2_create_class
* @param[in] studentToAdd pointer from smartresponseV2_create_student
*
* Returns a status code indicating whether adding a student to a class was successful.
* SR::OK - all good
* SR::ID_IN_USE - a student already is in the class with the same id.  Make sure the student to add has a unique id.
* SR::CLASS_OR_STUDENT_IS_NULL - either or both the parameters are null pointers
*/
SMARTRESPONSE_SDK_DECLSPEC SR::ADD_STUDENT_STATUS SMARTRESPONSE_SDK_CALLSPEC sr_class_addstudent(smartresponse_classV1_t * studentClass, sr_student_t *studentToAdd);

/**
* Gets the classroom name of a class as a UTF-8 encoded string.
* @param[in] aClass Class returned by a call to smartresponse_connectionV1_class().
* @param[out] aBuffer Buffer to hold returned UTF-8 encoded string or NULL to query for the length of buffer required.
* @param[in] theBufferSize Count of bytes in aBuffer, or zero to query for the length of buffer required.
* @return The size of buffer needed to hold the entire string (excluding NUL terminator).
*
* The string returned in aBuffer (if provided) is NUL terminated if the space for it is available.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_classroom_name(smartresponse_classV1_t *aClass, char *aBuffer, int theBufferSize);

/**
* Sets the current classroom name a UTF-8 encoded string. The classroom name must be less than 8 characters.
* @param[in] aConnection Connection instance.
* @param[in] aBuffer Buffer to hold UTF-8 encoded string to be used as classroom name.
* The total number of the chacters can not exceed 8 and only following characters are allowed: ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz0123456789`-=!@#$%&*()_+[];':\",./<?
* @param[in] theBufferSize Count of bytes in aBuffer, or zero to query for the length of buffer required.
*
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_set_classroom_name(smartresponse_connectionV1_t* aConnection, char *aBuffer, int theBufferSize);


/**
* Gets the title of a class as a UTF-8 encoded string.
* @param[in] aClass Class returned by a call to smartresponse_connectionV1_class().
* @param[out] aBuffer Buffer to hold returned UTF-8 encoded string or NULL to query for the length of buffer required.
* @param[in] theBufferSize Count of bytes in aBuffer, or zero to query for the length of buffer required.
* @return The size of buffer needed to hold the entire string (excluding NUL terminator).
*
* The string returned in aBuffer (if provided) is NUL terminated if the space for it is available.
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_class_title(smartresponse_classV1_t *aClass, char *aBuffer, int theBufferSize);

/**
* Delete a student from a class.
* @param[in] aClass a pointer to the class that a student will be deleted from.
* @param[in] student a pointer to the student that will be deleted from the class.
*
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC sr_class_removestudent(smartresponse_classV1_t *aClass, sr_student_t *student);

/**
* Delete a student from a class based on its id.
* @param[in] aClass a pointer to the class that a student will be deleted from.
* @param[in] studentid the student id.
*
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC sr_class_removestudentwithid(smartresponse_classV1_t *aClass, char *studentid);
	
/**
 * Get the total number of students in the class.
 * @param[in] aClass, a pointer to the class.
 * @return The  total number of students in the class.
 *
 */
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC sr_class_getStudentCount(smartresponse_classV1_t *aClass);

#ifdef __cplusplus
}
#endif

#endif
