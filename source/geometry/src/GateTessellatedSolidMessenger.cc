/*
 * GateTessellatedSolidMessenger.cc
 *
 *  Created on: 2015.07.01.
 *      Author: heszg
 */

#include "GateTessellatedSolidMessenger.hh"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWith3Vector.hh"

#include "GateTessellatedSolid.hh"

GateTessellatedSolidMessenger::GateTessellatedSolidMessenger(GateTessellatedSolid* itsCreator)
  : GateVolumeMessenger(itsCreator)
{
  G4String dir = GetDirectoryName() + "geometry/";

  G4String cmdName;
  cmdName = dir + "addVertex";
  TessellatedSolidVertexCmd = new G4UIcmdWith3VectorAndUnit(cmdName.c_str(), this);
  TessellatedSolidVertexCmd->SetGuidance("Add vertex of the tessellated solid");
  TessellatedSolidVertexCmd->SetParameterName("VertexX", "VertexY", "VertexZ", false);
  TessellatedSolidVertexCmd->SetUnitCategory("Length");

  cmdName = dir + "addFacet";
  TessellatedSolidFacetCmd = new G4UIcmdWith3Vector(cmdName.c_str(), this);
  TessellatedSolidFacetCmd->SetGuidance("Add a facet to the solid (3 index from the vertex list)");
  TessellatedSolidFacetCmd->SetParameterName("VertexNo1", "VertexNo2", "VertexNo3", false);

  cmdName = dir + "setCenter";
  TessellatedSolidCenterCmd = new G4UIcmdWith3VectorAndUnit(cmdName.c_str(), this);
  TessellatedSolidCenterCmd->SetGuidance("Set the center of the solid");
  TessellatedSolidCenterCmd->SetParameterName("x", "y", "z", false);

}

GateTessellatedSolidMessenger::~GateTessellatedSolidMessenger()
{
  delete TessellatedSolidVertexCmd;
  delete TessellatedSolidFacetCmd;
}

void GateTessellatedSolidMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
  if (command == TessellatedSolidVertexCmd ) {
      GetTessellatedSolidCreator()->AddVertex(TessellatedSolidVertexCmd->GetNew3VectorValue(newValue));
  } else if (command == TessellatedSolidFacetCmd) {
	  GetTessellatedSolidCreator()->AddFacet(TessellatedSolidFacetCmd->GetNew3VectorValue(newValue));
  } else if (command == TessellatedSolidCenterCmd) {
	  GetTessellatedSolidCreator()->SetCenter(TessellatedSolidCenterCmd->GetNew3VectorValue(newValue));
  } else {
    GateVolumeMessenger::SetNewValue(command,newValue);
  }
}
