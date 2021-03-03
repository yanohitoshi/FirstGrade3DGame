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

	// モデルハンドルの取得.
	int GetModelHandle() { return model; }

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }

private:
	int	   model;	// モデルハンドル.
	VECTOR pos;			// ポジション.
	int model2;
	VECTOR pos2;
};
#endif//_BG_H

