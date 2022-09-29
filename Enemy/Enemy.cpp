#include "Enemy.h"
#include "Player/Player.h"

using namespace MathUtility;

void Enemy::Initialize(Model* model, uint32_t textureHandle)
{

	// �����V�[�h������
	std::random_device seed_gen;
	// �����Z���k�E�c�C�X�^�[�̗����G���W��
	std::mt19937_64 engin(seed_gen());
	// �����͈͂̎w��
	std::uniform_real_distribution<float> trans(-10, 10);

	// NULL�|�C���^�`�F�b�N
	assert(model);
	// �����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	this->model_ = model;
	this->textureHandle_ = textureHandle;
	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	worldTransform_.translation_ = { trans(engin), trans(engin), 50 };
}

void Enemy::Approach()
{
	//�ڋߑ��x
	Vector3 approach_ = { 0.0f, 0.0f, -0.1f };

	worldTransform_.translation_ += approach_;
	//����̈ʒu�ɓ��B�����痣�E
	if (worldTransform_.translation_.z <= 0.0f)
	{
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave()
{
	//���E���x
	Vector3 leave_ = { -0.15f,0.1f,0.1f };

	worldTransform_.translation_ += leave_;
}

void Enemy::Fire()
{
	dalayTimer -= 0.1f;

	// �e�̑��x
	const float kBulletSpeed = 1.0f;


	assert(player_);

	Vector3 distance(0, 0, 0);


	//�v���C���[�̃��[���h���W�̎擾
	Vector3 playerPosition = player_->GetWorldPosition();
	//�G�̃��[���h���W�̎擾
	Vector3 enemyPosition = GetWorldPosition();

	//�����x�N�g�������߂�
	distance = playerPosition - enemyPosition;

	//���������߂�
	Vector3Length(distance);
	//���K��
	Vector3Normalize(distance);
	//�x�N�g���̒�����,�����ɍ��킹��
	distance *= kBulletSpeed;	//���ꂪ���x�ɂȂ�

	if (dalayTimer <= 0) {

		// �e�𐶐����A������
		std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_, distance);
		// �e��o�^����
		bullets_.push_back(std::move(newBullet));
		dalayTimer = 25.0f;
	}
}

void Enemy::UpDate()
{
	MyFunc::Matrix4(worldTransform_, 0);
	switch (phase_) {
	case Phase::Approach://�ڋ߃t�F�[�Y
	default:
		//�ړ�
		Approach();
		break;

	case Phase::Leave://���E�t�F�[�Y
		Leave();
		break;
	}
	Fire();
	// �e�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) { bullet->Update(); }

	// �ł��t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {return bullet->IsDead(); });
}

void Enemy::Draw(ViewProjection viewProjection)
{
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
	// �e�`��
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) { bullet->Draw(viewProjection); }
}

Vector3 Enemy::GetWorldPosition()
{
	//���[���h���W�����邽�߂̕ϐ�
	Vector3 worldPos;

	//���[���h�s��̕��s�ړ��������擾
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}