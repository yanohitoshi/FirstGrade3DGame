#ifndef _TITLEBG_H_
#define _TITLEBG_H_

#include "EffekseerForDXLib.h"


class TitleBg
{
public:
	TitleBg();
	~TitleBg();
	void Init();
	void Updata();
	void Draw();

	// ���f���n���h���̎擾.
	int GetModelHandle() { return model; }

	// �|�W�V������getter/setter.
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }

private:
	int	   model;	// ���f���n���h��.
	VECTOR pos;			// �|�W�V����.

};
#endif

