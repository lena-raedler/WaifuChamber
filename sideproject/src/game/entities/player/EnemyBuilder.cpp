//
// Created by auki on 27.01.20.
//

#include "EnemyBuilder.h"
#include "AbilityPicker.h"

namespace EnemyBuilder {
    void buildEnemy(std::vector<std::shared_ptr<Enemy>>& vece, int id, std::pair<int, int> pos){//hardcoded because fuck that shit
        Enemy e;
        Projectile p;
        AbilityPicker<TelegraphedAbility> telegraphedAbilities;
        p.textureLocation = "files/textures/weapons/Arrow.png";
        Ability a;
        TelegraphedAbility ta;
        statuseffect s;

        switch(id){
            case 1: //Skelly
                e.position = utility::convert(pos);
                e.velocity = {0,0};
                e.setMaxHealth(60);
                e.speed = 10;
                e.ai = STATIONARY;
                e.gravityType = NORMAL;
                e.souls = 100;
                utility::fillDefaultHitbox(e.hitbox);

                utility::fillDefaultHitbox(p.hitbox);
                p.damage = 20;
                p.timeToLive = 100;
                p.usesPlatforms = false;
                p.fragile = true;
                p.gravityType = NOGRAVITY;
                p.baseInit();

                /*
                s.type = BLEED;
                s.intensity = 50;

                p.status.push_back(s);

                s.type = SHOCK;
                p.status.push_back(s);

                 */
                a.projectiles.push_back(p);
                a.speed = 20;
                a.cooldown = 10;

                e.abilities.push_back(a);
                e.textureLocation = "files/textures/jellyfish.png";

                //rectangle is filled with the given position of the enemy and the global tilesize
                {
                    SDL_Rect r = {(int)e.position.x, (int)e.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
                    e.rec = std::make_shared<SDL_Rect>(r);
                }
                break;
            case 2://floating skelly
                e.position = utility::convert(pos);
                e.velocity = {0,0};
                e.setMaxHealth(10);
                e.speed = 10;
                e.ai = PATROL;
                e.gravityType = NOGRAVITY;
                utility::fillDefaultHitbox(e.hitbox);

                utility::fillDefaultHitbox(p.hitbox);
                p.damage = 20;
                p.timeToLive = 100;
                p.usesPlatforms = false;
                p.fragile = true;
                p.gravityType = NOGRAVITY;
                p.baseInit();

                s.type = BLEED;
                s.intensity = 20;
                p.status.push_back(s);

                a.projectiles.push_back(p);
                a.speed = 20;
                a.cooldown = 10;

                e.abilities.push_back(a);
                e.textureLocation = "files/textures/jellyfish.png";

                //rectangle is filled with the given position of the enemy and the global tilesize
                {
                    SDL_Rect r = {(int)e.position.x, (int)e.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
                    e.rec = std::make_shared<SDL_Rect>(r);
                }
                break;
            case 3: //spikes
                e.hasSprite = false;
                e.position = utility::convert(pos);
                e.setMaxHealth(10);
                e.speed = 10;
                e.ai = STATIONARY;
                e.gravityType = NOGRAVITY;
                utility::fillDefaultHitbox(e.hitbox);

                utility::fillDefaultHitbox(p.hitbox);
                e.iframes = true;
                e.damageOnTouch = 70;
                e.textureLocation = "files/textures/spike_01_cropped.png";

                //rectangle is filled with the given position of the enemy and the global tilesize
                {
                    SDL_Rect r = {(int)e.position.x, (int)e.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
                    e.rec = std::make_shared<SDL_Rect>(r);
                }

                break;
            case 4: //spikes
                e.hasSprite = false;
                e.position = utility::convert(pos);
                e.setMaxHealth(10);
                e.speed = 10;
                e.ai = PATROL;
                e.gravityType = NOGRAVITY;
                utility::fillDefaultHitbox(e.hitbox);

                utility::fillDefaultHitbox(p.hitbox);
                e.iframes = true;
                e.damageOnTouch = 70;
                e.textureLocation = "files/textures/spike_01_cropped.png";

                //rectangle is filled with the given position of the enemy and the global tilesize
                {
                    SDL_Rect r = {(int)e.position.x, (int)e.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
                    e.rec = std::make_shared<SDL_Rect>(r);
                }

                break;
            case 5: // chasing jelly
                e.position = utility::convert(pos);
                utility::fillDefaultHitbox(e.hitbox);
                e.setMaxHealth(30);
                s.type = SHOCK;
                s.intensity = 90;
                e.statusOnTouch = s;
                e.speed = 16;
                e.ai = CHASEXY;
                e.gravityType = NOGRAVITY;
                e.damageOnTouch = 30;
                e.textureLocation = "files/textures/jellyfish.png";
                {
                    SDL_Rect r = {(int)e.position.x, (int)e.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
                    e.rec = std::make_shared<SDL_Rect>(r);
                }
                break;
            case 6:
                e.position = utility::convert(pos);
                utility::fillDefaultHitbox(e.hitbox);
                e.setMaxHealth(30);
                s.type = SHOCK;
                s.intensity = 90;
                e.statusOnTouch = s;
                e.speed = 16;
                e.ai = STATIONARY;
                e.gravityType = NOGRAVITY;
                e.damageOnTouch = 30;
                e.textureLocation = "files/textures/jellyfish.png";
                telegraphedAbilities.pickAbility(ta, 1, NPC_RANGED);
                e.telegraphedAbilities.push_back(ta);
                {
                    SDL_Rect r = {(int)e.position.x, (int)e.position.y, GlobalConstants::tileSize, GlobalConstants::tileSize};
                    e.rec = std::make_shared<SDL_Rect>(r);
                }
                break;
            default:
                break;
        }

        // Health bar
        e.healthBar.x = e.position.x;
        e.healthBar.y = e.position.y - GlobalConstants::tileSize/2;
        e.healthBar.width = GlobalConstants::tileSize;
        e.healthBar.height = GlobalConstants::tileSize/4;
        e.healthBar = {static_cast<int>(e.position.x), static_cast<int>(e.position.y), e.healthBar.width, e.healthBar.height, {0xFF, 0x80, 0x80, 0xFF}, {0xFF, 0x00, 0x00, 0xFF}};
        e.healthBar.borderRect = {static_cast<int>(e.position.x), static_cast<int>(e.position.y), e.healthBar.width, e.healthBar.height};
        e.healthBar.backgroundRect = {static_cast<int>(e.position.x + e.healthBarOffset), static_cast<int>(e.position.y + e.healthBarOffset), e.healthBar.width - 2*e.healthBarOffset, e.healthBar.height - 2*e.healthBarOffset};
        e.healthBar.barRect = {static_cast<int>(e.position.x + e.healthBarOffset), static_cast<int>(e.position.y + e.healthBarOffset), e.healthBar.width - 2*e.healthBarOffset, e.healthBar.height - 2*e.healthBarOffset};
        e.healthBar.borderColor = {0xFF, 0x80, 0x80, 0xFF};
        e.healthBar.barColor = {0xFF, 0x00, 0x00, 0xFF};

        e.init(*GlobalObjects::renderPtr);
        GlobalObjects::enemies.push_back(std::make_shared<Enemy>(e));
    };

};