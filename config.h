#pragma once
#include <tuple>

class config {
private:
	//�Ԃ̈ړ�����
	int min_x; 
	int max_x;

	//�Ԃ̈ړ����x
	int speed;

	//�Ԃ̃T�C�Y
	int size_x;
	int size_y;

	//�摜��
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