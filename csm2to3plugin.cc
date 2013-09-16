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
//     31-Oct-2012   SCM      Fixed warnings.
//     12-Sep-2013   JPK      Updated class to construct from a
//                            TSMPlugin* . Made constructor private
//                            Made loadTsmPlugins() static.  Changed
//                            static data meber INSTANCE (csm2to3plugin*) to
//                            INSTANCES ( vector<csm2to3plugin*>).  Now an
//                            instance of this plugin is generated for each
//                            loaded TSMPlugin.
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
#include <vector>

std::vector<csm2to3plugin*> csm2to3plugin::INSTANCES;

//*****************************************************************************
// csm2to3plugin::csm2to3plugin
//*****************************************************************************
csm2to3plugin::csm2to3plugin(const TSMPlugin* plugin)
   :
      csm::Plugin  (),
      theTsmPlugin (plugin)
{}

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
   EXCEPTION_TRY("csm2to3plugin::getPluginName");
   
   std::string pluginName = "unknown";

   DROP_WARNING(theTsmPlugin->getPluginName(pluginName));
    
   return pluginName;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3plugin::getManufacturer
//*****************************************************************************
std::string csm2to3plugin::getManufacturer() const
{
   EXCEPTION_TRY("csm2to3plugin::getManufacturer");
   
   std::string manufacturer = "unknown";
   
   DROP_WARNING(theTsmPlugin->getManufacturer(manufacturer));
    
   return manufacturer;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3plugin::getReleaseDate
//*****************************************************************************
std::string csm2to3plugin::getReleaseDate() const
{
   EXCEPTION_TRY("csm2to3plugin::getReleaseDate");
   
   std::string releaseDate = "2012-04-01"; // April Fools!

   DROP_WARNING(theTsmPlugin->getReleaseDate(releaseDate));
   
   return releaseDate;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3plugin::getCsmVersion
//*****************************************************************************
csm::Version csm2to3plugin::getCsmVersion() const
{
   return CURRENT_CSM_VERSION;
}

//*****************************************************************************
// csm2to3plugin::getNumModels
//*****************************************************************************
size_t csm2to3plugin::getNumModels() const
{
   EXCEPTION_TRY("csm2to3plugin::getNumModels");
   
   int numModels = 0;
   
   DROP_WARNING(theTsmPlugin->getNSensorModels(numModels));
   
   return numModels;

   EXCEPTION_RETHROW_CONVERT;
}

//*****************************************************************************
// csm2to3plugin::getModelName
//*****************************************************************************
std::string csm2to3plugin::getModelName(size_t index) const
{
   EXCEPTION_TRY("csm2to3plugin::getModelName");

   if (index < 0)
   {
      std::ostringstream msg;
      msg << "Given index out of range: " << index << " < 0";
      throw csm::Error(csm::Error::INDEX_OUT_OF_RANGE, msg.str(), MODULE);
   }
   
   const int NUM_MODELS = getNumModels();
   
   if ((int)index >= NUM_MODELS)
   {
      std::ostringstream msg;
      msg << "Given index out of range: "
          << index << " >= " << NUM_MODELS;
      throw csm::Error(csm::Error::INDEX_OUT_OF_RANGE, msg.str(), MODULE);
   }
   
   std::string modelName = "unknown";
               
   DROP_WARNING(theTsmPlugin->getSensorModelName((int)index,
                                                 modelName));
   
   return modelName;
   
   EXCEPTION_RETHROW_CONVERT;
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

   csm::Version version(1,0,0);

   int ver = 100;
   DROP_WARNING(theTsmPlugin->getSensorModelVersion(modelName, ver));

   if (ver > 0)
   {
      //***
      // For Version 2.A and earlier CSMs, the convention for versioning
      // was to store the integer version as a 3 digit number, where the
      // digits represent the major,minor, and revision components of the
      // version respectively.  Some CSMs may not use this convention and
      // may use less than 3 digits.  In this case we will just use the
      // entire value as the major component of the version.
      //***
      if (ver >= 100)
      {
         int revision = ver % 10;
         int minor    = (ver / 10) % 10;
         int major    = ver / 100;
         
         version = csm::Version(major,minor,revision);
      }
      else
      {
         version = csm::Version(ver,0,0);
      }
   }
   
   return version;
  
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

   bool canConstruct = false;

   SAVE_WARNING(theTsmPlugin->
                canSensorModelBeConstructedFromState(modelName,
                                                     modelState,
                                                     canConstruct),
                warnings);
   
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

   std::auto_ptr<tsm_ISD> tsmIsd(convertIsd(imageSupportData));

   bool canConstruct = false;
   SAVE_WARNING(theTsmPlugin->
                canSensorModelBeConstructedFromISD(*tsmIsd,
                                                   modelName,
                                                   canConstruct),
                warnings);
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

   try
   {
      TSMSensorModel* tsmModel = NULL;
      SAVE_WARNING(theTsmPlugin->
                   constructSensorModelFromState(modelState,
                                                 tsmModel),
                   warnings);
      
      if (tsmModel != NULL)
      {
         std::string pluginName;
         
         SAVE_WARNING(theTsmPlugin->getPluginName(pluginName),warnings);

         return new csm2to3model(tsmModel,pluginName);
      }
   }
   catch(const TSMError& tsm)
   {
      // ignore any errors, probably from the wrong plugin
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

   std::auto_ptr<tsm_ISD> tsmIsd(convertIsd(imageSupportData));

   TSMSensorModel* tsmModel = NULL;
   SAVE_WARNING(theTsmPlugin->constructSensorModelFromISD(*tsmIsd,
                                                          modelName,
                                                          tsmModel),
                warnings);
   
   if (tsmModel == NULL)
   {
      throw csm::Error(csm::Error::SENSOR_MODEL_NOT_CONSTRUCTIBLE,
                       "Could not construct sensor model from ISD",
                       MODULE);
   }

   std::string pluginName;
   SAVE_WARNING(theTsmPlugin->getPluginName(pluginName),warnings);
   
   return new csm2to3model(tsmModel,pluginName);

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

   try
   {
      std::string name;
      SAVE_WARNING(theTsmPlugin->
                   getSensorModelNameFromSensorModelState(modelState,
                                                          name),
                   warnings);
      
      if (!name.empty()) return name;
   }
   catch(const TSMError& tsm)
   {
      // ignore any errors, probably from the wrong plugin
   }

    throw csm::Error(csm::Error::INVALID_SENSOR_MODEL_STATE,
                    "Provided state is not valid for this plugin.",
                    MODULE);


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
   EXCEPTION_TRY("csm2to3plugin::canISDBeConvertedToModelState");
   
   std::auto_ptr<tsm_ISD> tsmIsd(convertIsd(imageSupportData));
   
   bool canConvert = false;
   
   
   SAVE_WARNING(theTsmPlugin->
                canISDBeConvertedToSensorModelState(*tsmIsd,
                                                    modelName,
                                                    canConvert),
                warnings);
   
   return canConvert;

   EXCEPTION_RETHROW_CONVERT;
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
   
   std::auto_ptr<tsm_ISD> tsmIsd(convertIsd(imageSupportData));
   
   std::string modelState;
   
   SAVE_WARNING(theTsmPlugin->
                convertISDToSensorModelState(*tsmIsd,
                                             modelName,
                                             modelState),
                warnings);
                                                       
   return modelState;

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

      int length = (int)srcTres[i].length();
      TREs[i].length = length;
       
      TREs[i].record = new char[length+1];
      strncpy(TREs[i].record,srcTres[i].data().c_str(),length);
       // in case, NULL termination is needed
      TREs[i].record[length] = '\0';   
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

   convertTres(tsm->numTREs, tsm->fileTREs, nIsd.fileTres());
   
   const std::vector<csm::Des>& fileDes = nIsd.fileDess();
   
   tsm->numDESs = fileDes.size();
   tsm->fileDESs = new des[tsm->numDESs];
   for(size_t i = 0; i < (size_t)tsm->numDESs; ++i)
   {
      const csm::Des& currentDes = fileDes[i];
      const std::string& currentSubHdr = currentDes.subHeader();
      const std::string& currentData   = currentDes.data();

      int subhSize = currentSubHdr.length();
      int dataSize = currentData.length();
      tsm->fileDESs[i].setDES(subhSize,
                              const_cast<char*>(currentSubHdr.c_str()),
                              dataSize,
                              const_cast<char*>(currentData.c_str()));
   }

   tsm->numImages = nIsd.images().size();
   tsm->images = new image[tsm->numImages];
   for(size_t i = 0; i < (size_t)tsm->numImages; ++i)
   {
      tsm->images[i].imageSubHeader = nIsd.images()[i].subHeader();
      convertTres(tsm->images[i].numTREs,
                  tsm->images[i].imageTREs,
                  nIsd.images()[i].imageTres());
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
// csm2to3plugin::establishCsmPlugins
//*****************************************************************************
void csm2to3plugin::establishCsmPlugins()
{
   EXCEPTION_TRY("csm2to3plugin::establishCsmPlugins");
   
   TSMPlugin::TSMPluginList* plugins = NULL;
   
   DROP_WARNING(TSMPlugin::getList(plugins));
      
   if (plugins)
   {
      TSMPlugin::TSMPluginList::const_iterator TSM_END = plugins->end();
      
      for(TSMPlugin::TSMPluginList::const_iterator it = plugins->begin();
          it != TSM_END; ++it)
      {
         if (*it)
         {
            csm2to3plugin* pl2To3 = new csm2to3plugin(*it);
            
            if (pl2To3)
            {
               csm2to3plugin::INSTANCES.push_back(pl2To3);
            }
         }
      }
   }
   
   EXCEPTION_RETHROW_CONVERT;
}
