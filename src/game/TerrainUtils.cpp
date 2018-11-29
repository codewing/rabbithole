#include "TerrainUtils.hpp"

    std::shared_ptr<sre::Mesh> TerrainUtils::generateMesh(const std::vector<b2Vec2>& chain) {

		std::vector<p2t::Triangle*> triangles = createTriangulation(chain);
		return buildMesh(triangles);

	}

	std::vector<p2t::Triangle*> TerrainUtils::createTriangulation(const std::vector<b2Vec2>& points) {
		std::vector<p2t::Point*> res;
		for (int i = 0; i < points.size(); i++) {
			auto& point = points.at(i);
			res.push_back(&p2t::Point(point.x, point.y));
		}
		p2t::SweepContext& sc = p2t::SweepContext(res);
		p2t::Sweep sweep = p2t::Sweep();
		sweep.Triangulate(sc);
		return sc.GetTriangles();

	}
	
	std::shared_ptr<sre::Mesh> TerrainUtils::buildMesh(std::vector<p2t::Triangle*> triangles) {

		std::vector<glm::vec3> positions;
		for (p2t::Triangle* t : triangles) {
			positions.push_back({ toGlm(t->GetPoint(0)), toGlm(t->GetPoint(1)), toGlm(t->GetPoint(2)) });
		}

		std::shared_ptr<sre::Mesh> mesh = sre::Mesh::create()
			.withPositions(positions)
			.build();

		return mesh;
	}

	glm::vec3 TerrainUtils::toGlm(p2t::Point* point) {
		return glm::vec3{ point->x, point->y, 0 };
	}

	ring_t toRing(std::vector<b2Vec2> ring) {
		ring_t result;
		for (auto point : ring) {
			result.push_back(point);
		}

		return result;
	}

	ring_collection_t toRingCollection(std::vector<std::vector<b2Vec2>> collection) {
		ring_collection_t result;
		for (auto ring : collection) {
			result.push_back(toRing(ring));
		}

		return result;
	}

	ring_collection_t subtract(const ring_t& source, const ring_t& subtrahend)
	{
		ring_collection_t out;
		boost::geometry::difference(source, subtrahend, out);
		return out;
	}

	std::vector<std::vector<b2Vec2>> toWorldComponentStruct(ring_collection_t collection) {
		std::vector<std::vector<b2Vec2>> result;
		for (auto ring : collection) {
			result.push_back(tob2Ring(ring));
		}

		return result;
	}

	std::vector<b2Vec2> tob2Ring(ring_t ring) {
		std::vector<b2Vec2> result;
		for (auto point : ring) {
			result.push_back(point);
		}

		return result;
	}

	ring_t makeConvexRing(b2Vec2 position, float radius, int vertices)
	{
		ring_t convexRing;
		const float theta = boost::math::constants::two_pi<float>() / static_cast<float>(vertices);

		float c = std::cos(theta);
		float s = std::sin(theta);

		float t = 0.0f;
		float y = 0.0f;
		float x = radius;
		for (float i = 0; i < vertices; i++)
		{
			float v_x = x + position.x;
			float v_y = y + position.y;
			boost::geometry::append(convexRing, b2Vec2(v_x, v_y));

			t = x;
			x = c * x - s * y;
			y = s * t + c * y;
		}

		return convexRing;
	}