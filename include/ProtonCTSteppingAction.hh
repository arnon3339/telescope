#ifndef ProtonCTSteppingAction_h
#define ProtonCTSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4ios.hh"
#include "globals.hh"

class ProtonCTRunAction;
class ProtonCTSteppingMessenger;


#ifndef G4NOHIST
class HepTupleManager;
class HepHistogram;
#endif

class ProtonCTSteppingAction : public G4UserSteppingAction
{
public:
  ProtonCTSteppingAction(ProtonCTRunAction*);
  ~ProtonCTSteppingAction();
  
  void UserSteppingAction(const G4Step*);

private:
  ProtonCTRunAction* runAction;
};
#endif