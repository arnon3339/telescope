#ifndef ProtonCTActionInitialization_h
#define ProtonCTActionInitialization_h 1

#include "G4VUserActionInitialization.hh"

class ProtonCTDetectorConstruction;
class G4GeneralParticleSource;

class ProtonCTActionInitialization : public G4VUserActionInitialization
{
  public:
    ProtonCTActionInitialization(/*ProtonCTDetectorConstruction*/);
    virtual ~ProtonCTActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

  private:
   // G4VUserDetectorConstruction* fDetectorConstruction;
  //  G4GeneralParticleSource *masterGPS;

    
    
};

#endif