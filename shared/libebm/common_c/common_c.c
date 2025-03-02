// Copyright (c) 2023 The InterpretML Contributors
// Licensed under the MIT license.
// Author: Paul Koch <code@koch.ninja>

#define _CRT_SECURE_NO_DEPRECATE

#include <stdlib.h>

#include "libebm.h" // BoolEbm
#include "logging.h"
#include "common_c.h"

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

extern const char * SkipWhitespace(const char * s) {
   char oneChar = *s;
   while(0x20 == oneChar || (0x9 <= oneChar && oneChar <= 0xd)) {
      // skip whitespace
      ++s;
      oneChar = *s;
   }
   return s;
}

extern const char * ConvertStringToFloat(const char * const s, double * const pResultOut) {
   // we skip beginning whitespaces (strtod guarantees this)
   // unlike strtod, we also skip trailing whitespaces

   EBM_ASSERT(NULL != s);
   EBM_ASSERT(NULL != pResultOut);

   // the C++ standard says this about strtod:
   //   If the subject sequence is empty or does not have the expected form, no
   //   conversion is performed; the value of nptr is stored in the object
   //   pointed to by endptr, provided that endptr is not a null pointer.
   //
   // But, I'm unwilling to trust that there is no variation in the C++ runtime libraries, so I'll do my best to 
   // trust but verify by setting sNext before calling strtod, even though that involves a const cast
   char * sNext = (char *)(s);
   const double ret = strtod(s, &sNext);
   if(s == sNext || NULL == sNext) {
      // technically, sNext should never be nullptr, but we're again verifying our trust of the C++ library
      return NULL;
   }
   *pResultOut = ret;
   return SkipWhitespace(sNext);
}

extern const char * IsStringEqualsCaseInsensitive(const char * sMain, const char * sLabel) {
   // this function returns nullptr if there is no match, otherwise it returns a pointer to the 
   // first non-whitespace character following a successfully equal comparison

   char mainChar = *sMain;
   EBM_ASSERT(0x20 != mainChar && (mainChar < 0x9 || 0xd < mainChar));
   char labelChar = *sLabel;
   while('\0' != labelChar) {
      if('A' <= mainChar && mainChar <= 'Z') {
         mainChar += 'a' - 'A';
      }
      if('A' <= labelChar && labelChar <= 'Z') {
         // in theory within our executable we could ensure that all labels are lower case, but we want
         // people to tweak the objective and metric registrations, so let's be defensive here and do a full
         // case insensitive compare
         labelChar += 'a' - 'A';
      }
      if(mainChar != labelChar) {
         return NULL;
      }
      ++sMain;
      ++sLabel;
      mainChar = *sMain;
      labelChar = *sLabel;
   }
   while(0x20 == mainChar || (0x9 <= mainChar && mainChar <= 0xd)) {
      // skip whitespace
      ++sMain;
      mainChar = *sMain;
   }
   return sMain;
}

extern BoolEbm IsStringEqualsForgiving(const char * sMain, const char * sLabel) {
   sMain = IsStringEqualsCaseInsensitive(sMain, sLabel);
   if(NULL == sMain || '\0' != *sMain) {
      return EBM_FALSE;
   }
   return EBM_TRUE;
}

#ifdef __cplusplus
}
#endif // __cplusplus
