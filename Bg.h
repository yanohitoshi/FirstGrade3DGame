#ifndef _BG_H_
#define _BG_H_

#include "EffekseerForDXLib.h"

class Bg
{
public:
	Bg();
	~Bg();

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
	int model2;
	VECTOR pos2;
};
#endif//_BG_H

