#ifndef ProtonCTStepMaxMessenger_h
#define ProtonCTStepMaxMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class ProtonCTStepMax;
class G4UIcmdWithADoubleAndUnit;

/////////////////////////////////////////////////////////////////////////////
class ProtonCTStepMaxMessenger: public G4UImessenger
{
public:
  ProtonCTStepMaxMessenger(ProtonCTStepMax*);
  ~ProtonCTStepMaxMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  ProtonCTStepMax* stepMax;
  G4UIcmdWithADoubleAndUnit* StepMaxCmd;
};

#endif