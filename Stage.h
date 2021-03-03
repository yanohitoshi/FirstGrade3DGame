#ifndef _STAGE_H_
#define _STAGE_H_
#include "EffekseerForDXLib.h"

class Stage
{
public:
	//�R���X�g���N�^
	Stage();
	//�f�X�g���N�^
	~Stage();

	//������
	void Init();
	//�X�V
	void Updata();
	//�`��
	void Draw();

	// ���f���n���h���̎擾.
	int GetModelHandle() { return model; }

	//�Q�b�^�[�ƃZ�b�^�[
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }
	const VECTOR& GetSize() const { return size; }

private:
	//���f���n���h��
	int	   model;
	//	�|�W�V����
	VECTOR pos;
	//�T�C�Y
	VECTOR size;

};
#endif
