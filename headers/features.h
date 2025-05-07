#ifndef SMARTRESPONSE_V1_FEATURES_H
#define SMARTRESPONSE_V1_FEATURES_H

#include "types.h"

/**
* Definition for Multiple Choice question type feature. This type of question only allows users to choose one choice from multiple choices. 
*/
#define SMARTRESPONSE_FEATURETYPE_MULTIPLECHOICE 1

/**
* Definition for Multiple Answer question type feature. This type of question allows users to choose more than one selection from multiple choices. 
*/
#define SMARTRESPONSE_FEATURETYPE_MULTIPLEANSWER 2

/**
* Definition for Yes/No question type feature. 
*/
#define SMARTRESPONSE_FEATURETYPE_YESNO 3

/**
* Definition for True/False question type feature. 
*/
#define SMARTRESPONSE_FEATURETYPE_TRUEFALSE 4

/**
* Definition for decimal question type feature. 
*/
#define SMARTRESPONSE_FEATURETYPE_DECIMAL 5

/**
* Definition for fractional question type feature. 
*/
#define SMARTRESPONSE_FEATURETYPE_FRACTIONAL 6

/**
* Definition for text question type feature. 
*/
#define SMARTRESPONSE_FEATURETYPE_TEXT 7

/**
* Definition for the feature where a maximal number of 5 choices in a Multiple Choice question are allowed.
*/
#define SMARTRESPONSE_FEATURETYPE_CHOICE_MAX_5  8

/**
* Definition for the feature where a maximal number of 10 choices in a Multiple Choice question are allowed.
*/
#define SMARTRESPONSE_FEATURETYPE_CHOICE_MAX_10 9

/**
* Definition for the feature where a maximal number of 6 selections in a Multiple Selection question are allowed.
*/
#define SMARTRESPONSE_FEATURETYPE_SELECTION_MAX_6  10

/**
* Definition for the feature where a maximal number of 10 selections in a Multiple Selection question are allowed.
*/
#define SMARTRESPONSE_FEATURETYPE_SELECTION_MAX_10  11

/**
* Definition for the feature where a maximal number of 20 selections in a Multiple Selection question are allowed.
*/
#define SMARTRESPONSE_FEATURETYPE_SELECTION_MAX_20  12

#ifdef __cplusplus
extern "C" {
#endif
/**
* Query whether or not a feature type is supported in current mode.
* @param[in] aFeatureType type
* @return the result if a feature is supported by the Response Services in current mode.
*/
SMARTRESPONSE_SDK_DECLSPEC bool SMARTRESPONSE_SDK_CALLSPEC smartresponse_featuresV1_supported(int aFeatureType);

/**
* Query the maximal and minimal choice number that a choice question supports under current mode
* @param[out] maxChoiceNumber the maximal number of choices it supports
* @param[out] minChoiceNumber the minimal number of choices it supports
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_featuresV1_questionchoicenumber(int* maxChoiceNumber, int* minChoiceNumber);

/**
* Query the maximal and minimal selection number that a multiple answer question supports under current mode
* @param[out] maxSelectionNumber the maximal number of selections it supports
* @param[out] minSelectionNumber the minimal number of selections it supports
*/
SMARTRESPONSE_SDK_DECLSPEC void SMARTRESPONSE_SDK_CALLSPEC smartresponse_featuresV1_questionselectionnumber(int* maxSelectionNumber, int* minSelectionNumber);


/**
* Query the maximal length  that a numeric/fractional question supports under current mode
* @return  the maximal length a numeric/fractional question supports
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_featuresV1_numericanswerlength();
/**
* Query the maximal length  that a text question supports under current mode
* @return the maximal length a text question supports
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_featuresV1_textanswerlength();

/**
* Query the if a text answer is validly supported by the clicker 
* @param[in] aString UTF-8 encoded string for the answer string.
* @param[in] theStringLength Number of bytes in aString, or -1 if it is NUL terminated.
* @return if it is valid on clickers
*/
SMARTRESPONSE_SDK_DECLSPEC bool SMARTRESPONSE_SDK_CALLSPEC smartresponse_featuresV1_textanswervalid(const char* aString, int theStringLength);


/**
* Query the max number of questions in a question set under current mode
* @return the max number of questions
*/
SMARTRESPONSE_SDK_DECLSPEC int SMARTRESPONSE_SDK_CALLSPEC smartresponse_featuresV1_maxquestionsperquestionset();


#ifdef __cplusplus
}
#endif

#endif