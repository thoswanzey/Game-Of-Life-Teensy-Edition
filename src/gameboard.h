#include <Arduino.h>

struct Gameboard
{
    virtual void print() const = 0;
};

class Serial_Gameboard : Gameboard
{
public:
    Serial_Gameboard(uint32_t view_width, uint32_t view_height);

    Serial_Gameboard(Serial_Gameboard const&) = delete;
    Serial_Gameboard& operator=(Serial_Gameboard const&) = delete;

    void print() const override;

private:
    void clear_terminal() const;

    uint32_t m_view_width;
    uint32_t m_view_height;
};
