#ifndef COMBO_COMBO_H
#define COMBO_COMBO_H

#if !defined(__ASSEMBLER__)
# include <stddef.h>
# include <string.h>
# include <stdlib.h>

/* "Length" is how long the fish is, which affects how much it weighs, but I call it weight sometimes anyway. */
# define FISH_WEIGHT_TO_LENGTH(weight) (sqrtf((weight - 0.5f) / 0.0036f) + 1.0f) /* Add 1.0 to prevent errors due to truncating */

# include <ultra64.h>
# include <combo/actor_ovl.h>
# include <combo/defs.h>
# include <combo/equipment.h>
# include <combo/object.h>
# include <combo/patch.h>
# include <combo/npc.h>
# include <combo/text.h>
# include <combo/common/ocarina.h>
# include <combo/common/color.h>
# include <combo/common/actors/Obj_Mure2.h>
# include <combo/common/actors/Obj_Mure3.h>
# include <combo/common/actors/Obj_Tsubo.h>
# include <combo/common/actors/En_Tubo_Trap.h>

# if defined(GAME_OOT)
#  include <combo/oot/play.h>
#  include <combo/oot/pause_state.h>
#  include <combo/oot/actors/Item_Etcetera.h>
#  include <combo/oot/actors/Obj_Timeblock_Warp2Block.h>
#  include <combo/oot/actors/En_Kusa.h>
#  include <combo/oot/actors/En_Ossan.h>
#  include <combo/oot/actors/En_Ex_Ruppy.h>
#  include <combo/oot/actors/En_Diving_Game.h>
#  include <combo/oot/actors/En_Elf.h>
#  include <combo/oot/actors/Shot_Sun.h>
#  include <combo/oot/actors/Custom_Torch2.h>
#  include <combo/oot/actors/Demo_Effect.h>
# endif

# if defined(GAME_MM)
#  include <combo/mm/play.h>
#  include <combo/mm/actor_ensob1.h>
#  include <combo/mm/actor_enfsn.h>
#  include <combo/mm/actor_entrt.h>
#  include <combo/mm/actor_enossan.h>
#  include <combo/mm/actor_ensuttari.h>
#  include <combo/mm/actor_arms_hook.h>
#  include <combo/mm/actor_bgingate.h>
#  include <combo/mm/actor_objboat.h>
#  include <combo/mm/actors/Obj_Grass.h>
#  include <combo/mm/actors/Obj_Grass_Carry.h>
#  include <combo/mm/actors/En_Kusa.h>
#  include <combo/mm/actors/En_Elf.h>
# endif

# include <combo/common/actors/En_Item00.h>
# include <combo/common/actors/En_GirlA.h>
# include <combo/common/actor_init.h>
# include <combo/common/actors/Custom_Triggers.h>
# include <combo/common/api.h>
#endif

/* Shared with assembler */
#include <combo/save.h>
#include <combo/gi.h>
#include <combo/data/items.h>
#include <combo/entrances.h>
#include <combo/common/events.h>
#include <combo/scenes.h>
#include <combo/drawgi.h>
#if defined (GAME_OOT)
# include <combo/oot/pause_state_defs.h>
#else
# include <combo/mm/asm_defs.h>
#endif

#if !defined(__ASSEMBLER__)

#define PLAYER_SELF 0x00
#define PLAYER_ALL  0xff

/* Init */
void comboInit(void);
void comboInitOverride(void);
void comboInitData(void);

void comboItemIcon(void* dst, int itemId);
void comboLoadMmIcon(void* dst, u32 iconBank, int iconId);

#if defined(GAME_OOT)
extern u16 gBlastMaskDelayAcc;
#endif

/* Switch */
NORETURN void comboGameSwitch(GameState_Play* play, u32 entrance);

#if defined(GAME_OOT)
void swapFarore(void);
#endif

void    comboWalletRefresh(void);

/* Cache */
void    comboCacheClear(void);
void    comboCacheGarbageCollect(void);
void*   comboCacheGetFile(u32 vrom);

/* Objects */
void                comboObjectsReset(void);
void                comboObjectsGC(void);
void*               comboGetObject(u16 objectId);
const ObjectData*   comboGetObjectData(u16 objectId);
u32                 comboLoadObject(void* buffer, u16 objectId);
void                comboLoadCustomKeep(void);
void                comboExObjectsReset(void);

/* Custom_Warp */
void comboSpawnCustomWarps(GameState_Play*);

/* Util */
int comboStrayFairyIndex(void);
int comboOotDungeonScene(GameState_Play* play, int isBossKey);
int comboMmDungeonIndex(void);
int comboIsChateauActive(void);
int comboIsLinkAdult(void);

void comboSpawnItemGiver(GameState_Play* play, u16 npcId);
void comboSpawnItemGivers(GameState_Play* play);

/* libc */
int toupper(int c);

int comboDoorIsUnlocked(GameState_Play* play, Actor* actor);

/* Hints */
#define HINT_GOSSIP         0x00
#define HINT_GOSSIP_GROTTO  0x01

#define HINT_TYPE_PATH          0x00
#define HINT_TYPE_FOOLISH       0x01
#define HINT_TYPE_ITEM_EXACT    0x02
#define HINT_TYPE_ITEM_REGION   0x03
#define HINT_TYPE_JUNK          0x04

void Hint_Init(void);
void Hint_Display(GameState_Play* play, u8 key);
void Hint_DisplayJunk(GameState_Play* play, u32 key);
void Hint_DisplayJunkRandom(GameState_Play* play);

/* Entrance */
void comboInitEntrances(void);
s32 comboEntranceOverride(u32 entranceId);
int comboBossLairIndex();

extern s8 gIsEntranceOverride;
extern s32 gLastEntrance;
extern s32 gLastScene;

/* Warp */
void comboTriggerWarp(GameState_Play* play, int index);

/* MQ */
void comboMqKaleidoHook(GameState_Play* play);

extern GameState_Play* gPlay;

#if defined(GAME_MM)
void Ocarina_HandleWarp(Actor_Player* player, GameState_Play* ctxt);
#endif

#if defined(GAME_MM)
extern int gNoTimeFlow;
#endif

/* Ocarina */
void comboCheckSong(const OcarinaSongButtons* songButtons, int songIndex);

void comboCreditWarp(GameState_Play* play);

#if defined (GAME_OOT)
extern u16 gPrevPageIndex;
extern s16 gPrevCursorPoint;
extern s8 gSoaringIndexSelected;
#endif

void comboHandleAutoInvertClockSpeed(void);

void LoadMmItemIcon(void* dst, int iconId);

#else
# include <combo/asm.h>
#endif

#endif /* COMBO_COMBO_H */
