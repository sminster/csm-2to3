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
}

//*****************************************************************************
// csm2to3model::getModelType
//*****************************************************************************
std::string csm2to3model::getModelType() const
{
}

//*****************************************************************************
// csm2to3model::getModelName
//*****************************************************************************
std::string csm2to3model::getModelName() const
{
}

//*****************************************************************************
// csm2to3model::getPedigree
//*****************************************************************************
std::string csm2to3model::getPedigree() const
{
}

//*****************************************************************************
// csm2to3model::getImageIdentifier
//*****************************************************************************
std::string csm2to3model::getImageIdentifier() const
{
}

//*****************************************************************************
// csm2to3model::setImageIdentifier
//*****************************************************************************
void csm2to3model::setImageIdentifier(const std::string& imageId,
                                      csm::WarningList* warnings)
{
}

//*****************************************************************************
// csm2to3model::getSensorIdentifier
//*****************************************************************************
std::string csm2to3model::getSensorIdentifier() const
{
}

//*****************************************************************************
// csm2to3model::getPlatformIdentifier
//*****************************************************************************
std::string csm2to3model::getPlatformIdentifier() const
{
}

//*****************************************************************************
// csm2to3model::getCollectionIdentifier
//*****************************************************************************
std::string csm2to3model::getCollectionIdentifier() const
{
}

//*****************************************************************************
// csm2to3model::getSensorTypeAndMode
//*****************************************************************************
csm::SensorTypeAndMode csm2to3model::getSensorTypeAndMode() const
{
}

//*****************************************************************************
// csm2to3model::getReferencePoint
//*****************************************************************************
csm::EcefCoord csm2to3model::getReferencePoint() const
{
}

//*****************************************************************************
// csm2to3model::setReferencePoint
//*****************************************************************************
void csm2to3model::setReferencePoint(const csm::EcefCoord& groundPt)
{
}

//*****************************************************************************
// csm2to3model::getSensorModelState
//*****************************************************************************
std::string csm2to3model::getSensorModelState() const
{
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
}

//*****************************************************************************
// csm2to3model::imageToGround
//*****************************************************************************
csm::EcefCoord csm2to3model::imageToGround(
   const csm::ImageCoord& imagePt,
   double height,
   const std::vector<double> imageCovariance,
   std::vector<double>& groundCovariance,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings) const
{
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
}

//*****************************************************************************
// csm2to3model::imageToRemoteImagingLocus
//*****************************************************************************
std::vector<double> csm2to3model::imageToRemoteImagingLocus(
   const csm::ImageCoord& imagePt,
   const csm::EcefCoord& groundPt,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings) const
{
}

//*****************************************************************************
// csm2to3model::getImageStart
//*****************************************************************************
csm::ImageCoord csm2to3model::getImageStart() const
{
}

//*****************************************************************************
// csm2to3model::getImageSize
//*****************************************************************************
csm::ImageVector csm2to3model::getImageSize() const
{
}

//*****************************************************************************
// csm2to3model::getValidHeightRange
//*****************************************************************************
std::pair<double,double> csm2to3model::getValidHeightRange() const
{
}

//*****************************************************************************
// csm2to3model::getValidImageRange
//*****************************************************************************
std::pair<csm::ImageCoord,csm::ImageCoord>
csm2to3model::getValidImageRange() const
{
}

//*****************************************************************************
// csm2to3model::getIlluminationDirection
//*****************************************************************************
csm::EcefVector
csm2to3model::getIlluminationDirection(const csm::EcefCoord& gndPt) const
{
}

//*****************************************************************************
// csm2to3model::getTrajectoryIdentifier
//*****************************************************************************
std::string csm2to3model::getTrajectoryIdentifier() const
{
}

//*****************************************************************************
// csm2to3model::getReferenceDateAndTime
//*****************************************************************************
std::string csm2to3model::getReferenceDateAndTime() const
{
}

//*****************************************************************************
// csm2to3model::getImageTime
//*****************************************************************************
double csm2to3model::getImageTime(const csm::ImageCoord& pt) const
{
}

//*****************************************************************************
// csm2to3model::getSensorPosition
//*****************************************************************************
csm::EcefCoord csm2to3model::getSensorPosition(const csm::ImageCoord& pt) const
{
}

//*****************************************************************************
// csm2to3model::getSensorPosition
//*****************************************************************************
csm::EcefCoord csm2to3model::getSensorPosition(double time) const
{
}

//*****************************************************************************
// csm2to3model::getSensorVelocity
//*****************************************************************************
csm::EcefVector csm2to3model::getSensorVelocity(const csm::ImageCoord& pt)const
{
}

//*****************************************************************************
// csm2to3model::getSensorVelocity
//*****************************************************************************
csm::EcefVector csm2to3model::getSensorVelocity(double time) const
{
}

//*****************************************************************************
// csm2to3model::getNumParameters
//*****************************************************************************
int csm2to3model::getNumParameters() const
{
}

//*****************************************************************************
// csm2to3model::getParameterName
//*****************************************************************************
std::string csm2to3model::getParameterName(int index) const
{
}

//*****************************************************************************
// csm2to3model::isParameterShareable
//*****************************************************************************
bool csm2to3model::isParameterShareable(int index) const
{
}

