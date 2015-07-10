/*
 * GateTessellatedSolidMessenger.hh
 *
 *  Created on: 2015.07.01.
 *      Author: heszg
 */

#ifndef GATETESSELLATEDSOLIDMESSENGER_HH_
#define GATETESSELLATEDSOLIDMESSENGER_HH_

#include "globals.hh"
#include "GateVolumeMessenger.hh"

class GateTessellatedSolid;

class GateTessellatedSolidMessenger: public GateVolumeMessenger
{
public:
  GateTessellatedSolidMessenger(GateTessellatedSolid* itsCreator);
  ~GateTessellatedSolidMessenger();

  void SetNewValue(G4UIcommand*, G4String);
  virtual inline GateTessellatedSolid* GetTessellatedSolidCreator()
    { return (GateTessellatedSolid*)GetVolumeCreator(); }

private:
  G4UIcmdWith3VectorAndUnit* TessellatedSolidVertexCmd;
  G4UIcmdWith3Vector* TessellatedSolidFacetCmd;
  G4UIcmdWith3VectorAndUnit* TessellatedSolidCenterCmd;
};

#endif /* GATETESSELLATEDSOLIDMESSENGER_HH_ */
