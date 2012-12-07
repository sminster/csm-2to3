//#############################################################################
//## Restricted Rights
//## WARNING: This is a restricted distribution HARRIS REPOSITORY file.
//##          Do Not Use Under A Government Charge Number Without Permission.
//#############################################################################

//*****************************************************************************
// FILE:              csm2to3model.cc
//
//    Copyright (C)  2012 Harris Corporation. All rights reserved.
//
// CLASSIFICATION:    Unclassified
//
// DESCRIPTION:       csm2to3model
//
// LIMITATIONS:       None
//
// SOFTWARE HISTORY:
//
//>
//     Date          Author   Comment   
//     -----------   ------   ------- 
//     30-Mar-2012   SCM      Initial Coding
//     26-Sep-2012   JPK      Ripple class hierarchy change
//     11-Oct-2012   SCM      Added getParameterUnits.
//     30-Oct-2012   SCM      Fixed includes.  Rippled other changes.
//     31-Oct-2012   SCM      Rippled more interface changes.
//     27-Nov-2012   JPK      Changed return type for getCovarianceModel()
//                            and cleaned up some variable names.
//     29-Nov-2012   JPK      Added support for ParamSet enumeration and
//                            Parameter and SharingCriteria structures.
//<
//*****************************************************************************

#include "csm2to3model.h"
#include "csm2to3-private.h"

#include <tsm/TSMSensorModel.h>
#include <tsm/TSMPlugin.h>
#include <tsm/CSMFourParameterCorrelationModel.h>
#include <csm/Error.h>
#include <csm/FourParameterCorrelationModel.h>

#include <sstream>

#define CHECK_IMPL if (!theImpl) throw csm::Error(csm::Error::INVALID_USE, "Implementation model is NULL", MODULE)

#define DROP_WARNING(expr) \
   do { TSMWarning* w = expr; if (w) delete w; } while (0)

#define SAVE_WARNING(expr,warnings) \
   do { TSMWarning* w = expr; if (w) { if (warnings) warnings->push_back(CONVERT_WARNING(w)); delete w; } } while (0)


//*****************************************************************************
// csm2to3model::csm2to3model
//*****************************************************************************
csm2to3model::csm2to3model(TSMSensorModel* impl,const std::string& pluginName)
   :
      theImpl            (impl),
      thePluginName      (pluginName),
      theCovarianceModel (NULL)
{
}

//*****************************************************************************
// csm2to3model::~csm2to3model
//*****************************************************************************
csm2to3model::~csm2to3model()
{
   delete theImpl;
   theImpl = NULL;
   
   thePluginName = "";
   
   delete theCovarianceModel;
   theCovarianceModel = NULL;
   
}

