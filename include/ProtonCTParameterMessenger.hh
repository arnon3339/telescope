#ifndef ProtonCTParameterMessenger_h
#define ProtonCTParameterMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class ProtonCTInteractionParameters;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

class ProtonCTParameterMessenger : public G4UImessenger
{
public:
  ProtonCTParameterMessenger(ProtonCTInteractionParameters* );
  ~ProtonCTParameterMessenger();

  void SetNewValue(G4UIcommand*, G4String);

private:
  ProtonCTInteractionParameters* pParam;

  G4UIdirectory           *paramDir;
  G4UIcmdWithAString      *dedxCmd, *listCmd;  

};
#endif