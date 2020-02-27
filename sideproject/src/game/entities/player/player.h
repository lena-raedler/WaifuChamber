//
// Created by lena on 11/11/19.
//

#ifndef WAIFUCHAMBER_PLAYER_H
#define WAIFUCHAMBER_PLAYER_H

#include <iostream>
#include <string>
#include <vector>
#include "../../utils/renderer.h"
#include "../../utils/Vec2.h"
#include <utility>
#include "Movable.h"
#include <iostream>
#include <chrono>
#include <string>
#include <utility>
#include "Checkpoint.h"
#include "statuseffect.h"
#include "../../Inventory/Inventory.hpp"
#include "Ability.h"
#include "Bar.hpp"
#include "../../utils/Image.h"
#include "Sprites.h"
#include "../../SavedVariables.h"

enum lastCheckPoint{//maybe we dont need this
    A1C1,
    A1C2,
    A1C3,
    A2C1,
    A2C2,
    A2C3,
    A3C1,
    A3C2,
    A3C3 //TODO: give cool names
};

struct attributes{
    int str;
    int dex;
    int agi;
    int bluedex;// (intelligence)
    int con;
};
struct vitals{
    double  maxHp = 100;
    double hp = 100;

    double maxStam = 100;
    double stam = 100;
    int maxMp = 100;
    int mp = 50;

    int armor;

    double stamRegen = 10;
    double healthPercentage(){return (double) hp / maxHp;}
    double staminaPercentage(){return (double) stam / maxStam;}
    double bleedPercentage() { return (double) bleed / bleedRes; }
    double shockPercentage() { return (double) shock / shockRes; }
    double burnPercentage() { return (double) burn / burnRes; }
    double rotPercentage() { return (double) rot / rotRes; }

    double bleedRes = 100;
    double shockRes = 100;
    double burnRes = 100;
    double rotRes = 100;
    double frenzyRes = 100;

    double bleed = 0;
    double shock = 0;
    double burn = 0;
    double rot = 0;
    double frenzy = 0;

    bool bleeding = false;
    bool shocked = false;
    bool burning = false;
    bool rotting = false;
    bool frenzied = false;

    double statusDecay = 1.5;

    void setStatusToZero(){
        bleed = 0;
        shock = 0;
        burn = 0;
        rot = 0;
        frenzy = 0;

        bleeding = false;
        shocked = false;
        burning = false;
        rotting = false;
        frenzied = false;
    }
};
class Player : public Movable {
public:
    /////////////////// Constructors //////////////////////////
    Player();
    ~Player();

    /////////////////// Fields ////////////////////////////////
    const int iFrameDuration = 500; //iframe duration on getting hit
    int jumps = 2;
    const int jumpCooldown = 250; //ms
    const int pauseCooldown = 250;  //ms
    int spawnProjectileCooldown = 250;  //ms no const because different weapons will have different cds
    const double jumpSpeed = -40;
    vec_t dashOrigin;
    vec_t dashDest;
    double dashSpeed = 10;
    int dashFullDuration = 1;
    double dashDuration = dashFullDuration;

    std::chrono::high_resolution_clock::time_point lastJump = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point lastHit;
    std::chrono::high_resolution_clock::time_point lastPause = std::chrono::high_resolution_clock::now();
    std::chrono::high_resolution_clock::time_point lastSpawnProjectile = std::chrono::high_resolution_clock::now();
    attributes attr;
    vitals vit;
    double stamRegenMultiplier = 1;
    double speedMultiplier = 1;
    double staminaCostReduction = 1;
    double floatStaminaCost = 10;
    double dashStaminaCost = 150;
    Checkpoint* lastCP;
    Inventory inventory;

    Bar healthBar;
    Bar staminaBar;

    bool dashingDown = false;
    bool dashingUp = false;

    double dashRange = 128;

    int statusBarWidth = GlobalConstants::tileSize * 2;
    int statusBarBackgroundOffset = 4;
    int statusBarHeight = GlobalConstants::tileSize / 4;
    int statusBarMultiplier = 1;
    Bar bleedBar, activeBleedBar;
    Bar shockBar, activeShockBar;
    Bar burnBar, activeBurnBar;
    Bar rotBar, activeRotBar;
    Bar frenzyBar, activeFrenzyBar;


    /////////////////// Functions /////////////////////////////
    void updatePlayer(double x, double y);
    void jump();
    bool canJump();
    void pause();
    bool canPause();
    void spawnProjectile();
    bool canSpawnProjectile();
    void upkeep(double delta);//call this every frame
    void getHit(double damage);
    void getHit(double damage, statuseffect status);
    void kill();
    void grounded(double delta);
    void rangedAttack();

    vec_t getMiddle();

    void applyStatusEffect(statuseffect &status);
    void processStatusEffects(statuseffect &status, double delta);
    void removeStatusEffect(statuseffect &status);

    void rest();
    void checkStatusEffects();
    std::vector<statuseffect> statusEffects;
    void updateStatusEffectBars();
    void setStatusBarPosition(Bar& bar);
    void setStatusBarPosition(Bar& bar, statuseffect& status);


    void dashTo(vec_t dest);
    // sprites -> override functions from movable
    Sprites playerSprite;
    void init(Renderer& renderer);
    void render(Renderer& renderer);

    bool areWeThereYet(vec_t dest);

    bool hasKey(Gate &g);

    void addKey(int keyId);
};


#endif //WAIFUCHAMBER_PLAYER_H
