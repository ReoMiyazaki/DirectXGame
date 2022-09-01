#include "Enemy.h"
#include "Player/Player.h"

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
	coolTimer -= 0.1f;

	assert(player_);
	// �e�̑��x
	const float kBulletSpeed = 1.0f;

	//�v���C���[�̃��[���h���W�̎擾
	Vector3 playerPosition;
	playerPosition = player_->GetWorldPosition();
	//�G�̃��[���h���W�̎擾
	Vector3 enemyPosition;
	enemyPosition = GetWorldPosition();

	Vector3 distance(0, 0, 0);

	//�����x�N�g�������߂�
	distance.x = playerPosition.x - enemyPosition.x;
	distance.y = playerPosition.y - enemyPosition.y;
	distance.z = playerPosition.z - enemyPosition.z;

	//���������߂�
	Vector3 Length(distance);
	//���K��
	Vector3 Normalize(distance);
	//�x�N�g���̒�����,�����ɍ��킹��
	distance *= kBulletSpeed;	//���ꂪ���x�ɂȂ�

	// �e�𐶐����A������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();

	//�N�[���^�C�����O�ɂȂ����Ƃ�
	if (coolTimer <= 0)
	{
		// �G�L�����̍��W���R�s�[
		Vector3 position = worldTransform_.translation_;
		Vector3 velocity(0, 0, kBulletSpeed);
		newBullet->Initialize(model_, position, velocity);
		// �e��o�^����
		bullets_.push_back(std::move(newBullet));
		coolTimer = 20.0f;
	}
}

void Enemy::OnCollision() {}



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
	DeleteBullet();
	// �e�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) { bullet->Update(); }

	// �ł��t���O�̗������e���폜
//	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {return bullet->IsDead(); });
}

void Enemy::DeleteBullet()
{
	// �f�X�t���O�̗������e���폜
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