#include "ProtonCTActionInitialization.hh"
#include "ProtonCTPrimaryGeneratorAction.hh"
#include "ProtonCTRunAction.hh"
#include "ProtonCTSteppingAction.hh"
//#include "ProtonCTDetectorConstruction.hh"
#include "G4GeneralParticleSource.hh"

#include "ProtonCTEventAction.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ProtonCTActionInitialization::ProtonCTActionInitialization(/*G4VUserDetectorConstruction* detConstruction*/)
: G4VUserActionInitialization()//,
 // fDetectorConstruction(detConstruction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

ProtonCTActionInitialization::~ProtonCTActionInitialization()
{//delete masterGPS;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ProtonCTActionInitialization::BuildForMaster() const
{
	// In MT mode, to be clearer, the RunAction class for the master thread might be
	// different than the one used for the workers.
	// This RunAction will be called before and after starting the
	// workers.
	// For more details, please refer to :
	// https://twiki.cern.ch/twiki/bin/view/Geant4/Geant4MTForApplicationDevelopers
	//
	// ProtonCTRunAction* runAction= new ProtonCTRunAction(fDetectorConstruction);
	// SetUserAction(runAction);
  ProtonCTRunAction* pRunAction = new ProtonCTRunAction();
  SetUserAction(pRunAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void ProtonCTActionInitialization::Build() const
{       
 // Initialize the primary particles
  ProtonCTPrimaryGeneratorAction *pPrimaryGenerator = new ProtonCTPrimaryGeneratorAction();
  SetUserAction(pPrimaryGenerator);
	
  // Optional UserActions: run, event, stepping
  ProtonCTRunAction* pRunAction = new ProtonCTRunAction();
  SetUserAction(pRunAction);

	
  ProtonCTEventAction* pEventAction = new ProtonCTEventAction();
  SetUserAction(pEventAction);
	
  ProtonCTSteppingAction* steppingAction = new ProtonCTSteppingAction(pRunAction); 
  SetUserAction(steppingAction);  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......