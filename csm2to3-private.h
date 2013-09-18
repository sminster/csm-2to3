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
//>
//     Date          Author   Comment
//     -----------   ------   -------
//    30-Mar-2012    SCM      Initial Coding.
//    12-Sep-2013    JPK      Moved DROP_WARNING and SAVE_WARNING here from
//                            csm2to3model.cc
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

#define DROP_WARNING(expr) \
   do { TSMWarning* w = expr; if (w) delete w; } while (0)

#define SAVE_WARNING(expr,warnings) \
   do { TSMWarning* w = expr; if (w) { if (warnings) warnings->push_back(CONVERT_WARNING(w)); delete w; } } while (0)

#endif
