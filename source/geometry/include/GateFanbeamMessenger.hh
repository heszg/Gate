/*----------------------
   GATE version name: gate_v6

   Copyright (C): OpenGATE Collaboration

This software is distributed under the terms
of the GNU Lesser General  Public Licence (LGPL)
See GATE/LICENSE.txt for further details
----------------------*/


#ifndef GateFanbeamMessenger_h
#define GateFanbeamMessenger_h 1

#include "globals.hh"

#include "GateVolumeMessenger.hh"

class GateVisAttributesMessenger;
class GateFanbeam;
class G4UIdirectory;

class GateFanbeamMessenger: public GateVolumeMessenger
{
  public:
    GateFanbeamMessenger(GateFanbeam* itsInserter);
   ~GateFanbeamMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
    virtual inline GateFanbeam* GetCollimatorInserter() 
      { return (GateFanbeam*) GetVolumeCreator(); }

  private:
  
    G4String                    name_Geometry;
    G4UIdirectory*              dir_Geometry;

    G4UIcmdWithADoubleAndUnit*  CollimatorDimensionXCmd;
    G4UIcmdWithADoubleAndUnit*  CollimatorDimensionYCmd;
    G4UIcmdWithADoubleAndUnit*  CollimatorFocalDistanceXCmd;
    G4UIcmdWithADoubleAndUnit*  CollimatorHeightCmd;
    G4UIcmdWithADoubleAndUnit*  CollimatorSeptalThicknessCmd;
    G4UIcmdWithADoubleAndUnit*  CollimatorInnerRadiusCmd;
    G4UIcmdWithAString*         CollimatorMaterialCmd;

    GateVisAttributesMessenger* visAttributesMessenger;
};

#endif

