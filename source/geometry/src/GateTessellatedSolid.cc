/*
 * GateTessellatedSolid.cc
 *
 *  Created on: 2015.07.01.
 *      Author: heszg
 *
 * Allows the usage of G4TessallatedSolid objects in phantom geometry.
 * Support solids built up from triangles only at the moment.
 * You should define all vertices of the solid with the command "addVertex" 
 * and then set up the triangles with "addFacet". 
 *
 * For example to create a unit cube:
 * 
 * /gate/world/daughters/name cube
 * /gate/world/daughters/insert tessellatedsolid
 * # set the reference center of this object
 * /gate/cube/geometry/setCenter 0 0 0 mm
 *
 * # List of vertices
 * /gate/cube/geometry/addVertex 0 1 1 cm
 * /gate/cube/geometry/addVertex 1 1 1 cm
 * /gate/cube/geometry/addVertex 0 0 1 cm
 * /gate/cube/geometry/addVertex 1 0 1 cm
 * /gate/cube/geometry/addVertex 0 1 0 cm
 * /gate/cube/geometry/addVertex 1 1 0 cm
 * /gate/cube/geometry/addVertex 0 0 0 cm
 * /gate/cube/geometry/addVertex 1 0 0 cm
 * 
 * # List of facets
 * /gate/cube/geometry/addFacet 1 0 2 
 * /gate/cube/geometry/addFacet 1 2 3 
 * /gate/cube/geometry/addFacet 0 1 5 
 * /gate/cube/geometry/addFacet 0 5 4 
 * /gate/cube/geometry/addFacet 1 3 5 
 * /gate/cube/geometry/addFacet 3 7 5 
 * /gate/cube/geometry/addFacet 3 2 7 
 * /gate/cube/geometry/addFacet 2 6 7 
 * /gate/cube/geometry/addFacet 2 0 4 
 * /gate/cube/geometry/addFacet 2 4 6 
 * /gate/cube/geometry/addFacet 5 6 4
 * /gate/cube/geometry/addFacet 5 7 6
 * 
 * /gate/cube/placement/setTranslation 0 0 0 mm
 * /gate/cube/attachPhantomSD
 *
 */

#include "GateTessellatedSolid.hh"
#include "GateTessellatedSolidMessenger.hh"

#include "G4TessellatedSolid.hh"
#include "G4TriangularFacet.hh"
#include "G4QuadrangularFacet.hh"
#include "GateTools.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4Colour.hh"
#include "G4UnitsTable.hh"
#include "G4PVPlacement.hh"
#include "G4Material.hh"
#include "globals.hh"

//-----------------------------------------------------------------------------------------------
// Constructor
GateTessellatedSolid::GateTessellatedSolid(const G4String& itsName,
                               const G4String& itsMaterialName,
                               G4ThreeVectorList itsVertices,
							   GateFacetVerticesList itsFacets,
                               G4bool acceptsChildren,
                               G4int depth)
: GateVVolume(itsName, acceptsChildren, depth),
  m_TessellatedSolid_solid(0), m_TessellatedSolid_log(0),
  m_center(0,0,0),
  m_vertices(itsVertices), m_facets(itsFacets),
  m_Messenger(0)
{
  SetMaterialName(itsMaterialName);
  m_Messenger = new GateTessellatedSolidMessenger(this);
}

//-----------------------------------------------------------------------------------------------
// Constructor with default values
GateTessellatedSolid::GateTessellatedSolid(const G4String& itsName,
                               G4bool acceptsChildren,
                               G4int depth)
: GateVVolume(itsName, acceptsChildren, depth),
  m_TessellatedSolid_solid(0), m_TessellatedSolid_log(0),
  m_center(0,0,0),
  m_Messenger(0)
{
  SetMaterialName("Vacuum");
  m_Messenger = new GateTessellatedSolidMessenger(this);
}

//-----------------------------------------------------------------------------------------------
// Destructor
GateTessellatedSolid::~GateTessellatedSolid()
{
  delete m_Messenger;
}

