#pragma once
#include <tuple>

class config {
private:
	//車の移動制限
	int min_x; 
	int max_x;

	//車の移動速度
	int speed;

	//車のサイズ
	int size_x;
	int size_y;

	//画像類
	int road;
	int vehicle[8];

public:
	config(int,int,int,int,int);
	void load_graph();
	int get_back();
	int* get_vehicles();
	std::tuple<int,int> get_move_restrict();
	std::tuple<int, int> get_size_of_vehicle();
	int get_speed();
};