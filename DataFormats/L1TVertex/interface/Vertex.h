#ifndef DataFormats_L1TVertex_Vertex_h
#define DataFormats_L1TVertex_Vertex_h


#include <vector>

#include "DataFormats/Common/interface/Ptr.h"
#include "DataFormats/L1TrackTrigger/interface/TTTrack.h"
#include "DataFormats/L1TrackTrigger/interface/TTTypes.h"


namespace l1t {

class Vertex;
typedef std::vector<Vertex> VertexCollection;


class Vertex {
public:
  typedef TTTrack<Ref_Phase2TrackerDigi_> Track_t;

  Vertex();

  Vertex(float z0, const std::vector<edm::Ptr<Track_t>>& tracks);
  Vertex(float z0, const std::vector<edm::Ptr<Track_t>>& matchedTracks, const std::vector<edm::Ptr<Track_t>>& tracks);
  ~Vertex();

  float z0() const;

  // tracks used for fitting
  const std::vector<edm::Ptr<Track_t>>& tracks() const;

  // tracks associated with the vertex
  const std::vector<edm::Ptr<Track_t>>& matchedTracks() const;

private:

  float z0_;
  // tracks used for fit
  std::vector<edm::Ptr<Track_t>> tracks_;
  // tracks judged by vertex reconstruction aglo to belong to vertex
  std::vector<edm::Ptr<Track_t>> matchedTracks_;
};

}

#endif

