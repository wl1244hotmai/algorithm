#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <functional>
#include <string>

using namespace std;

class solution_cross_river {
private:	
	int MONK_COUNT, MONSTER_COUNT;

	enum class BOAT_LOCATION {
		LOCAL,
		REMOTE,
	};

	enum class ACTION_NAME {
		ONE_MONSTER_GO,
		TWO_MONSTER_GO,
		ONE_MONK_GO,
		TWO_MONK_GO,
		ONE_MONSTER_ONE_MONK_GO,
		ONE_MONSTER_BACK,
		TWO_MONSTER_BACK,
		ONE_MONK_BACK,
		TWO_MONK_BACK,
		ONE_MONSTER_ONE_MONK_BACK,
	};

	struct ActionEffection {
		ACTION_NAME actionName;
		int Monk_move;
		int Monster_move;
		BOAT_LOCATION boatDirection;
		bool operator== (ActionEffection& other) {
			return (this->actionName == other.actionName &&
				this->Monk_move == other.Monk_move &&
				this->Monster_move == other.Monster_move &&
				this->boatDirection == other.boatDirection
				);
		}
	};

	struct ItemState {
		int local_monk;
		int local_monster;
		int remote_monk;
		int remote_monster;
		BOAT_LOCATION boatLocation;
		ActionEffection curAct;
		bool operator==(ItemState &other) {
			return (
				this->local_monk == other.local_monk &&
				this->local_monster == other.local_monster &&
				this->remote_monk == other.remote_monk &&
				this->remote_monster == other.remote_monster &&
				this->boatLocation == other.boatLocation
				);
		}
		bool canTakeAction(ActionEffection & ae) const
		{
			if (this->boatLocation == ae.boatDirection) 
				return false;
			if ((this->local_monk + ae.Monk_move) <  0||
				(this->local_monk + ae.Monk_move) > 3) 
				return false;
			if ((this->local_monster + ae.Monster_move) < 0 ||
				(this->local_monster + ae.Monster_move) > 3)
				return false;
			return true;
		}
		bool isValid() {
			if (local_monk!=0 && local_monk < local_monster || remote_monk!=0 && remote_monk < remote_monster) return false;
			return true;
		}
		bool isResult() {
			return (remote_monk == 3
				&& remote_monster == 3
				&& boatLocation == BOAT_LOCATION::REMOTE);
		}
	};

	vector<ActionEffection> actionEffections = vector<ActionEffection>({
		{ ACTION_NAME::ONE_MONSTER_GO , 0 , -1, BOAT_LOCATION::REMOTE },
		{ ACTION_NAME::TWO_MONSTER_GO , 0 , -2, BOAT_LOCATION::REMOTE },
		{ ACTION_NAME::ONE_MONK_GO , -1 , 0, BOAT_LOCATION::REMOTE },
		{ ACTION_NAME::TWO_MONK_GO , -2 , 0, BOAT_LOCATION::REMOTE },
		{ ACTION_NAME::ONE_MONSTER_ONE_MONK_GO , -1 , -1, BOAT_LOCATION::REMOTE },
		{ ACTION_NAME::ONE_MONSTER_BACK, 0 , 1, BOAT_LOCATION::LOCAL },
		{ ACTION_NAME::TWO_MONSTER_BACK , 0 , 2, BOAT_LOCATION::LOCAL },
		{ ACTION_NAME::ONE_MONK_BACK, 1 , 0, BOAT_LOCATION::LOCAL },
		{ ACTION_NAME::TWO_MONK_BACK , 2 , 0, BOAT_LOCATION::LOCAL },
		{ ACTION_NAME::ONE_MONSTER_ONE_MONK_BACK , 1 , 1, BOAT_LOCATION::LOCAL },
	});

	
public:

	bool makeActionNewState(const ItemState& current, ActionEffection& ae, ItemState& newState) {
		if (current.canTakeAction(ae)) {
			newState = current;
			newState.local_monk += ae.Monk_move;
			newState.local_monster += ae.Monster_move;
			newState.remote_monk -= ae.Monk_move;
			newState.remote_monster -= ae.Monster_move;
			newState.boatLocation = ae.boatDirection;
			newState.curAct = ae;
			return true;
		}
		return false;
	}

	bool IsProcessedState(deque<ItemState>& states, ItemState& newState) {
		deque<ItemState>::iterator it = states.end();
		it = find_if(states.begin(), states.end(), [&](ItemState& state) -> bool{
			if (state == newState) return true;
			else return false;
		});
		if (it == states.end())
			return false;
		else
			return true;
	}

	void searchOnAction(deque<ItemState>& states, ItemState& current, ActionEffection& ae) {
		ItemState newState;
		if (makeActionNewState(current, ae, newState)) {
			if (newState.isValid() && !IsProcessedState(states, newState)) {
				states.push_back(newState);
				searchState(states);
				states.pop_back();
			}
		}
	}

	void printResult(deque<ItemState>& states) {
		cout << "LOCAL MONK\t LOCAL MONSTER\t REMOTE_MONK\t REMOTE_MONSTER\t BOAT ¡ª MONK_MOVE LOCAL_MOVE BOAT_DIRECTION" << endl;
		for_each(states.begin(), states.end(), [](ItemState & state) {
			cout << state.local_monk << '\t'
				<< state.local_monster << '\t'
				<< state.remote_monk << '\t'
				<< state.remote_monster << '\t'
				<< (state.boatLocation == BOAT_LOCATION::LOCAL ? "LOCAL" : "REMOTE")
				<< state.curAct.Monk_move << '\t'
				<< state.curAct.Monster_move << '\t'
				<< (state.curAct.boatDirection == BOAT_LOCATION::LOCAL ? "LOCAL" : "REMOTE") << endl;
		});

	}

	void searchState(deque<ItemState>& states) {
		ItemState current = states.back();
		if (current.isResult()) {
			printResult(states);
			return;
		}
		for_each(actionEffections.begin(), actionEffections.end(), [&](ActionEffection &ae) {
			searchOnAction(states, current, ae);
		});
	}

	void func() {
		ItemState initial{ 3 ,3, 0, 0, BOAT_LOCATION::LOCAL };
		deque<ItemState> states;
		states.push_back(initial);
		searchState(states);
	}
};


