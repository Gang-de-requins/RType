#ifndef MACROS_HPP
#define MACROS_HPP

#define DEFAULT_NB_ENTITIES 1000 // Default number of entities
#define DEFAULT_NB_SCENES 10 // Default number of scenes

/* -------------------- Colors -------------------- */
#define GE_LIGHTGRAY  CLITERAL(ecs::Color){ 200, 200, 200, 255 }   // Light Gray
#define GE_GRAY       CLITERAL(ecs::Color){ 130, 130, 130, 255 }   // Gray
#define GE_DARKGRAY   CLITERAL(ecs::Color){ 80, 80, 80, 255 }      // Dark Gray
#define GE_YELLOW     CLITERAL(ecs::Color){ 253, 249, 0, 255 }     // Yellow
#define GE_GOLD       CLITERAL(ecs::Color){ 255, 203, 0, 255 }     // Gold
#define GE_ORANGE     CLITERAL(ecs::Color){ 255, 161, 0, 255 }     // Orange
#define GE_PINK       CLITERAL(ecs::Color){ 255, 109, 194, 255 }   // Pink
#define GE_RED        CLITERAL(ecs::Color){ 230, 41, 55, 255 }     // Red
#define GE_MAROON     CLITERAL(ecs::Color){ 190, 33, 55, 255 }     // Maroon
#define GE_GREEN      CLITERAL(ecs::Color){ 0, 228, 48, 255 }      // Green
#define GE_LIME       CLITERAL(ecs::Color){ 0, 158, 47, 255 }      // Lime
#define GE_DARKGREEN  CLITERAL(ecs::Color){ 0, 117, 44, 255 }      // Dark Green
#define GE_SKYBLUE    CLITERAL(ecs::Color){ 102, 191, 255, 255 }   // Sky Blue
#define GE_BLUE       CLITERAL(ecs::Color){ 0, 121, 241, 255 }     // Blue
#define GE_DARKBLUE   CLITERAL(ecs::Color){ 0, 82, 172, 255 }      // Dark Blue
#define GE_PURPLE     CLITERAL(ecs::Color){ 200, 122, 255, 255 }   // Purple
#define GE_VIOLET     CLITERAL(ecs::Color){ 135, 60, 190, 255 }    // Violet
#define GE_DARKPURPLE CLITERAL(ecs::Color){ 112, 31, 126, 255 }    // Dark Purple
#define GE_BEIGE      CLITERAL(ecs::Color){ 211, 176, 131, 255 }   // Beige
#define GE_BROWN      CLITERAL(ecs::Color){ 127, 106, 79, 255 }    // Brown
#define GE_DARKBROWN  CLITERAL(ecs::Color){ 76, 63, 47, 255 }      // Dark Brown
#define GE_WHITE      CLITERAL(ecs::Color){ 255, 255, 255, 255 }   // White
#define GE_BLACK      CLITERAL(ecs::Color){ 0, 0, 0, 255 }         // Black
#define GE_BLANK      CLITERAL(ecs::Color){ 0, 0, 0, 0 }           // Blank (Transparent)
#define GE_MAGENTA    CLITERAL(ecs::Color){ 255, 0, 255, 255 }     // Magenta

/* -------------------- Components -------------------- */
#define ALL_COMPONENTS "Acceleration",\
                            "Animation",\
                            "Color",\
                            "Collision",\
                            "Controllable",\
                            "Damage",\
                            "FontSize",\
                            "Health",\
                            "Music",\
                            "Position",\
                            "Rectangle",\
                            "Rotation",\
                            "Scale",\
                            "Sound",\
                            "Sprite",\
                            "Text",\
                            "Velocity"

#endif /* MACROS_HPP */