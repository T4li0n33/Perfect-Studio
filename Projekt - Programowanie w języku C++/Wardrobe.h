#pragma once
#include <string>

/**
 * Represents a customizable wardrobe unit with configurable:
 * - Types (bottom, top, unusual)
 * - Models (shelf, drawer, corner, cargo)
 * - Dimensions and component ratios
 * - Front panel options
 * - Material selections
 */
class Wardrobe
{
    // Type configuration flags
    bool wardrobe_type_bottom = false;   // True for bottom-mounted units
    bool wardrobe_type_top = false;      // True for top-mounted units
    bool wardrobe_type_unusual = false;  // True for custom/non-standard units

    // Model configuration flags
    bool wardrobe_model_shelf = false;   // Shelf-dominant configuration
    bool wardrobe_model_drawer = false;  // Drawer-dominant configuration
    bool wardrobe_model_corner = false;  // Corner unit configuration
    bool wardrobe_model_cargo = false;   // Cargo-style configuration

    // Automatic ratio calculation flags
    bool auto_shelf_ratio = true;       // Auto-calculate shelf heights
    bool auto_drawer_ratio = true;      // Auto-calculate drawer heights
    bool auto_front_ratio = true;       // Auto-calculate front widths

    // Corner-specific configurations
    bool wardrobe_corner_lemans = false; // LeMans-style corner solution
    bool wardrobe_corner_shelf = false;  // Shelf-style corner solution

    // Configuration state trackers
    bool wardrobe_type_choosed = false;  // True when type is selected
    bool wardrobe_model_choosed = false; // True when model is selected
    bool wardrobe_size_placed = false;   // True when dimensions are set

    // Front panel options
    bool with_front = false;            // True if unit has front panels
    bool front_bool = true;             // Front panel activation state

    // Physical dimensions (in millimeters)
    float base_x = 0;  // Width dimension
    float base_y = 0;  // Height dimension
    float base_z = 0;  // Depth dimension

    // Component quantities
    int shelf_number = 0;     // Number of shelves
    int drawer_number = 0;    // Number of drawers
    int wardrobe_index = 0;   // Unit identifier
    int fronts_amount = 0;    // Number of front panels

    // Appearance settings
    int selected_drawer_color = 0;  // 0=gray, 1=white, 2=black
    float blind_side_size = 0.00f;   // Blind side dimension (corner units)
    float diaphragm_size = 0.00f;    // Partition thickness
    std::string veneer;              // Veneer material/color selection

public:
    // Ratio history buffers (stores previous configurations)
    float previous_s_ratio[4] = { 0 };  // Previous shelf height ratios
    float previous_d_ratio[4] = { 0 };  // Previous drawer height ratios
    float previous_f_ratio[4] = { 0 };  // Previous front panel ratios

    // Current configuration ratios
    float drawer_ratio[4] = { 0 };  // Current drawer height distribution
    float shelf_ratio[4] = { 0 };   // Current shelf height distribution
    float front_ratio[4] = { 0 };   // Current front panel width distribution

    // ==================== GETTER METHODS ====================

    /**
     * Retrieves wardrobe type status
     * @param i Type selector: 1=bottom, 2=top, 3=unusual
     * @return True if selected type is active
     */
    bool GetWardrobeType(int i);

    /**
     * Checks corner configuration type
     * @param i Type selector: 1=leMans, 2=shelf
     * @return True if selected corner type is active
     */
    bool GetWardrobeTypeCorner(int i);

    /**
     * Retrieves model configuration status
     * @param i Model selector: 1=shelf, 2=drawer, 3=cargo, 4=corner
     * @return True if selected model is active
     */
    bool GetWardrobeModel(int i);

    /**
     * Checks automatic ratio calculation status
     * @param i Ratio type: 1=shelf, 2=drawer, 3=front
     * @return True if auto-calculation is enabled
     */
    bool GetAutoRatio(int i);

