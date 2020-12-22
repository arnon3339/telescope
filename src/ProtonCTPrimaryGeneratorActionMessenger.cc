#include "ProtonCTPrimaryGeneratorActionMessenger.hh"
#include "ProtonCTPrimaryGeneratorAction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4SystemOfUnits.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithABool.hh"

ProtonCTPrimaryGeneratorActionMessenger::ProtonCTPrimaryGeneratorActionMessenger(
                                             ProtonCTPrimaryGeneratorAction* ProtonCTGun)
:ProtonCTAction(ProtonCTGun)
{
   
}

ProtonCTPrimaryGeneratorActionMessenger::~ProtonCTPrimaryGeneratorActionMessenger()
{

}