//*****************************************************************************
// csm2to3model::getParameterSharingCriteria
//*****************************************************************************
std::vector<csm::ParameterSharingCriteria>&
csm2to3model::getParameterSharingCriteria(int index) const
{
}

//*****************************************************************************
// csm2to3model::getOriginalParameterValue
//*****************************************************************************
double csm2to3model::getOriginalParameterValue(int index) const
{
}

//*****************************************************************************
// csm2to3model::getCurrentParameterValue
//*****************************************************************************
double csm2to3model::getCurrentParameterValue(int index) const
{
}

//*****************************************************************************
// csm2to3model::setCurrentParameterValue
//*****************************************************************************
void csm2to3model::setCurrentParameterValue(int index, double value)
{
}

//*****************************************************************************
// csm2to3model::setOriginalParameterValue
//*****************************************************************************
void csm2to3model::setOriginalParameterValue(int index, double value)
{
}

//*****************************************************************************
// csm2to3model::getOriginalParameterType
//*****************************************************************************
csm::ParamType csm2to3model::getOriginalParameterType(int index) const
{
}

//*****************************************************************************
// csm2to3model::getCurrentParameterType
//*****************************************************************************
csm::ParamType csm2to3model::getCurrentParameterType(int index) const
{
}

//*****************************************************************************
// csm2to3model::setOriginalParameterType
//*****************************************************************************
void csm2to3model::setOriginalParameterType(int index, csm::ParamType pType)
{
}

//*****************************************************************************
// csm2to3model::setCurrentParameterType
//*****************************************************************************
void csm2to3model::setCurrentParameterType(int index, csm::ParamType pType)
{
}

//*****************************************************************************
// csm2to3model::computeGroundPartials
//*****************************************************************************
std::vector<double>
csm2to3model::computeGroundPartials(const csm::EcefCoord& groundPt)
{
}

//*****************************************************************************
// csm2to3model::computeSensorPartials
//*****************************************************************************
SensorPartials csm2to3model::computeSensorPartials(
   int index,
   const csm::EcefCoord& groundPt,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings)
{
}

//*****************************************************************************
// csm2to3model::computeSensorPartials
//*****************************************************************************
SensorPartials csm2to3model::computeSensorPartials(
   int index,
   const csm::ImageCoord& imagePt,
   const csm::EcefCoord& groundPt,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings)
{
}

//*****************************************************************************
// csm2to3model::computeAllSensorPartials
//*****************************************************************************
std::vector<SensorPartials> csm2to3model::computeAllSensorPartials(
   const csm::EcefCoord& groundPt,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings)
{
}

//*****************************************************************************
// csm2to3model::computeAllSensorPartials
//*****************************************************************************
std::vector<SensorPartials> csm2to3model::computeAllSensorPartials(
   const csm::ImageCoord& imagePt,
   const csm::EcefCoord& groundPt,
   double desired_precision,
   double* achieved_precision,
   csm::WarningList* warnings)
{
}

//*****************************************************************************
// csm2to3model::getCurrentParameterCovariance
//*****************************************************************************
double csm2to3model::getCurrentParameterCovariance(int index1,
                                                   int index2) const
{
}

//*****************************************************************************
// csm2to3model::setCurrentParameterCovariance
//*****************************************************************************
void csm2to3model::setCurrentParameterCovariance(int index1,
                                                 int index2,
                                                 double covariance)
{
}

//*****************************************************************************
// csm2to3model::getOriginalParameterCovariance
//*****************************************************************************
double csm2to3model::getOriginalParameterCovariance(int index1,
                                                    int index2) const
{
}

//*****************************************************************************
// csm2to3model::setOriginalParameterCovariance
//*****************************************************************************
void csm2to3model::setOriginalParameterCovariance(int index1,
                                                  int index2,
                                                  double covariance)
{
}

//*****************************************************************************
// csm2to3model::getNumGeometricCorrectionSwitches
//*****************************************************************************
int csm2to3model::getNumGeometricCorrectionSwitches() const
{
}

//*****************************************************************************
// csm2to3model::getGeometricCorrectionName
//*****************************************************************************
std::string csm2to3model::getGeometricCorrectionName(int index) const
{
}

//*****************************************************************************
// csm2to3model::setCurrentGeometricCorrectionSwitch
//*****************************************************************************
void csm2to3model::setCurrentGeometricCorrectionSwitch(int index,
                                                       bool value,
                                                       csm::ParamType pType)
{
}

//*****************************************************************************
// csm2to3model::getCurrentGeometricCorrectionSwitch
//*****************************************************************************
bool csm2to3model::getCurrentGeometricCorrectionSwitch(int index) const
{
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
}

//*****************************************************************************
// csm2to3model::getCovarianceModel
//*****************************************************************************
csm::CovarianceModel* csm2to3model::getCovarianceModel() const
{
}

//*****************************************************************************
// csm2to3model::getUnmodeledError
//*****************************************************************************
std::vector<double> csm2to3model::getUnmodeledError(const csm::ImageCoord& pt) const
{
}

//*****************************************************************************
// csm2to3model::getUnmodeledCrossCovariance
//*****************************************************************************
std::vector<double> csm2to3model::getUnmodeledCrossCovariance(
   const csm::ImageCoord& pt1,
   const csm::ImageCoord& pt2) const
{
}
