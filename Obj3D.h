#include "Model.h"
class Obj3D {
public:
	Obj3D(WorldTransform wld, ViewProjection* vProj, unsigned int tex, Model* model);
	void Draw();

	WorldTransform wld;
	ViewProjection* vProj;
	unsigned int tex;
	Model* model;
private:
};