    /**
     * Retrieves front panel configuration
     * @param i Option selector: 1=with_front, 2=front_bool
     * @return Current front panel status
     */
    bool GetFrontBool(int i);

    /**
     * Calculates and returns current shelf height ratio
     * @return Dominant shelf ratio value
     */
    float GetShelfRatio();

    /**
     * Calculates and returns current drawer height ratio
     * @return Dominant drawer ratio value
     */
    float GetDrawerRatio();

    /**
     * Retrieves component quantities
     * @param i Component type: 1=drawers, 2=shelves, 3=fronts
     * @return Count of requested component
     */
    int GetAmount(int i);

    /**
     * @return Currently selected veneer material
     */
    std::string GetVeener();

    /**
     * @return Index of currently selected drawer color (0-2)
     */
    int GetDrawerColor();

    /**
     * Retrieves texture identifier for drawer fronts
     * @return Texture ID based on current selection
     */
    int GetDrawerTexture();

    /**
     * Gets color name for specified drawer color ID
     * @param id Color index: 0=gray, 1=white, 2=black
     * @return String representation of color name
     */
    std::string GetDrawerColor(int id);

    /**
     * Verifies all required configuration options are set
     * @return True when unit is fully configured
     */
    bool AreOptionsPicked();

    /**
     * Retrieves base dimension by index or character
     * @param i Dimension selector (1/2/3 or 'x'/'y'/'z')
     * @return Requested dimension in millimeters
     */
    float GetBaseSettings(int i);
    float GetBaseSettings(char i);

    /**
     * @return Current diaphragm partition thickness
     */
    float GetDiaphragmSize();

    /**
     * @return Blind side dimension for corner units
     */
    float GetBlindSideSize();

    // ==================== SETTER METHODS ====================

    /**
     * Updates wardrobe dimensions
     * @param i Axis selector: 1=x, 2=y, 3=z
     * @param value New dimension in millimeters
     */
    void SetSize(int i, float value);

    /**
    * Updates wardrobe blind side size (if exists)
    * @param size Size of element in milimeters
    */
    void SetBlindSideSize(float size);

    /**
     * Configures wardrobe type and state
     * @param i Option: 1=bottom, 2=top, 3=unusual,
     *               4=mark type chosen, 5=mark dimensions set
     */
    void SetWardrobeType(int i);

    /**
     * Sets corner solution type
     * @param i Type: 1=leMans, 2=shelf
     */
    void SetWardrobeTypeCorner(int i);

    /**
     * Configures wardrobe model
     * @param i Model: 1=shelf, 2=drawer, 3=corner, 4=cargo
     */
    void SetWardrobeModel(int i);

    /**
     * Toggles automatic ratio calculation
     * @param i Option: 1=disable shelf auto, 2=disable drawer auto,
     *               3=enable drawer auto, 4=enable shelf auto,
     *               5=disable front auto, 6=enable front auto
     */
    void SetAutoRatio(int i);

    /**
     * Configures front panel options
     * @param i Option: 1=disable with_front, 2=enable with_front,
     *               3=disable front_bool, 4=enable front_bool
     */
    void SetFrontBool(int i);

    /**
     * Configures shelf layout
     * @param amount Number of shelves
     * @param height Array of shelf heights (ratios)
     */
    void SetShelfs(int amount, float* height);

    /**
     * Configures drawer layout
     * @param amount Number of drawers
     * @param height Array of drawer heights (ratios)
     */
    void SetDrawers(int amount, float* height);

    /**
     * Configures front panel layout
     * @param amount Number of front panels
     * @param width Array of panel widths (ratios)
     */
    void SetFronts(int amount, float* width);

    /**
     * Sets drawer front color
     * @param color Index: 0=gray, 1=white, 2=black
     */
    void SetDrawerColor(int color);

    /**
     * Sets veneer material/color
     * @param color Material description string
     */
    void SetVeenerColor(std::string color);

    /**
     * Detects ratio configuration changes
     * @return True if any ratios were modified since last check
     */
    bool CheckRatioChanges();
};