#include "ProtonCTStepMax.hh"
#include "ProtonCTStepMaxMessenger.hh"

/////////////////////////////////////////////////////////////////////////////
ProtonCTStepMax::ProtonCTStepMax(const G4String& processName)
 : G4VDiscreteProcess(processName),MaxChargedStep(DBL_MAX)
{
  pMess = new ProtonCTStepMaxMessenger(this);
}
 
/////////////////////////////////////////////////////////////////////////////
ProtonCTStepMax::~ProtonCTStepMax() { delete pMess; }

/////////////////////////////////////////////////////////////////////////////
G4bool ProtonCTStepMax::IsApplicable(const G4ParticleDefinition& particle) 
{ 
  return (particle.GetPDGCharge() != 0.);
}

/////////////////////////////////////////////////////////////////////////////    
void ProtonCTStepMax::SetMaxStep(G4double step) {MaxChargedStep = step;}

/////////////////////////////////////////////////////////////////////////////
G4double ProtonCTStepMax::PostStepGetPhysicalInteractionLength(const G4Track& aTrack,
                                                  G4double,
                                                  G4ForceCondition* condition )
{
  // condition is set to "Not Forced"
  *condition = NotForced;
  
  G4double ProposedStep = DBL_MAX;
if((MaxChargedStep > 0.) &&(aTrack.GetVolume() != 0) && (aTrack.GetVolume()->GetName() == "Tracker"))
  ProposedStep = MaxChargedStep;
else if ((MaxChargedStep > 0.) &&(aTrack.GetVolume() != 0) && (aTrack.GetVolume()->GetName() == "Calorimeter"))
{
  ProposedStep = MaxChargedStep*10;
}
  return ProposedStep;
}

/////////////////////////////////////////////////////////////////////////////
G4VParticleChange* ProtonCTStepMax::PostStepDoIt(const G4Track& aTrack, const G4Step&)
{
   // do nothing
   aParticleChange.Initialize(aTrack);
   return &aParticleChange;
}