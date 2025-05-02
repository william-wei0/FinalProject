#include "LevelA.h"
#include "Utility.h"


#define LEVEL1_LEFT_EDGE 0.0f
#define LEVEL1_RIGHT_EDGE 10.0f
#define LEVEL1_BOTTOM_EDGE -18.0f

#define LEVEL_WIDTH 43
#define LEVEL_HEIGHT 18

GLuint g_font_texture_id_A;
int ENEMY_COUNT = 5;
int PROJECTILE_COUNT = 4;
bool all_enemies_defeated = false;

constexpr char FONTSHEET_FILEPATH[] = "assets/font1.png",
SPRITESHEET_FILEPATH[] = "assets/LinkU.png",
WEAPON_FILEPATH[] = "assets/sword.png",
OCTOROCK_FILEPATH[] = "assets/octorock.png",
BEAST_FILEPATH[] = "assets/armos.png",
SPHERE_FILEPATH[] = "assets/sphere.png";


unsigned int LEVEL_DATA_A[] =
{
256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,326,327,328,329,330,331,256,256,256,256,256,256,320,320,320,320,320,320,320,320,320,320,320,320,320,320,320,320,320,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,390,391,392,393,394,395,256,256,256,256,256,256,320,256,256,256,256,256,256,256,256,320,320,320,320,320,320,320,320,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,454,455,456,457,458,459,256,256,256,256,256,256,320,256,256,256,256,256,256,256,256,320,320,320,320,320,320,320,320,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,518,519,520,521,522,523,256,256,256,256,256,256,320,256,256,256,256,256,256,256,256,320,320,320,320,320,320,320,320,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,582,583,584,585,586,587,256,256,256,256,256,256,320,256,256,256,256,256,256,256,256,320,320,320,320,320,320,320,320,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,256,320,320,320,320,320,320,320,320,320,320,320,320,256,256,256,256,256,256,256,256,320,320,320,320,320,320,320,320,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,320,320,320,320,320,320,320,320,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,
256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,

};

