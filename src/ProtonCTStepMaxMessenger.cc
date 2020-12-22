#include "ProtonCTStepMaxMessenger.hh"
#include "ProtonCTStepMax.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4SystemOfUnits.hh"

/////////////////////////////////////////////////////////////////////////////
ProtonCTStepMaxMessenger::ProtonCTStepMaxMessenger(ProtonCTStepMax* stepM)
:stepMax(stepM)
{ 
  StepMaxCmd = new G4UIcmdWithADoubleAndUnit("/Step/TrackerStep",this);
  StepMaxCmd->SetGuidance("Set max allowed step length");
  StepMaxCmd->SetParameterName("mxStep",false);
  StepMaxCmd->SetRange("mxStep>0.");
  StepMaxCmd->SetUnitCategory("Length");
}

/////////////////////////////////////////////////////////////////////////////
ProtonCTStepMaxMessenger::~ProtonCTStepMaxMessenger()
{
  delete StepMaxCmd;
}

/////////////////////////////////////////////////////////////////////////////
void ProtonCTStepMaxMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
  if (command == StepMaxCmd)
    { stepMax->SetMaxStep(StepMaxCmd->GetNewDoubleValue(newValue));}
}