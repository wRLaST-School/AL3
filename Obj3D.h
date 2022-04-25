#include "Model.h"
#include "Vec3.h"
class Obj3D {
public:
	Obj3D() {};
	Obj3D(WorldTransform wld, ViewProjection* vProj, unsigned int tex, Model* model);
	void Draw();

	WorldTransform wld;
	ViewProjection* vProj;
	unsigned int tex;
	Model* model;

	Vec3 front;

	float speed = 0.1f;
private:
};