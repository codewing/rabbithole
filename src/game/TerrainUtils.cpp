#include "TerrainUtils.hpp"

#include <math.h>

    std::shared_ptr<sre::Mesh> TerrainUtils::generateMesh(const std::vector<b2Vec2>& chain) {

		/*std::vector<p2t::Triangle*> triangles = createTriangulation(chain);
		return buildMesh(triangles);*/

		return buildTrianglesAndMesh(chain);

	}

	std::shared_ptr<sre::Mesh> TerrainUtils::buildTrianglesAndMesh(const std::vector<b2Vec2>& chain) {
		static std::vector<p2t::Point*> p2tPoints;
		for (int i = 0; i < chain.size() -1; i++) {
			auto& point = chain.at(i);
			p2tPoints.push_back(new p2t::Point(point.x, point.y));
		}
		p2t::SweepContext sc{ p2tPoints };
		p2t::Sweep sweep = p2t::Sweep();
		sweep.Triangulate(sc);

		std::shared_ptr<sre::Mesh> result = buildMesh(sc.GetTriangles());

		// free the points again
		for (auto it = p2tPoints.begin(); it != p2tPoints.end(); ++it ) {
			delete *it;
		}
		p2tPoints.clear();

		return result;
	}
	
	std::shared_ptr<sre::Mesh> TerrainUtils::buildMesh(std::vector<p2t::Triangle*> triangles) {

		std::vector<glm::vec3> positions;
		std::vector<glm::vec4> uvs;
		for (p2t::Triangle* t : triangles) {
			positions.push_back(toGlm(t->GetPoint(0)));
            positions.push_back(toGlm(t->GetPoint(1)));
            positions.push_back(toGlm(t->GetPoint(2)));

			uvs.emplace_back(glm::vec4{toGlm(t->GetPoint(0)) / terrainImageSize, 1.0f});
			uvs.emplace_back(glm::vec4{toGlm(t->GetPoint(1)) / terrainImageSize, 1.0f});
			uvs.emplace_back(glm::vec4{toGlm(t->GetPoint(2)) / terrainImageSize, 1.0f});
		}

		std::shared_ptr<sre::Mesh> mesh = sre::Mesh::create()
			.withPositions(positions)
			.withUVs(uvs)
			.build();

		return mesh;
	}

	glm::vec3 TerrainUtils::toGlm(p2t::Point* point) {
		return glm::vec3{ point->x, point->y, 0 };
	}

	ring_t TerrainUtils::toRing(std::vector<b2Vec2> ring) {
		ring_t result;
		for (auto point : ring) {
			result.push_back(point);
		}

		return result;
	}

	ring_collection_t TerrainUtils::toRingCollection(std::vector<std::vector<b2Vec2>> collection) {
		ring_collection_t result;
		for (auto ring : collection) {
			result.push_back(toRing(ring));
		}

		return result;
	}

	ring_collection_t TerrainUtils::subtract(const ring_t& source, const ring_t& subtrahend)
	{
		ring_collection_t out;
		boost::geometry::difference(source, subtrahend, out);
		return out;
	}

	std::vector<std::vector<b2Vec2>> TerrainUtils::toWorldComponentStruct(ring_collection_t collection) {
		std::vector<std::vector<b2Vec2>> result;
		for (auto ring : collection) {
			result.push_back(tob2Ring(ring));
		}

		return result;
	}

	std::vector<b2Vec2> TerrainUtils::tob2Ring(ring_t ring) {
		std::vector<b2Vec2> result;
		for (auto point : ring) {
			result.push_back(point);
		}

		return result;
	}

	ring_t TerrainUtils::makeConvexRing(b2Vec2 position, float radius, int numberVertices)
	{
		ring_t convexRing;
		const float theta = static_cast<float>(glm::radians(360.f) / numberVertices);

		float c = std::cos(theta);
		float s = std::sin(theta);

		float y = 0.0f;
		float x = radius;
		for (int i = 0; i < numberVertices; i++)
		{
			float v_x = x + position.x;
			float v_y = y + position.y;
			boost::geometry::append(convexRing, b2Vec2(v_x, v_y));

			float lastX = x;
			x = c * x - s * y;
			y = s * lastX + c * y;
		}

		return convexRing;
	}