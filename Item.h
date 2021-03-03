#ifndef _ITEM_H_
#define _ITEM_H_
#include "EffekseerForDXLib.h"

class Stage;
class Player;

enum flagNum
{
	POWER_UP
	, POWER_DOWN
	,SPEED_UP
	,SPEED_DOWN
};

class Item
{
public:
	Item();
	~Item();
	//������
	void Init();
	//�X�V
	void Update(Stage &stage, Player &player);
	//�`��
	void Draw();
	//�����߂�
	void Back(Stage &stage);
	//�A�C�e�����ʂ̃t���O�X�C�b�`
	void flagSwith();

	//�����Ă���t���O
	int flagState = 0;

	//------�t���O�֘A------//
	//�d�̓t���O
	bool gravityFlag = true;
	//�ڒn����t���O
	bool isGround = false;
	//�����t���O
	bool aliveFlag = true;
	//���X�|�[���t���O
	bool respawnFlag = true;

	// ���f���n���h���̎擾.
	int GetModelHandle() { return model; }

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return pos; }
	const VECTOR& GetSize() const { return size; }
	void SetPos(const VECTOR set) { pos = set; }
	const float GetRote() const { return rote; }


private:
	int	   model;	// ���f���n���h��.
	VECTOR pos;			// �|�W�V����.
	float rote;

	//���ۂɍ�p���鑬�x
	VECTOR vel;
	//�T�C�Y
	VECTOR size;
	//����
	VECTOR dir;
	//���x
	float speed;

	//
	VECTOR tilt;

	//�J�E���g�֘A
	//���X�|�[���J�E���g
	int respawnCount;
	int frameCount;
	int tiltCount;
	//�G�t�F�N�g�ǂݍ��ݎ��̃n���h��
	int effectResourceHandle;
	//�Đ����̃G�t�F�N�g�̃n���h��
	int playingEffectHandle = -1;
	//�G�t�F�N�g�̍Đ����Ԃ���邽�߂̎���
	int time;
	//�G�t�F�N�g�̃|�W�V����
	VECTOR effectPos;



};
#endif

