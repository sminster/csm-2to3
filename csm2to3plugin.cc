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
//>
//     Date          Author   Comment   
//     -----------   ------   ------- 
//     30-Mar-2012   SCM      Initial Coding
//     26-Sep-12     JPK      Ripple class hierarchy change
//     30-Oct-2012   SCM      Fixed includes.
//<
//*****************************************************************************

#include "csm2to3plugin.h"
#include "csm2to3model.h"
#include "csm2to3-private.h"

#include <csm/RasterGM.h>
#include <csm/BytestreamIsd.h>
#include <csm/NitfIsd.h>

#include <tsm/TSMPlugin.h>
#include <tsm/TSMWarning.h>
#include <tsm/TSMISDByteStream.h>
#include <tsm/TSMISDFilename.h>
#include <tsm/TSMISDNITF20.h>
#include <tsm/TSMISDNITF21.h>

#include <sstream>

csm2to3plugin csm2to3plugin::INSTANCE;

//*****************************************************************************
// csm2to3plugin::csm2to3plugin
//*****************************************************************************
csm2to3plugin::csm2to3plugin()
   :
      theOrderedNames(),
      theNameMap()
{
   loadTsmPlugins();
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
csm::Version csm2to3plugin::getCSMVersion() const
{
   return CURRENT_CSM_VERSION;
}

//*****************************************************************************
// csm2to3plugin::getNumModels
//*****************************************************************************
size_t csm2to3plugin::getNumModels() const
{
   return theOrderedNames.size();
}

//*****************************************************************************
// csm2to3plugin::getModelName
//*****************************************************************************
std::string csm2to3plugin::getModelName(size_t index) const
{
   static const char* const MODULE = "csm2to3plugin::getModelName";

   if (index < 0)
   {
      std::ostringstream msg;
      msg << "Given index out of range: " << index << " < 0";
      throw csm::Error(csm::Error::INDEX_OUT_OF_RANGE, msg.str(), MODULE);
   }

   if (index >= theOrderedNames.size())
   {
      std::ostringstream msg;
      msg << "Given index out of range: "
          << index << " >= " << theOrderedNames.size();
      throw csm::Error(csm::Error::INDEX_OUT_OF_RANGE, msg.str(), MODULE);
   }

   return theOrderedNames[index];
}

//*****************************************************************************
// csm2to3plugin::getModelFamily
//*****************************************************************************
std::string csm2to3plugin::getModelFamily(size_t index) const
{
   // always a sensor model
   return CSM_GEOMETRIC_MODEL_FAMILY CSM_RASTER_FAMILY;
}

//*****************************************************************************
// csm2to3plugin::getModelVersion
//*****************************************************************************
csm::Version csm2to3plugin::getModelVersion(
   const std::string& modelName) const
{
   EXCEPTION_TRY("csm2to3plugin::getModelVersion");

   SensorNameMap::const_iterator it = theNameMap.find(modelName);
   if (it == theNameMap.end())
   {
      throw csm::Error(csm::Error::SENSOR_MODEL_NOT_SUPPORTED,
                       "Cannot find sensor model named " + modelName,
                       MODULE);
   }

   int version = 0;
   TSMWarning* w =
      it->second->getSensorModelVersion(modelName, version);
   if (w) delete w;
   else return csm::Version(version, 0);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3plugin::canModelBeConstructedFromState
//*****************************************************************************
bool csm2to3plugin::canModelBeConstructedFromState(
   const std::string& modelName,
   const std::string& modelState,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3plugin::canModelBeConstructedFromState");

   SensorNameMap::const_iterator it = theNameMap.find(modelName);
   if (it == theNameMap.end())
   {
      throw csm::Error(csm::Error::SENSOR_MODEL_NOT_SUPPORTED,
                       "Cannot find sensor model named " + modelName,
                       MODULE);
   }

   bool canConstruct = false;
   TSMWarning* w =
      it->second->canSensorModelBeConstructedFromState(modelName,
                                                       modelState,
                                                       canConstruct);
   if (w)
   {
      if (warnings) warnings->push_back(CONVERT_WARNING(w));
      delete w;
   }

   return canConstruct;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3plugin::canModelBeConstructedFromISD
//*****************************************************************************
bool csm2to3plugin::canModelBeConstructedFromISD(
   const csm::Isd& imageSupportData,
   const std::string& modelName,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3plugin::canModelBeConstructedFromISD");

   SensorNameMap::const_iterator it = theNameMap.find(modelName);
   if (it == theNameMap.end())
   {
      throw csm::Error(csm::Error::SENSOR_MODEL_NOT_SUPPORTED,
                       "Cannot find sensor model named " + modelName,
                       MODULE);
   }

   std::auto_ptr<tsm_ISD> tsmIsd(convertIsd(imageSupportData));

   bool canConstruct = false;
   TSMWarning* w =
      it->second->canSensorModelBeConstructedFromISD(*tsmIsd,
                                                     modelName,
                                                     canConstruct);
   if (w)
   {
      if (warnings) warnings->push_back(CONVERT_WARNING(w));
      delete w;
   }

   return canConstruct;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3plugin::constructModelFromState
//*****************************************************************************
csm::Model* csm2to3plugin::constructModelFromState(
   const std::string& modelState,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3plugin::constructModelFromState");

   TSMPlugin::TSMPluginList* plugins = NULL;
   TSMWarning* w = TSMPlugin::getList(plugins);
   if (w) delete w;

   if (plugins)
   {
      for(TSMPlugin::TSMPluginList::const_iterator it = plugins->begin();
          it != plugins->end(); ++it)
      {
         try
         {
            TSMSensorModel* tsmModel = NULL;
            TSMWarning* w =
               (*it)->constructSensorModelFromState(modelState,
                                                    tsmModel);
            if (w)
            {
               if (warnings) warnings->push_back(CONVERT_WARNING(w));
               delete w;
            }

            if (tsmModel != NULL)
            {
               return new csm2to3model(tsmModel);
            }
         }
         catch(const TSMError& tsm)
         {
            // ignore any errors, probably from the wrong plugin
         }
      }
   }

   throw csm::Error(csm::Error::SENSOR_MODEL_NOT_CONSTRUCTIBLE,
                    "Could not construct sensor model from state",
                    MODULE);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3plugin::constructModelFromISD
//*****************************************************************************
csm::Model* csm2to3plugin::constructModelFromISD(
   const csm::Isd& imageSupportData,
   const std::string& modelName,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3plugin::constructModelFromISD");

   SensorNameMap::const_iterator it = theNameMap.find(modelName);
   if (it == theNameMap.end())
   {
      throw csm::Error(csm::Error::SENSOR_MODEL_NOT_SUPPORTED,
                       "Cannot find sensor model named " + modelName,
                       MODULE);
   }

   std::auto_ptr<tsm_ISD> tsmIsd(convertIsd(imageSupportData));

   TSMSensorModel* tsmModel = NULL;
   TSMWarning* w =
      it->second->constructSensorModelFromISD(*tsmIsd,
                                              modelName,
                                              tsmModel);
   if (w)
   {
      if (warnings) warnings->push_back(CONVERT_WARNING(w));
      delete w;
   }

   if (tsmModel == NULL)
   {
      throw csm::Error(csm::Error::SENSOR_MODEL_NOT_CONSTRUCTIBLE,
                       "Could not construct sensor model from ISD",
                       MODULE);
   }

   return new csm2to3model(tsmModel);

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3plugin::getModelNameFromModelState
//*****************************************************************************
std::string csm2to3plugin::getModelNameFromModelState(
   const std::string& modelState,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3plugin::getNModels");

   TSMPlugin::TSMPluginList* plugins = NULL;
   TSMWarning* w = TSMPlugin::getList(plugins);
   if (w) delete w;

   if (plugins)
   {
      for(TSMPlugin::TSMPluginList::const_iterator it = plugins->begin();
          it != plugins->end(); ++it)
      {
         try
         {
            std::string name;
            w = (*it)->getSensorModelNameFromSensorModelState(modelState,
                                                              name);
            if (w)
            {
               if (warnings) warnings->push_back(CONVERT_WARNING(w));
               delete w;
            }

            if (!name.empty()) return name;
         }
         catch(const TSMError& tsm)
         {
            // ignore any errors, probably from the wrong plugin
         }
      }
   }

   return "";

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3plugin::canISDBeConvertedToModelState
//*****************************************************************************
bool csm2to3plugin::canISDBeConvertedToModelState(
   const csm::Isd& imageSupportData,
   const std::string& modelName,
   csm::WarningList* warnings) const
{
   // assume if we can make a sensor model, we can convert it to its state
   return canModelBeConstructedFromISD(imageSupportData,
                                             modelName,
                                             warnings);
}

//*****************************************************************************
// csm2to3plugin::convertISDToModelState
//*****************************************************************************
std::string csm2to3plugin::convertISDToModelState(
   const csm::Isd& imageSupportData,
   const std::string& modelName,
   csm::WarningList* warnings) const
{
   EXCEPTION_TRY("csm2to3plugin::convertISDToModelState");

   csm::Model* model = constructModelFromISD(imageSupportData,
                                                         modelName,
                                                         warnings);
   if (!model)
   {
      throw csm::Error(csm::Error::SENSOR_MODEL_NOT_CONSTRUCTIBLE,
                       "Could not construct sensor model from ISD",
                       MODULE);
   }

   return model->getModelState();

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// convertTres
//> This method is a helper to convert a vector of csm::Tre objects into an
//  array of TSM tre objects.
//<
//*****************************************************************************
void convertTres(int& numTres, tre*& TREs,
                 const std::vector<csm::Tre>& srcTres)
{
   numTres = srcTres.size();
   TREs = new tre[srcTres.size()];
   for(size_t i = 0; i < srcTres.size(); ++i)
   {
      strncpy(TREs[i].name, srcTres[i].name().c_str(), 6);
      TREs[i].name[6] = '\0';
      TREs[i].length = srcTres[i].length();
      TREs[i].record = strdup(srcTres[i].data().c_str());
   }
}

//*****************************************************************************
// convertNitfIsd
//> This helper method converts the given CSM NITF ISD object into a TSM NITF
//  ISD, based on the template type, TSM_NITF_ISD.  That type must be either
//  NITF_2_0_ISD or NITF_2_1_ISD.
//<
//*****************************************************************************
template<class TSM_NITF_ISD>
TSM_NITF_ISD* convertNitfIsd(const csm::NitfIsd& nIsd)
{
   TSM_NITF_ISD* tsm = new TSM_NITF_ISD();
   tsm->fileHeader = nIsd.fileHeader();

   convertTres(tsm->numTREs, tsm->fileTREs, nIsd.fileTREs());

   tsm->numDESs = nIsd.fileDESs().size();
   tsm->fileDESs = new des[tsm->numDESs];
   for(size_t i = 0; i < tsm->numDESs; ++i)
   {
      tsm->fileDESs[i].desShLength = nIsd.fileDESs()[i].subHeader().length();
      tsm->fileDESs[i].desSh = strdup(nIsd.fileDESs()[i].subHeader().c_str());
      tsm->fileDESs[i].desDataLength = nIsd.fileDESs()[i].data().length();
      tsm->fileDESs[i].desData = strdup(nIsd.fileDESs()[i].data().c_str());
   }

   tsm->numImages = nIsd.images().size();
   tsm->images = new image[tsm->numImages];
   for(size_t i = 0; i < tsm->numImages; ++i)
   {
      tsm->images[i].imageSubHeader = nIsd.images()[i].subHeader();
      convertTres(tsm->images[i].numTREs,
                  tsm->images[i].imageTREs,
                  nIsd.images()[i].imageTREs());
   }

   return tsm;
}

//*****************************************************************************
// csm2to3plugin::convertIsd
//*****************************************************************************
tsm_ISD* csm2to3plugin::convertIsd(const csm::Isd& isd)
{
   if (isd.format() == "BYTESTREAM")
   {
      const csm::BytestreamIsd& bIsd = dynamic_cast<const csm::BytestreamIsd&>(isd);
      bytestreamISD* tsm = new bytestreamISD();
      tsm->_isd = bIsd.data();
      return tsm;
   }

   if (isd.format() == "FILENAME")
   {
      filenameISD* tsm = new filenameISD();
      tsm->_filename = isd.filename();
      return tsm;
   }

   if (isd.format() == "NITF2.0" || isd.format() == "NITF2.1")
   {
      const csm::NitfIsd& nIsd = dynamic_cast<const csm::NitfIsd&>(isd);

      if (isd.format() == "NITF2.0")
      {
         return convertNitfIsd<NITF_2_0_ISD>(nIsd);
      }
      if (isd.format() == "NITF2.1")
      {
         return convertNitfIsd<NITF_2_1_ISD>(nIsd);
      }
   }

   return NULL;
}

//*****************************************************************************
// csm2to3plugin::loadTsmPlugins
//*****************************************************************************
void csm2to3plugin::loadTsmPlugins()
{
   // TODO

   loadNameMap();
}

//*****************************************************************************
// csm2to3plugin::loadNameMap
//*****************************************************************************
void csm2to3plugin::loadNameMap()
{
   EXCEPTION_TRY("csm2to3plugin::loadNameMap");

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

         for(int i = 0; i < count; ++count)
         {
            std::string name;
            w = (*it)->getSensorModelName(i, name);
            if (w) delete w;

            theOrderedNames.push_back(name);
            theNameMap[name] = *it;
         }
      }
   }

   EXCEPTION_RETHROW_CONVERT;
}
