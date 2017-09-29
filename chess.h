namespace Chess
{
	void re_turn();
	void init();
	void graph();
	int vvod();
	int correct(int i0, int j0, int i1, int j1);
	void turns();
	bool knock(int i0, int j0);
	int move(int car);
	bool check();
	void turn_pawn(int i, int j);
	void turn_rook(int i0, int j0);
	void turn_knight(int i0, int j0);
	void turn_bishop(int i0, int j0);
	void turn_queen(int i0, int j0);
	void turn_king(int i0, int j0);
	void mass_load_castle(int k, int i0);
	void mass_load(int i, int j, int i0, int j0);
	void mass_load_king(int i, int j, int i0, int j0);
	void mass_load_pass(int i, int j, int i0, int j0);
	void intel(int skill);
	int power_vs(int power, int power_0);
	int estimate();
	void var_restore();
	void var_load();
	void back_move(int car);
}