//#############################################################################
//## Restricted Rights
//## WARNING: This is a restricted distribution HARRIS REPOSITORY file.
//##          Do Not Use Under A Government Charge Number Without Permission.
//#############################################################################

//*****************************************************************************
// FILE:              csm2to3plugin.h
//
//    Copyright (C)  2012 Harris Corporation. All rights reserved.
//
// CLASSIFICATION:    Unclassified
//
// DESCRIPTION:       csm2to3plugin
//
// LIMITATIONS:       None
//
// SOFTWARE HISTORY:
//
//> 30MAR12 956F PTR#?????-IPL  S. Minster
//               Initial Coding.
//<
//*****************************************************************************

#ifndef csm2to3plugin_HEADER
#define csm2to3plugin_HEADER

#include "csm/CSMPlugin.h"

//*****************************************************************************
// CLASS:  csm2to3plugin
//> This class TODO
//  
//<
//*****************************************************************************
class csm2to3plugin : public csm::Plugin
{
public:
   csm2to3plugin();
      //> This is the default constructor.
      //<
   virtual ~csm2to3plugin();
      //> This is the destructor.
      //<

   virtual std::string getPluginName() const;
   virtual std::string getManufacturer() const;
   virtual std::string getReleaseDate() const;
   virtual int getCSMVersion() const;

   virtual int getNSensorModels() const;
   virtual std::string getSensorModelName(int index) const;

   virtual int getSensorModelVersion(const std::string& sensor_model_name) const;

   virtual bool canSensorModelBeConstructedFromState(
      const std::string& sensor_model_name,
      const std::string& sensor_model_state,
      csm::WarningList* warnings = NULL) const;
   virtual bool canSensorModelBeConstructedFromISD(
      const csm::Isd& image_support_data,
      const std::string& sensor_model_name,
      csm::WarningList* warnings = NULL) const;

   virtual csm::SensorModel* constructSensorModelFromState(
      const std::string& sensor_model_state,
      csm::WarningList* warnings = NULL) const;
   virtual csm::SensorModel* constructSensorModelFromISD(
      const csm::Isd& image_support_data,
      const std::string& sensor_model_name,
      csm::WarningList* warnings = NULL) const;

   virtual std::string getSensorModelNameFromSensorModelState(
      const std::string& sensor_model_state,
      csm::WarningList* warnings = NULL) const;

   virtual bool canISDBeConvertedToSensorModelState(
      const csm::Isd& image_support_data,
      const std::string& sensor_model_name,
      csm::WarningList* warnings = NULL) const;
   virtual std::string convertISDToSensorModelState(
      const csm::Isd& image_support_data,
      const std::string& sensor_model_name,
      csm::WarningList* warnings = NULL) const;

private:
   static csm2to3plugin INSTANCE;
};


#endif
