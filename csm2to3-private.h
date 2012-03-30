//#############################################################################
//## Restricted Rights
//## WARNING: This is a restricted distribution HARRIS REPOSITORY file.
//##          Do Not Use Under A Government Charge Number Without Permission.
//#############################################################################

//*****************************************************************************
// FILE:              csm2to3-private.h
//
//    Copyright (C)  2012 Harris Corporation. All rights reserved.
//
// CLASSIFICATION:    Unclassified
//
// DESCRIPTION:       This file contains implementation private functions and
//                    macros shared among the CSM 2to3 files.  Do not
//                    distribute this file.
//
// LIMITATIONS:       None
//
// SOFTWARE HISTORY:
//
//> 30MAR12 956F PTR#?????-IPL  S. Minster
//               Initial Coding.
//<
//*****************************************************************************

#ifndef csm2to3_private_HEADER
#define csm2to3_private_HEADER

#define EXCEPTION_TRY(m) static const char* const MODULE = m; try {
#define EXCEPTION_RETHROW_CONVERT \
   } catch(const csm::Error& csm) { \
      throw; \
   } catch(TSMError& tsm) { \
      throw csm::Error((csm::Error::ErrorType)tsm.getError(), \
                       tsm.getMessage(), \
                       tsm.getFunction()); \
   } catch(...) { \
      throw csm::Error(csm::Error::UNKNOWN_ERROR, "Unkown exception", MODULE); \
   }

#define CONVERT_WARNING(w) \
   csm::Warning((csm::Warning::WarningType)((w)->getWarning()), \
                (w)->getMessage(), (w)->getFunction())

#endif
