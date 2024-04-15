#include "Wardrobe.h"

bool Wardrobe::GetWardrobeType(int i) // Returns boolean based od i-value /1=bottom/2=top/3=unusual
{
    switch (i)
    {
    case 1:
    {
        return wardrobe_type_bottom;
        break;
    }

    case 2:
    {
        return wardrobe_type_top;
        break;
    }

    case 3:
    {
        return wardrobe_type_unusual;
        break;
    }
    default:
        return -1;
        break;
    };
}

bool Wardrobe::GetWardrobeTypeCorner(int i) // Returns boolean based od i-value /1=corner_lemans/2=corner_shelf/
{
    switch (i)
    {
    case 1:
    {
        return wardrobe_corner_lemans;
        break;
    }

    case 2:
    {
        return wardrobe_corner_shelf;
        break;
    }
    default:
        return -1;
        break;
    };
}

bool Wardrobe::GetWardrobeModel(int i) // Returns boolean based od i-value /1=model_shelf/2=model_drawer/3=model_cargo/4=model_corner/
{
    switch (i)
    {
    case 1:
    {
        return wardrobe_model_shelf;
    }

    case 2:
    {
        return wardrobe_model_drawer;
    }

    case 3:
    {
        return wardrobe_model_cargo;
    }

    case 4:
    {
        return wardrobe_model_corner;
    }
    default:
        return -1;
        break;
    };
}

bool Wardrobe::GetAutoRatio(int i)//Returns boolean based on i-value where /1=shelf_ratio/2=drawer_ratio/3=front_ratio
{

    switch (i)
    {
    case 1:
    {
        return auto_shelf_ratio;
    }

    case 2:
    {
        return auto_drawer_ratio;
    }

    case 3:
    {
        return auto_front_ratio;
    }
    default:
        break;
    }
}

bool Wardrobe::GetFrontBool(int i)
{
    switch (i)
    {
        case 1:
        {
            return with_front;
        }

        case 2:
        {
            return front_bool;
        }

        default:
        {
            return -1;
            break;
        }

    }
    
}

float Wardrobe::GetShelfRatio()
{
    for (int i = 0; i < 4; i++)
    {
        if (shelf_ratio[i] == 0)
        {
            shelf_ratio[i] = base_y / shelf_number + 1;
            return shelf_ratio[i];
        }

        else
        {
            return shelf_ratio[i];
        }
    }
}

float Wardrobe::GetDrawerRatio()
{
    for (int i = 0; i < 4; i++)
    {
        if (drawer_ratio[i] == 0)
        {
            drawer_ratio[i] = base_y / drawer_number + 1;
            return drawer_ratio[i];
        }

        else
        {
            return drawer_ratio[i];
        }
    }
}

int Wardrobe::GetAmount(int i)
{
    switch (i)
    {
    case 1:
    {
        return drawer_number;
        break;
    }

    case 2:
    {
        return shelf_number;
        break;
    }

    case 3:
    {
        return fronts_amount;
        break;
    }
    default:
        break;
    }
}

bool Wardrobe::AreOptionsPicked()
{
    if (wardrobe_type_bottom || wardrobe_type_top || wardrobe_type_unusual)wardrobe_type_choosed = true;
    if (base_x != 0 && base_y != 0 && base_z != 0)wardrobe_size_placed = true;
    if (wardrobe_model_shelf || wardrobe_model_drawer || wardrobe_model_corner || wardrobe_model_cargo)wardrobe_model_choosed = true;

    if (wardrobe_type_choosed && wardrobe_model_choosed && wardrobe_size_placed)
    {
        return true;
    }
    else
    {
        return false;
    }
}

float Wardrobe::GetBaseSettings(int i)
{
    switch (i)
    {
    case 1:
    {
        return base_x;
        break;
    }
    case 2:
    {
        return base_y;
        break;
    }
    case 3:
    {
        return base_z;
        break;
    }
    default:
        break;
    }
}

float Wardrobe::GetDiaphragmSize()
{
    return diaphragm_size;
}

float Wardrobe::GetBlindSize()
{
    return blind_side_size;
}


void Wardrobe::SetSize(int i, float value)
{
    switch (i)
    {
    case 1:
    {
        base_x = value;
        break;
    }
    case 2:
    {
        base_y = value;
        break;
    }
    case 3:
    {
        base_z = value;
        break;
    }
    default:
        break;
    }
}

void Wardrobe::SetWardrobeType(int i)// 1 - bottom / 2 - top / 3 - unusual / 4 - model_choosed / 5 - size_placed
{
    switch (i)
    {
    case 1:
    {
        wardrobe_type_bottom = true;
        wardrobe_type_top = false;
        wardrobe_type_unusual = false;
        break;
    }

    case 2:
    {
        wardrobe_type_bottom = false;
        wardrobe_type_top = true;
        wardrobe_type_unusual = false;
        break;
    }

    case 3:
    {
        wardrobe_type_bottom = false;
        wardrobe_type_top = false;
        wardrobe_type_unusual = true;
        break;
    }

    case 4:
    {
        wardrobe_model_choosed = true;
        break;
    }
    case 5:
    {
        wardrobe_size_placed = true;
        break;
    }
    default:
        break;
    };
}

