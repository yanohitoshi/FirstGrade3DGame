#ifndef _TITLESTAGE_H_
#define _TITLESTAGE_H_
#include "EffekseerForDXLib.h"

class TitleStage
{
public:
	TitleStage();
	~TitleStage();
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
	//3D�|�W�V����
	VECTOR pos;
	//�T�C�Y
	VECTOR size;
	//���f��
	int model;

};
#endif

