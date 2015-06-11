/*
 * omxhddevice.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 */

/* 
 * File:   omxhddevice.c
 * Author: Roland Fehr
 *
 * Created on 3. Juni 2015, 13:58
 */

// vdr includes
#include "vdr/plugin.h"

// plugin includes
#include "allwinnerdevice.h"
#include "tools.h"




static const char *VERSION        = "0.0.1";
static const char *DESCRIPTION    = trNOOP("Enter description for 'omxhddevice' plugin");
static const char *MAINMENUENTRY  = "omxhddevice";

class cPluginOmxhddevice : public cPlugin {
    
private:

  cAllwinnerDevice *m_allwinner_device;

  static void OnPrimaryDevice(void)
  {
    //if (cRpiSetup::HasOsd())
    //	new cRpiOsdProvider();
  }

public:
  cPluginOmxhddevice(void);
  virtual ~cPluginOmxhddevice();
  virtual const char *Version(void) { return VERSION; }
  virtual const char *Description(void) { return DESCRIPTION; }
  virtual const char *CommandLineHelp(void);
  virtual bool ProcessArgs(int argc, char *argv[]);
  virtual bool Initialize(void);
  virtual bool Start(void);
  virtual void Stop(void);
  virtual void Housekeeping(void);
  virtual void MainThreadHook(void);
  virtual cString Active(void);
  virtual time_t WakeupTime(void);
  virtual const char *MainMenuEntry(void) { return MAINMENUENTRY; }
  virtual cOsdObject *MainMenuAction(void);
  virtual cMenuSetupPage *SetupMenu(void);
  virtual bool SetupParse(const char *Name, const char *Value);
  virtual bool Service(const char *Id, void *Data = NULL);
  virtual const char **SVDRPHelpPages(void);
  virtual cString SVDRPCommand(const char *Command, const char *Option, int &ReplyCode);
  };

cPluginOmxhddevice::cPluginOmxhddevice(void)  : 
    m_allwinner_device(0)
{
    
    DLOG("omxhddevice construktor");
}

cPluginOmxhddevice::~cPluginOmxhddevice()
{
   DLOG("omxhddevice destruktor");
}

const char *cPluginOmxhddevice::CommandLineHelp(void)
{
  // Return a string that describes all known command line options.
  return NULL;
}

bool cPluginOmxhddevice::ProcessArgs(int argc, char *argv[])
{
  // Implement command line argument processing here if applicable.
  return true;
}

bool cPluginOmxhddevice::Initialize(void)
{
    m_allwinner_device = new cAllwinnerDevice(&OnPrimaryDevice);
    
    if(m_allwinner_device)
    {
        return !m_allwinner_device->Init();
    }
  return true;
}

bool cPluginOmxhddevice::Start(void)
{
  return m_allwinner_device->Start();
}

void cPluginOmxhddevice::Stop(void)
{
  // Stop any background activities the plugin is performing.
}

void cPluginOmxhddevice::Housekeeping(void)
{
  // Perform any cleanup or other regular tasks.
}

void cPluginOmxhddevice::MainThreadHook(void)
{
  // Perform actions in the context of the main program thread.
  // WARNING: Use with great care - see PLUGINS.html!
}

cString cPluginOmxhddevice::Active(void)
{
  // Return a message string if shutdown should be postponed
  return NULL;
}

time_t cPluginOmxhddevice::WakeupTime(void)
{
  // Return custom wakeup time for shutdown script
  return 0;
}

cOsdObject *cPluginOmxhddevice::MainMenuAction(void)
{
  // Perform the action when selected from the main VDR menu.
  return NULL;
}

cMenuSetupPage *cPluginOmxhddevice::SetupMenu(void)
{
  // Return a setup menu in case the plugin supports one.
  return NULL;
}

bool cPluginOmxhddevice::SetupParse(const char *Name, const char *Value)
{
  // Parse your own setup parameters and store their values.
  return false;
}

bool cPluginOmxhddevice::Service(const char *Id, void *Data)
{
  // Handle custom service requests from other plugins
  return false;
}

const char **cPluginOmxhddevice::SVDRPHelpPages(void)
{
  // Return help text for SVDRP commands this plugin implements
  return NULL;
}

cString cPluginOmxhddevice::SVDRPCommand(const char *Command, const char *Option, int &ReplyCode)
{
  // Process SVDRP commands this plugin implements
  return NULL;
}

VDRPLUGINCREATOR(cPluginOmxhddevice); // Don't touch this!
