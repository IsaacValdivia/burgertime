#include "MapView.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int main() {
	Map m("./maps/map5.map");

	MapView view(&m);

	view.draw();

}
