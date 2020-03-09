#include "MapView.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
	//vector<string> v{"v__v_v_v___v__v_v","#  # # #   #  # #","#  # # #   #  # #"};

	Map m("./maps/map1.map");

	MapView view(&m);

	view.draw();

}
