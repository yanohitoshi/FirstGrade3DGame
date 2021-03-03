#include "Wall.h"
#include "Time.h"
#include "EffekseerForDXLib.h"



Wall::Wall()
{
}


Wall::~Wall()
{
	// モデルのアンロード.
	MV1DeleteModel(model1);
	MV1DeleteModel(model2);
}

//初期化
void Wall::Init()
{
	// ３Ｄモデルの読み込み
	//横壁
	model1 = MV1LoadModel("data/model/wall2.x");
	//縦壁
	model2 = MV1LoadModel("data/model/wall.x");
	//実際に使用するサイズ
	size = VGet(0.0f, 0.0f, 0.0f);
	//横壁サイズ
	size1 = VGet(1535.0f, 50.0f, 50.0f);
	//縦壁サイズ
	size2 = VGet(20.0f, 50.0f, 1550.0f);
	//ポジション初期化
	pos = VGet(0.0f, 0.0f, 0.0f);
	//カウント関連
	wallCount = 0;
	preWallCount = 0;
	speed = 0.5f;
}
//更新
void Wall::Update()
{

	//壁移動の予備動作
	if (TIME_INSTANCE.countDown <= 53 && TIME_INSTANCE.countDown >= 50 ||
		TIME_INSTANCE.countDown <= 33 && TIME_INSTANCE.countDown >= 30 ||
		TIME_INSTANCE.countDown <= 13 && TIME_INSTANCE.countDown >= 10)
	{
		if (flag == true)
		{
			if (model == model1 && preWallCount == 0)
			{
				pos.z += 3.0f;
			}
			if (model == model2)
			{
				pos.x += 3.0f;
			}
			flag = false;
		}
		if (model == model1 && pos.z <= 0.0f)
		{
			if (preWallCount % 10 == 0)
			{
				pos.z -= 3.0f;
			}
			if (preWallCount % 20 == 0)
			{
				pos.z += 6.0f;
			}
		}
		if (model == model1 && pos.z >= 0.0f)
		{
			if (preWallCount % 10 == 0)
			{
				pos.z -= 3.0f;
			}
			if (preWallCount % 20 == 0)
			{
				pos.z += 6.0f;
			}
		}

		if (model == model2 && pos.x <= 0.0f)
		{
			if (preWallCount % 10 == 0)
			{
				pos.x -= 3.0f;
			}
			if (preWallCount % 20 == 0)
			{
				pos.x += 6.0f;
			}
		}
		if (model == model2 && pos.x >= 0.0f)
		{
			if (preWallCount % 10 == 0)
			{
				pos.x -= 3.0f;
			}
			if (preWallCount % 20 == 0)
			{
				pos.x += 6.0f;
			}
		}
		++preWallCount;
	}
	//時間が来たら壁を移動
	if (TIME_INSTANCE.countDown <= 50 && TIME_INSTANCE.countDown >= 40)
	{
		if (wallState == UP)
		{
			if (pos.z >= 600.0f)
			{
				pos.z -= speed;	
			}
		}
		if (wallState == DOWN)
		{
			if (pos.z <= -600.0f)
			{
				pos.z += speed;
			}
		}
		if (wallState == RIGHT)
		{
			if (pos.x >= 610.0f)
			{
				pos.x -= speed;
			}
		}
		if (wallState == LEFT)
		{
			if (pos.x <= -610.0f)
			{
				pos.x += speed;
			}
		}
	}

	if (TIME_INSTANCE.countDown <= 30 && TIME_INSTANCE.countDown >= 20)
	{
		if (wallState == UP)
		{
			if (pos.z >= 450.0f)
			{
				pos.z -= speed;
			}
		}
		if (wallState == DOWN)
		{
			if (pos.z <= -450.0f)
			{
				pos.z += speed;
			}
		}
		if (wallState == RIGHT)
		{
			if (pos.x >= 460.0f)
			{
				pos.x -= speed;
			}
		}
		if (wallState == LEFT)
		{
			if (pos.x <= -460.0f)
			{
				pos.x += speed;
			}
		}
	}
	if (TIME_INSTANCE.countDown <= 10 && TIME_INSTANCE.countDown >= 0)
	{
		if (wallState == UP)
		{
			if (pos.z >= 200.0f)
			{
				pos.z -= speed;
			}
		}
		if (wallState == DOWN)
		{
			if (pos.z <= -200.0f)
			{
				pos.z += speed;
			}
		}
		if (wallState == RIGHT)
		{
			if (pos.x >= 210.0f)
			{
				pos.x -= speed;
			}
		}
		if (wallState == LEFT)
		{
			if (pos.x <= -210.0f)
			{
				pos.x += speed;
			}
		}
	}

	if (TIME_INSTANCE.countDown == 13)
	{
		MV1SetDifColorScale(model, GetColorF(1.0f, 0.0f, 0.0f, 100.0f));

	}

}
//描画
void Wall::Draw()
{
	//壁1の位置の設定
	MV1SetPosition(model, pos);
	//壁1の描画
	MV1DrawModel(model);

}



