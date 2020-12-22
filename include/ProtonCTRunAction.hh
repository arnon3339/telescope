#ifndef ProtonCTRunAction_h
#define ProtonCTRunAction_h 1

#include "G4UserRunAction.hh"
#include "G4RunManager.hh"
#include "globals.hh"

class G4Run;
class ProtonCTAnalysisManager;
class ProtonCTDetectorConstruction;
class ProtonCTRunMessenger;
class ProtonCTFactory;

class ProtonCTRunAction : public G4UserRunAction
{
public:
  ProtonCTRunAction();
  ~ProtonCTRunAction();

public:
  void BeginOfRunAction(const G4Run*);
  void EndOfRunAction(const G4Run* );
  void SelectEnergy(G4int); 

  void AddEMProcess();
  // Counts the number of electromagnetic processes
  // of primary particles in the phantom

  void AddHadronicProcess();
  // Counts the number of hadronic processes 
  // of primary particles in the phantom

private:  
  G4int electromagnetic;
  G4int hadronic;
};
#endif