include(FindPkgConfig)

find_package(SDL2 REQUIRED)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})


add_library(libPlayer player.cpp Movable.cpp Movable.h Projectile.cpp Projectile.hpp statuseffect.cpp statuseffect.h Interactable.h Enemy.cpp Enemy.h Ability.cpp Ability.h EnemyBuilder.h Boss.cpp Boss.h EnemyBuilder.cpp EnemyBuilder.h AbilityPicker.h SoundEffect.h TelegraphedAbility.cpp TelegraphedAbility.h TelegraphedAttack.cpp TelegraphedAttack.h Sprites.cpp Sprites.h)

target_include_directories (libPlayer PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
