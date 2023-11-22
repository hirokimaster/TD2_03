#include "Model/Model.h"
#include <cassert>
#include "Input.h"
#include "PlayerBullet.h"
using namespace std;

class Player {
public:

	Player();
	~Player();

	void Initialize(Model* model, uint32_t texHandle);

	void Update();

	void Draw(const ViewProjection& viewProjection);

	void Rotate();

	void Attack();

private:

	Model* model_ = nullptr;
	unique_ptr<Model> bulletModel_;
	WorldTransform worldTransform_ = {};
	const float moveSpeed = 0.2f;
	unique_ptr<PlayerBullet> bullet_;

};