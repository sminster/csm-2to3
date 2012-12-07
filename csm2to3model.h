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
//     30-Oct-2012   SCM      Fixed includes.
//     31-Oct-2012   SCM      Rippled more interface changes.
//     27-Nov-2012   JPK      Changed return type for getCovarianceModel(),
//                            cleaned up variable names.
//     29-Nov-2012   JPK      Added support for ParamSet enumeration and
//                            Parameter and SharingCriteria structures.
//     06-Dec-2102   JPK      Rippled various name / scoping changes.
//<
//*****************************************************************************

#ifndef csm2to3model_HEADER
#define csm2to3model_HEADER

#include <csm/RasterGM.h>
#include <csm/CovarianceModel.h>
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
   explicit csm2to3model(TSMSensorModel* impl,const std::string& pluginName);
      //> This constructs the csm2to3model with the given TSMSensorModel
      //  object.  This object must not be NULL.  The csm2to3model takes
      //  ownership of the TSMSensorModel object, and will delete it when it is
      //  destructed.  The passed in plugin name enables the capability to
      //  re-load a state.  Without this data member being set to the 
      //  actual name of the plugin containing this model, an exception will
      //  be thrown when atempting to reload the state.
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
   virtual std::string getSensorType() const;
   virtual std::string getSensorMode() const;

   virtual csm::EcefCoord getReferencePoint() const;
   virtual void setReferencePoint(const csm::EcefCoord& groundPt);

   //---
   // Sensor Model State
   //---
   virtual std::string getModelState() const;
   virtual void replaceModelState(const std::string& argState);
      //> This method loads the argument state string and attempts to
      //  use it to initialize the state of the current model.
      //  If the state string contains a valid state for current
      //  model, the internal state of the model is updated.
      //  If the argument state string is empty, 
      //<
 
   //---
   // Core Photogrammetry
   //---
   virtual csm::ImageCoord groundToImage(
                const csm::EcefCoord& groundPt,
                double desiredPrecision = 0.001,
                double* achievedPrecision = NULL,
                csm::WarningList* warnings = NULL) const;

   virtual csm::ImageCoordCovar groundToImage(
                const csm::EcefCoordCovar& groundPt,
                double desiredPrecision = 0.001,
                double* achievedPrecision = NULL,
                csm::WarningList* warnings = NULL) const;
   virtual csm::EcefCoord imageToGround(
                const csm::ImageCoord& imagePt,
                double height,
                double desiredPrecision = 0.001,
                double* achievedPrecision = NULL,
                csm::WarningList* warnings = NULL) const;
   virtual csm::EcefCoordCovar imageToGround(
                const csm::ImageCoordCovar& imagePt,
                double height, double heightVariance,
                double desiredPrecision = 0.001,
                double* achievedPrecision = NULL,
                csm::WarningList* warnings = NULL) const;

   virtual csm::EcefLocus imageToProximateImagingLocus(
                const csm::ImageCoord& imagePt,
                const csm::EcefCoord& groundPt,
                double desiredPrecision = 0.001,
                double* achievedPrecision = NULL,
                csm::WarningList* warnings = NULL) const;

   virtual csm::EcefLocus imageToRemoteImagingLocus(
                const csm::ImageCoord& imagePt,
                double desiredPrecision = 0.001,
                double* achievedPrecision = NULL,
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
   virtual bool hasShareableParameters() const;
   virtual bool isParameterShareable(int index) const;
   virtual csm::SharingCriteria getParameterSharingCriteria(int index) const;

  
   virtual double getParameterValue(int index) const;
   virtual void setParameterValue(int index, double value);
  
   virtual csm::param::Type getParameterType(int index) const;
   virtual void setParameterType(int index, csm::param::Type pType);
   
   //---
   // Uncertainty Propagation
   //---
   virtual std::vector<double> computeGroundPartials(const csm::EcefCoord& groundPt) const;

   virtual SensorPartials computeSensorPartials(
                int index,
                const csm::EcefCoord& groundPt,
                double desiredPrecision    = 0.001,
                double* achievedPrecision  = NULL,
                csm::WarningList* warnings = NULL) const;

   virtual SensorPartials computeSensorPartials(
                int index,
                const csm::ImageCoord& imagePt,
                const csm::EcefCoord& groundPt,
                double desiredPrecision    = 0.001,
                double* achievedPrecision  = NULL,
                csm::WarningList* warnings = NULL) const;

   virtual double getParameterCovariance(int index1,
                                         int index2) const;
   virtual void setParameterCovariance(int index1,
                                       int index2,
                                       double covariance);
   //---
   // Error Correction
   //---
   virtual int getNumGeometricCorrectionSwitches() const;
   virtual std::string getGeometricCorrectionName(int index) const;
   virtual void setGeometricCorrectionSwitch(int index,
                                             bool value,
                                             csm::param::Type pType);
   virtual bool getGeometricCorrectionSwitch(int index) const;

   virtual std::vector<double> getCrossCovarianceMatrix(
                const csm::GeometricModel& comparisonModel,
                csm::param::Set pSet = csm::param::VALID,
                const GeometricModelList& otherModels = GeometricModelList()) const;

   virtual const csm::CovarianceModel& getCovarianceModel() const;

   virtual std::vector<double> getUnmodeledCrossCovariance(
                const csm::ImageCoord& pt1,
                const csm::ImageCoord& pt2) const;

private:
   TSMSensorModel*       theImpl;
   std::string           thePluginName;
      //> This data member is used when attempting to reload the state
      //  of a model.  Only look for the plugin whose name matches this name.
      //<
   csm::CovarianceModel* theCovarianceModel;
};

#endif
