#pragma once

#include "weapon.h"

class Shooter: public Weapon{
public:
	Shooter();
	virtual ~Shooter();

	void loadProjIMG();
	Projectile getProjectile(float xmove, float ymove);

	int getAmmo();
	void updateAmmo(int ammo);

private:
	int _ammo;

	Projectile _projectile;
};
