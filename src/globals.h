#pragma once

/*
namespace globes{
	int SWIDTH = 1280;
	int SHEIGHT = 720;

	const int SPRITE_SCALE = 2.0f;
}*/


namespace sides {
	enum Side{TOP, BOTTOM, LEFT, RIGHT, NONE};

	inline Side getOppositeSide(Side side){
		return
			side == TOP ? BOTTOM:
			side == BOTTOM ? TOP:
			side == LEFT ? RIGHT:
			side == RIGHT ? LEFT:
			NONE;

	}
}
//DDIAGL, DDIAGR, UDIAGL, UDIAGR,
enum Direction{LEFT, RIGHT, UP, DOWN, STOPU, STOPL, STOPR, STOPD, STOPPED};
enum itemType{ABILITY, PASSIVE, SHIELD, WEAPON, MOVABLE, HEALTH};
enum apType{DAMAGE, HEAL, MOVEMENT};
enum aMoveType{TELEPORT, SPEED, NOTM};
enum wType{MELEE, PROJECTILE, HITSCAN};
enum menuStatus{PAUSED, UNPAUSED, MAIN, LEVELEDITOR, OPTIONS, GRAPHICS, AUDIO, BLANK};

