#include "parts.h"
#include <cmath>

float ShapePart::computeDistance(const ShapePart& other_part) {
	sf::Vector2f diff = _coordinates - other_part.getCoordinates();
	return sqrt(diff.x*diff.x+diff.y*diff.y);
}

bool ShapePart::checkIntersection(const ShapePart& other_part) {
	float dist = computeDistance(other_part);
	return dist <= (_radius + other_part.getRadius()); 
}

bool ShapePart::checkIntersection(const ShapePart& other_part, float radius) {
	float dist = computeDistance(other_part);
	return dist <= (_radius + radius + other_part.getRadius()); 
}

sf::Vector2f ShapePart::computeAim(const ShapePart& other_part) {
	return (other_part.getCoordinates() - _coordinates)/computeDistance(other_part); 
}