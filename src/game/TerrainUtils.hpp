#pragma once

#define BOOST_GEOMETRY_OVERLAY_NO_THROW
#include <boost/geometry/geometry.hpp>
#include <boost/geometry/geometries/register/point.hpp>
#include <boost/geometry/geometries/ring.hpp>
#include <sre/Mesh.hpp>
#include <Box2D/Box2D.h>
#include <poly2tri/poly2tri.h>
#include <boost/geometry/geometry.hpp>

BOOST_GEOMETRY_REGISTER_POINT_2D(b2Vec2, float, boost::geometry::cs::cartesian, x, y);

using ring_t = boost::geometry::model::ring<b2Vec2, false, true>;
using ring_collection_t = std::vector<ring_t>;

class TerrainUtils {

public:

	std::shared_ptr<sre::Mesh> generateMesh(const std::vector<b2Vec2>& chain);

	std::vector<std::vector<float>> generateNoise(std::vector<int> xPoints, int ampl, int wavelen, int octaves, int divisor);

	std::vector<b2Vec2> combineNoise(std::vector<int> xPoints, std::vector<std::vector<float>> noiseOctaves);

	void reshapeEdges(std::vector<b2Vec2>& terrain);

	// Conversion methods
	glm::vec3 toGlm(p2t::Point* point);
	ring_t toRing(std::vector<b2Vec2> ring);
	ring_collection_t toRingCollection(std::vector<std::vector<b2Vec2>> collection);
	std::vector<b2Vec2> tob2Ring(ring_t ring);
	std::vector<std::vector<b2Vec2>> toWorldComponentStruct(ring_collection_t collection);
	static ring_t makeConvexRing(b2Vec2 position, float radius, int numberVertices);
	static void simplify(ring_collection_t& rings);
	static void subtract(const ring_t& source, const ring_t& subtrahend, ring_collection_t& result);
	
private:
	std::shared_ptr<sre::Mesh> buildMesh(std::vector<p2t::Triangle*> triangles);

	std::shared_ptr<sre::Mesh> buildTrianglesAndMesh(const std::vector<b2Vec2>& chain);

	float linearCongruentialGen();

	float coserp(float x, float y, float t);

	std::vector<float> perlinNoise1D(std::vector<int> xPoints, int ampl, int wavelen);

	static constexpr float terrainImageSize = 2048.0f;
};