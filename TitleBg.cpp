#include "TitleBg.h"
#include "EffekseerForDXLib.h"



TitleBg::TitleBg()
{
}


TitleBg::~TitleBg()
{
}

void TitleBg::Init()
{
	// �R�c���f���̓ǂݍ���
	model = MV1LoadModel("data/model/skynao/skynao01/skynao.pmx");
	pos = VGet(0.0f, -1000.0f,0.0f);
}

void TitleBg::Updata()
{
	//�X�e�[�W�̈ʒu�̐ݒ�
	MV1SetPosition(model, pos);
}

void TitleBg::Draw()
{
	// �R�c���f���̊g��
	MV1SetScale(model, VGet(20.0f, 25.0f, 20.0f));
	//�X�e�[�W�̕`��
	MV1DrawModel(model);
}
