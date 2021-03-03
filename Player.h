#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "EffekseerForDXLib.h"

class Stage;
class Shot;
class Wall;
class Camera;
class TitleStage;

class Player
{
public:

	Player();
	~Player();

	//������
	void Init();
	//�X�V
	void Update(Stage& stage,Shot* shot[],Wall* wall[]);
	//�^�C�g���p
	void UpdateTitle(TitleStage &stage, Shot* shot[]);
	//�G���h�p
	void UpdateEnd();
	//�N���A�p
	void UpdateClear(Stage &stage);

	//�`��
	void Draw();
	void DrawEnd();
	void DrawTitle();
	//�����߂�
	void Back(Stage& stage);
	void BackTitle(TitleStage& stage);

	//------�t���O�֘A------//
	//�W�����v�t���O
	bool jumpFlag = true;
	//�d�̓t���O
	bool gravityFlag = true;
	//�ڒn����t���O
	bool isGround = false;
	//�����t���O
	bool aliveFlag = true;
	//�ǔ���t���O
	bool hitWallFlag = false;
	//�^�C�g���p�_���[�W�t���O
	bool tileDamageFlag = false;
	int damageCount;

	//����
	VECTOR dir;
	//�J�E���g�֘A
	int frameCount;
	int tiltCount;
	int hitCount;
	// ���f���n���h���̎擾.
	int GetModelHandle() { return model; }
	int GetplayingEffectHandle() { return playingEffectHandle; }

	//�Q�b�^�[�ƃZ�b�^�[
	void SetPos(const VECTOR set) { pos = set; }
	const float GetRote() const { return rote; }
	const VECTOR& GetPos() const { return pos; }
	const VECTOR& GetSize() const { return size; }

private:
	// ���f���n���h��
	int model;
	int model2;
	int model3;
	// �|�W�V����.
	VECTOR pos;
	//���f���̉�]�l
	float rote;
	float rote2;
	//�X���x
	float tilt;
	//���ۂɍ�p���鑬�x
	VECTOR vel;
	//�X�s�[�h
	float speed;
	//�T�C�Y
	VECTOR size;
	//�d��
	float gravity;
	//�G�t�F�N�g�ǂݍ��ݎ��̃n���h��
	int effectResourceHandle;
	//�Đ����̃G�t�F�N�g�̃n���h��
	int playingEffectHandle = -1;
	//�G�t�F�N�g�̍Đ����Ԃ���邽�߂̎���
	int time;
	//�G�t�F�N�g�̃|�W�V����
	VECTOR effectPos;

	float tmpRote;

	//SE�֘A
	int shotSeHandle;

};
#endif
