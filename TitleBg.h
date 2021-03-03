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

	// モデルハンドルの取得.
	int GetModelHandle() { return model; }

	// ポジションのgetter/setter.
	const VECTOR& GetPos() const { return pos; }
	void SetPos(const VECTOR set) { pos = set; }

private:
	int	   model;	// モデルハンドル.
	VECTOR pos;			// ポジション.

};
#endif

