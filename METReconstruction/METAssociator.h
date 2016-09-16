///////////////////////// -*- C++ -*- /////////////////////////////
// METAssociator.h
// Header file for class METAssociator
//
// This is the base class for tools that construct MET terms
// from other object collections.
//
//  * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//
// Author: P Loch, S Resconi, TJ Khoo, AS Mete
///////////////////////////////////////////////////////////////////
#ifndef METRECONSTRUCTION_METASSOCIATOR_H
#define METRECONSTRUCTION_METASSOCIATOR_H

// STL includes
#include <string>

// FrameWork includes
#include "AsgTools/AsgTool.h"
#include "AsgTools/ToolHandle.h"

// Tracking Tool
#include "InDetTrackSelectionTool/IInDetTrackSelectionTool.h"

// METRecoInterface includes
#include "METRecoInterface/IMETAssocToolBase.h"

#include "xAODTracking/TrackParticle.h"
#include "xAODTracking/Vertex.h"
#include "xAODPFlow/PFOContainer.h"
#include "xAODPFlow/PFO.h"
#include "PFlowUtils/IRetrievePFOTool.h"
#include "PFlowUtils/IWeightPFOTool.h"
#include "FourMomUtils/xAODP4Helpers.h"

#include "RecoToolInterfaces/ITrackIsolationTool.h"
#include "RecoToolInterfaces/ICaloTopoClusterIsolationTool.h"

namespace met {
  class METAssociator
    : virtual public asg::AsgTool,
      virtual public IMETAssocToolBase
  {
    ///////////////////////////////////////////////////////////////////
    // Public methods:
    ///////////////////////////////////////////////////////////////////
    public:

    // Constructor w/ name
    METAssociator(const std::string& name);
    // Default Destructor
    virtual ~METAssociator();

    // AsgTool Handles
    virtual StatusCode initialize();
    virtual StatusCode execute   (xAOD::MissingETContainer* metCont, xAOD::MissingETAssociationMap* metMap);
    virtual StatusCode finalize  ();

    ///////////////////////////////////////////////////////////////////
    // Protected methods:
    ///////////////////////////////////////////////////////////////////
    protected:

    std::string m_input_data_key;
    std::string m_pvcoll;
    std::string m_trkcoll;
    std::string m_clcoll;
    std::string m_goodtracks_coll;

    bool m_pflow;
    bool m_useTracks;
    bool m_useRapidity;
    bool m_useIsolationTools;
    bool m_useModifiedClus;
    bool m_weight_charged_pfo;

    ToolHandle<CP::IRetrievePFOTool> m_pfotool;
    ToolHandle<CP::IWeightPFOTool> m_pfoweighttool;
    ToolHandle<InDet::IInDetTrackSelectionTool> m_trkseltool;
    ToolHandle<xAOD::ITrackIsolationTool> m_trkIsolationTool;
    ToolHandle<xAOD::ICaloTopoClusterIsolationTool> m_caloIsolationTool;
    bool m_skipconst;
    std::string m_forcoll;
    double m_foreta;

    double m_cenTrackPtThr;
    double m_forTrackPtThr;

    // reconstruction process to be defined in the individual tools
    // pure virtual -- we have no default
    virtual StatusCode executeTool(xAOD::MissingETContainer* metCont, xAOD::MissingETAssociationMap* metMap) = 0;
    StatusCode retrieveConstituents(const xAOD::IParticleContainer*& tcCont,const xAOD::Vertex*& pv,const xAOD::TrackParticleContainer*& trkCont,const xAOD::PFOContainer*& pfoCont) const;

    StatusCode filterTracks(const xAOD::TrackParticleContainer* tracks,
		      const xAOD::Vertex* pv) const;
    bool acceptTrack (const xAOD::TrackParticle* trk, const xAOD::Vertex* pv) const;
    bool acceptChargedPFO(const xAOD::TrackParticle* trk, const xAOD::Vertex* pv) const;
    bool isGoodEoverP(const xAOD::TrackParticle* trk,const xAOD::IParticleContainer*& tcCont) const;

    virtual StatusCode fillAssocMap(xAOD::MissingETAssociationMap* metMap,
				    const xAOD::IParticleContainer* hardObjs) const;
    virtual StatusCode extractPFO(const xAOD::IParticle* obj,
				  std::vector<const xAOD::IParticle*>& pfolist,
				  const xAOD::PFOContainer* pfoCont,
				  std::map<const xAOD::IParticle*,MissingETBase::Types::constvec_t> &momenta,
				  const xAOD::Vertex* pv) const = 0;
    virtual StatusCode extractTracks(const xAOD::IParticle* obj,
				     std::vector<const xAOD::IParticle*>& constlist,
				     const xAOD::IParticleContainer* tcCont,
				     const xAOD::Vertex* pv) const = 0;
    virtual StatusCode extractTopoClusters(const xAOD::IParticle* obj,
					   std::vector<const xAOD::IParticle*>& tclist,
				           const xAOD::IParticleContainer* tcCont) const = 0;
    static inline bool greaterPt(const xAOD::IParticle* part1, const xAOD::IParticle* part2) {
      return part1->pt()>part2->pt();
    }
    static inline bool greaterPtPFO(const xAOD::PFO* part1, const xAOD::PFO* part2) {
      if (part1->charge()==0 && part2->charge()!=0) return false;
      if (part1->charge()!=0 && part2->charge()==0) return true;
      if (part1->charge()==0 && part2->charge()==0) return part1->ptEM()>part2->ptEM();
      return part1->pt()>part2->pt();
    }
    ///////////////////////////////////////////////////////////////////
    // Private methods:
    ///////////////////////////////////////////////////////////////////
    private:

    // Default Constructor
    METAssociator();
  };
}

#endif // METRECONSTRUCTION_METASSOCBUILDERTOOL_H
