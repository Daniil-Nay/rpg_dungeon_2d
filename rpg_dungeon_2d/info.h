#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
int CurrentScoreInfo(int const &score) {
	int u_text = 2;
	if (score <= 5) {
		u_text = 2;
	}
	if (score > 5){
		u_text = 1;
	}
	return u_text;
}

string UserInfoText(int const &user_state) {
	string user_mission = "";
	switch (user_state) {
	case 2:
		user_mission = "Uh-oh! Someone gets going! \nKeep on collecting coins to complete the game";
	case 1:
		user_mission = "To finish the game, collect coins! \nShift is to speed up, E to interact,\nLClickMouse to attack!";
	}
	return user_mission;
};
