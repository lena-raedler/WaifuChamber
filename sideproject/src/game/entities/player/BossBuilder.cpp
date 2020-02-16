//
// Created by auki on 12.02.20.
//
#include "BossBuilder.h"
#include "AbilityPicker.h"

namespace BossBuilder{
    void boss1(int i, Boss& b){
        TelegraphedAttack a;
        switch(i){
            case 2:
                b.speed *=1.2;
                a.damage = 20;
                for(int tmp = 32; tmp < 1880; tmp += 64*3) {
                    a.set(tmp, 32, 64, 1000);
                    a.spawn();

                }
                std::cout << "Phase 2" << std::endl;
                break;
            case 3:
                std::cout << "Phase 3" << std::endl;
            default:
                break;
        }

    }
    void buildBoss(int id, std::pair<int, int> pos){
        AbilityPicker<Ability> abilities;
        AbilityPicker<TelegraphedAbility> telegraphedAbilities;
        Boss b;
        Ability a;
        TelegraphedAbility ta;
        Projectile p;
        switch(id){
            case 1:
                b.size = {2,2};
                b.textureLocation = "files/textures/weapons/rabbit.png";
                abilities.pickAbility(a, 1, BOSS_RANGED);
                b.addAbility(a, 1, 1);

                abilities.pickAbility(a, 2, BOSS_RANGED);
                b.addAbility(a, 1, 3);

                telegraphedAbilities.pickAbility(ta, 3, BOSS_RANGED);
                b.addAbility(ta, 1, 2);

                //boss.addHealthBar(200);
                //boss.addHealthBar(100);
                b.addHealthBar(200, {0xFF, 0x80, 0x80, 0xFF}, {0xFF, 0x00, 0x00, 0xFF});
                b.addHealthBar(160, {0x80, 0xFF, 0x80, 0xFF}, {0x00, 0xFF, 0x00, 0xFF});
                b.addHealthBar(180, {0x80, 0x80, 0xff, 0xFF}, {0x00, 0x00, 0xFF, 0xFF});
                //boss.healthBar ( {64, 900, 1500, 30, {0xFF, 0x80, 0x80, 0xFF}, {0xFF, 0x00, 0x00, 0xFF}});
                b.position = utility::convert(pos);
                b.speed = 20;
                b.id = 1;
                b.velocity = {0, 0};
                b.gravityType = NORMAL;
                b.usesPlatforms = true;
                utility::fillDefaultHitbox(b.hitbox, b.size.x, b.size.y);
                b.phaseTransitionAbility= &BossBuilder::boss1;

                {
                    SDL_Rect r = {(int)b.position.x, (int)b.position.y, GlobalConstants::tileSize*b.size.x, GlobalConstants::tileSize*b.size.y};
                    b.rec = std::make_shared<SDL_Rect>(r);
                }
                GlobalObjects::bosses.push_back(std::make_shared<Boss>(b));
                break;
        }
        GlobalObjects::bosses.back()->init(*GlobalObjects::renderPtr);
    }
}