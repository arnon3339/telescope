#include "ProtonCTAnalysisFileMessenger.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIdirectory.hh"
#include "G4SystemOfUnits.hh"

#include "ProtonCTMatrix.hh"
#include "ProtonCTLet.hh"

/////////////////////////////////////////////////////////////////////////////
ProtonCTAnalysisFileMessenger::ProtonCTAnalysisFileMessenger(ProtonCTAnalysisManager* amgr)
:AnalysisManager(amgr)
{  
  secondaryCmd = new G4UIcmdWithABool("/analysis/secondary",this);
  secondaryCmd -> SetParameterName("secondary", true);
  secondaryCmd -> SetDefaultValue("true");
  secondaryCmd -> SetGuidance("Set if dose/fluence for the secondary particles will be written" 
				"\n[usage]: /analysis/secondary [true/false]"); 
  secondaryCmd -> AvailableForStates(G4State_Idle, G4State_PreInit);

  DoseMatrixCmd = new G4UIcmdWithAString("/analysis/writeDoseFile",this);
  DoseMatrixCmd->SetGuidance("Write the dose/fluence to an ASCII file");
  DoseMatrixCmd->SetDefaultValue("Dose.out");
  DoseMatrixCmd->SetParameterName("choice",true); 

    LetCmd = new G4UIcmdWithABool("/analysis/computeLet",this);
	LetCmd  -> SetParameterName("choice",true); 
	LetCmd  -> SetDefaultValue(true);
	LetCmd  -> SetGuidance("Set if Let must be computed and write the ASCII filename for the Let");
	LetCmd  -> AvailableForStates(G4State_Idle, G4State_PreInit);

}

/////////////////////////////////////////////////////////////////////////////
ProtonCTAnalysisFileMessenger::~ProtonCTAnalysisFileMessenger()
{
  delete secondaryCmd; 
  delete DoseMatrixCmd; 
  delete LetCmd;
}

/////////////////////////////////////////////////////////////////////////////
void ProtonCTAnalysisFileMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
    if (command == secondaryCmd)
    {
    }

    else if (command == DoseMatrixCmd) // Filename can be passed here TODO 
    { 
	
    }
    
     else if (command == LetCmd)
    {
		
    }
}