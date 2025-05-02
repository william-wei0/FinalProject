#include "MainMenu.h"
#include "Utility.h"

#define LEVEL1_LEFT_EDGE 6.0f
#define LEVEL1_RIGHT_EDGE 10.0f
#define LEVEL1_BOTTOM_EDGE -12.5f

#define LEVEL_WIDTH 39
#define LEVEL_HEIGHT 18

GLuint g_font_texture_id;

constexpr char  FONTSHEET_FILEPATH[] = "assets/font1.png",
SPRITESHEET_FILEPATH[] = "assets/LOZ_dungeon.png";
    

unsigned int LEVEL_DATA[] =
{
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
    1, 1, 22,22,22,22,22,22,22,1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};

MainMenu::~MainMenu()
{
    delete[] m_game_state.enemies;
    delete    m_game_state.player;
    delete    m_game_state.map;
    delete    m_game_state.weapon;
    Mix_FreeChunk(m_game_state.sword);
    Mix_FreeMusic(m_game_state.bgm);
}

void MainMenu::initialise()
{
    GLuint map_texture_id = Utility::load_texture("assets/LOZ_dungeon.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_DATA, map_texture_id, 1.0f, 22, 11);
    
    GLuint player_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);

    int player_walking_animation[4][4] =
    {
        { 7, 6, 5, 4},  // Left
        { 0, 1, 2, 3},  // Right
        { 8, 9, 10, 11 }, // for George to move upwards,
        { 12, 13, 14, 15 }   // for George to move downwards
    };

    glm::vec3 acceleration = glm::vec3(0.0f, -4.81f, 0.0f);

    m_game_state.player = new Entity(
        player_texture_id,         // texture id
        0.0f,                      // speed
        acceleration,              // acceleration
        5.0f,                      // jumping power
        player_walking_animation,  // animation index sets
        10000.0f,                      // animation time
        4,                         // animation frame amount
        0,                         // current animation index
        4,                         // animation column amount
        4,                         // animation row amount
        1.0f,                      // width
        1.0f,                       // height
        PLAYER
    );
    m_game_state.player->set_lives(lives);
    m_game_state.player->set_position(glm::vec3(16.5f, -10.0f, 0.0f));
    m_game_state.next_scene_id = 0;

    /**
 Enemies' stuff */
    m_game_state.enemies = new Entity[ENEMY_COUNT];

    m_game_state.weapon = new Entity(
        player_texture_id,         // texture id
        0.0f,                      // speed
        acceleration,              // acceleration
        5.0f,                      // jumping power
        player_walking_animation,  // animation index sets
        10000.0f,                      // animation time
        4,                         // animation frame amount
        0,                         // current animation index
        4,                         // animation column amount
        4,                         // animation row amount
        1.0f,                      // width
        1.0f,                       // height
        PLAYER
    );
    /*
     BGM and SFX
     */

    g_font_texture_id = Utility::load_texture(FONTSHEET_FILEPATH);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    
    m_game_state.bgm = Mix_LoadMUS("assets/Adventure Meme.mp3");
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(3);
    
    m_game_state.player->update(0, m_game_state.player, m_game_state.weapon, m_game_state.enemies, ENEMY_COUNT, 0, m_game_state.map);
    m_game_state.player->deactivate();
}

void MainMenu::update(float delta_time)
{
    if (m_game_state.player->get_clicked_enter()) 
            m_game_state.next_scene_id = 1;
}


void MainMenu::render(ShaderProgram *g_shader_program)
{
    
    m_game_state.map->render(g_shader_program);
    m_game_state.player->render(g_shader_program);
    Utility::draw_text(g_shader_program, g_font_texture_id, "Link's Adventure", 0.75f, 0.0f, glm::vec3(10.5f, -6.0f, 0.0f));
    Utility::draw_text(g_shader_program, g_font_texture_id, "Press Enter to Start", 0.5f, 0.0f, glm::vec3(12.0f, -8.0f, 0.0f));
    Utility::draw_text(g_shader_program, g_font_texture_id, "Defeat all enemies", 0.5f, 0.0f, glm::vec3(12.0f, -10.0f, 0.0f));
    Utility::draw_text(g_shader_program, g_font_texture_id, "on each stage", 0.5f, 0.0f, glm::vec3(13.0f, -12.0f, 0.0f));
}

void MainMenu::move_camera(glm::mat4& g_view_matrix) {
    if (m_game_state.player->get_position().x > LEVEL1_LEFT_EDGE) {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-m_game_state.player->get_position().x, 0, 0));
    }
    else {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(-LEVEL1_LEFT_EDGE, 0, 0));
    }

    if (m_game_state.player->get_position().y > LEVEL1_BOTTOM_EDGE) {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(0.0f, -m_game_state.player->get_position().y, 0.0f));
    }
    else {
        g_view_matrix = glm::translate(g_view_matrix, glm::vec3(0, -LEVEL1_BOTTOM_EDGE, 0));
    }

}