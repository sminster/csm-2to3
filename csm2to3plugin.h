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

#include <string>
#include <vector>
#include <map>

class TSMPlugin;
class tsm_ISD;

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
   virtual csm::Version getCSMVersion() const;

   virtual size_t getNumModels() const;
   virtual std::string getModelName(size_t index) const;
   virtual std::string getModelFamily(size_t modelIndex) const;

   virtual int getModelVersion(const std::string& modelName) const;

   virtual bool canModelBeConstructedFromState(
      const std::string& modelName,
      const std::string& modelState,
      csm::WarningList* warnings = NULL) const;
   virtual bool canModelBeConstructedFromISD(
      const csm::Isd& imageSupportData,
      const std::string& modelName,
      csm::WarningList* warnings = NULL) const;

   virtual csm::Model* constructModelFromState(
      const std::string& modelState,
      csm::WarningList* warnings = NULL) const;
   virtual csm::Model* constructModelFromISD(
      const csm::Isd& imageSupportData,
      const std::string& modelName,
      csm::WarningList* warnings = NULL) const;

   virtual std::string getModelNameFromModelState(
      const std::string& modelState,
      csm::WarningList* warnings = NULL) const;

   virtual bool canISDBeConvertedToModelState(
      const csm::Isd& imageSupportData,
      const std::string& modelName,
      csm::WarningList* warnings = NULL) const;
   virtual std::string convertISDToModelState(
      const csm::Isd& imageSupportData,
      const std::string& modelName,
      csm::WarningList* warnings = NULL) const;

private:
   static csm2to3plugin INSTANCE;

   static tsm_ISD* convertIsd(const csm::Isd& isd);

   void loadTsmPlugins();
   void loadNameMap();

   typedef std::vector<std::string> SensorNameList;
   typedef std::map<std::string, const TSMPlugin*> SensorNameMap;

   SensorNameList theOrderedNames;
   SensorNameMap  theNameMap;
};


#endif
