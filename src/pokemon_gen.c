#include "global.h"
#include "data_util.h"
#include "event_object_movement.h"
#include "map_gen.h"
#include "random.h"
#include "constants/event_objects.h"
#include "constants/pokemon.h"

// This is called on map load.
u16 GetOverworldEncounterGraphicsId(u32 localId)
{
    u32 i;
    const struct PrefabRules * rules = GetPrefabRules(gFloorplan.prefabType);

    // Advance RNG to a repeatable state based on the local ID.
    // This is to allow for consistency between saves and seed.
    SetRNGToRoomSeed();
    for (i = 0; i < localId; ++i)
        RandomF();
    
    return ChooseElementFromPool(rules->encounterPool) + OBJ_EVENT_GFX_MON_BASE;
}
