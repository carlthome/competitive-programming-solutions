#include "player.hpp"
#define DEPTH 12
namespace checkers
{
    typedef long long ll;
    
    bool found, isRed;
    GameState next;

    ll negamax(const GameState& s, ll d, ll a, ll b, ll c)
    {
        if (d == 0)
        {
            auto w = 0, r = 0;
            for (auto i = 1; i <= 32; ++i)
            {
                auto c = s.at(i);
                if (c & CELL_RED) ++r;
                else if (c & CELL_WHITE) ++w;
            }
            return c*(isRed?r-w:w-r);
        } 
        else if (s.isEOG())
        {
            auto w = 0, r = 0;
            if (s.isRedWin()) r += 100+d;
            else if (s.isWhiteWin()) w += 100+d;
            else if (s.isDraw()) return 0;
            return c*(isRed?r-w:w-r);
        }

        std::vector<GameState> ns;
        s.findPossibleMoves(ns);
        
        for (const auto& n : ns)
        {
            auto r = -negamax(n, d-1, -b, -a, -c);
            if (r > a)
            {
                a = r;
                if (d == DEPTH)
                {
                    found = true;
                    next = n;
                }
            }
            if (b <= a) return a;
        }

        return a;
    }

    GameState Player::play(const GameState& pState, const Deadline& due)
    {
        isRed = (pState.getNextPlayer() & CELL_RED);        
        found = false;
        negamax(pState, DEPTH, -1000, 1000, true);
        return found ? next : GameState(pState, Move());
    }
}
