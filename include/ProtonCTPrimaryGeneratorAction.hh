#ifndef ProtonCTPrimaryGeneratorAction_h
#define ProtonCTPrimaryGeneratorAction_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "globals.hh"
#include "ProtonCTPrimaryGeneratorActionMessenger.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"

class G4GeneralParticleSource;
class G4Event;

class ProtonCTPrimaryGeneratorActionMessenger;
class ProtonCTPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
public:
  ProtonCTPrimaryGeneratorAction();    
  ~ProtonCTPrimaryGeneratorAction();
  
public:
  // Methods to change the parameters of primary particle generation 
  // interactively
 void GeneratePrimaries(G4Event*);
  static G4bool ReadFile;

    inline void setNewSource(G4bool Varbool){NewSource= Varbool;};
  G4String PathSource;
  G4bool Readfile;
    G4bool NewSource;
inline void setCalculatedPhaseSpaceFileIN(G4String val){calculatedPhaseSpaceFileIN=val;}
  
    
private:
  void SetDefaultPrimaryParticle();

    
G4String calculatedPhaseSpaceFileIN;
void setGunCalculatedPhaseSpace();
    
    ProtonCTPrimaryGeneratorActionMessenger *PrimaryGeneratorMessenger;
   G4ParticleGun *particleGuns;
 

private:
  G4GeneralParticleSource* particleGun;
  G4double sigmaX;
      std::ifstream in;
      std::ofstream ofs;
    
};

#endif