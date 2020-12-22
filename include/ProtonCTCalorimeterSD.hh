#ifndef ProtonCTCalorimeterSD_h
#define ProtonCTCalorimeterSD_h 1

#include "G4VSensitiveDetector.hh"
#include "ProtonCTCalorimeterHit.hh"
#include "globals.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class ProtonCTCalorimeterSD : public G4VSensitiveDetector
{
public:
  ProtonCTCalorimeterSD(G4String name);
  ~ProtonCTCalorimeterSD();

  std::ofstream ofs;
  void Initialize(G4HCofThisEvent*);
 
  G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
 
  void EndOfEvent(G4HCofThisEvent*HCE);
 
private:
  ProtonCTCalorimeterHitsCollection *HitsCollection;
  G4String sensitiveCalorimeterName;	
};
#endif