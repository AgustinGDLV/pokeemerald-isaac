#ifndef GUARD_MAP_GEN_H
#define GUARD_MAP_GEN_H

#include "data_util.h"
#include "item_gen.h"

// Floor Constants
#define LAYOUT_SIZE                 90
#define MAX_LAYOUT_WIDTH            9
#define MAX_LAYOUT_HEIGHT           8
#define MIN_ROOMS                   7
#define MAX_ROOMS                   20
#define STARTING_ROOM               45
#define TEMPLATE_MAP_GROUP_START    MAP_GROUP(FOREST_PREFABS_BASES)

// Room Constants
#define ROOM_COORD(x, y)            ((x+1) + (y+1)*10)  // gFloorplan.layout is not zero-indexed

enum RoomTypes {
    NORMAL_ROOM = 1,
    BOSS_ROOM,
    TREASURE_ROOM,
    SHOP_ROOM,
    CHALLENGE_ROOM,
    NUM_ROOM_TYPES,
};

struct Room {
    enum RoomTypes type:8;
    u8 mapNum;
};

enum PrefabTypes {
    PREFABS_CAVE,
    PREFABS_DARK_CAVE,
    PREFABS_ICE_CAVE,
    PREFAB_TYPES_COUNT,
};

struct Floorplan {
    u8 numRooms;
    u8 maxRooms;
    struct Room layout[LAYOUT_SIZE];
    struct Queue queue;                     // the queue of rooms to visit during algorithm
    struct Stack endrooms;                  // stores the indices of endrooms in order of decr. distance
    u8 occupiedRooms[20];                   // stores the indices of occupied rooms
    enum PrefabTypes prefabType;
    u16 nextFloorSeed;
};

struct PrefabRules {
    u8 mapGroup;
    u16 bgm;
    u8 battleTerrain;
    u8 lighting; // stored as hours
    s8 offsets[5][2]; // (x, y) entrance cover offsets for each direction
    u8 numNormalRooms;
    const u8* normalRoomIds;
    u8 specialRoomIds[NUM_ROOM_TYPES];
    const struct ItemPoolTable * const itemPools;
    const struct WeightedElement encounterPool[MAX_WEIGHTED_POOL_SIZE];    
};

extern struct Floorplan gFloorplan;
extern const struct PrefabRules gPrefabRules[PREFAB_TYPES_COUNT];

void DebugPrintFloorplan(struct Floorplan* floorplan);
void CreateDebugFloorplan(void);
void SetRoomAsVisited(u8 i);
bool32 IsRoomVisited(u8 i);
bool32 DoesRoomExist(u8 i);
bool32 IsRoomAdjacentToVisited(u8 i);
u32 GetRoomInDirection(u32 dir);
bool32 IsPlayerInFloorMap(void);
void SetWarpDestinationToRoom(u32 index, u32 warpId);
bool32 TryWarpToRoom(u32 target, u32 warpId);
u32 GetRoomType(u32 index);
const struct PrefabRules* GetPrefabRules(enum PrefabTypes prefabType);
void SetRNGToRoomSeed(void);
void GenerateFloorplan(void);
void GoToNextFloor(void);

#endif
