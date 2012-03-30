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
//
//> 30MAR12 956F PTR#?????-IPL  S. Minster
//               Initial Coding.
//<
//*****************************************************************************

#ifndef csm2to3model_HEADER
#define csm2to3model_HEADER

#include <csm/CSMSensorModel.h>

class TSMSensorModel;

//*****************************************************************************
// CLASS:  csm2to3model
//> This class TODO
//  
//<
//*****************************************************************************
class csm2to3model : public csm::SensorModel
{
public:
   csm2to3model(TSMSensorModel* impl);
      //> This is the default constructor.
      //<
   virtual ~csm2to3model();
      //> This is the destructor.
      //<

   virtual int getVersion() const;
   virtual std::string getModelType() const;
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
   virtual std::string getSensorModelState() const;

   //---
   // Core Photogrammetry
   //---
   virtual csm::ImageCoord groundToImage(
                const csm::EcefCoord& groundPt,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                csm::WarningList* warnings = NULL) const;

   virtual csm::ImageCoord groundToImage(
                const csm::EcefCoord& groundPt,
                const std::vector<double> groundCovariance,
                std::vector<double>& imageCovariance,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                csm::WarningList* warnings = NULL) const;
   virtual csm::EcefCoord imageToGround(
                const csm::ImageCoord& imagePt,
                double height,
                double desired_precision = 0.001,
                double* achieved_precision = NULL,
                csm::WarningList* warnings = NULL) const;
   virtual csm::EcefCoord imageToGround(
                const csm::ImageCoord& imagePt,
                double height,
                const std::vector<double> imageCovariance,
                std::vector<double>& groundCovariance,
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
                const csm::EcefCoord& groundPt,
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
   virtual bool isParameterShareable(int index) const;
   virtual std::vector<csm::ParameterSharingCriteria>& getParameterSharingCriteria(int index) const;

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

   typedef std::pair<double, double> SensorPartials;
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

   virtual std::vector<std::vector<double> > getCurrentCrossCovarianceMatrix(
                const csm::ImageCoord imagePt,
                const csm::SensorModel* comparisonModel,
                const csm::ImageCoord&  comparisonModelImagePt) const;

   virtual std::vector<std::vector<double> > getOriginalCrossCovarianceMatrix(
                const csm::ImageCoord imagePt,
                const csm::SensorModel* comparisonModel,
                const csm::ImageCoord&  comparisonModelImagePt) const;

   virtual csm::CovarianceModel* getCovarianceModel() const;

   virtual std::vector<double> getUnmodeledError(const csm::ImageCoord& pt) const;
   virtual std::vector<double> getUnmodeledCrossCovariance(
                const csm::ImageCoord& pt1,
                const csm::ImageCoord& pt2) const;

private:
   TSMSensorModel* theImpl;
};


#endif
