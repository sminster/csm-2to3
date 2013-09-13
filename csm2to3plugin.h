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
//>
//     Date          Author   Comment   
//     -----------   ------   ------- 
//     30-Mar-2012   SCM      Initial Coding
//     30-Oct-2012   SCM      Fixed includes.
//     12-Sep-2013   JPK      Updated class to construct from a
//                            TSMPlugin* . Made constructor private
//                            Made loadTsmPlugins() static.  Changed
//                            static data meber INSTANCE (csm2to3plugin*) to
//                            INSTANCES ( vector<csm2to3plugin*>).  Now an
//                            instance of this plugin is generated for each
//                            loaded TSMPlugin.
//<
//*****************************************************************************

#ifndef csm2to3plugin_HEADER
#define csm2to3plugin_HEADER

#include <csm/Plugin.h>

#include <string>
#include <vector>
#include <map>

class TSMPlugin;
class tsm_ISD;

//*****************************************************************************
// CLASS:  csm2to3plugin
//> This class implements the "maker" for a CSM version 3 model that is
//  implemented by calling a CSM version 2 model implementation.
//<
//*****************************************************************************
class csm2to3plugin : public csm::Plugin
{
public:

   virtual ~csm2to3plugin();
      //> This is the destructor.
      //<

   virtual std::string getPluginName() const;
   virtual std::string getManufacturer() const;
   virtual std::string getReleaseDate() const;
   virtual csm::Version getCsmVersion() const;

   virtual size_t getNumModels() const;
   virtual std::string getModelName(size_t index) const;
   virtual std::string getModelFamily(size_t modelIndex) const;

   virtual csm::Version getModelVersion(const std::string& modelName) const;

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
   
   static void loadTsmPlugins();
   
private:
   static std::vector<csm2to3plugin*> INSTANCES;

   static tsm_ISD* convertIsd(const csm::Isd& isd);

   csm2to3plugin(const TSMPlugin*);
      //> This is the default constructor.
      //<
   
   const TSMPlugin* theTsmPlugin;
};

#endif
