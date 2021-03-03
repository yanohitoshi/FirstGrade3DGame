#include "Stage.h"
#include "EffekseerForDXLib.h"



Stage::Stage()
{
}


Stage::~Stage()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(model);
}

//������
void Stage::Init()
{
	// �R�c���f���̓ǂݍ���
	model = MV1LoadModel("data/model/stage5.x");
	pos = VGet(0.0f, 0.0f, 0.0f);
	size = VGet(1700.0f, 60.0f, 1700.0f);

}
//�X�V
void Stage::Updata()
{
	//�X�e�[�W�̈ʒu�̐ݒ�
	MV1SetPosition(model, pos);
}
//�`��
void Stage::Draw()
{
	//�X�e�[�W�̕`��
	MV1DrawModel(model);
}
