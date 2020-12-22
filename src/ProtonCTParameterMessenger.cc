#include "ProtonCTParameterMessenger.hh"
#include "ProtonCTInteractionParameters.hh"
#include "G4SystemOfUnits.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

ProtonCTParameterMessenger::ProtonCTParameterMessenger(ProtonCTInteractionParameters* param)
:pParam(param)
{
    paramDir = new G4UIdirectory("/parameter/");
    paramDir -> SetGuidance("Commands to generate stopping power and range");
    
    dedxCmd = new G4UIcmdWithAString("/parameter/getstopping",this);  
    dedxCmd->SetGuidance("Get mass stopping powers"
			"\n[usage]: /parameter/getstopping Material [Emin] [Emax] [N] [Particle] [File]" 
			"\n         Material:(string) Material name, like G4_H, G4_WATER,..., look at /parameter/nist"
			"\n         Emin Emax:(double) minimum and maximum kinetic energy (MeV)"
			"\n         N:(double) [number of points]"
			"\n         Particle:(string) Particle name, look at /particle/list"
			"\n         File:(string) Name for the output file."
			"\nDefault values for parameters inside [] are respectively:"
			"\n \"1 MeV\", \"Emin\", \"1\", \"proton\", \"stdout\"");
    dedxCmd->SetParameterName("inputData",false);
    dedxCmd->AvailableForStates(G4State_Idle);  

    listCmd = new G4UIcmdWithAString("/parameter/nist",this);  
    listCmd -> SetGuidance("Print NIST elements/materials.\nParameters:"
			    "\n\t all: will print elements and compounds"
			    "\n\t simple: will print elements only"
			    "\n\t compound: will print compounds only"
			    "\n\t hep: will print hep compounds"
			    "\n\t list: will print a simple full list of all elements and compounds");
    listCmd -> SetParameterName("String",true);
    listCmd -> SetDefaultValue("list");
    listCmd -> SetCandidates("all simple compound hep list");
    listCmd ->AvailableForStates(G4State_Idle);  
    //Available G4 States (G4State_PreInit, G4State_Init, G4State_Idle,G4State_GeomClosed, G4State_EventProc);  
}
ProtonCTParameterMessenger::~ProtonCTParameterMessenger()
{
	delete paramDir;
	delete dedxCmd;
	delete listCmd;
}

void ProtonCTParameterMessenger::SetNewValue(G4UIcommand* command, G4String vararg)
{
	if (command == dedxCmd)
	{
		pParam -> GetStoppingTable(vararg);
	}
	else if (command == listCmd)
	{
		pParam -> ListOfNistMaterials(vararg);
	}
}