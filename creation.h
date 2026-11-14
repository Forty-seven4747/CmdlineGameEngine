struct creation{
	int freq;
	char pose;//the null character means an empty slot
	string words;
	short x;
	short y;
	bool trig;
	unsigned long long tick;
	short nex;//nex and ney are not used for now
	short ney;
	vector<short> deltax;//deltax and deltay are step tables, one pair from each per move
	vector<short> deltay;
	int mdpoint;
	short dx;
	short dy;
	int roomat;
};
extern creation cre[cremax];
extern short creacur;//next free slot of cre
void crerase(int n);
