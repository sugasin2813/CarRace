#include <tuple>
#include "config.h"
#include "DxLib.h"

config::config(int max=290,int min=39, int speed=2, int size_x=68, int size_y=120) {
	this->max_x = max;
	this->min_x = min;
	this->speed = speed;
	this->size_x = size_x;
	this->size_y = size_y;
	config::load_graph();
}

void config::load_graph() {
	this->road = DxLib::LoadGraph("./img/road.jpg");
	DxLib::LoadDivGraph("./img/vehicles.png", 8, 4, 2, 589, 902, this->vehicle);
}

int config::get_back() {
	return this->road;
}

int* config::get_vehicles() {
	return this->vehicle;
}

std::tuple<int,int> config::get_move_restrict() {
	return std::forward_as_tuple(this->max_x, this->min_x);
}

std::tuple<int, int> config::get_size_of_vehicle() {
	return std::forward_as_tuple(this->size_x, this->size_y);
}

int config::get_speed() {
	return this->speed;
}