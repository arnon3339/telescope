#ifndef ProtonCTEventActionMessenger_h
#define ProtonCTEventActionMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class ProtonCTEventAction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;

class ProtonCTEventActionMessenger: public G4UImessenger
{
public:
  ProtonCTEventActionMessenger(ProtonCTEventAction*);
  ~ProtonCTEventActionMessenger();
    
  void SetNewValue(G4UIcommand*, G4String);
    
private:
  ProtonCTEventAction*          eventAction;
  G4UIdirectory*        eventDir;        
  G4UIcmdWithAString*   DrawCmd;
  G4UIcmdWithAnInteger* PrintCmd;    
};

#endif
