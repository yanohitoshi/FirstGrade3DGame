#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "EffekseerForDXLib.h"

class Stage;
class Shot;
class Player;
class Wall;
class Camera;
class TitleStage;

enum state
{
	HOMING = 0
	,REFLECTION = 1
	,SLOW = 2
};


class Enemy
{
public:
	Enemy();
	~Enemy();


	//������
	void Init(int modelhandle1, int modelhandle2, int modelhandle3,int modelhandle4);
	//�X�V
	void Update(Stage &stage, Player &player, Shot* shot[], Wall* wall[],Camera* camera);
	void UpdateTitle(TitleStage &stage, Player &player, Shot* shot[], Camera* camera);
	void UpdateClear(Stage &stage, Player &player, Shot* shot[], Wall* wall[], Camera* camera);

	//�`��
	void Draw();
	//�����߂�
	void Back(Stage &stage);
	//�G�l�~�[�̎��
	int enemyType = 0;

	//�^�C�g���p�Q�[���X�^�[�g�J�E���g
	int startCount;
	//------�t���O�֘A------//
	//�W�����v�t���O
	bool jumpFlag = true;
	//�d�̓t���O
	bool gravityFlag = true;
	//�ڒn����t���O
	bool isGround = false;
	//�����t���O
	bool aliveFlag = true;
	//���X�|�[���t���O
	bool respawnFlag = false;
	//�G���h�t���O
	bool clearFlag = false;
	//�����Z�b�g�t���O
	bool dirSetFlag = true;
	//�G�l�~�[�^�C�v�P�p�̃t���O
	bool type1Flag = true;
	//�Q�[���N���A���̃G�t�F�N�g�����p�t���O
	bool endEffectFlag = true;
	//�Q�[���J�n���܂��͎��ԂŋN�����邽�߂̃t���O
	bool startUpFlag = false;

	// ���f���n���h���̎擾.
	int GetModelHandle() { return model; }

	//getter
	const VECTOR& GetPos() const { return pos;}
	const VECTOR& GetSize() const { return size;}
	const float GetRote() const { return rote;}
	//setter
	void SetPos(const VECTOR set) { pos = set;}
	void SetVel(const VECTOR set) { vel = set; }


private:

	// ���f���n���h��
	int model;
	int model1;
	int model2;
	int model3;
	//�e�̃��f���n���h��
	int shadowModel;
	// �|�W�V����
	VECTOR pos;			
	//�e�p�̃|�W�V����
	VECTOR shadowPos;
	//���ۂɍ�p���鑬�x
	VECTOR vel;
	//�T�C�Y
	VECTOR size;
	//����
	VECTOR dir;
	//�v���C���[�Ɍ������x�N�g��
	VECTOR enemyToPlayer;
	//�X�s�[�h
	float speed;
	//�G�̐�
	const int enemyNum = 10;
	//�X���x
	float tilt;
	//��]�l
	float rote;

	//-----�J�E���g�֘A------//
	//���X�|�[���J�E���g
	int respawnCount;
	//�t���[���J�E���g
	int frameCount;
	//�X���p
	int tiltCount;
	//�G�l�~�[�^�C�v�P�p�J�E���g
	int type1Count;

	//--------�G�t�F�N�g�֘A---------//
	//�G�t�F�N�g�̃|�W�V����
	VECTOR effectPos;
	//�G�t�F�N�g�ǂݍ��ݎ��̃n���h��
	int effectResourceHandle;
	//�Đ����̃G�t�F�N�g�̃n���h��
	int playingEffectHandle;
	//�G�t�F�N�g�̍Đ����Ԃ���邽�߂̎���
	int time;

	//���ʉ��֘A
	int hitSE;
	int titleButHitSE;
	int titleHitSE;


};
#endif


