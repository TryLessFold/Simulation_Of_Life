#include <SFML\Graphics.hpp>
const int HEIGHT_MAP = 36;//������ ����� ������
const int WIDTH_MAP = 64;//������ ����� ������ 

sf::String TileMap[WIDTH_MAP] = {
	"2222222222222222222222222222222222222222222222222222222222222222",
	"2222222222222222222222222222222222222222222222222222222222222222",
	"2222222222222222222222222222222222222222222222222222222222222222",
	"2222222222222222222222222222222222222222222222222222222222222222",
	"2222222222222222222222222222222222222222222222222222222222222222",
	"2222222222222222222222222222222222222222222222222222000000000000",
	"0222222222222222222222222222222222222222222200000000000000000000",
	"0002222222222222222220000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000011111111111111111111111111111111",
	"0000000000000000000000000001111111111111111111111111111111111111",
	"0000000000000000000011111111111111111110000000000000000000000000",
	"1111111111111111111111111111111110000000000000000000000000000000",
	"1111111111111111111111111110000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000002200000000000000000000000000000000000000000000000000",
	"0000000002222222200000000000000000000000000000000000000000000000",
	"0000002222222222222000000000000000000000000000000000000000000000",
	"0000222222222222222222200000000000000000000000000000000000000000",
	"0000000000222222222220000000000000000000000000000000000000000000",
	"0000000000000022222200000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000"	
};
sf::String Objects[WIDTH_MAP] = {
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"00000000000-00000000000000000000*0000000000000000000000000000000",
	"00000000000000000000000000000000=|000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"00000000000+0000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000070000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000007000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000888888000000000000000000000000000000000",
	"0000000000000000000000000330000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000",
	"0000000000000000000000000000000000000000000000000003000000000000",
	"0000000000000000000000000000000000000000000000000000300000000000",
	"0000000000000000000000000000000000000000000000000030000000000000",
	"0000000000000000000003333333333333333300000000000000000000000000",
	"0000000000000006006660000000333333333000000900000000000000000000",
	"0000000000000000606000000000000000000000000009900000000000000000",
	"0000000000006666600000000000000000000000000000000090000000000000",
	"0000000000000000000000000000000000000000009000000000000000000000",
	"0000000000000000000000000000000000000000000000000000000000000000"
};
