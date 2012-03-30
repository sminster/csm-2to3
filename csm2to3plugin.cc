//#############################################################################
//## Restricted Rights
//## WARNING: This is a restricted distribution HARRIS REPOSITORY file.
//##          Do Not Use Under A Government Charge Number Without Permission.
//#############################################################################

//*****************************************************************************
// FILE:              csm2to3plugin.cc
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

#include "csm2to3plugin.h"

#include "csm/CSMSensorModel.h"

#include "tsm/TSMPlugin.h"
#include "tsm/TSMWarning.h"

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

csm2to3plugin csm2to3plugin::INSTANCE;

//*****************************************************************************
// csm2to3plugin::csm2to3plugin
//*****************************************************************************
csm2to3plugin::csm2to3plugin()
{
   // TODO -- load CSM2A sensor models
}

//*****************************************************************************
// csm2to3plugin::~csm2to3plugin
//*****************************************************************************
csm2to3plugin::~csm2to3plugin()
{
}

//*****************************************************************************
// csm2to3plugin::getPluginName
//*****************************************************************************
std::string csm2to3plugin::getPluginName() const
{
   return "CSM 2-to-3";
}

//*****************************************************************************
// csm2to3plugin::getManufacturer
//*****************************************************************************
std::string csm2to3plugin::getManufacturer() const
{
   return "Harris";
}

//*****************************************************************************
// csm2to3plugin::getReleaseDate
//*****************************************************************************
std::string csm2to3plugin::getReleaseDate() const
{
   return "2012-04-01";                 // April Fools!
}

//*****************************************************************************
// csm2to3plugin::getManufacturer
//*****************************************************************************
int csm2to3plugin::getCSMVersion() const
{
   return 3;                        // TODO
}

//*****************************************************************************
// csm2to3plugin::getNSensorModels
//*****************************************************************************
int csm2to3plugin::getNSensorModels() const
{
   EXCEPTION_TRY("csm2to3plugin::getNSensorModels");

   TSMPlugin::TSMPluginList* plugins = NULL;
   TSMWarning* w = TSMPlugin::getList(plugins);
   if (w) delete w;

   int total = 0;
   if (plugins)
   {
      for(TSMPlugin::TSMPluginList::const_iterator it = plugins->begin();
          it != plugins->end(); ++it)
      {
         int count = 0;
         w = (*it)->getNSensorModels(count);
         if (w)
         {
            // TODO -- ignore?
            delete w;
         }
         total += count;
      }
   }

   return total;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3plugin::getSensorModelName
//*****************************************************************************
std::string csm2to3plugin::getSensorModelName(int index) const
{
   EXCEPTION_TRY("csm2to3plugin::getNSensorModels");

   TSMPlugin::TSMPluginList* plugins = NULL;
   TSMWarning* w = TSMPlugin::getList(plugins);
   if (w) delete w;

   if (plugins)
   {
      for(TSMPlugin::TSMPluginList::const_iterator it = plugins->begin();
          it != plugins->end(); ++it)
      {
         int count = 0;
         w = (*it)->getNSensorModels(count);
         if (w) delete w;

         if (index < count)
         {
            std::string name;
            w = (*it)->getSensorModelName(index, name);
            if (w) delete w;
            return name;
         }

         index -= count;
      }
   }

   // name not found
   return "";

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3plugin::getSensorModelVersion
//*****************************************************************************
int csm2to3plugin::getSensorModelVersion(const std::string& sensor_model_name) const
{
   EXCEPTION_TRY("csm2to3plugin::getSensorModelVersion");

   TSMPlugin::TSMPluginList* plugins = NULL;
   TSMWarning* w = TSMPlugin::getList(plugins);
   if (w) delete w;

   if (plugins)
   {
      for(TSMPlugin::TSMPluginList::const_iterator it = plugins->begin();
          it != plugins->end(); ++it)
      {
         int version = 0;
         try
         {
            int version = 0;
            w = (*it)->getSensorModelVersion(sensor_model_name, version);
            if (w) delete w;
            else return version;
         }
         catch(const TSMError& tsm)
         {
            // ignore -- probably wrong plugin
         }
      }
   }

   throw csm::Error(csm::Error::SENSOR_MODEL_NOT_SUPPORTED,
                    "Cannot find sensor model named " + sensor_model_name,
                    MODULE);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3plugin::canSensorModelBeConstructedFromState
//*****************************************************************************
bool csm2to3plugin::canSensorModelBeConstructedFromState(
   const std::string& sensor_model_name,
   const std::string& sensor_model_state,
   csm::WarningList* warnings) const
{
   // TODO
   return false;
}

//*****************************************************************************
// csm2to3plugin::canSensorModelBeConstructedFromISD
//*****************************************************************************
bool csm2to3plugin::canSensorModelBeConstructedFromISD(
   const csm::Isd& image_support_data,
   const std::string& sensor_model_name,
   csm::WarningList* warnings) const
{
   // TODO
   return false;
}

//*****************************************************************************
// csm2to3plugin::constructSensorModelFromState
//*****************************************************************************
csm::SensorModel* csm2to3plugin::constructSensorModelFromState(
   const std::string& sensor_model_state,
   csm::WarningList* warnings) const
{
   // TODO
   return NULL;
}

//*****************************************************************************
// csm2to3plugin::constructSensorModelFromISD
//*****************************************************************************
csm::SensorModel* csm2to3plugin::constructSensorModelFromISD(
   const csm::Isd& image_support_data,
   const std::string& sensor_model_name,
   csm::WarningList* warnings) const
{
   // TODO
   return NULL;
}

//*****************************************************************************
// csm2to3plugin::getSensorModelNameFromSensorModelState
//*****************************************************************************
std::string csm2to3plugin::getSensorModelNameFromSensorModelState(
   const std::string& sensor_model_state,
   csm::WarningList* warnings) const
{
   // TODO
   return "";
}

//*****************************************************************************
// csm2to3plugin::canISDBeConvertedToSensorModelState
//*****************************************************************************
bool csm2to3plugin::canISDBeConvertedToSensorModelState(
   const csm::Isd& image_support_data,
   const std::string& sensor_model_name,
   csm::WarningList* warnings) const
{
   // assume if we can make a sensor model, we can convert it to its state
   return canSensorModelBeConstructedFromISD(image_support_data,
                                             sensor_model_name,
                                             warnings);
}

//*****************************************************************************
// csm2to3plugin::convertISDToSensorModelState
//*****************************************************************************
std::string csm2to3plugin::convertISDToSensorModelState(
   const csm::Isd& image_support_data,
   const std::string& sensor_model_name,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3plugin::convertISDToSensorModelState");

   csm::SensorModel* model = constructSensorModelFromISD(image_support_data,
                                                         sensor_model_name,
                                                         warnings);
   if (!model)
   {
      throw csm::Error(csm::Error::SENSOR_MODEL_NOT_CONSTRUCTIBLE,
                       "Could not construct sensor model from ISD",
                       MODULE);
   }

   return model->getSensorModelState();

   EXCEPTION_RETHROW_CONVERT;
}



