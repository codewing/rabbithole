#include "TerrainUtils.hpp"

#include <math.h>
#include "LevelGenerator.hpp"

std::shared_ptr<sre::Mesh> TerrainUtils::generateMesh(const std::vector<b2Vec2>& chain) {
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

void TerrainUtils::subtract(const ring_t& source, const ring_t& subtrahend, ring_collection_t& result)
{
	boost::geometry::difference(source, subtrahend, result);
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

float TerrainUtils::coserp(float x, float y, float t) {
	float tetha = t * glm::radians(180.f);
	float f = (1 - cos(tetha)) * 0.5;
	return x * (1 - f) + y * f;
}

std::vector<float> TerrainUtils::perlinNoise1D(std::vector<int> xPoints, int ampl, int wavelen) {
	int x = 0;
	int h = 0;
	int y;

	float a = (static_cast<float>(rand()) / RAND_MAX + 1);
	float b = (static_cast<float>(rand()) / RAND_MAX + 1);

	std::vector<float> result;

	for (int i = 0; i < xPoints.size(); i++) {
		if (xPoints.at(i) % wavelen == 0) {
			a = b;
			b = (static_cast<float>(rand()) / RAND_MAX + 1);
			y = h / 2 + a * ampl;
		}
		else {
			y = h / 2 + coserp(a, b, static_cast<float>((xPoints.at(i) % wavelen)) / wavelen) * ampl;
		}
		result.push_back(y);
	}

	return result;
}

std::vector<std::vector<float>> TerrainUtils::generateNoise(std::vector<int> xPoints, int ampl, int wavelen, int octaves, int divisor) {
	std::vector<std::vector<float>> result;
	for (int i = 0; i < octaves; i++) {
		result.push_back(perlinNoise1D(xPoints, ampl, wavelen));
		ampl /= divisor;
		wavelen /= divisor;
	}
	return result;
}

std::vector<b2Vec2> TerrainUtils::combineNoise(std::vector<int> xPoints, std::vector<std::vector<float>> noiseOctaves) {
	std::vector<b2Vec2> result;
	float yTotal;

	for (int i = 0; i < xPoints.size(); i++) {
		yTotal = 0;
		for (auto octave : noiseOctaves) {
			yTotal += octave.at(i);
		}
		result.push_back({static_cast<float>(xPoints.at(i)), yTotal});
	}
	return result;
}

// Curves the edges of the terrain to give it the shape of an island.
void TerrainUtils::reshapeEdges(std::vector<b2Vec2>& terrain) {
	float curvatureLength = (LevelGenerator::roundTerrainRatio / 2) * terrainImageSize;
	float angle, step;

	for (int i = 0; i < (curvatureLength/16); i++) {
		step = i / (curvatureLength/16);
		angle = glm::radians(step * 90.f);

        auto xPrev = terrain.at(i).x;
		auto yPrev = terrain.at(i).y * sin(angle);

		terrain.erase(terrain.begin() + i);
		terrain.insert(terrain.begin() + i, b2Vec2{ xPrev, yPrev });

		xPrev = terrain.at(terrain.size() - 1 - i).x;
        yPrev = terrain.at(terrain.size() - 1 - i).y * sin(angle);

        terrain.erase(terrain.end() - 1 - i);
		terrain.insert(terrain.end() - i, b2Vec2{ xPrev, yPrev });
	}
}

void TerrainUtils::simplify(ring_collection_t& rings) {
	std::transform(rings.begin(), rings.end(), rings.begin(), [](const ring_t& r){
		ring_t simplified;
		boost::geometry::simplify(r, simplified, 0.05 * PhysicsSystem::PHYSICS_SCALE);
		// Discard self intersecting rings
		return boost::geometry::intersects(simplified) ? r : simplified;
	});
}