//*****************************************************************************
// csm2to3model::getVersion
//*****************************************************************************
csm::Version csm2to3model::getVersion() const
{
   EXCEPTION_TRY("csm2to3model::getVersion");

   // TODO
   return csm::Version(1, 0);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getModelName
//*****************************************************************************
std::string csm2to3model::getModelName() const
{
   EXCEPTION_TRY("csm2to3model::getModelName");

   // TODO
   return "csm2to3model";

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getPedigree
//*****************************************************************************
std::string csm2to3model::getPedigree() const
{
   EXCEPTION_TRY("csm2to3model::getPedigree");

   CHECK_IMPL;

   std::string val;
   DROP_WARNING(theImpl->getPedigree(val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getImageIdentifier
//*****************************************************************************
std::string csm2to3model::getImageIdentifier() const
{
   EXCEPTION_TRY("csm2to3model::getImageIdentifier");

   CHECK_IMPL;

   std::string val;
   DROP_WARNING(theImpl->getImageIdentifier(val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setImageIdentifier
//*****************************************************************************
void csm2to3model::setImageIdentifier(const std::string& imageId,
                                      csm::WarningList* warnings)
{
   EXCEPTION_TRY("csm2to3model::setImageIdentifier");

   CHECK_IMPL;

   SAVE_WARNING(theImpl->setImageIdentifier(imageId), warnings);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getSensorIdentifier
//*****************************************************************************
std::string csm2to3model::getSensorIdentifier() const
{
   EXCEPTION_TRY("csm2to3model::getSensorIdentifier");

   CHECK_IMPL;

   std::string val;
   DROP_WARNING(theImpl->getSensorIdentifier(val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getPlatformIdentifier
//*****************************************************************************
std::string csm2to3model::getPlatformIdentifier() const
{
   EXCEPTION_TRY("csm2to3model::getPlatformIdentifier");

   CHECK_IMPL;

   std::string val;
   DROP_WARNING(theImpl->getPlatformIdentifier(val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getCollectionIdentifier
//*****************************************************************************
std::string csm2to3model::getCollectionIdentifier() const
{
   EXCEPTION_TRY("csm2to3model::getCollectionIdentifier");

   CHECK_IMPL;

   std::string val;
   DROP_WARNING(theImpl->getCollectionIdentifier(val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getSensorType
//*****************************************************************************
std::string csm2to3model::getSensorType() const
{
   EXCEPTION_TRY("csm2to3model::getSensorType");

   // TODO -- maybe getPedigree could help here?
   return CSM_SENSOR_TYPE_UNKNOWN;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getSensorMode
//*****************************************************************************
std::string csm2to3model::getSensorMode() const
{
   EXCEPTION_TRY("csm2to3model::getSensorMode");

   // TODO -- maybe getPedigree could help here?
   return CSM_SENSOR_MODE_UNKNOWN;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getReferencePoint
//*****************************************************************************
csm::EcefCoord csm2to3model::getReferencePoint() const
{
   EXCEPTION_TRY("csm2to3model::getReferencePoint");

   CHECK_IMPL;

   csm::EcefCoord val(0, 0, 0);
   DROP_WARNING(theImpl->getReferencePoint(val.x, val.y, val.z));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setReferencePoint
//*****************************************************************************
void csm2to3model::setReferencePoint(const csm::EcefCoord& groundPt)
{
   EXCEPTION_TRY("csm2to3model::setReferencePoint");

   CHECK_IMPL;

   DROP_WARNING(theImpl->setReferencePoint(groundPt.x, groundPt.y, groundPt.z));

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getModelState
//*****************************************************************************
std::string csm2to3model::getModelState() const
{
   EXCEPTION_TRY("csm2to3model::getModelState");

   CHECK_IMPL;

   std::string val;
   DROP_WARNING(theImpl->getSensorModelState(val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::replaceModelState
//*****************************************************************************
void csm2to3model::replaceModelState(const std::string& argState)
{
   EXCEPTION_TRY("csm2to3model::replaceModelState");

   CHECK_IMPL;
   
   //***
   // Since this functionality doesn't exist on the 2.A model, we will
   // attempt to construct a new model.  If this is successful, the current
   // model is replaced.  Otherwise the current model is left intact, but
   // and exception is thrown to indicate the state couldn't be loaded.
   //***
   
   if(argState.empty())
   {
       std::ostringstream msg;
       msg << "Provided state string is empty.  Cannot reload CSM";
       
       throw csm::Error(csm::Error::INVALID_SENSOR_MODEL_STATE,
                        msg.str(),
                        MODULE);
   }
   
   TSMPlugin* csmPlugin = NULL;

   DROP_WARNING(TSMPlugin::findPlugin(thePluginName,
                                         csmPlugin));
      
   
   if (csmPlugin)
   {
      TSMSensorModel* model = 0;
      
      DROP_WARNING(csmPlugin->
                   constructSensorModelFromState(argState,
                                                 model));

      if (model)
      {
         delete theImpl;
         theImpl = model;
         delete theCovarianceModel;
         theCovarianceModel = 0;
      }
      else
      {
         std::ostringstream msg;
         msg << "Could not construct model from provided state.";

         throw csm::Error(csm::Error::SENSOR_MODEL_NOT_CONSTRUCTIBLE,
                          msg.str(),
                          MODULE);
      }
   }
   else
   {
      std::ostringstream msg;
      msg << "Could not instantiate plugin for current model!";
      
      throw csm::Error(csm::Error::UNKNOWN_ERROR,
                        msg.str(),
                       MODULE);
   }
   
   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::groundToImage
//*****************************************************************************
csm::ImageCoord csm2to3model::groundToImage(
   const csm::EcefCoord& groundPt,
   double desiredPrecision,
   double* achievedPrecision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::groundToImage");

   CHECK_IMPL;

   csm::ImageCoord val(0, 0);
   double tmp;
   SAVE_WARNING(theImpl->groundToImage(groundPt.x, groundPt.y, groundPt.z,
                                       val.line, val.samp,
                                       achievedPrecision ? *achievedPrecision : tmp,
                                       desiredPrecision),
                warnings);
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::groundToImage
//*****************************************************************************
csm::ImageCoordCovar csm2to3model::groundToImage(
   const csm::EcefCoordCovar& groundPt,
   double desiredPrecision,
   double* achievedPrecision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::groundToImage");

   CHECK_IMPL;
\
   csm::ImageCoordCovar val(0, 0);
   double tmp;
   SAVE_WARNING(theImpl->groundToImage(groundPt.x, groundPt.y, groundPt.z,
                                       groundPt.covariance,
                                       val.line, val.samp, val.covariance,
                                       achievedPrecision ? *achievedPrecision : tmp,
                                       desiredPrecision),
                warnings);

   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::imageToGround
//*****************************************************************************
csm::EcefCoord csm2to3model::imageToGround(
   const csm::ImageCoord& imagePt,
   double height,
   double desiredPrecision,
   double* achievedPrecision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::imageToGround");

   CHECK_IMPL;

   csm::EcefCoord val(0, 0, 0);
   double tmp;
   SAVE_WARNING(theImpl->imageToGround(imagePt.line, imagePt.samp, height,
                                       val.x, val.y, val.z,
                                       achievedPrecision ? *achievedPrecision : tmp,
                                       desiredPrecision),
                warnings);
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::imageToGround
//*****************************************************************************
csm::EcefCoordCovar csm2to3model::imageToGround(
   const csm::ImageCoordCovar& imagePt,
   double height, double heightVariance,
   double desiredPrecision,
   double* achievedPrecision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::imageToGround");

   CHECK_IMPL;

   csm::EcefCoordCovar val(0, 0, 0);
   double tmp;
   SAVE_WARNING(theImpl->imageToGround(imagePt.line, imagePt.samp, imagePt.covariance,
                                       height, heightVariance,
                                       val.x, val.y, val.z, val.covariance,
                                       achievedPrecision ? *achievedPrecision : tmp,
                                       desiredPrecision),
                warnings);

   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::imageToProximateImagingLocus
//*****************************************************************************
csm::EcefLocus csm2to3model::imageToProximateImagingLocus(
   const csm::ImageCoord& imagePt,
   const csm::EcefCoord& groundPt,
   double desiredPrecision,
   double* achievedPrecision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::imageToProximateImagingLocus");

   CHECK_IMPL;

   double tmp;
   double locus[6] = {0.,0.,0.,0.,0.,0.};
   SAVE_WARNING(theImpl->imageToProximateImagingLocus(
                   imagePt.line, imagePt.samp,
                   groundPt.x, groundPt.y, groundPt.z,
                   locus,
                   achievedPrecision ? *achievedPrecision : tmp,
                   desiredPrecision),
                warnings);
   
   return csm::EcefLocus(locus[0],locus[1],locus[2],
                         locus[3],locus[4],locus[5]);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::imageToRemoteImagingLocus
//*****************************************************************************
csm::EcefLocus csm2to3model::imageToRemoteImagingLocus(
   const csm::ImageCoord& imagePt,
   double desiredPrecision,
   double* achievedPrecision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::imageToRemoteImagingLocus");

   CHECK_IMPL;

   double tmp;
   double locus[6] = {0.,0.,0.,0.,0.,0.};
   SAVE_WARNING(theImpl->imageToRemoteImagingLocus(
                   imagePt.line, imagePt.samp,
                   locus,
                   achievedPrecision ? *achievedPrecision : tmp,
                   desiredPrecision),
                warnings);

   return csm::EcefLocus(locus[0],locus[1],locus[2],
                         locus[3],locus[4],locus[5]);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getImageStart
//*****************************************************************************
csm::ImageCoord csm2to3model::getImageStart() const
{
   EXCEPTION_TRY("csm2to3model::getImageStart");

   // nothing better to do...
   return csm::ImageCoord(0, 0);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getImageSize
//*****************************************************************************
csm::ImageVector csm2to3model::getImageSize() const
{
   EXCEPTION_TRY("csm2to3model::getImageSize");

   CHECK_IMPL;

   int lines = 0;
   int samps = 0;
   DROP_WARNING(theImpl->getImageSize(lines, samps));
   return csm::ImageVector(lines, samps);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getValidHeightRange
//*****************************************************************************
std::pair<double,double> csm2to3model::getValidHeightRange() const
{
   EXCEPTION_TRY("csm2to3model::getValidHeightRange");

   CHECK_IMPL;

   std::pair<double,double> val(0., 0.);
   DROP_WARNING(theImpl->getValidAltitudeRange(val.first, val.second));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getValidImageRange
//*****************************************************************************
std::pair<csm::ImageCoord,csm::ImageCoord>
csm2to3model::getValidImageRange() const
{
   EXCEPTION_TRY("csm2to3model::getValidImageRange");

   csm::ImageCoord start = getImageStart();
   csm::ImageVector size = getImageSize();

   return std::make_pair(start, csm::ImageCoord(start.line + size.line,
                                                start.samp + size.samp));

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getIlluminationDirection
//*****************************************************************************
csm::EcefVector
csm2to3model::getIlluminationDirection(const csm::EcefCoord& gndPt) const
{
   EXCEPTION_TRY("csm2to3model::getIlluminationDirection");

   CHECK_IMPL;

   csm::EcefVector val;
   DROP_WARNING(theImpl->getIlluminationDirection(gndPt.x, gndPt.y, gndPt.z,
                                                  val.x, val.y, val.z));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getTrajectoryIdentifier
//*****************************************************************************
std::string csm2to3model::getTrajectoryIdentifier() const
{
   EXCEPTION_TRY("csm2to3model::getTrajectoryIdentifier");

   CHECK_IMPL;

   std::string val;
   DROP_WARNING(theImpl->getTrajectoryIdentifier(val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getReferenceDateAndTime
//*****************************************************************************
std::string csm2to3model::getReferenceDateAndTime() const
{
   EXCEPTION_TRY("csm2to3model::getReferenceDateAndTime");

   CHECK_IMPL;

   std::string val;
   DROP_WARNING(theImpl->getReferenceDateAndTime(val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getImageTime
//*****************************************************************************
double csm2to3model::getImageTime(const csm::ImageCoord& pt) const
{
   EXCEPTION_TRY("csm2to3model::getImageTime");

   CHECK_IMPL;

   double val = 0.0;
   DROP_WARNING(theImpl->getImageTime(pt.line, pt.samp, val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getSensorPosition
//*****************************************************************************
csm::EcefCoord csm2to3model::getSensorPosition(const csm::ImageCoord& pt) const
{
   EXCEPTION_TRY("csm2to3model::getSensorPosition");

   CHECK_IMPL;

   csm::EcefCoord val(0.0, 0.0, 0.0);
   DROP_WARNING(theImpl->getSensorPosition(pt.line, pt.samp,
                                           val.x, val.y, val.z));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getSensorPosition
//*****************************************************************************
csm::EcefCoord csm2to3model::getSensorPosition(double time) const
{
   EXCEPTION_TRY("csm2to3model::getSensorPosition");

   CHECK_IMPL;

   csm::EcefCoord val(0.0, 0.0, 0.0);
   DROP_WARNING(theImpl->getSensorPosition(time, val.x, val.y, val.z));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getSensorVelocity
//*****************************************************************************
csm::EcefVector csm2to3model::getSensorVelocity(const csm::ImageCoord& pt)const
{
   EXCEPTION_TRY("csm2to3model::getSensorVelocity");

   CHECK_IMPL;

   csm::EcefVector val(0.0, 0.0, 0.0);
   DROP_WARNING(theImpl->getSensorVelocity(pt.line, pt.samp,
                                           val.x, val.y, val.z));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getSensorVelocity
//*****************************************************************************
csm::EcefVector csm2to3model::getSensorVelocity(double time) const
{
   EXCEPTION_TRY("csm2to3model::getSensorVelocity");

   CHECK_IMPL;

   csm::EcefVector val(0.0, 0.0, 0.0);
   DROP_WARNING(theImpl->getSensorVelocity(time, val.x, val.y, val.z));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getNumParameters
//*****************************************************************************
int csm2to3model::getNumParameters() const
{
   EXCEPTION_TRY("csm2to3model::getNumParameters");

   CHECK_IMPL;

   int val = 0;
   DROP_WARNING(theImpl->getNumParameters(val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getParameterName
//*****************************************************************************
std::string csm2to3model::getParameterName(int index) const
{
   EXCEPTION_TRY("csm2to3model::getParameterName");

   CHECK_IMPL;

   std::string val;
   DROP_WARNING(theImpl->getParameterName(index, val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getParameterUnits
//*****************************************************************************
std::string csm2to3model::getParameterUnits(int index) const
{
   //***
   // This is not a function on the 2A interface, so return "unknown" as a
   // default (this is preferable to an empty string).
   //***
   return "unknown";
}

//*****************************************************************************
// csm2to3model::hasShareableParameters
//*****************************************************************************
bool csm2to3model::hasShareableParameters() const
{
   EXCEPTION_TRY("csm2to3model::isParameterShareable");

   CHECK_IMPL;

   const int numParams = getNumParameters();
   for(int i = 0; i < numParams; ++i)
   {
      if (isParameterShareable(i)) return true;
   }

   return false;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::isParameterShareable
//*****************************************************************************
bool csm2to3model::isParameterShareable(int index) const
{
   EXCEPTION_TRY("csm2to3model::isParameterShareable");

   CHECK_IMPL;

   bool val = false;
   DROP_WARNING(theImpl->isParameterShareable(index, val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getParameterSharingCriteria
//*****************************************************************************
csm::SharingCriteria
csm2to3model::getParameterSharingCriteria(int index) const
{
   EXCEPTION_TRY("csm2to3model::getParameterSharingCriteria");

   CHECK_IMPL;
   
   csm::SharingCriteria criteria;
  
   DROP_WARNING(theImpl->
                getParameterSharingCriteria(index,
                                            criteria.matchesName,
                                            criteria.matchesSensorID,
                                            criteria.matchesPlatformID,
                                            criteria.matchesCollectionID,
                                            criteria.matchesTrajectoryID,
                                            criteria.matchesDateTime,
                                            criteria.maxTimeDelta));
   
   return criteria;
   
   EXCEPTION_RETHROW_CONVERT;
}


//*****************************************************************************
// csm2to3model::getParameterValue
//*****************************************************************************
double csm2to3model::getParameterValue(int index) const
{
   EXCEPTION_TRY("csm2to3model::getParameterValue");

   CHECK_IMPL;

   double val = 0.;
   DROP_WARNING(theImpl->getCurrentParameterValue(index, val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setParameterValue
//*****************************************************************************
void csm2to3model::setParameterValue(int index, double value)
{
   EXCEPTION_TRY("csm2to3model::setParameterValue");

   CHECK_IMPL;

   DROP_WARNING(theImpl->setCurrentParameterValue(index, value));

   EXCEPTION_RETHROW_CONVERT;
}


//*****************************************************************************
// csm2to3model::getParameterType
//*****************************************************************************
csm::param::Type csm2to3model::getParameterType(int index) const
{
   EXCEPTION_TRY("csm2to3model::getParameterType");

   CHECK_IMPL;

   TSMMisc::Param_CharType val;
   DROP_WARNING(theImpl->getParameterType(index, val));

   // enums have the same values, so just cast
   return (csm::param::Type)val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setParameterType
//*****************************************************************************
void csm2to3model::setParameterType(int index, csm::param::Type pType)
{
   EXCEPTION_TRY("csm2to3model::setParameterType");

   CHECK_IMPL;

   // enums have the same values, so just cast
   TSMMisc::Param_CharType val = (TSMMisc::Param_CharType)pType;
   DROP_WARNING(theImpl->setParameterType(index, val));

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::computeGroundPartials
//*****************************************************************************
std::vector<double>
csm2to3model::computeGroundPartials(const csm::EcefCoord& groundPt) const
{
   EXCEPTION_TRY("csm2to3model::computeGroundPartials");

   CHECK_IMPL;

   double partials[6] = {0.,0.,0.,0.,0.,0.};
   DROP_WARNING(theImpl->computeGroundPartials(groundPt.x,
                                               groundPt.y,
                                               groundPt.z,
                                               partials));
   return std::vector<double>(partials, partials+ 6);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::computeSensorPartials
//*****************************************************************************
csm::RasterGM::SensorPartials csm2to3model::computeSensorPartials(
   int index,
   const csm::EcefCoord& groundPt,
   double desiredPrecision,
   double* achievedPrecision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::computeSensorPartials");

   CHECK_IMPL;

   double tmp;
   SensorPartials partials(0., 0.);
   SAVE_WARNING(theImpl->computeSensorPartials(
                   index,
                   groundPt.x, groundPt.y, groundPt.z,
                   partials.first, partials.second,
                   achievedPrecision ? *achievedPrecision : tmp,
                   desiredPrecision),
                warnings);
   return partials;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::computeSensorPartials
//*****************************************************************************
csm::RasterGM::SensorPartials csm2to3model::computeSensorPartials(
   int index,
   const csm::ImageCoord& imagePt,
   const csm::EcefCoord& groundPt,
   double desiredPrecision,
   double* achievedPrecision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::computeSensorPartials");

   CHECK_IMPL;

   double tmp;
   SensorPartials partials(0., 0.);
   SAVE_WARNING(theImpl->computeSensorPartials(
                   index,
                   imagePt.line, imagePt.samp,
                   groundPt.x, groundPt.y, groundPt.z,
                   partials.first, partials.second,
                   achievedPrecision ? *achievedPrecision : tmp,
                   desiredPrecision),
                warnings);
   return partials;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getParameterCovariance
//*****************************************************************************
double csm2to3model::getParameterCovariance(int index1,
                                                   int index2) const
{
   EXCEPTION_TRY("csm2to3model::getParameterCovariance");

   CHECK_IMPL;

   double val;
   DROP_WARNING(theImpl->getCurrentParameterCovariance(index1, index2, val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setParameterCovariance
//*****************************************************************************
void csm2to3model::setParameterCovariance(int index1,
                                                 int index2,
                                                 double covariance)
{
   EXCEPTION_TRY("csm2to3model::setParameterCovariance");

   CHECK_IMPL;

   DROP_WARNING(theImpl->setCurrentParameterCovariance(index1, index2,
                                                       covariance));

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getNumGeometricCorrectionSwitches
//*****************************************************************************
int csm2to3model::getNumGeometricCorrectionSwitches() const
{
   EXCEPTION_TRY("csm2to3model::getNumGeometricCorrectionSwitches");

   CHECK_IMPL;

   int val;
   DROP_WARNING(theImpl->getNumSystematicErrorCorrections(val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getGeometricCorrectionName
//*****************************************************************************
std::string csm2to3model::getGeometricCorrectionName(int index) const
{
   EXCEPTION_TRY("csm2to3model::getGeometricCorrectionName");

   CHECK_IMPL;

   std::string val;
   DROP_WARNING(theImpl->getSystematicErrorCorrectionName(index, val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setGeometricCorrectionSwitch
//*****************************************************************************
void csm2to3model::setGeometricCorrectionSwitch(int index,
                                                bool value,
                                                csm::param::Type pType)
{
   EXCEPTION_TRY("csm2to3model::setGeometricCorrectionSwitch");

   CHECK_IMPL;

   // enums have the same values, so just cast
   TSMMisc::Param_CharType val = (TSMMisc::Param_CharType)pType;

   DROP_WARNING(theImpl->setCurrentSystematicErrorCorrectionSwitch(index,
                                                                   value,
                                                                   val));

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getGeometricCorrectionSwitch
//*****************************************************************************
bool csm2to3model::getGeometricCorrectionSwitch(int index) const
{
   EXCEPTION_TRY("csm2to3model::getGeometricCorrectionSwitch");

   CHECK_IMPL;

   bool val = false;
   DROP_WARNING(theImpl->getCurrentSystematicErrorCorrectionSwitch(index, val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getCrossCovarianceMatrix
//*****************************************************************************
std::vector<double>
csm2to3model::getCrossCovarianceMatrix(
   const csm::GeometricModel& comparisonModel,
   csm::param::Set pSet,
   const GeometricModelList& otherModels) const
{
   EXCEPTION_TRY("csm2to3model::getCrossCovarianceMatrix");

   CHECK_IMPL;
   
   const std::vector<int> indicesForThis = getParameterSetIndices(pSet);
   const std::vector<int> indicesForComp = comparisonModel.
                                           getParameterSetIndices(pSet);
   
   
   std::vector<double> mat(indicesForThis.size() *
                           indicesForComp.size(),
                           0.0);

   // TODO

   return mat;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// CLASS: TransferFourParams
//> This class derives from TSM's CSMFourParameterCorrelationModel and is used
//  to access the protected elements of that class to populate a CSM
//  FourParameterCorrelationModel's correlation group parameters.
//
//  Do not construct an object of this class -- only cast a
//  CSMFourParameterCorrelationModel* to it to call the transferParams()
//  method.
//<
//*****************************************************************************
class TransferFourParams : public CSMFourParameterCorrelationModel
{
public:
   void transferParams(csm::FourParameterCorrelationModel* csmModel)
   {
      const size_t count = _corrParams.size();
      for(size_t i = 0; i < count; ++i)
      {
         csmModel->setCorrelationGroupParameters(i,
                                                 _corrParams[i]._a,
                                                 _corrParams[i]._alpha,
                                                 _corrParams[i]._beta,
                                                 _corrParams[i]._tau);
      }
   }

private:
   TransferFourParams() : CSMFourParameterCorrelationModel(0,0) {}
      //> Do not use
      //<
};

//*****************************************************************************
// csm2to3model::getCovarianceModel
//*****************************************************************************
const csm::CovarianceModel& csm2to3model::getCovarianceModel() const
{
   EXCEPTION_TRY("csm2to3model::getCovarianceModel");
   
   if (!theCovarianceModel)
   { 
      CHECK_IMPL;

      bool hasCovarianceModel = true;
      
      // use an auto_ptr to store the TSM model so that it will be deleted
      std::auto_ptr<tsm_CovarianceModel> tsmModel;
      {
         tsm_CovarianceModel* tmp;
         DROP_WARNING(theImpl->getCovarianceModel(tmp));
         if (!tmp) hasCovarianceModel = false;
         
         tsmModel.reset(tmp);
      }

      if (hasCovarianceModel)
      {
         // see if this is a 4 param model we can convert to the CSM version
         CSMFourParameterCorrelationModel* tsmFourParamModel =
            dynamic_cast<CSMFourParameterCorrelationModel*>(tsmModel.get());
         if (tsmFourParamModel != NULL)
         {
            int numSm = 0;
            int numCp = 0;
            DROP_WARNING(tsmFourParamModel->getNumSensorModelParameters(numSm));
            DROP_WARNING(tsmFourParamModel->getNumCorrelationParameterGroups(numCp));
            
            csm::FourParameterCorrelationModel* csmModel =
               new csm::FourParameterCorrelationModel(numSm, numCp);
            
            for(int i = 0; i < numSm; ++i)
            {
               int index = 0;
               DROP_WARNING(tsmFourParamModel->getCorrelationParameterGroup(i, index));
               csmModel->setCorrelationParameterGroup(i, index);
            }
            
            //***
            // Use the TransferFourParams class to access the protected members and
            // copy data to the CSM covar model.
            //***
            ((TransferFourParams*)tsmFourParamModel)->transferParams(csmModel);
            
            csm2to3model* nonConstThis = const_cast<csm2to3model*>(this); 
            nonConstThis->theCovarianceModel = csmModel;
         }
         else
         {
            std::string format;
            tsmModel->getFormat(format);
            std::ostringstream msg;
            msg << "Unsupported TSM covaraince model: \"" << format
                << "\".  Cannot convert to CSM.";
            throw csm::Error(csm::Error::UNSUPPORTED_FUNCTION, msg.str(), MODULE);
         }
      }
      else
      {
         csm2to3model* nonConstThis = const_cast<csm2to3model*>(this);
         nonConstThis->theCovarianceModel = new csm::NoCovarianceModel();
      }
   }
   return (*theCovarianceModel);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getUnmodeledCrossCovariance
//*****************************************************************************
std::vector<double> csm2to3model::getUnmodeledCrossCovariance(
   const csm::ImageCoord& pt1,
   const csm::ImageCoord& pt2) const
{
   EXCEPTION_TRY("csm2to3model::getUnmodeledCrossCovariance");

   CHECK_IMPL;

   double covar[4] = {0., 0., 0., 0.};
   DROP_WARNING(theImpl->getUnmodeledCrossCovariance(pt1.line, pt1.samp,
                                                     pt2.line, pt2.samp,
                                                     covar));
   return std::vector<double>(covar, covar+4);

   EXCEPTION_RETHROW_CONVERT;
}
