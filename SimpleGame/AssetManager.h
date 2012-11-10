#ifndef AssetManager_h_
#define AssetManager_h_


#include "Images.h"
#include <vector>

namespace sg
{
    class AssetManager
    {
    public:
        
        int load();
        std::vector<TankImage> tankImages;
        std::vector<FloorImage> floorImages;
        std::vector<ProjectileImage> projectileImages;
        std::vector<MinionImage> minionImages;
    };
};
#endif

