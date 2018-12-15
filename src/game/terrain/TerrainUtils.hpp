#pragma once

#define BOOST_GEOMETRY_OVERLAY_NO_THROW
#include <boost/geometry/geometry.hpp>
#include <sre/Mesh.hpp>
#include <Box2D/Box2D.h>
#include <poly2tri/poly2tri.h>
#include <boost/geometry/geometry.hpp>

using point_t = boost::geometry::model::point<double, 2, boost::geometry::cs::cartesian>;
using polygon_t = boost::geometry::model::polygon<point_t, false, true >;
using polygon_collection_t = std::vector<polygon_t>;

class TerrainUtils {

public:
	static std::shared_ptr<sre::Mesh> generateMesh(const std::vector<b2Vec2>& chain);

	static polygon_t makeConvexRing(b2Vec2 position, float radius, int numberVertices);
	static std::vector<std::vector<float>> generateNoise(std::vector<int> xPoints, int ampl, int wavelen, int octaves, int divisor);
	static std::vector<b2Vec2> combineNoise(std::vector<int> xPoints, std::vector<std::vector<float>> noiseOctaves);
	static void reshapeEdges(std::vector<b2Vec2>& terrain);
	static void simplify(polygon_collection_t& rings);
	static void subtract(polygon_t& source, const polygon_t& subtrahend, polygon_collection_t& result);

	// Conversion methods
	static glm::vec3 toGlm(p2t::Point* point);
	static polygon_t toBoostPolygon(std::vector<b2Vec2> b2Ring);
	static std::vector<b2Vec2> tob2Ring(polygon_t shape);
	static std::vector<std::vector<b2Vec2>> toWorldComponentStruct(polygon_collection_t collection);
	static b2Vec2 toB2DPoint(point_t point);
	static point_t toBoostPoint(b2Vec2 point);
	
private:
	TerrainUtils() = default;

	static std::shared_ptr<sre::Mesh> buildMesh(std::vector<p2t::Triangle*> triangles);

	static float coserp(float x, float y, float t);
	static std::vector<float> perlinNoise1D(std::vector<int> xPoints, int ampl, int wavelen);

	static constexpr float terrainImageSize = 2048.0f;
};