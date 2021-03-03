#ifndef _SHOT_H_
#define _SHOT_H_
#include "EffekseerForDXLib.h"

class Player;
class Wall;

class Shot
{
public:

	Shot();
	~Shot();

	//������
	void Init();
	//�X�V
	void Update(Player &player, Wall* wall[]);
	//�^�C�g���p�X�V
	void UpdateTitle(Player &player);
	//�`��
	void Draw();

	//���ۂɍ�p���鑬�x
	VECTOR vel;

	//------�t���O�֘A------//
	//�t���O
	bool attackflag;
	bool moveFlag;
	//�U���ҋ@�t���O
	bool reAttackFlag;
	bool firstShotFlag;
	//�J�E���g�֘A
	int attackCount;


	//�G�t�F�N�g�̓ǂݍ��ݗp�n���h��
	int effectResourceHandle;

	// ���f���n���h���̎擾.
	int GetModelHandle() { return model; }

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }
	const VECTOR& GetSize() const { return size; }
	void SetDir(const VECTOR set) { dir = set; }
	const VECTOR& GetDir() const { return tmpDir; }

	//�|�W�V����
	VECTOR pos;

	const int shotNum = 3;

private:

	//���f���n���h��
	int	 model;
	//�T�C�Y
	VECTOR size;
	//����
	VECTOR dir;
	//���p���o�����߂�VECTOR
	VECTOR upDir;
	//��]
	VECTOR rote;
	//�X�s�[�h
	float speed;

	//�t���[���J�E���g
	int frameCount;

	//�G�t�F�N�g�̍Đ����̃n���h��
	int playingEffectHandle = -1;
	//�G�t�F�N�g���Đ����邽�߂̎���
	int time;
	//�G�t�F�N�g�̃|�W�V����
	VECTOR effectPos;
	//
	VECTOR tmpDir;

	//�N�H�[�^�j�I���֘A
	//��
	VECTOR axis;
	MATRIX mat;
	double radian;
};
#endif
