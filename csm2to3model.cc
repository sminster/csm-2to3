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
//> 30MAR12 956F PTR#?????-IPL  S. Minster
//               Initial Coding.
//<
//*****************************************************************************

#include "csm2to3model.h"
#include "csm2to3-private.h"

#include <tsm/TSMSensorModel.h>
#include <tsm/CSMFourParameterCorrelationModel.h>
#include <csm/CSMError.h>
#include <csm/CSMFourParameterCorrelationModel.h>

#include <sstream>

#define CHECK_IMPL if (!theImpl) throw csm::Error(csm::Error::INVALID_USE, "Implementation model is NULL", MODULE)

#define DROP_WARNING(expr) \
   do { TSMWarning* w = expr; if (w) delete w; } while (0)

#define SAVE_WARNING(expr,warnings) \
   do { TSMWarning* w = expr; if (w) { if (warnings) warnings->push_back(CONVERT_WARNING(w)); delete w; } } while (0)


//*****************************************************************************
// csm2to3model::csm2to3model
//*****************************************************************************
csm2to3model::csm2to3model(TSMSensorModel* impl)
   :
      theImpl(impl)
{
}

//*****************************************************************************
// csm2to3model::~csm2to3model
//*****************************************************************************
csm2to3model::~csm2to3model()
{
   delete theImpl;
   theImpl = NULL;
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
// csm2to3model::getModelType
//*****************************************************************************
std::string csm2to3model::getModelType() const
{
   EXCEPTION_TRY("csm2to3model::getModelType");

   // TODO
   return "csm2to3model";

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
// csm2to3model::getSensorTypeAndMode
//*****************************************************************************
csm::SensorTypeAndMode csm2to3model::getSensorTypeAndMode() const
{
   EXCEPTION_TRY("csm2to3model::getSensorTypeAndMode");

   // TODO -- maybe getPedigree could help here?
   return csm::SensorTypeAndMode(TYPE_UNK, "");

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
// csm2to3model::groundToImage
//*****************************************************************************
csm::ImageCoord csm2to3model::groundToImage(
   const csm::EcefCoord& groundPt,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::groundToImage");

   CHECK_IMPL;

   csm::ImageCoord val(0, 0);
   double tmp;
   SAVE_WARNING(theImpl->groundToImage(groundPt.x, groundPt.y, groundPt.z,
                                       val.line, val.samp,
                                       achieved_precision ? *achieved_precision : tmp,
                                       desired_precision),
                warnings);
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::groundToImage
//*****************************************************************************
csm::ImageCoordCovar csm2to3model::groundToImage(
   const csm::EcefCoordCovar& groundPt,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::groundToImage");

   CHECK_IMPL;
\
   csm::ImageCoordCovar val(0, 0);
   double tmp;
   SAVE_WARNING(theImpl->groundToImage(groundPt.x, groundPt.y, groundPt.z,
                                       groundPt.covar(),
                                       val.line, val.samp, val.covar(),
                                       achieved_precision ? *achieved_precision : tmp,
                                       desired_precision),
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
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::imageToGround");

   CHECK_IMPL;

   csm::EcefCoord val(0, 0, 0);
   double tmp;
   SAVE_WARNING(theImpl->imageToGround(imagePt.line, imagePt.samp, height,
                                       val.x, val.y, val.z,
                                       achieved_precision ? *achieved_precision : tmp,
                                       desired_precision),
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
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::imageToGround");

   CHECK_IMPL;

   csm::EcefCoordCovar val(0, 0, 0);
   double tmp;
   SAVE_WARNING(theImpl->imageToGround(imagePt.line, imagePt.samp, imagePt.covar(),
                                       height, heightVariance,
                                       val.x, val.y, val.z, val.covar(),
                                       achieved_precision ? *achieved_precision : tmp,
                                       desired_precision),
                warnings);

   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::imageToProximateImagingLocus
//*****************************************************************************
std::vector<double> csm2to3model::imageToProximateImagingLocus(
   const csm::ImageCoord& imagePt,
   const csm::EcefCoord& groundPt,
   double desired_precision,
   double* achieved_precision,
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
                   achieved_precision ? *achieved_precision : tmp,
                   desired_precision),
                warnings);
   return std::vector<double>(locus, locus + 6);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::imageToRemoteImagingLocus
//*****************************************************************************
std::vector<double> csm2to3model::imageToRemoteImagingLocus(
   const csm::ImageCoord& imagePt,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::imageToRemoteImagingLocus");

   CHECK_IMPL;

   double tmp;
   double locus[6] = {0.,0.,0.,0.,0.,0.};
   SAVE_WARNING(theImpl->imageToRemoteImagingLocus(
                   imagePt.line, imagePt.samp,
                   locus,
                   achieved_precision ? *achieved_precision : tmp,
                   desired_precision),
                warnings);
   return std::vector<double>(locus, locus + 6);

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
std::vector<csm::ParameterSharingCriteria>
csm2to3model::getParameterSharingCriteria(int index) const
{
   EXCEPTION_TRY("csm2to3model::getParameterSharingCriteria");

   CHECK_IMPL;

   bool modelName = false;
   bool sensorId = false;
   bool platformId = false;
   bool collectionId = false;
   bool trajectoryId = false;
   bool dateTime = false;
   double timeDelta = 0.0;
   DROP_WARNING(theImpl->getParameterSharingCriteria(index,
                                                     modelName,
                                                     sensorId,
                                                     platformId,
                                                     collectionId,
                                                     trajectoryId,
                                                     dateTime,
                                                     timeDelta));

   std::vector<csm::ParameterSharingCriteria> val;
   if (modelName) val.push_back(csm::ParameterSharingCriteria(csm::SHARE_BY_MODEL_NAME));
   if (sensorId) val.push_back(csm::ParameterSharingCriteria(csm::SHARE_BY_SENSOR_ID));
   if (platformId) val.push_back(csm::ParameterSharingCriteria(csm::SHARE_BY_PLATFORM_ID));
   if (collectionId) val.push_back(csm::ParameterSharingCriteria(csm::SHARE_BY_COLLECTION_ID));
   if (trajectoryId) val.push_back(csm::ParameterSharingCriteria(csm::SHARE_BY_TRAJECTORY_ID));
   if (dateTime) val.push_back(csm::ParameterSharingCriteria(timeDelta));

   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getOriginalParameterValue
//*****************************************************************************
double csm2to3model::getOriginalParameterValue(int index) const
{
   EXCEPTION_TRY("csm2to3model::getOriginalParameterValue");

   CHECK_IMPL;

   double val = 0.;
   DROP_WARNING(theImpl->getOriginalParameterValue(index, val));
   return val;


   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getCurrentParameterValue
//*****************************************************************************
double csm2to3model::getCurrentParameterValue(int index) const
{
   EXCEPTION_TRY("csm2to3model::getCurrentParameterValue");

   CHECK_IMPL;

   double val = 0.;
   DROP_WARNING(theImpl->getCurrentParameterValue(index, val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setCurrentParameterValue
//*****************************************************************************
void csm2to3model::setCurrentParameterValue(int index, double value)
{
   EXCEPTION_TRY("csm2to3model::setCurrentParameterValue");

   CHECK_IMPL;

   DROP_WARNING(theImpl->setCurrentParameterValue(index, value));

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setOriginalParameterValue
//*****************************************************************************
void csm2to3model::setOriginalParameterValue(int index, double value)
{
   EXCEPTION_TRY("csm2to3model::setOriginalParameterValue");

   CHECK_IMPL;

   DROP_WARNING(theImpl->setOriginalParameterValue(index, value));

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getOriginalParameterType
//*****************************************************************************
csm::ParamType csm2to3model::getOriginalParameterType(int index) const
{
   EXCEPTION_TRY("csm2to3model::getOriginalParameterType");

   CHECK_IMPL;

   TSMMisc::Param_CharType val;
   DROP_WARNING(theImpl->getParameterType(index, val));

   // enums have the same values, so just cast
   return (csm::ParamType)val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getCurrentParameterType
//*****************************************************************************
csm::ParamType csm2to3model::getCurrentParameterType(int index) const
{
   EXCEPTION_TRY("csm2to3model::getCurrentParameterType");

   // no difference between original and current in TSM model
   return getOriginalParameterType(index);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setOriginalParameterType
//*****************************************************************************
void csm2to3model::setOriginalParameterType(int index, csm::ParamType pType)
{
   EXCEPTION_TRY("csm2to3model::setOriginalParameterType");

   CHECK_IMPL;

   // enums have the same values, so just cast
   TSMMisc::Param_CharType val = (TSMMisc::Param_CharType)pType;
   DROP_WARNING(theImpl->setParameterType(index, val));

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setCurrentParameterType
//*****************************************************************************
void csm2to3model::setCurrentParameterType(int index, csm::ParamType pType)
{
   EXCEPTION_TRY("csm2to3model::setCurrentParameterType");

   // no difference between original and current in TSM model
   return setOriginalParameterType(index, pType);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::computeGroundPartials
//*****************************************************************************
std::vector<double>
csm2to3model::computeGroundPartials(const csm::EcefCoord& groundPt)
{
   EXCEPTION_TRY("csm2to3model::computeGroundPartials");

   CHECK_IMPL;

   double tmp;
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
csm::SensorModel::SensorPartials csm2to3model::computeSensorPartials(
   int index,
   const csm::EcefCoord& groundPt,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings)
{
   EXCEPTION_TRY("csm2to3model::computeSensorPartials");

   CHECK_IMPL;

   double tmp;
   SensorPartials partials(0., 0.);
   SAVE_WARNING(theImpl->computeSensorPartials(
                   index,
                   groundPt.x, groundPt.y, groundPt.z,
                   partials.first, partials.second,
                   achieved_precision ? *achieved_precision : tmp,
                   desired_precision),
                warnings);
   return partials;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::computeSensorPartials
//*****************************************************************************
csm::SensorModel::SensorPartials csm2to3model::computeSensorPartials(
   int index,
   const csm::ImageCoord& imagePt,
   const csm::EcefCoord& groundPt,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings)
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
                   achieved_precision ? *achieved_precision : tmp,
                   desired_precision),
                warnings);
   return partials;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::computeAllSensorPartials
//*****************************************************************************
std::vector<csm::SensorModel::SensorPartials>
csm2to3model::computeAllSensorPartials(
   const csm::EcefCoord& groundPt,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings)
{
   EXCEPTION_TRY("csm2to3model::computeAllSensorPartials");

   CHECK_IMPL;

   std::vector<csm::SensorModel::SensorPartials> val;
   const int numParams = getNumParameters();
   for(int i = 0; i < numParams; ++i)
   {
      double prec = 0.0;
      val.push_back(
         computeSensorPartials(i, groundPt,
                               desired_precision, &prec, warnings));

      if (achieved_precision && prec < *achieved_precision)
      {
         *achieved_precision = prec;
      }
   }
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::computeAllSensorPartials
//*****************************************************************************
std::vector<csm::SensorModel::SensorPartials>
csm2to3model::computeAllSensorPartials(
   const csm::ImageCoord& imagePt,
   const csm::EcefCoord& groundPt,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings)
{
   EXCEPTION_TRY("csm2to3model::computeAllSensorPartials");

   CHECK_IMPL;

   std::vector<csm::SensorModel::SensorPartials> val;
   const int numParams = getNumParameters();
   for(int i = 0; i < numParams; ++i)
   {
      double prec = 0.0;
      val.push_back(
         computeSensorPartials(i, imagePt, groundPt,
                               desired_precision, &prec, warnings));

      if (achieved_precision && prec < *achieved_precision)
      {
         *achieved_precision = prec;
      }
   }
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getCurrentParameterCovariance
//*****************************************************************************
double csm2to3model::getCurrentParameterCovariance(int index1,
                                                   int index2) const
{
   EXCEPTION_TRY("csm2to3model::getCurrentParameterCovariance");

   CHECK_IMPL;

   double val;
   DROP_WARNING(theImpl->getCurrentParameterCovariance(index1, index2, val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setCurrentParameterCovariance
//*****************************************************************************
void csm2to3model::setCurrentParameterCovariance(int index1,
                                                 int index2,
                                                 double covariance)
{
   EXCEPTION_TRY("csm2to3model::setCurrentParameterCovariance");

   CHECK_IMPL;

   DROP_WARNING(theImpl->setCurrentParameterCovariance(index1, index2,
                                                       covariance));

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getOriginalParameterCovariance
//*****************************************************************************
double csm2to3model::getOriginalParameterCovariance(int index1,
                                                    int index2) const
{
   EXCEPTION_TRY("csm2to3model::getOriginalParameterCovariance");

   CHECK_IMPL;

   double val;
   DROP_WARNING(theImpl->getOriginalParameterCovariance(index1, index2, val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setOriginalParameterCovariance
//*****************************************************************************
void csm2to3model::setOriginalParameterCovariance(int index1,
                                                  int index2,
                                                  double covariance)
{
   EXCEPTION_TRY("csm2to3model::setOriginalParameterCovariance");

   CHECK_IMPL;

   DROP_WARNING(theImpl->setOriginalParameterCovariance(index1, index2,
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
// csm2to3model::setCurrentGeometricCorrectionSwitch
//*****************************************************************************
void csm2to3model::setCurrentGeometricCorrectionSwitch(int index,
                                                       bool value,
                                                       csm::ParamType pType)
{
   EXCEPTION_TRY("csm2to3model::setCurrentGeometricCorrectionSwitch");

   CHECK_IMPL;

   // enums have the same values, so just cast
   TSMMisc::Param_CharType val = (TSMMisc::Param_CharType)pType;

   DROP_WARNING(theImpl->setCurrentSystematicErrorCorrectionSwitch(index,
                                                                   value,
                                                                   val));

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getCurrentGeometricCorrectionSwitch
//*****************************************************************************
bool csm2to3model::getCurrentGeometricCorrectionSwitch(int index) const
{
   EXCEPTION_TRY("csm2to3model::getCurrentGeometricCorrectionSwitch");

   CHECK_IMPL;

   bool val = false;
   DROP_WARNING(theImpl->getCurrentSystematicErrorCorrectionSwitch(index, val));
   return val;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getCurrentCrossCovarianceMatrix
//*****************************************************************************
std::vector<double>
csm2to3model::getCurrentCrossCovarianceMatrix(
   const csm::SensorModel& comparisonModel,
   const SensorModelList& otherModels) const
{
   EXCEPTION_TRY("csm2to3model::getCurrentCrossCovarianceMatrix");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getOriginalCrossCovarianceMatrix
//*****************************************************************************
std::vector<double>
csm2to3model::getOriginalCrossCovarianceMatrix(
   const csm::SensorModel& comparisonModel,
   const SensorModelList& otherModels) const
{
   EXCEPTION_TRY("csm2to3model::getOriginalCrossCovarianceMatrix");

   // TODO

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
csm::CovarianceModel* csm2to3model::getCovarianceModel() const
{
   EXCEPTION_TRY("csm2to3model::getCovarianceModel");

   CHECK_IMPL;

   // use an auto_ptr to store the TSM model so that it will be deleted
   std::auto_ptr<tsm_CovarianceModel> tsmModel;
   {
      tsm_CovarianceModel* tmp;
      DROP_WARNING(theImpl->getCovarianceModel(tmp));
      if (!tmp) return NULL;
      tsmModel.reset(tmp);
   }

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

      return csmModel;
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
