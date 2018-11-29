#pragma once

#include <sre/Mesh.hpp>
#include <Box2D/Box2D.h>
#include <poly2tri/poly2tri.h>
#include <boost/geometry/geometry.hpp>

using ring_t = boost::geometry::model::ring<b2Vec2, false, true>;
using ring_collection_t = std::vector<ring_t>;

class TerrainUtils {

public:

	std::shared_ptr<sre::Mesh> generateMesh(const std::vector<b2Vec2>& chain);
	
private:
	std::vector<p2t::Triangle*> createTriangulation(const std::vector<b2Vec2>& points);

	std::shared_ptr<sre::Mesh> buildMesh(std::vector<p2t::Triangle*> triangles);

	// Conversion methods
	glm::vec3 toGlm(p2t::Point* point);
	ring_t toRing(std::vector<b2Vec2> ring);
	ring_collection_t toRingCollection(std::vector<std::vector<b2Vec2>> collection);
	std::vector<b2Vec2> tob2Ring(ring_t ring);
	std::vector<std::vector<b2Vec2>> toWorldComponentStruct(ring_collection_t collection);
	ring_t makeConvexRing(b2Vec2 position, float radius, int numberVertices);
	ring_collection_t subtract(const ring_t& source, const ring_t& subtrahend);
};