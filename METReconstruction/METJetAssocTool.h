///////////////////////// -*- C++ -*- /////////////////////////////
// METJetAssocTool.h 
// Header file for class METJetAssocTool
//
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Author: P Loch, S Resconi, TJ Khoo, AS Mete
/////////////////////////////////////////////////////////////////// 
#ifndef METRECONSTRUCTION_METJETASSOCTOOL_H
#define METRECONSTRUCTION_METJETASSOCTOOL_H 1

// METReconstruction includes
#include "METReconstruction/METAssociator.h"

namespace met{
  class METJetAssocTool final
    : public METAssociator
  { 
    // This macro defines the constructor with the interface declaration
    ASG_TOOL_CLASS(METJetAssocTool, IMETAssocToolBase)


    /////////////////////////////////////////////////////////////////// 
    // Public methods: 
    /////////////////////////////////////////////////////////////////// 
    public: 

    // Constructor with name
    METJetAssocTool(const std::string& name);
    ~METJetAssocTool();

    // AsgTool Hooks
    StatusCode  initialize();
    StatusCode  finalize();

    /////////////////////////////////////////////////////////////////// 
    // Const methods: 
    ///////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////// 
    // Non-const methods: 
    /////////////////////////////////////////////////////////////////// 

    /////////////////////////////////////////////////////////////////// 
    // Private data: 
    /////////////////////////////////////////////////////////////////// 
    protected: 

    StatusCode executeTool(xAOD::MissingETContainer* metCont, xAOD::MissingETAssociationMap* metMap);
    StatusCode extractPFO(const xAOD::IParticle*,
			  std::vector<const xAOD::IParticle*>&,
			  const xAOD::PFOContainer*,
			  std::map<const xAOD::IParticle*,MissingETBase::Types::constvec_t>&,
			  const xAOD::Vertex*) const {return StatusCode::FAILURE;} // should not be called

    StatusCode extractTracks(const xAOD::IParticle*,
			     std::vector<const xAOD::IParticle*>&,
			     const xAOD::IParticleContainer*,
			     const xAOD::Vertex*) const {return StatusCode::FAILURE;} // should not be called
    StatusCode extractTopoClusters(const xAOD::IParticle*,
				   std::vector<const xAOD::IParticle*>&,
				   const xAOD::IParticleContainer*) const {return StatusCode::FAILURE;} // should not be called

    private:
 
    /// Default constructor: 
    METJetAssocTool();

    void getPFOs(const xAOD::Jet *jet,
                 std::vector<const xAOD::IParticle*> &consts,
                 const xAOD::Vertex *pv,
                 const xAOD::PFOContainer *pfoCont,
                 std::map<const xAOD::IParticle*,MissingETBase::Types::constvec_t> &momenta) const;
    void getClus(const xAOD::Jet *jet,std::vector<const xAOD::IParticle*> &consts) const;
    void getOther(const xAOD::Jet *jet,
                  std::vector<const xAOD::IParticle*> &consts,
                  std::set<const xAOD::IParticle*> *newConst) const;

    double m_matchRadius;
  }; 

}

#endif //> !METRECONSTRUCTION_METJETASSOCTOOL_H
