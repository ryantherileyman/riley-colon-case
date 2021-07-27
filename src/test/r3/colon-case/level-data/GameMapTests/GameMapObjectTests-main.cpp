
#include <assert.h>
#include <iostream>
#include <r3/colon-case/level-data/r3-colonCase-levelDefn.hpp>
#include <r3/colon-case/level-data/r3-colonCase-GameMap.hpp>

using namespace r3::colonCase;

GameMapObjectDefn createRectangleObjectDefn(const sf::Vector2f& topLeft, const sf::Vector2f& bottomRight) {
	GameMapObjectDefn result;
	result.objectType = GameMapObjectType::POPUP_TEXT;
	result.shape = GameMapObjectShape::RECTANGLE;
	result.position = topLeft;
	result.size = bottomRight - topLeft;
	result.key = "TestRectangle";
	return result;
}

GameMapObjectDefn createEllipseObjectDefn(const sf::Vector2f& center, const sf::Vector2f& radius) {
	GameMapObjectDefn result;
	result.objectType = GameMapObjectType::POPUP_TEXT;
	result.shape = GameMapObjectShape::ELLIPSE;
	result.position = center - radius;
	result.size = radius * 2.0f;
	result.key = "TestEllipse";
	return result;
}

bool testContains(const GameMapObjectDefn& objectDefn, const sf::Vector2f& point, bool expectedResult) {
	GameMapObject object(objectDefn);
	bool actualResult = object.contains(point);

	bool result = (actualResult == expectedResult);
	return result;
}

int main() {
	assert(testContains(createRectangleObjectDefn(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(2.0f, 3.0f)), sf::Vector2f(1.0f, 1.5f), true));
	assert(testContains(createRectangleObjectDefn(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(2.0f, 3.0f)), sf::Vector2f(0.0f, 0.0f), true));
	assert(testContains(createRectangleObjectDefn(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(2.0f, 3.0f)), sf::Vector2f(2.0f, 3.0f), true));
	assert(testContains(createRectangleObjectDefn(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(2.0f, 3.0f)), sf::Vector2f(-0.1f, 1.5f), false));
	assert(testContains(createRectangleObjectDefn(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(2.0f, 3.0f)), sf::Vector2f(2.1f, 1.5f), false));

	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(1.0f, 1.0f), true));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(0.0f, 1.0f), true));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(-0.01f, 1.0f), false));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(2.0f, 1.0f), true));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(2.01f, 1.0f), false));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(1.0f, 0.0f), true));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(1.0f, -0.01f), false));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(1.0f, 2.0f), true));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(1.0f, 2.01f), false));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(0.3f, 0.3f), true));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(0.29f, 0.29f), false));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(1.7f, 0.3f), true));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(1.71f, 0.29f), false));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(0.3f, 1.7f), true));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(0.29f, 1.71f), false));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(1.7f, 1.7f), true));
	assert(testContains(createEllipseObjectDefn(sf::Vector2f(1.0f, 1.0f), sf::Vector2f(1.0f, 1.0f)), sf::Vector2f(1.71f, 1.71f), false));

	std::cout << "All tests passed!\n";
	return 0;
}
