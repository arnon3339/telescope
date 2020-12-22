#ifndef ProtonCTStepMax_h
#define ProtonCTStepMax_h 1

#include "globals.hh"
#include "G4VDiscreteProcess.hh"
#include "G4ParticleDefinition.hh"
#include "G4Step.hh"

class ProtonCTStepMaxMessenger;

/////////////////////////////////////////////////////////////////////////////
class ProtonCTStepMax : public G4VDiscreteProcess
{
  public:     

     ProtonCTStepMax(const G4String& processName ="UserStepMax");
    ~ProtonCTStepMax();

     G4bool   IsApplicable(const G4ParticleDefinition&);    
     void     SetMaxStep(G4double);
     G4double GetMaxStep() {return MaxChargedStep;};
     
     G4double PostStepGetPhysicalInteractionLength( const G4Track& track,
			                     G4double   previousStepSize,
			                     G4ForceCondition* condition);

     G4VParticleChange* PostStepDoIt(const G4Track&, const G4Step&);

     G4double GetMeanFreePath(const G4Track&, G4double, G4ForceCondition*)
       {return 0.;};     // it is not needed here !

  private:

     G4double    MaxChargedStep;
     ProtonCTStepMaxMessenger* pMess;
};

#endif