#pragma once

#include "headers.h"
#include "player.h"
#include "assets.h"
#include "complex_shapes.h"
#include "camera.h"
#include "scenery.h"
#include "command.h"

#define sm_rnd() (rand() - 0.5f) / 255
constexpr auto GRAVITY = 1.0f;
constexpr auto FRICTION = 1.0f;
constexpr auto TOD_CARDINALITY = 6 ;
constexpr auto TRANSITION_RATE_TOD = 0.25f;
constexpr auto MAX_STROKE = 4;
constexpr auto THICKNESS = 8;

enum TOD { DAY, AFTERNOON, EVENING, NITE, DNITE, MORNING };

inline void operator++(TOD &ti, int)
{
	const int i = static_cast<int>(ti);
	ti = static_cast<TOD>((i + 1) % TOD_CARDINALITY);
}

class Platform {
private:
	Quad _body;
	Quad _outline;
public:
	Platform();
	Platform(Vec center, float width, float height, ColorSet color);

	friend class Player;
	friend class PlatformGroup;
};

class PlatformGroup {
private:
	vector<Platform> _platforms;
public:
	void render();
	PlatformGroup();

	friend class Player;
};

class RState;
class NextColorCommand;

class Level {
private:
	PlatformGroup _platforms;
	static PlayerMap _players;
	unique_ptr<SceneryGroup> _scenery;
public:
	virtual void render();
	virtual void gfx_handler();
	virtual void phys_handler();
	virtual void event_handler();
	void setScenery(SceneryGroup scenery);

	explicit Level();
	virtual ~Level() {}

	friend class CharacterSelectState;
	friend class LevelState;
	friend class LevelSelectState;
	friend class JumpCommand;
	friend class AttackCommand;
	friend class MoveLeftCommand;
	friend class MoveRightCommand;
	friend class StopCommand;
	friend class ChangeCharacterCommand;
	friend class AddCharacterCommand;
	friend class RemoveCharacterCommand;
	friend class PrevColorCommand;
	friend class NextColorCommand;

	//friend void NextColorCommand::execute(RState*);
};
