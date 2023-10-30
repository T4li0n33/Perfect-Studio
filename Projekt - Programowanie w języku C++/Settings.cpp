#include "Settings.h"

bool Settings::GetWindow(int i) // Returns boolean "show window" /1=window1/2=window2/
{
    switch(i)
    {
        case 1:
        {
            return showWindow;
            break;
        }

        case 2:
        {
            return showWindow2;
            break;
        }

        default:
            break;
    }
}

bool Settings::GetMode(int i) //Returns boolean based on i-value /1=project_mode/2=calc_mode/3=opengl/4=exit
{
    switch (i)
    {
        case 1 :
        {
            return project_mode;
            break;
        }

        case 2:
        {
            return calc_mode;
            break;
        }

        case 3:
        {
            return opengl_presentation_mode;
            break;
        }

        case 4:
        {
            return exit;
            break;
        }
        default:
            break;
    };
}


int Settings::WindowWidth()
{
    return width;
}

int Settings::WindowHeight()
{
    return height;
}


void Settings::SetWindow(int i)
{
    switch (i)
    {
    case 1:
    {
        showWindow = !showWindow;
        break;
    }

    case 2:
    {
        showWindow2 = !showWindow2;
        break;
    }

    default:
        break;
    }
}

void Settings::SetMode(int i)
{
    switch (i)
    {
    case 1:
    {
        project_mode = !project_mode;
        break;
    }

    case 2:
    {
        calc_mode = !calc_mode;
        break;
    }

    case 3:
    {
        opengl_presentation_mode = !opengl_presentation_mode;
        break;
    }
    case 4:
    {
        exit = !exit;
        break;
    }
    default:
        break;
    };
}


void Settings::RepairWindow()
{
        if (project_mode == true && showWindow == false)
        {
            showWindow = true;
            project_mode = false;
        }
        if (opengl_presentation_mode == true && showWindow2 == false)
        {
            showWindow2 = true;
            opengl_presentation_mode = false;
        }
}
