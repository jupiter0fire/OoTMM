#if 0
#include <combo.h>
#include <combo/item.h>
#include <combo/csmc.h>
#include <combo/config.h>
#include <combo/actor.h>

void ObjGrass_GetXflag(Xflag* xflag, Actor_ObjGrass_PackBush* bush);

void ObjGrassCarry_SpawnDropsWrapper(Actor_ObjGrassCarry* this)
{
    Xflag xflag;

    if (Config_Flag(CFG_MM_SHUFFLE_GRASS))
    {
        /* Extract the ID and build the xflag */
        ObjGrass_GetXflag(&xflag, this->bush);

        /* Check if the reward was already collected */
        if (!comboXflagsGet(&xflag))
        {
            EnItem00_DropCustom(gPlay, &this->base.world.pos, &xflag);
            return;
        }
    }

    /* Run the default function */
    void (*ObjGrassCarry_SpawnDrops)(Vec3f*, u16, PlayState*);
    ObjGrassCarry_SpawnDrops = actorAddr(ACTOR_OBJ_GRASS_CARRY, 0x809aaf9c);
    ObjGrassCarry_SpawnDrops(&this->base.world.pos, this->drop, gPlay);
}

static void ObjGrassCarry_Draw(Actor_ObjGrassCarry* this, PlayState* play)
{
    Xflag xflag;
    ComboItemOverride o;

    o.gi = 0;
    if (Config_Flag(CFG_MM_SHUFFLE_GRASS))
    {
        /* Extract the ID and build the xflag */
        ObjGrass_GetXflag(&xflag, this->bush);

        /* Check if the reward was already collected */
        if (!comboXflagsGet(&xflag))
            comboXflagItemOverride(&o, &xflag, 0);
    }

    /* Prepare the draw */
    csmcGrassPreDraw(play, o.gi, CSMC_GRASS_NORMAL, 0, 0);

    /* Draw */
    Gfx_DrawDListOpa(play, (void*)0x50078a0);
}

PATCH_FUNC(0x809abb7c, ObjGrassCarry_Draw);

#endif
