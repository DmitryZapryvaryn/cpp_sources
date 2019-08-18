#include "geo2d.h"
#include "game_object.h"

#include "test_runner.h"

#include <vector>
#include <memory>

using namespace std;

// CRTP - static polymorphism
// https://habr.com/ru/post/210894/
template<typename T>
struct Collider : GameObject {
	bool Collide(const GameObject& that) const final override {
		return that.CollideWith(static_cast<const T&>(*this));
	}
};

// class Derived : public Base<Derived>
class Unit final : public Collider<Unit> {
public:
	explicit Unit(geo2d::Point position) : position_(position) {}

	geo2d::Point getPosition() const;

	bool CollideWith(const Unit& that) const override;
	bool CollideWith(const Building& that) const override;
	bool CollideWith(const Tower& that) const override;
	bool CollideWith(const Fence& that) const override;

private:
	geo2d::Point position_;
};

class Building final : public Collider<Building> {
public:
	explicit Building(geo2d::Rectangle geometry) : geometry_(geometry) {}

	geo2d::Rectangle getGeometry() const;

	bool CollideWith(const Unit& that) const override;
	bool CollideWith(const Building& that) const override;
	bool CollideWith(const Tower& that) const override;
	bool CollideWith(const Fence& that) const override;

private:
	geo2d::Rectangle geometry_;
};

class Tower final : public Collider<Tower> {
public:
	explicit Tower(geo2d::Circle geometry) : geometry_(geometry) {}

	geo2d::Circle getGeometry() const;

	bool CollideWith(const Unit& that) const override;
	bool CollideWith(const Building& that) const override;
	bool CollideWith(const Tower& that) const override;
	bool CollideWith(const Fence& that) const override;

private:
	geo2d::Circle geometry_;
};

class Fence final : public Collider<Fence> {
public:
	explicit Fence(geo2d::Segment geometry) : geometry_(geometry) {}

	geo2d::Segment getGeometry() const;

	bool CollideWith(const Unit& that) const override;
	bool CollideWith(const Building& that) const override;
	bool CollideWith(const Tower& that) const override;
	bool CollideWith(const Fence& that) const override;

private:
	geo2d::Segment geometry_;
};

bool Collide(const GameObject& first, const GameObject& second) {
	if (&first == &second) {
		return true;
	}

	return first.Collide(second);
}

geo2d::Point Unit::getPosition() const
{
	return position_;
}

bool Unit::CollideWith(const Unit& that) const {
	return geo2d::Collide(position_, that.getPosition());
}

bool Unit::CollideWith(const Building& that) const {
	return geo2d::Collide(position_, that.getGeometry());
}

bool Unit::CollideWith(const Tower& that) const {
	return geo2d::Collide(position_, that.getGeometry());
}

bool Unit::CollideWith(const Fence& that) const {
	return geo2d::Collide(position_, that.getGeometry());
}

geo2d::Rectangle Building::getGeometry() const { return geometry_; }

bool Building::CollideWith(const Unit& that) const {
	return geo2d::Collide(geometry_, that.getPosition());
}

bool Building::CollideWith(const Building& that) const {
	return geo2d::Collide(geometry_, that.getGeometry());
}

bool Building::CollideWith(const Tower& that) const {
	return geo2d::Collide(geometry_, that.getGeometry());
}

bool Building::CollideWith(const Fence& that) const {
	return geo2d::Collide(geometry_, that.getGeometry());
}

geo2d::Circle Tower::getGeometry() const { return geometry_; }

bool Tower::CollideWith(const Unit& that) const {
	return geo2d::Collide(geometry_, that.getPosition());
}

bool Tower::CollideWith(const Building& that) const {
	return geo2d::Collide(geometry_, that.getGeometry());
}

bool Tower::CollideWith(const Tower& that) const {
	return geo2d::Collide(geometry_, that.getGeometry());
}

bool Tower::CollideWith(const Fence& that) const {
	return geo2d::Collide(geometry_, that.getGeometry());
}

geo2d::Segment Fence::getGeometry() const { return geometry_; }

bool Fence::CollideWith(const Unit& that) const {
	return geo2d::Collide(geometry_, that.getPosition());
}

bool Fence::CollideWith(const Building& that) const {
	return geo2d::Collide(geometry_, that.getGeometry());
}

bool Fence::CollideWith(const Tower& that) const {
	return geo2d::Collide(geometry_, that.getGeometry());
}

bool Fence::CollideWith(const Fence& that) const {
	return geo2d::Collide(geometry_, that.getGeometry());
}

void TestAddingNewObjectOnMap() {
	// Юнит-тест моделирует ситуацию, когда на игровой карте уже есть какие-то объекты,
	// и мы хотим добавить на неё новый, например, построить новое здание или башню.
	// Мы можем его добавить, только если он не пересекается ни с одним из существующих.
	using namespace geo2d;

	const vector<shared_ptr<GameObject>> game_map = {
	  make_shared<Unit>(Point{3, 3}),
	  make_shared<Unit>(Point{5, 5}),
	  make_shared<Unit>(Point{3, 7}),
	  make_shared<Fence>(Segment{{7, 3}, {9, 8}}),
	  make_shared<Tower>(Circle{Point{9, 4}, 1}),
	  make_shared<Tower>(Circle{Point{10, 7}, 1}),
	  make_shared<Building>(Rectangle{{11, 4}, {14, 6}})
	};

	for (size_t i = 0; i < game_map.size(); ++i) {
		Assert(
			Collide(*game_map[i], *game_map[i]),
			"An object doesn't collide with itself: " + to_string(i)
		);

		for (size_t j = 0; j < i; ++j) {
			Assert(
				!Collide(*game_map[i], *game_map[j]),
				"Unexpected collision found " + to_string(i) + ' ' + to_string(j)
			);
		}
	}

	auto new_warehouse = make_shared<Building>(Rectangle{ {4, 3}, {9, 6} });
	ASSERT(!Collide(*new_warehouse, *game_map[0]));
	ASSERT(Collide(*new_warehouse, *game_map[1]));
	ASSERT(!Collide(*new_warehouse, *game_map[2]));
	ASSERT(Collide(*new_warehouse, *game_map[3]));
	ASSERT(Collide(*new_warehouse, *game_map[4]));
	ASSERT(!Collide(*new_warehouse, *game_map[5]));
	ASSERT(!Collide(*new_warehouse, *game_map[6]));

	auto new_defense_tower = make_shared<Tower>(Circle{ {8, 2}, 2 });
	ASSERT(!Collide(*new_defense_tower, *game_map[0]));
	ASSERT(!Collide(*new_defense_tower, *game_map[1]));
	ASSERT(!Collide(*new_defense_tower, *game_map[2]));
	ASSERT(Collide(*new_defense_tower, *game_map[3]));
	ASSERT(Collide(*new_defense_tower, *game_map[4]));
	ASSERT(!Collide(*new_defense_tower, *game_map[5]));
	ASSERT(!Collide(*new_defense_tower, *game_map[6]));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestAddingNewObjectOnMap);
	return 0;
}