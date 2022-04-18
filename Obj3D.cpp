#include "Obj3D.h"

Obj3D::Obj3D(WorldTransform wld, ViewProjection* vProj, unsigned int tex, Model* model):wld(wld),vProj(vProj),tex(tex),model(model)
{
	front = Vec3(0, 0, 1);
}

void Obj3D::Draw()
{
	model->Draw(wld, *vProj, tex);
}
