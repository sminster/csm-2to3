//#############################################################################
//## Restricted Rights
//## WARNING: This is a restricted distribution HARRIS REPOSITORY file.
//##          Do Not Use Under A Government Charge Number Without Permission.
//#############################################################################

//*****************************************************************************
// FILE:              csm2to3model.h
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
//>
//     Date          Author   Comment   
//     -----------   ------   ------- 
//     30-Mar-2012   SCM      Initial Coding
//     26-Sep-2012   JPK      Ripple class hierarchy change
//     11-Oct-2012   SCM      Added getParameterUnits.
//<
//*****************************************************************************

#ifndef csm2to3model_HEADER
#define csm2to3model_HEADER

#include <csm/CSMRasterGM.h>

class TSMSensorModel;

//*****************************************************************************
// CLASS:  csm2to3model
//> This class implements a CSM version 3 RasterGM interface by calling the
//  equivalent CSM version 2 TSMSensorModel methods.  It must be constructed
//  with that TSMSensorModel object
//<
//*****************************************************************************
class csm2to3model : public csm::RasterGM
{
public:
   explicit csm2to3model(TSMSensorModel* impl);
      //> This constructs the csm2to3model with the given TSMSensorModel
      //  object.  This object must not be NULL.  The csm2to3model takes
      //  ownership of the TSMSensorModel object, and will delete it when it is
      //  destructed.
      //<
   virtual ~csm2to3model();
      //> This is the destructor.
      //<

   virtual csm::Version getVersion() const;
   virtual std::string getModelName() const;
   virtual std::string getPedigree() const;

   //---
   // Basic collection information
   //---
   virtual std::string getImageIdentifier() const;
   virtual void setImageIdentifier(const std::string& imageId,
                                   csm::WarningList* warnings = NULL);

   virtual std::string getSensorIdentifier() const;
   virtual std::string getPlatformIdentifier() const;
   virtual std::string getCollectionIdentifier() const;
   virtual csm::SensorTypeAndMode getSensorTypeAndMode() const;

   virtual csm::EcefCoord getReferencePoint() const;
   virtual void setReferencePoint(const csm::EcefCoord& groundPt);

   //---
   // Sensor Model State
   //---
   virtual std::string getModelState() const;

   //---
   // Core Photogrammetry
   //---
   virtual csm::ImageCoord groundToImage(
                const csm::EcefCoord& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                csm::WarningList* warnings = NULL) const;

   virtual csm::ImageCoordCovar groundToImage(
                const csm::EcefCoordCovar& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                csm::WarningList* warnings = NULL) const;
   virtual csm::EcefCoord imageToGround(
                const csm::ImageCoord& imagePt,
                double height,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                csm::WarningList* warnings = NULL) const;
   virtual csm::EcefCoordCovar imageToGround(
                const csm::ImageCoordCovar& imagePt,
                double height, double heightVariance,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                csm::WarningList* warnings = NULL) const;

   virtual std::vector<double> imageToProximateImagingLocus(
                const csm::ImageCoord& imagePt,
                const csm::EcefCoord& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                csm::WarningList* warnings = NULL) const;

   virtual std::vector<double> imageToRemoteImagingLocus(
                const csm::ImageCoord& imagePt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                csm::WarningList* warnings = NULL) const;

   //---
   // Monoscopic Mensuration
   //---
   virtual csm::ImageCoord getImageStart() const;
   virtual csm::ImageVector getImageSize() const;
   virtual std::pair<double,double> getValidHeightRange() const;
   virtual std::pair<csm::ImageCoord,csm::ImageCoord> getValidImageRange() const;
   virtual csm::EcefVector getIlluminationDirection(const csm::EcefCoord& gndPt) const;

   //---
   // Time and Trajectory
   //---
   virtual std::string getTrajectoryIdentifier() const;
   virtual std::string getReferenceDateAndTime() const;
   virtual double getImageTime(const csm::ImageCoord& pt) const;
   virtual csm::EcefCoord getSensorPosition(const csm::ImageCoord& pt) const;
   virtual csm::EcefCoord getSensorPosition(double time) const;
   virtual csm::EcefVector getSensorVelocity(const csm::ImageCoord& pt) const;
   virtual csm::EcefVector getSensorVelocity(double time) const;

   //---
   // Sensor Model Parameters
   //---
   virtual int getNumParameters() const;
   virtual std::string getParameterName(int index) const;
   virtual std::string getParameterUnits(int index) const;
   virtual bool isParameterShareable(int index) const;
   virtual std::vector<csm::ParameterSharingCriteria> getParameterSharingCriteria(int index) const;

   virtual double getOriginalParameterValue(int index) const;
   virtual double getCurrentParameterValue(int index) const;
   virtual void setCurrentParameterValue(int index, double value);
   virtual void setOriginalParameterValue(int index, double value);

   virtual csm::ParamType getOriginalParameterType(int index) const;
   virtual csm::ParamType getCurrentParameterType(int index) const;
   virtual void setOriginalParameterType(int index, csm::ParamType pType);
   virtual void setCurrentParameterType(int index, csm::ParamType pType);

   //---
   // Uncertainty Propagation
   //---
   virtual std::vector<double> computeGroundPartials(const csm::EcefCoord& groundPt);

   virtual SensorPartials computeSensorPartials(
                int index,
                const csm::EcefCoord& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                csm::WarningList* warnings = NULL);

   virtual SensorPartials computeSensorPartials(
                int index,
                const csm::ImageCoord& imagePt,
                const csm::EcefCoord& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                csm::WarningList* warnings = NULL);

   virtual std::vector<SensorPartials> computeAllSensorPartials(
                const csm::EcefCoord& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                csm::WarningList* warnings = NULL);
   virtual std::vector<SensorPartials> computeAllSensorPartials(
                const csm::ImageCoord& imagePt,
                const csm::EcefCoord& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                csm::WarningList* warnings = NULL);

   virtual double getCurrentParameterCovariance(int index1,
                                                int index2) const;
   virtual void setCurrentParameterCovariance(int index1,
                                              int index2,
                                              double covariance);

   virtual double getOriginalParameterCovariance(int index1,
                                                 int index2) const;
   virtual void setOriginalParameterCovariance(int index1,
                                               int index2,
                                               double covariance);

   //---
   // Error Correction
   //---
   virtual int getNumGeometricCorrectionSwitches() const;
   virtual std::string getGeometricCorrectionName(int index) const;
   virtual void setCurrentGeometricCorrectionSwitch(int index,
                                                    bool value,
                                                    csm::ParamType pType);
   virtual bool getCurrentGeometricCorrectionSwitch(int index) const;

   virtual std::vector<double> getCurrentCrossCovarianceMatrix(
                const csm::GeometricModel& comparisonModel,
                const GeometricModelList& otherModels = GeometricModelList()) const;

   virtual std::vector<double> getOriginalCrossCovarianceMatrix(
                const csm::GeometricModel& comparisonModel,
                const GeometricModelList& otherModels = GeometricModelList()) const;

   virtual csm::CovarianceModel* getCovarianceModel() const;

   virtual std::vector<double> getUnmodeledCrossCovariance(
                const csm::ImageCoord& pt1,
                const csm::ImageCoord& pt2) const;

private:
   TSMSensorModel* theImpl;
};


#endif