void Wardrobe::SetWardrobeTypeCorner(int i)
{
    switch (i)
    {
    case 1:
    {
        wardrobe_corner_lemans = true;
        wardrobe_corner_shelf = false;
        break;
    }

    case 2:
    {
        wardrobe_corner_shelf = true;
        wardrobe_corner_lemans = false;
        break;
    }
    default:
        break;
    }

}

void Wardrobe::SetWardrobeModel(int i)
{
    switch (i)
    {
    case 1:
    {
        wardrobe_model_shelf = !wardrobe_model_shelf;
        wardrobe_model_drawer = false;
        wardrobe_model_corner = false;
        wardrobe_model_cargo = false;
        break;
    }

    case 2:
    {
        wardrobe_model_shelf = false;
        wardrobe_model_drawer = !wardrobe_model_drawer;
        wardrobe_model_corner = false;
        wardrobe_model_cargo = false;
        break;
    }

    case 3:
    {
        wardrobe_model_shelf = false;
        wardrobe_model_drawer = false;
        wardrobe_model_corner = !wardrobe_model_corner;
        wardrobe_model_cargo = false;
        break;
    }
    case 4:
    {
        wardrobe_model_shelf = false;
        wardrobe_model_drawer = false;
        wardrobe_model_corner = false;
        wardrobe_model_cargo = !wardrobe_model_cargo;
        break;
    }
    default:
        break;
    };
}

void Wardrobe::SetAutoRatio(int i)
{
    switch (i)
    {
    case 1:
    {
        auto_shelf_ratio = false;
        break;
    }

    case 2:
    {
        auto_drawer_ratio = false;
        break;
    }
    case 3:
        auto_drawer_ratio = true;
        break;

    case 4:
        auto_shelf_ratio = true;
        break;

    case 5 :
    {
        auto_front_ratio = false;
        break;
    }

    case 6 :
    {
        auto_front_ratio = true;
        break;
    }

    default:
        break;
    }
  
}

void Wardrobe::SetFrontBool(int i)
{
    switch (i)
    {
    case 1:
    {
        with_front = false;
        break;
    }

    case 2:
    {
        with_front = true;
        break;
    }


    //case 3:
    //{
    //    front_bool = false;
    //    break;
    //}

    //case 4:
    //{
    //    front_bool = true;
    //    break;
    //}
    default:
    {
        break;
    }
    }
}

void Wardrobe::SetShelfs(int amount, float* height)
{
    shelf_number = amount;
    float spaces = amount + 1;
    float shelf_height_ratio = (base_y - 18.0f)/spaces;

    if (auto_shelf_ratio)
    {
        
        for (int x = 0; x < 4; x++)
        {
            float result = shelf_height_ratio + (shelf_height_ratio * x);
            if(result < base_y - 18.0f)
            shelf_ratio[x] = result;
            else shelf_ratio[x] = 0;
        }
    }
    else
    {
        for (int x = 0; x < 4; x++)
            shelf_ratio[x] = height[x];
    }
   
}

void Wardrobe::SetDrawers(int amount, float* height)
{
    float table[3];
    for (int x = 0; x < 3; x++)
    {
        float first_front = 0.0f;
        float divider = amount;
        if (amount == 3 && GetAutoRatio(3)) {
            table[2] = 143; divider = 2;
            first_front = 142;
        }

        table[x] = (GetBaseSettings(2) - first_front - 5.00 - 3 * (amount - 1)) / divider;
        if (amount == 3 && GetAutoRatio(3)) {
            table[2] = 143; 
        }
    }
    

    drawer_number = amount;
    float spaces = amount + 1;
    float drawer_height_ratio = (base_y - 18.0f) / spaces;
    int i = 0;
    int k = 33;
    float result = 0;
    if (auto_drawer_ratio)
    {
        drawer_ratio[0] = 33;
        for (int x = 1; x < 4; x++)
        {

            result = result + (table[i] + k);
            if (result < base_y)
            {
                drawer_ratio[x] = result;
                k = 0;
            }

            else drawer_ratio[x] = 0;
            i++;
        }
    }
    else
    {
        for (int x = 0; x < 4; x++)
            drawer_ratio[x] = height[x];
    }

}

void Wardrobe::SetFronts(int amount, float* width)

{
    fronts_amount = amount;
    float front_width = (base_x - 6.0f) / amount;
    if (auto_front_ratio)
    {
        for (int x = 0; x < 4; x++)
        {
            float result = front_width + (front_width * x);
            if (result < base_x - 6.0f)
                front_ratio[x] = result;
            else front_ratio[x] = 0;
        }
    }
    else
    {
        for (int x = 0; x < 4; x++)
            front_ratio[x] = width[x];
    }
}


bool Wardrobe::CheckRatioChanges()
{
    for (int x = 0; x < 4; x++)
    {
        if (drawer_ratio[x] != previous_d_ratio[x] || shelf_ratio[x] != previous_s_ratio[x] || front_ratio[x] != previous_f_ratio[x]) //Check if all fields are equal
        {
            for (int i = 0; i < 4; i++)
            {
                previous_d_ratio[i] =  drawer_ratio[i]; //If not overwrite previous
               previous_s_ratio[i] = shelf_ratio[i];
               previous_f_ratio[i] = front_ratio[i];
            }
            return true;
            // Signalize that you've catched an input change
        }
    }

    return false;
}
