#pragma once

#include <cstdint>

enum DoomEdThing : uint16_t {
    Player1StartPos = 1,
    Player2StartPos = 2,
    Player3StartPos = 3,
    Player4StartPos = 4,
    BlueKeycard = 5,
    YellowKeycard = 6,
    Spiderdemon = 7,
    Backpack = 8,
    ShotgunGuy = 9,
    BloodyMess1 = 10,
    DeathmatchStart = 11,
    BloodyMess2 = 12,
    RedKeycard = 13,
    // TODO...
};

enum ThingFlag : uint16_t {
    ThingIsOnSkillLevels1And2 = 1 << 0,
    ThingIsOnSkillLevel3 = 1 << 1,
    ThingIsOnSkillLevels4And5 = 1 << 2,
    ThingIsDead = 1 << 3,
    ThingIsNotInSinglePlayer = 1 << 4,
    // TODO...
};

enum LinedefFlag : uint16_t {
    BlocksPlayersAndMonsters = 1 << 0,
    BlocksMonsters = 1 << 1,
    TwoSided = 1 << 2,
    UpperTextureIsUnpegged = 1 << 3,
    LowerTextureIsUnpegged = 1 << 4,
    Secret = 1 << 5,
    BlocksSound = 1 << 6,
    NeverShowsOnAutomap = 1 << 7,
    AlwaysShowsOnAutomap = 1 << 8,
    // TODO...
};

#pragma pack(push, 1)

struct Thing {
    int16_t x;
    int16_t y;
    int16_t angle;
    DoomEdThing type;
    ThingFlag flags;
};

struct Linedef {
    uint16_t startVertex;
    uint16_t endVertex;
    LinedefFlag flags;
    uint16_t specialType;
    uint16_t sectorTag;
    uint16_t rightSidedef;
    uint16_t leftSidedef;
};

struct Sidedef {
    int16_t xOffset;
    int16_t yOffset;
    char upperTexture[8];
    char lowerTexture[8];
    char middleTexture[8];
    uint16_t sector;
};

struct Vertex {
    int16_t x;
    int16_t y;
};

#pragma pack(pop)