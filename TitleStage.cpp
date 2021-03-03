#include "TitleStage.h"
#include "EffekseerForDXLib.h"


TitleStage::TitleStage()
{
}


TitleStage::~TitleStage()
{
	// ���f���̃A�����[�h.
	MV1DeleteModel(model);
}

//������
void TitleStage::Init()
{
	//-----�RD�֘A-----//
	//3D���f���̃��[�h
	model = MV1LoadModel("data/model/titleStage/titleStage.pmd");
	pos = VGet(0.0f, 200.0f, 50.0f);
	size = VGet(800.0f, 10.0f, 800.0f);
}
//�X�V
void TitleStage::Updata()
{
	//�X�e�[�W�̈ʒu�̐ݒ�
	MV1SetPosition(model, pos);

}
//�`��
void TitleStage::Draw()
{
	// �R�c���f���̃X�P�[���������L�΂�
	MV1SetScale(model, VGet(4.0f, 4.0f, 4.0f));
	//�X�e�[�W�̕`��
	MV1DrawModel(model);
}
