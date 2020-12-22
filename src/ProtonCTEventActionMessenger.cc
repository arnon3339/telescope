#include "ProtonCTEventActionMessenger.hh"

#include "ProtonCTEventAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"


/////////////////////////////////////////////////////////////////////////////
ProtonCTEventActionMessenger::ProtonCTEventActionMessenger(ProtonCTEventAction* EvAct)
:eventAction(EvAct)
{
  eventDir = new G4UIdirectory("/event/");
  eventDir->SetGuidance("Permits controls on simulation events");
 
  DrawCmd = new G4UIcmdWithAString("/event/drawTracks",this);
  DrawCmd->SetGuidance("Draw the tracks in the event");
  DrawCmd->SetGuidance("  Choice : none,charged, all, neutral");
  DrawCmd->SetParameterName("choice",true);
  DrawCmd->SetDefaultValue("all");
  DrawCmd->SetCandidates("none charged all neutral");
  DrawCmd->AvailableForStates(G4State_Idle);
  
  PrintCmd = new G4UIcmdWithAnInteger("/event/printEventNumber",this);
  PrintCmd->SetGuidance("Print the event number of modulo n");
  PrintCmd->SetParameterName("EventNb",false);
  PrintCmd->SetRange("EventNb>0");
  PrintCmd->AvailableForStates(G4State_Idle);      
}

/////////////////////////////////////////////////////////////////////////////
ProtonCTEventActionMessenger::~ProtonCTEventActionMessenger()
{
  delete DrawCmd;
  delete PrintCmd;
  delete eventDir;         
}

/////////////////////////////////////////////////////////////////////////////
void ProtonCTEventActionMessenger::SetNewValue(G4UIcommand* command,
                                          G4String newValue)
{ 
  if(command == DrawCmd)
    {eventAction->SetDrawFlag(newValue);}
    
  if(command == PrintCmd)
    {eventAction->SetPrintModulo(PrintCmd->GetNewIntValue(newValue));}           
 }