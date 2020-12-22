#ifndef ProtonCTAnalysisFileMessenger_h
#define ProtonCTAnalysisFileMessenger_h 1


#include "G4UImessenger.hh"
#include "globals.hh"

class ProtonCTAnalysisManager; ///< Provides SetanalysisFileName()
class G4UIcmdWithAString; 
class G4UIcmdWithABool; 

/**
 * A messenger object of this class is created by the AnalysisManager.
 * The point of a messenger is to connect the G4UI with the simulation
 * functionality.
 * The messenger needs to contain a command object and to have SetValue
 * method that is called once a command is set.
 * 
 * @see ProtonCTAnalysisManager
 */
class ProtonCTAnalysisFileMessenger: public G4UImessenger
{
public:
  ProtonCTAnalysisFileMessenger(ProtonCTAnalysisManager*);
  ~ProtonCTAnalysisFileMessenger();

  /**   
   * Called when new command given.
   * @param command is a pointer to the given command object
   * @param newValue holds the argument given as a G4String
   * @return is void   
   */     
  void SetNewValue(G4UIcommand* command, G4String newValue);
  ProtonCTAnalysisManager* AnalysisManager; ///< handle to AnalysisManager
    
private:

  /**   
   * G4 user interface command (that takes a string argument) object
   * Constructor requires command name and messenger class(this).
   */ 
  G4UIcmdWithABool *LetCmd, *secondaryCmd; 
  G4UIcmdWithAString *DoseMatrixCmd;

};

#endif