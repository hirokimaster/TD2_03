#include "Model/Model.h"
#include <cassert>
#include "Input.h"
#include "PlayerBullet.h"
using namespace std;

class Player {
public:

	void Initialize(Model* model, uint32_t texHandle);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void Rotate();

	void Attack();

private:

	Model* model_ = nullptr;
	WorldTransform worldTransform_ = {};
	const float moveSpeed = 0.2f;

};