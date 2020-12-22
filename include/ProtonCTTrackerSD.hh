#ifndef ProtonCTTrackerSD_h
#define ProtonCTTrackerSD_h 1

#include "G4VSensitiveDetector.hh"
#include "ProtonCTTrackerHit.hh"
#include "globals.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class ProtonCTTrackerSD : public G4VSensitiveDetector
{
public:
  ProtonCTTrackerSD(G4String name);
  ~ProtonCTTrackerSD();

  std::ofstream ofs;
  void Initialize(G4HCofThisEvent*);
 
  G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
 
  void EndOfEvent(G4HCofThisEvent*HCE);
 
private:
  ProtonCTTrackerHitsCollection *HitsCollection;
  G4String sensitiveDetectorName;	
};
#endif