LevelA::~LevelA()
{
    delete[] m_game_state.enemies;
    m_game_state.enemies = nullptr;
    delete    m_game_state.player;
    delete    m_game_state.map;
    delete m_game_state.weapon;
    Mix_FreeChunk(m_game_state.sword);
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelA::initialise()
{
    GLuint map_texture_id = Utility::load_texture("assets/minish_cap_tileset.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_DATA_A, map_texture_id, 1.0f, 64, 32);

    GLuint player_texture_id = Utility::load_texture(SPRITESHEET_FILEPATH);

    int player_walking_animation[4][4] =
    {
        {12, 13, 14, 15 },
        { 8, 9, 10, 11},
        { 7, 6, 5, 4 },
        { 0, 1, 2, 3}
    };

    glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

    m_game_state.player = new Entity(
        player_texture_id,         // texture id
        6.0f,                      // speed
        acceleration,              // acceleration
        6.0f,                      // jumping power
        player_walking_animation,  // animation index sets
        0.0f,                      // animation time
        4,                         // animation frame amount
        0,                         // current animation index
        4,                         // animation column amount
        4,                         // animation row amount
        1.0f,                      // width
        1.0f,                       // height
        PLAYER
    );
    m_game_state.player->set_lives(lives);
    m_game_state.player->set_position(glm::vec3(7.0f, -9.0f, 0.0f));
    m_game_state.player->set_scale(glm::vec3(1.0f, 1.0f, 1.0f));


    /**
     Enemies' stuff */
    GLuint enemy_texture_id = Utility::load_texture(BEAST_FILEPATH);

    m_game_state.enemies = new Entity[ENEMY_COUNT + PROJECTILE_COUNT];

    for (int i = 0; i < ENEMY_COUNT; i++)
    {
        m_game_state.enemies[i] = Entity(enemy_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, GUARD, IDLE);
        m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    }
    m_game_state.enemies[0].set_position(glm::vec3(20.0f, -11.0f, 0.0f));
    m_game_state.enemies[0].set_movement(glm::vec3(0.0f));
    
    
    m_game_state.enemies[1].set_ai_type(SHOOTER);
    m_game_state.enemies[1].set_position(glm::vec3(19.5f, -7.0f, 0.0f));
    m_game_state.enemies[1].set_movement(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[1].set_projectile_id(ENEMY_COUNT);


    m_game_state.enemies[2].set_ai_type(WALKER);
    m_game_state.enemies[2].set_position(glm::vec3(29.0f, -8.0f, 0.0f));
    m_game_state.enemies[2].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[2].set_width(2.0f);
    m_game_state.enemies[2].set_height(2.0f);
    m_game_state.enemies[2].set_scale(glm::vec3(2.0f, 2.0f, 2.0f));

    m_game_state.enemies[3].set_ai_type(WALKER);
    m_game_state.enemies[3].set_position(glm::vec3(29.0f, -4.0f, 0.0f));
    m_game_state.enemies[3].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[3].set_width(2.0f);
    m_game_state.enemies[3].set_height(2.0f);
    m_game_state.enemies[3].set_scale(glm::vec3(2.0f, 2.0f, 2.0f));

    m_game_state.enemies[4].set_ai_type(SHOOTER);
    m_game_state.enemies[4].set_position(glm::vec3(29.0f, -5.0f, 0.0f));
    m_game_state.enemies[4].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[4].set_width(2.0f);
    m_game_state.enemies[4].set_height(2.0f);
    m_game_state.enemies[4].set_scale(glm::vec3(2.0f, 2.0f, 2.0f));
    m_game_state.enemies[4].set_projectile_id(ENEMY_COUNT-1);

    m_game_state.enemies[5].set_ai_type(SHOOTER);
    m_game_state.enemies[5].set_position(glm::vec3(20.0f, -5.0f, 0.0f));
    m_game_state.enemies[5].set_movement(glm::vec3(0.0f));
    m_game_state.enemies[5].set_width(2.0f);
    m_game_state.enemies[5].set_height(2.0f);
    m_game_state.enemies[5].set_scale(glm::vec3(2.0f, 2.0f, 2.0f));
    m_game_state.enemies[5].set_projectile_id(ENEMY_COUNT - 2);

    GLuint projectile_texture_id = Utility::load_texture(SPHERE_FILEPATH);
    for (int i = ENEMY_COUNT; i < ENEMY_COUNT + PROJECTILE_COUNT ; i++)
    {
        m_game_state.enemies[i] = Entity(projectile_texture_id, 2.0f, 1.0f, 1.0f, ENEMY, PROJECTILE, IDLE);
        m_game_state.enemies[i].set_position(glm::vec3(29.0f-i, -4.0f, 0.0f));
        m_game_state.enemies[i].deactivate();
    }


    GLuint weapon_texture_id = Utility::load_texture(WEAPON_FILEPATH);
    m_game_state.weapon = new Entity(weapon_texture_id, 2.0f, 1.0f, 1.0f, WEAPON, PROJECTILE, IDLE);
    m_game_state.weapon->set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
    m_game_state.weapon->set_position(glm::vec3(5.0f, -9.0f, 0.0f));
    /**
     BGM and SFX
     */
    g_font_texture_id_A = Utility::load_texture(FONTSHEET_FILEPATH);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);

    m_game_state.bgm = Mix_LoadMUS("assets/Adventure Meme.mp3");
    Mix_PlayMusic(m_game_state.bgm, -1);
    Mix_VolumeMusic(3);

    m_game_state.sword = Mix_LoadWAV("assets/sword.wav");
    m_game_state.death_sfx = Mix_LoadWAV("assets/male_death.wav");
    Mix_VolumeChunk(
        m_game_state.sword,
        20  
    );

    Mix_VolumeChunk(
        m_game_state.death_sfx,  
        30  
    );
   
    m_game_state.next_scene_id = 0;
}

void LevelA::update(float delta_time)
{
    all_enemies_defeated = true;

    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.weapon, m_game_state.enemies, ENEMY_COUNT + PROJECTILE_COUNT, PROJECTILE_COUNT, m_game_state.map);
    m_game_state.weapon->update(delta_time, m_game_state.player, m_game_state.weapon, m_game_state.enemies, 0, 0, m_game_state.map);


    if (m_game_state.player->get_was_hit()) {
        this->set_lives(lives - 1);

        Mix_PlayChannel(-1, m_game_state.death_sfx, 0);

        if (this->get_lives() <= 0) {
            m_game_state.player->set_lives(0);
            m_game_state.player->deactivate();
            return;
        }

        m_game_state.next_scene_id = 1;
    }

    for (int i = 0; i < ENEMY_COUNT + PROJECTILE_COUNT; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, NULL, m_game_state.enemies, ENEMY_COUNT + PROJECTILE_COUNT, PROJECTILE_COUNT, m_game_state.map);
        if (i < ENEMY_COUNT && m_game_state.enemies[i].get_is_active()) {
            all_enemies_defeated = false;
        }
    }
    if (all_enemies_defeated) {
        m_game_state.next_scene_id = 2;
    }
}


void LevelA::render(ShaderProgram* g_shader_program)
{
    m_game_state.map->render(g_shader_program);
    m_game_state.player->render(g_shader_program);
    m_game_state.weapon->render(g_shader_program);

    for (int i = 0; i < ENEMY_COUNT+PROJECTILE_COUNT; i++)
        m_game_state.enemies[i].render(g_shader_program);
    Utility::draw_text(g_shader_program, g_font_texture_id_A, 
                        "Lives: " + std::to_string((m_game_state.player->get_lives())),
                        0.5f, 0.0f, glm::vec3(m_game_state.player->get_position().x-6.0f, m_game_state.player->get_position().y+4.3f, 0.0f));

    if (this->get_lives() <= 0) {
        Utility::draw_text(g_shader_program, g_font_texture_id_A,
            "Game Over",
            1.0f, 0.0f, glm::vec3(m_game_state.player->get_position().x - 4.3f, m_game_state.player->get_position().y + 3.0f, 0.0f));
    }
}

void LevelA::move_camera(glm::mat4& g_view_matrix) {
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