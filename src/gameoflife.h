#include <cstdint>
#include <vector>

/*
1.Any live cell with fewer than two live neighbours dies, as if caused by under-population.
2.Any live cell with two or three live neighbours lives on to the next generation.
3.Any live cell with more than three live neighbours dies, as if by over-population.
4.Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
*/

struct Cell
{
    uint32_t x;
    uint32_t y;
};

class GameOfLife
{
public:
    void update();
    void spawn_cell();
    void kill_cell();

private:
    uint32_t get_neighbor_count() const;
    std::vector<Cell> m_alive_cells;
};
