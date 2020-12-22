#ifndef ProtonCTPhysicsListMessenger_h
#define ProtonCTPhysicsListMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class ProtonCTPhysicsList;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class ProtonCTPhysicsListMessenger: public G4UImessenger
{
public:
  
  ProtonCTPhysicsListMessenger(ProtonCTPhysicsList* );
  ~ProtonCTPhysicsListMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  
  ProtonCTPhysicsList* pPhysicsList;
    
  G4UIdirectory*             physDir;        
    G4UIcmdWithAString*      pListCmd;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif