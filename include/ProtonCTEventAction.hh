#ifndef ProtonCTEventAction_h
#define ProtonCTEventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"

class ProtonCTMatrix;
class ProtonCTEventActionMessenger;

class ProtonCTEventAction : public G4UserEventAction
{
public:
  ProtonCTEventAction();
  ~ProtonCTEventAction();

public:
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);

  void SetPrintModulo(G4int val)
  {
    printModulo = val;
  };

  void SetDrawFlag(G4String val)
  {
    drawFlag = val;
  };

private: 
  G4String drawFlag; //Visualisation flag
  G4int trackerCollID;
  G4int calorimeterCollID;
  //ProtonCTMatrix *matrix; 
  G4int printModulo;  
  ProtonCTEventActionMessenger* pointerEventMessenger;
};

class B4aEventAction : public G4UserEventAction
{
public:
    B4aEventAction();
    virtual ~B4aEventAction();
    
    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);
    
    void AddAbs(G4double de, G4double dl);
    void AddGap(G4double de, G4double dl);
    
private:
    G4double  fEnergyAbs;
    G4double  fEnergyGap;
    G4double  fTrackLAbs;
    G4double  fTrackLGap;
};

// inline functions

inline void B4aEventAction::AddAbs(G4double de, G4double dl) {
    fEnergyAbs += de;
    fTrackLAbs += dl;
}

inline void B4aEventAction::AddGap(G4double de, G4double dl) {
    fEnergyGap += de;
    fTrackLGap += dl;
}


#endif
