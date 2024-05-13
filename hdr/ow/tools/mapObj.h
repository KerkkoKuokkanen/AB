
#ifndef MAP_OBJ_H
# define MAP_OBJ_H

typedef struct s_Pos
{
	int x;
	int y;
}				t_Pos;

class MapObj
{
	public:
		virtual ~MapObj() {}
		bool done = false;
		t_Pos current = {0, 0};
		t_Pos last = {0, 0};
		virtual void Update() = 0;
		void MovePosition(int x, int y) {last = current; current = {x, y};};
};

#endif
