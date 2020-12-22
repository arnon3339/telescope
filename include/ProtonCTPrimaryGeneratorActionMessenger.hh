#ifndef ProtonCTPrimaryGeneratorActionMessenger_h
#define ProtonCTPrimaryGeneratorActionMessenger_h 1

#include "G4UImessenger.hh"
#include "globals.hh"

class ProtonCTPrimaryGeneratorAction;
class G4UIdirectory;
class G4UIcmdWithAnInteger;
class G4UIcmdWithAString;
class G4UIcmdWithABool;
class ProtonCTPrimaryGeneratorActionMessenger:

public G4UImessenger
{
public:
   
  ProtonCTPrimaryGeneratorActionMessenger(ProtonCTPrimaryGeneratorAction*);
  ~ProtonCTPrimaryGeneratorActionMessenger();


    ProtonCTPrimaryGeneratorAction* ProtonCTAction;


private:

};

#endif
