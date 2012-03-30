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
#include <csm/CSMError.h>

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
int csm2to3model::getVersion() const
{
   EXCEPTION_TRY("csm2to3model::getVersion");

   // TODO
   return 1;

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

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getSensorTypeAndMode
//*****************************************************************************
csm::SensorTypeAndMode csm2to3model::getSensorTypeAndMode() const
{
   EXCEPTION_TRY("csm2to3model::getSensorTypeAndMode");

   // TODO

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
csm::ImageCoord csm2to3model::groundToImage(
   const csm::EcefCoord& groundPt,
   const std::vector<double> groundCovariance,
   std::vector<double>& imageCovariance,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::groundToImage");

   CHECK_IMPL;

   if (groundCovariance.size() != 9)
   {
      std::ostringstream msg;
      msg << "Ground convariance has " << groundCovariance.size()
          << " elements instead of 9";
      throw csm::Error(csm::Error::INVALID_USE, msg.str(), MODULE);
   }

   csm::ImageCoord val(0, 0);
   double tmp;
   double imageCovar[4] = {0.,0.,0.,0.};
   SAVE_WARNING(theImpl->groundToImage(groundPt.x, groundPt.y, groundPt.z,
                                       &(groundCovariance[0]),
                                       val.line, val.samp,
                                       imageCovar,
                                       achieved_precision ? *achieved_precision : tmp,
                                       desired_precision),
                warnings);
   imageCovariance = std::vector<double>(imageCovar, imageCovar + 4);
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
csm::EcefCoord csm2to3model::imageToGround(
   const csm::ImageCoord& imagePt,
   const std::vector<double> imageCovariance,
   double height, double heightVariance,
   std::vector<double>& groundCovariance,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3model::imageToGround");

   CHECK_IMPL;

   if (imageCovariance.size() != 4)
   {
      std::ostringstream msg;
      msg << "Ground convariance has " << imageCovariance.size()
          << " elements instead of 4";
      throw csm::Error(csm::Error::INVALID_USE, msg.str(), MODULE);
   }

   csm::EcefCoord val(0, 0, 0);
   double tmp;
   double groundCovar[9] = {0.,0.,0.,0.,0.,0.,0.,0.,0.};
   SAVE_WARNING(theImpl->imageToGround(imagePt.line, imagePt.samp,
                                       &(imageCovariance[0]),
                                       height, heightVariance,
                                       val.x, val.y, val.z,
                                       groundCovar,
                                       achieved_precision ? *achieved_precision : tmp,
                                       desired_precision),
                warnings);
   groundCovariance = std::vector<double>(groundCovar, groundCovar + 9);
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

   // TODO

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

   // TODO

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

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getParameterName
//*****************************************************************************
std::string csm2to3model::getParameterName(int index) const
{
   EXCEPTION_TRY("csm2to3model::getParameterName");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::isParameterShareable
//*****************************************************************************
bool csm2to3model::isParameterShareable(int index) const
{
   EXCEPTION_TRY("csm2to3model::isParameterShareable");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getParameterSharingCriteria
//*****************************************************************************
std::vector<csm::ParameterSharingCriteria>&
csm2to3model::getParameterSharingCriteria(int index) const
{
   EXCEPTION_TRY("csm2to3model::getParameterSharingCriteria");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getOriginalParameterValue
//*****************************************************************************
double csm2to3model::getOriginalParameterValue(int index) const
{
   EXCEPTION_TRY("csm2to3model::getOriginalParameterValue");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getCurrentParameterValue
//*****************************************************************************
double csm2to3model::getCurrentParameterValue(int index) const
{
   EXCEPTION_TRY("csm2to3model::getCurrentParameterValue");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setCurrentParameterValue
//*****************************************************************************
void csm2to3model::setCurrentParameterValue(int index, double value)
{
   EXCEPTION_TRY("csm2to3model::setCurrentParameterValue");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setOriginalParameterValue
//*****************************************************************************
void csm2to3model::setOriginalParameterValue(int index, double value)
{
   EXCEPTION_TRY("csm2to3model::setOriginalParameterValue");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getOriginalParameterType
//*****************************************************************************
csm::ParamType csm2to3model::getOriginalParameterType(int index) const
{
   EXCEPTION_TRY("csm2to3model::getOriginalParameterType");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getCurrentParameterType
//*****************************************************************************
csm::ParamType csm2to3model::getCurrentParameterType(int index) const
{
   EXCEPTION_TRY("csm2to3model::getCurrentParameterType");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setOriginalParameterType
//*****************************************************************************
void csm2to3model::setOriginalParameterType(int index, csm::ParamType pType)
{
   EXCEPTION_TRY("csm2to3model::setOriginalParameterType");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::setCurrentParameterType
//*****************************************************************************
void csm2to3model::setCurrentParameterType(int index, csm::ParamType pType)
{
   EXCEPTION_TRY("csm2to3model::setCurrentParameterType");

   // TODO

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

   // TODO

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

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getCurrentParameterCovariance
//*****************************************************************************
double csm2to3model::getCurrentParameterCovariance(int index1,
                                                   int index2) const
{
   EXCEPTION_TRY("csm2to3model::getCurrentParameterCovariance");

   // TODO

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

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getOriginalParameterCovariance
//*****************************************************************************
double csm2to3model::getOriginalParameterCovariance(int index1,
                                                    int index2) const
{
   EXCEPTION_TRY("csm2to3model::getOriginalParameterCovariance");

   // TODO

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

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getNumGeometricCorrectionSwitches
//*****************************************************************************
int csm2to3model::getNumGeometricCorrectionSwitches() const
{
   EXCEPTION_TRY("csm2to3model::getNumGeometricCorrectionSwitches");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getGeometricCorrectionName
//*****************************************************************************
std::string csm2to3model::getGeometricCorrectionName(int index) const
{
   EXCEPTION_TRY("csm2to3model::getGeometricCorrectionName");

   // TODO

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

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getCurrentGeometricCorrectionSwitch
//*****************************************************************************
bool csm2to3model::getCurrentGeometricCorrectionSwitch(int index) const
{
   EXCEPTION_TRY("csm2to3model::getCurrentGeometricCorrectionSwitch");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getCurrentCrossCovarianceMatrix
//*****************************************************************************
std::vector<std::vector<double> >
csm2to3model::getCurrentCrossCovarianceMatrix(
   const csm::ImageCoord imagePt,
   const csm::SensorModel* comparisonModel,
   const csm::ImageCoord&  comparisonModelImagePt) const
{
   EXCEPTION_TRY("csm2to3model::getCurrentCrossCovarianceMatrix");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getOriginalCrossCovarianceMatrix
//*****************************************************************************
std::vector<std::vector<double> >
csm2to3model::getOriginalCrossCovarianceMatrix(
   const csm::ImageCoord imagePt,
   const csm::SensorModel* comparisonModel,
   const csm::ImageCoord&  comparisonModelImagePt) const
{
   EXCEPTION_TRY("csm2to3model::getOriginalCrossCovarianceMatrix");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getCovarianceModel
//*****************************************************************************
csm::CovarianceModel* csm2to3model::getCovarianceModel() const
{
   EXCEPTION_TRY("csm2to3model::getCovarianceModel");

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3model::getUnmodeledError
//*****************************************************************************
std::vector<double> csm2to3model::getUnmodeledError(const csm::ImageCoord& pt) const
{
   EXCEPTION_TRY("csm2to3model::getUnmodeledError");

   // TODO

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

   // TODO

   EXCEPTION_RETHROW_CONVERT;
}
