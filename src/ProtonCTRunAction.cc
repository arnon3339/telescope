#include "ProtonCTRunAction.hh"
#include "ProtonCTEventAction.hh"
#include "G4Run.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4ios.hh"
#include "ProtonCTDetectorConstruction.hh"
#include "G4SDManager.hh"
#include "G4Timer.hh"
#include "ProtonCTRunAction.hh"

//#include "ProtonCTMatrix.hh"

ProtonCTRunAction::ProtonCTRunAction()
{

    
}

ProtonCTRunAction::~ProtonCTRunAction()
{
    
}



void ProtonCTRunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4RunManager::GetRunManager()-> SetRandomNumberStore(true);
    G4cout << "Run " << aRun -> GetRunID() << " starts ..." << G4endl;
    
    electromagnetic = 0;
    hadronic = 0;
    
    
    
}

void ProtonCTRunAction::EndOfRunAction(const G4Run*)
{
    //G4cout << " Summary of Run " << aRun -> GetRunID() <<" :"<< G4endl;
    //G4cout << "Number of electromagnetic processes of primary particles in the phantom:"
    // 	   << electromagnetic << G4endl;
    //G4cout << "Number of hadronic processes of primary particles in the phantom:"
    //	   << hadronic << G4endl;
}
void ProtonCTRunAction::AddEMProcess()
{
    electromagnetic += 1;
}
void ProtonCTRunAction::AddHadronicProcess()
{
    hadronic += 1;
}