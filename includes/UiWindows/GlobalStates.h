
#ifndef APP_STATES_H
#define APP_STATES_H
#include <unordered_map>

class WinStatesHandler;
class DisplayStatesHandler;
class DelaunayStatesHandler;

extern WinStatesHandler win_states;
// Horrible name for the
extern DisplayStatesHandler display_states;
extern DelaunayStatesHandler delaunay_states;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum class DelaunayStates
{
    // Operations
    flip_edge,
    insert_point,   // Either Insetion/Flip or other
    delaunay_check, // Check before insertions
    NumberOfTypes
};

class DelaunayStatesHandler
{
private:
    std::unordered_map<DelaunayStates, bool> m_states;
    void resolveDependencies(DelaunayStates &states)
    {
        if (isTrue(states))
        {
            // Currently don't do anyyhing
            switch (states)
            {
            case DelaunayStates::flip_edge:
                setState(DelaunayStates::insert_point, false);
                break;
            case DelaunayStates::insert_point:
                setState(DelaunayStates::flip_edge, false);
                break;
            default:
                break;
            }
        }
    }

public:
    DelaunayStatesHandler()
    {
        m_states.emplace(DelaunayStates(0), false);

        for (int i = 0; i < static_cast<unsigned int>(DelaunayStates::NumberOfTypes); i++)
        {
            m_states.emplace(DelaunayStates(i), false);
        }
    }

    void invState(DelaunayStates state)
    {
        m_states.at(state) = !m_states.at(state);
        resolveDependencies(state);
    }

    void setState(DelaunayStates state, bool val)
    {
        m_states.at(state) = val;
        resolveDependencies(state);
    }

    bool isTrue(DelaunayStates state)
    {
        return m_states.at(state);
    }
};

enum class WinStates
{
    img_area,
    NumberOfTypes
};

// Class just to have a cosntructor at hand
class WinStatesHandler
{
private:
    std::unordered_map<WinStates, bool> m_states;
    void resolveDependencies(WinStates &states)
    {
        if (isTrue(states))
        {
        }
        // Currently don't do anyyhing
    }

public:
    WinStatesHandler()
    {
        m_states.emplace(WinStates(0), true);

        for (int i = 1; i < static_cast<unsigned int>(WinStates::NumberOfTypes); i++)
        {
            m_states.emplace(WinStates(i), false);
        }
    }

    void invState(WinStates state)
    {
        m_states.at(state) = !m_states.at(state);
        resolveDependencies(state);
    }

    void setState(WinStates state, bool val)
    {
        m_states.at(state) = val;
        resolveDependencies(state);
    }

    bool isTrue(WinStates state)
    {
        return m_states.at(state);
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
enum class MainWinSt
{
    // DisplayStates
    none,
    wireframe,
    normals,
    curvature,
    NumberOfTypes,

};
// int num_mainwin = 2;

// Class just to have a cosntructor at hand
class DisplayStatesHandler
{
private:
    std::unordered_map<MainWinSt, bool> m_states;
    void resolveDependencies(MainWinSt &states)
    {
        // Currently don't do anyyhing
        if (isTrue(states))
        {
            switch (states)
            {
            case MainWinSt::none:
                setState(MainWinSt::wireframe, false);
                setState(MainWinSt::normals, false);
                setState(MainWinSt::curvature, false);
                break;
            case MainWinSt::wireframe:
                setState(MainWinSt::none, false);
                setState(MainWinSt::normals, false);

                setState(MainWinSt::curvature, false);
                break;
            case MainWinSt::normals:
                setState(MainWinSt::none, false);
                setState(MainWinSt::wireframe, false);
                setState(MainWinSt::curvature, false);
                break;
            case MainWinSt::curvature:
                setState(MainWinSt::none, false);
                setState(MainWinSt::wireframe, false);
                setState(MainWinSt::normals, false);
                break;
            default:
                break;
            }
        }
    }

public:
    DisplayStatesHandler()
    {
        m_states.emplace(MainWinSt(0), false);

        for (int i = 0; i < static_cast<unsigned int>(MainWinSt::NumberOfTypes); i++)
        {
            m_states.emplace(MainWinSt(i), false);
        }
    }

    void invState(MainWinSt state)
    {
        m_states.at(state) = !m_states.at(state);
        resolveDependencies(state);
    }

    void setState(MainWinSt state, bool val)
    {
        std::cout << val << std::endl;

        m_states.at(state) = val;

        resolveDependencies(state);
    }

    bool isTrue(MainWinSt state)
    {
        return m_states.at(state);
    }
};

#endif