//-----------------------------------------------------------------------------------------------
// Implementation of the pure virtual method ConstructOwnSolidAndLogical() declared by the base-class.
// Construct a new TessellatedSolid solid and its logical volume.
// If flagUpdateOnly is set to 1, the TessellatedSolid is updated rather than rebuilt.
G4LogicalVolume* GateTessellatedSolid::ConstructOwnSolidAndLogicalVolume(G4Material* mater, G4bool flagUpdateOnly)
{
	if (GetVerbosity()>=2) {
		G4cout << "GateTessellatedSolid::ConstructOwnSolidAndLogicalVolume" << G4endl;
		DescribeMyself(1);
	}

	if (!flagUpdateOnly || !m_TessellatedSolid_solid) {
	    // Build mode: build the solid, then the logical volume
	    m_TessellatedSolid_solid = new G4TessellatedSolid(GetSolidName());
	
		//
		// Check the geometry
		// For each edge we should have exactly 2 facets with opposite orientation to get a closed surface 
		// !TODO! unless there are vertices in the middle of edges (G4 doesn't like it either)
		// !TODO! check if the normal vector points inside 
		// !TODO! check if the geometry is intersecting itself
		bool geomcheck = true;
		for (G4ThreeVectorList::size_type v=0; v < m_vertices.size(); v++) {
			bool used = false;	// check if the vertex is used or not
			std::vector< int > connections0( m_vertices.size(), 0);
			std::vector< int > connections1( m_vertices.size(), 0);
			for (GateFacetVerticesList::size_type f=0; f < m_facets.size(); f++) {
				for (GateFacetVertices::size_type i=0; i < m_facets[f].size(); i++) {
					int v0 = m_facets[f][i];
					int v1 = m_facets[f][i + 1 < m_facets[f].size() ? i+1 : 0];
					if (v0 == v) {
						connections1[v1]++;
						used = true;
					}
					else if (v1==v) {
						connections0[v0]++;
						used = true;
					}
//					G4cout << "Edge: " << v0 << " - " << v1 << G4endl;
				}
			}

			for (G4ThreeVectorList::size_type w=0; w < v; w++) {
				if (connections0[w] != connections1[w] || connections0[w] > 1) {
					geomcheck = false;
					G4cerr << "Geometry check failed on edge " << v << "--" << w << "   " <<
						connections0[w] << " == " << connections1[w] << "    " <<
						m_vertices[v] << ", " << m_vertices[w] << G4endl;
				}
			}
			if (!used)
			{
				geomcheck = false;
				G4cerr << "Vertex point #" << v << " is not used." << G4endl;
			}
		}
		if (!geomcheck)
		{
			G4cerr << "Geometry check failed for solid: " << GetSolidName() << G4endl;
			//G4Exception("GateTessellatedSolid", "Invalid solid geometry", FatalErrorInArgument, 
			//	(G4String("Invalid solid geometry: ")+GetSolidName()).c_str());
		}
		
		for (GateFacetVerticesList::size_type i=0; i < m_facets.size(); i++) {
			if (m_facets[i].size()==3) {
				G4TriangularFacet *f = new G4TriangularFacet( 
					m_vertices[m_facets[i][0]] - m_center, 
					m_vertices[m_facets[i][1]] - m_center,
					m_vertices[m_facets[i][2]] - m_center, ABSOLUTE);
				m_TessellatedSolid_solid->AddFacet(f);
			}
			else if (m_facets[i].size()==4) {
				G4QuadrangularFacet *f = new G4QuadrangularFacet( 
					m_vertices[m_facets[i][0]] - m_center, 
					m_vertices[m_facets[i][1]] - m_center,
					m_vertices[m_facets[i][2]] - m_center, 
					m_vertices[m_facets[i][3]] - m_center, 
					ABSOLUTE);
				m_TessellatedSolid_solid->AddFacet(f);
			} 
			else {
				GateMessage("Warning", 0, "GateTessellatedSolid::ConstructOwnSolidAndLogicalVolume only tri- and quadrangulars are supported"<<G4endl);
			}
		}
		m_TessellatedSolid_log = new G4LogicalVolume(m_TessellatedSolid_solid, mater, GetLogicalVolumeName(),0,0,0);
		m_TessellatedSolid_solid->SetSolidClosed(true);
	}
	else {
     // Update mode: refresh the dimensions of the solid
		static bool updateWarning = true;
		if (updateWarning) {
			GateMessage("Warning", 0, "GateTessellatedSolid::ConstructOwnSolidAndLogicalVolume update mode not implemented"<<G4endl);
			updateWarning = false;
		}
	}
	return m_TessellatedSolid_log;
}

void GateTessellatedSolid::DestroyOwnSolidAndLogicalVolume()
{
  if (m_TessellatedSolid_log)
    delete m_TessellatedSolid_log;
  m_TessellatedSolid_log = 0;

  if (m_TessellatedSolid_solid)
    delete m_TessellatedSolid_solid;
  m_TessellatedSolid_solid = 0;

}

void GateTessellatedSolid::DescribeMyself(size_t level)
{
  G4cout << GateTools::Indent(level) << "Shape: TessellatedSolid" << G4endl;
  G4cout << GateTools::Indent(level) << "Vertices: " << m_vertices.size() << G4endl;
  for (G4ThreeVectorList::size_type i=0; i < m_vertices.size(); i++) {
	  G4cout << GateTools::Indent(level) << "	#"<<i << " " << m_vertices[i] << G4endl;
  }
  G4cout << GateTools::Indent(level) << "Facets: " << m_facets.size() << G4endl;
  for (GateFacetVerticesList::size_type i=0; i < m_facets.size(); i++) {
	  G4cout << GateTools::Indent(level) << "#" << i;
	  for (GateFacetVertices::size_type j=0; j < m_facets[i].size(); j++) {
			G4cout << " "  << m_facets[i][j];
	  }
	  G4cout << G4endl;
  }
}

G4double GateTessellatedSolid::ComputeMyOwnVolume() const
{
  return m_TessellatedSolid_solid->GetCubicVolume();
}
