#ifndef _WALL_H_
#define _WALL_H_
#include "EffekseerForDXLib.h"

enum WallState
{
	RIGHT = 0
	,LEFT = 1
	,UP = 2
	,DOWN = 3
};

class Wall
{
public:
	//�R���X�g���N�^
	Wall();
	//�f�X�g���N�^
	~Wall();
	//������
	void Init();
	//�X�V
	void Update();
	//�`��
	void Draw();

	const int wallNum = 4;
	bool flag = true;

	// ���f���n���h���̎擾.
	int GetModelHandle1() { return model1; }
	int GetModelHandle2() { return model2; }
	//�Q�b�^�[�ƃZ�b�^�[
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }
	void SetModelHandole(int set) { model = set; }
	const VECTOR& GetSize() const { return size; }
	const VECTOR& GetSize1() const { return size1; }
	const VECTOR& GetSize2() const { return size2; }
	void SetSize(const VECTOR set) { size = set; }

	int wallState;
private:
	//���f���n���h��
	int model;
	int model1;
	int model2;
	//�|�W�V����
	VECTOR pos;
	//���x
	VECTOR vel;
	//�T�C�Y
	VECTOR size;
	VECTOR size1;
	VECTOR size2;
	//�J�E���g
	int wallCount;
	int preWallCount;
	float speed;

};
#endif
