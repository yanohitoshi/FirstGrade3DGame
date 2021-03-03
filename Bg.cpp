#include "Bg.h"
#include "EffekseerForDXLib.h"



Bg::Bg()
{
}

Bg::~Bg()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(model);
	MV1DeleteModel(model2);

}

void Bg::Init()
{

	//�R�c���f���̓ǂݍ���
	model = MV1LoadModel("data/model/skynao/skynao01/skynao.pmx");
	model2 = MV1LoadModel("data/model/bgGrund.x");

	pos = VGet(0.0f, -1000.0f, 0.0f);
	pos2 = VGet(0.0f, -1000.0f, 0.0f);

}

void Bg::Updata()
{
	//�X�e�[�W�̈ʒu�̐ݒ�
	MV1SetPosition(model, pos);
	//�X�e�[�W�̈ʒu�̐ݒ�
	MV1SetPosition(model2, pos2);
}

void Bg::Draw()
{
	// �R�c���f���̊g��
	MV1SetScale(model, VGet(25.0f, 25.0f, 25.0f));
	//�X�e�[�W�̕`��
	MV1DrawModel(model);
	// �R�c���f���̊g��
	MV1SetScale(model2, VGet(25.0f, 25.0f, 25.0f));
	//�X�e�[�W�̕`��
	MV1DrawModel(model2);
}
