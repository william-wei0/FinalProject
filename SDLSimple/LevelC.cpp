#include "LevelC.h"
#include "Utility.h"
#define LEVELC_LEFT_EDGE 6.0f
#define LEVELC_RIGHT_EDGE 47.0f
#define LEVELC_BOTTOM_EDGE -14.0f
#define LEVELC_TOP_EDGE -5.0f

GLuint g_font_texture_id_C;

#define LEVEL_WIDTH 54
#define LEVEL_HEIGHT 20
int ENEMY_COUNT_C = 12;
int PROJECTILE_COUNT_C = 4;
bool player_won = false;
bool all_enemies_defeated_C = false;

constexpr char FONTSHEET_FILEPATH[] = "assets/font1.png",
SPRITESHEET_FILEPATH[] = "assets/LinkU.png",
PLATFORM_FILEPATH[] = "assets/platform.png",
WEAPON_FILEPATH[] = "assets/sword.png",
BEAST_FILEPATH[] = "assets/enemy1.png",
SPHERE_FILEPATH[] = "assets/sphere.png",
GANON_FILEPATH[] = "assets/ganon.png";

unsigned int LEVEL_DATA_C[] =
{
4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,2,3,
26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,24,25,
48,49,22,22,22,22,22,22,22,22,22,22,22,22,22,22,46,47,48,49,22,22,22,22,22,22,22,22,22,22,22,22,22,22,46,47,48,49,22,22,22,22,22,22,22,22,22,22,22,22,22,22,46,47,
70,71,22,22,22,22,22,22,22,22,22,22,22,22,22,22,68,69,70,71,22,22,22,22,22,22,22,22,22,22,22,22,22,22,68,69,70,71,22,22,22,22,22,22,22,22,22,22,22,22,22,22,68,69,
92,93,22,22,22,22,22,22,22,22,22,22,22,22,22,22,90,91,92,93,22,22,22,22,22,22,22,22,22,22,22,22,22,22,90,91,92,93,22,22,22,22,22,22,22,22,22,22,22,22,22,22,90,91,
114,115,22,22,22,22,22,22,22,22,22,22,22,22,22,22,112,113,114,115,22,22,22,22,22,22,22,22,22,22,22,22,22,22,112,113,114,115,22,22,22,22,22,22,22,22,22,22,22,22,22,22,90,91,
136,137,22,22,22,22,22,22,22,22,22,22,22,22,22,22,134,135,136,137,22,22,22,22,22,22,22,22,22,22,22,22,22,22,134,135,136,137,22,22,22,22,22,22,22,22,22,22,22,22,22,22,134,135,
158,159,22,22,22,22,22,22,22,22,22,22,22,22,22,22,156,157,158,159,22,22,22,22,22,22,22,22,22,22,22,22,22,22,156,157,158,159,22,22,22,22,22,22,22,22,22,22,22,22,22,22,156,157,
180,181,50,51,52,53,54,55,56,57,58,59,60,61,62,63,178,179,180,181,50,51,52,53,54,55,56,57,58,59,60,61,62,63,178,179,180,181,22,22,22,22,22,22,22,22,22,22,22,22,22,22,178,179,
202,203,72,73,74,75,76,77,78,79,80,81,82,83,84,85,200,201,202,203,72,73,74,75,76,77,78,79,80,81,82,83,84,85,200,201,202,203,22,22,22,22,22,22,22,22,22,22,22,22,22,22,200,201,
4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,2,3,4,5,22,22,22,22,22,22,22,22,22,22,22,22,22,22,2,3,
26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,24,25,26,27,22,22,22,22,22,22,22,22,22,22,22,22,22,22,24,25,
48,49,22,22,22,22,22,22,22,22,22,22,22,22,22,22,46,47,48,49,22,22,22,22,22,22,22,22,22,22,22,22,22,22,46,47,48,49,22,22,22,22,22,22,22,22,22,22,22,22,22,22,46,47,
70,71,22,22,22,22,22,22,22,22,22,22,22,22,22,22,68,69,70,71,22,22,22,22,22,22,22,22,22,22,22,22,22,22,68,69,70,71,22,22,22,22,22,22,22,22,22,22,22,22,22,22,68,69,
92,93,22,22,22,22,22,22,22,22,22,22,22,22,22,22,90,91,92,93,22,22,22,22,22,22,22,22,22,22,22,22,22,22,90,91,92,93,22,22,22,22,22,22,22,22,22,22,22,22,22,22,90,91,
114,115,22,22,22,22,22,22,22,22,22,22,22,22,22,22,112,113,114,115,22,22,22,22,22,22,22,22,22,22,22,22,22,22,112,113,114,115,22,22,22,22,22,22,22,22,22,22,22,22,22,22,90,91,
136,137,22,22,22,22,22,22,22,22,22,22,22,22,22,22,134,135,136,137,22,22,22,22,22,22,22,22,22,22,22,22,22,22,134,135,136,137,22,22,22,22,22,22,22,22,22,22,22,22,22,22,134,135,
158,159,22,22,22,22,22,22,22,22,22,22,22,22,22,22,156,157,158,159,22,22,22,22,22,22,22,22,22,22,22,22,22,22,156,157,158,159,22,22,22,22,22,22,22,22,22,22,22,22,22,22,156,157,
180,181,50,51,52,53,54,55,56,57,58,59,60,61,62,63,178,179,180,181,50,51,52,53,54,55,56,57,58,59,60,61,62,63,178,179,180,181,50,51,52,53,54,55,56,57,58,59,60,61,62,63,178,179,
202,203,72,73,74,75,76,77,78,79,80,81,82,83,84,85,200,201,202,203,72,73,74,75,76,77,78,79,80,81,82,83,84,85,200,201,202,203,72,73,74,75,76,77,78,79,80,81,82,83,84,85,200,201,


};

LevelC::~LevelC()
{
    delete[] m_game_state.enemies;
    m_game_state.enemies = nullptr;
    delete    m_game_state.player;
    delete    m_game_state.map;
    Mix_FreeChunk(m_game_state.sword);
    Mix_FreeMusic(m_game_state.bgm);
}

void LevelC::initialise()
{
    GLuint map_texture_id = Utility::load_texture("assets/LOZ_dungeon - Copy.png");
    m_game_state.map = new Map(LEVEL_WIDTH, LEVEL_HEIGHT, LEVEL_DATA_C, map_texture_id, 1.0f, 22, 11);

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
    m_game_state.player->set_position(glm::vec3(2.0f, -5.0f, 0.0f));
    m_game_state.player->set_scale(glm::vec3(1.0f, 1.0f, 1.0f));


    /**
     Enemies' stuff */
    GLuint beast_texture_id = Utility::load_texture(BEAST_FILEPATH);

    m_game_state.enemies = new Entity[ENEMY_COUNT_C + PROJECTILE_COUNT_C];

    for (int i = 0; i < 4; i++)
    {
        m_game_state.enemies[i] = Entity(beast_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, WALKER, IDLE);
        m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    }
    m_game_state.enemies[0].set_position(glm::vec3(12.0f, -4.0f, 0.0f));
    m_game_state.enemies[1].set_position(glm::vec3(30.0f, -7.0f, 0.0f));
    m_game_state.enemies[2].set_position(glm::vec3(27.0f, -16.0f, 0.0f));
    m_game_state.enemies[3].set_position(glm::vec3(26.0f, -11.0f, 0.0f));

    //GLuint shooter_texture_id = Utility::load_texture(OCTOROCK_FILEPATH);
    for (int i = 4; i < 8; i++)
    {
        m_game_state.enemies[i] = Entity(beast_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, SHOOTER, IDLE);
        m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
        m_game_state.enemies[i].set_projectile_id(ENEMY_COUNT_C + PROJECTILE_COUNT_C - i + 3);
    }
    m_game_state.enemies[4].set_position(glm::vec3(40.0f, -11.0f, 0.0f));
    m_game_state.enemies[5].set_position(glm::vec3(46.0f, -15.0f, 0.0f));
    m_game_state.enemies[6].set_position(glm::vec3(5.0f, -18.0f, 0.0f));
    m_game_state.enemies[7].set_position(glm::vec3(7.0f, -13.0f, 0.0f));



    for (int i = 8; i < 11; i++)
    {
        m_game_state.enemies[i] = Entity(beast_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, GUARD, IDLE);
        m_game_state.enemies[i].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
        m_game_state.enemies[i].set_width(2.0f);
        m_game_state.enemies[i].set_height(2.0f);
        m_game_state.enemies[i].set_scale(glm::vec3(2.0f, 2.0f, 2.0f));
    }
    m_game_state.enemies[8].set_position(glm::vec3(27.0f, -11.0f, 0.0f));
    m_game_state.enemies[9].set_position(glm::vec3(17.0f, -15.0f, 0.0f));
    m_game_state.enemies[10].set_position(glm::vec3(21.0f, -17.0f, 0.0f));
    m_game_state.enemies[10].set_width(2.0f);
    m_game_state.enemies[10].set_height(2.0f);

    GLuint ganon_texture_id = Utility::load_texture(GANON_FILEPATH);

    m_game_state.enemies[11] = Entity(ganon_texture_id, 1.0f, 1.0f, 1.0f, ENEMY, GANON, IDLE);
    m_game_state.enemies[11].set_acceleration(glm::vec3(0.0f, 0.0f, 0.0f));
    m_game_state.enemies[11].set_position(glm::vec3(45.0f, -10.0f, 0.0f));
    m_game_state.enemies[11].set_width(5.0f);
    m_game_state.enemies[11].set_height(5.0f);
    m_game_state.enemies[11].set_scale(glm::vec3(5.0f,5.0f, 4.0f));
    m_game_state.enemies[11].set_lives(3);


    GLuint projectile_texture_id = Utility::load_texture(SPHERE_FILEPATH);
    for (int i = ENEMY_COUNT_C; i < ENEMY_COUNT_C + PROJECTILE_COUNT_C; i++)
    {
        m_game_state.enemies[i] = Entity(projectile_texture_id, 2.0f, 1.0f, 1.0f, ENEMY, PROJECTILE, IDLE);
        m_game_state.enemies[i].set_position(glm::vec3(29.0f - i, -4.0f, 0.0f));
        m_game_state.enemies[i].deactivate();
    }


    GLuint weapon_texture_id = Utility::load_texture(WEAPON_FILEPATH);
    m_game_state.weapon = new Entity(weapon_texture_id, 2.0f, 1.0f, 1.0f, WEAPON, PROJECTILE, IDLE);
    m_game_state.weapon->set_scale(glm::vec3(1.0f, 1.0f, 1.0f));
    m_game_state.weapon->set_position(glm::vec3(5.0f, -9.0f, 0.0f));
    /**
     BGM and SFX
     */
    g_font_texture_id_C = Utility::load_texture(FONTSHEET_FILEPATH);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    m_game_state.win_sfx = Mix_LoadWAV("assets/Win.wav");
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

void LevelC::update(float delta_time)
{

    if (player_won) return;
    m_game_state.player->update(delta_time, m_game_state.player, m_game_state.weapon, m_game_state.enemies, ENEMY_COUNT_C, PROJECTILE_COUNT_C, m_game_state.map);
    m_game_state.weapon->update(delta_time, m_game_state.player, m_game_state.weapon, m_game_state.enemies, 0, 0, m_game_state.map);
    if (m_game_state.player->get_was_hit() || m_game_state.player->get_position().y < LEVELC_BOTTOM_EDGE-6.0f) {
        this->set_lives(lives - 1);
        Mix_PlayChannel(-1, m_game_state.death_sfx, 0);

        if (this->get_lives() <= 0) {
            m_game_state.player->set_lives(0);
            m_game_state.player->deactivate();
            return;
        }

        m_game_state.next_scene_id = 3;
    }
    

    for (int i = 0; i < ENEMY_COUNT_C + PROJECTILE_COUNT_C; i++)
    {
        m_game_state.enemies[i].update(delta_time, m_game_state.player, NULL, m_game_state.enemies, ENEMY_COUNT_C + PROJECTILE_COUNT_C, PROJECTILE_COUNT_C, m_game_state.map);
        if (i < ENEMY_COUNT_C && m_game_state.enemies[i].get_is_active()) {
            all_enemies_defeated_C = false;
        }
    }
    if (m_game_state.enemies[11].get_lives() <= 0) {
        Mix_PlayChannel(-1, m_game_state.win_sfx, 0);
        m_game_state.enemies[11].deactivate();
        player_won = true;
    }
}


void LevelC::render(ShaderProgram *g_shader_program)
{
    m_game_state.map->render(g_shader_program);
    m_game_state.player->render(g_shader_program);
    m_game_state.weapon->render(g_shader_program);
    for (int i = 0; i < ENEMY_COUNT_C + PROJECTILE_COUNT_C; i++)
        m_game_state.enemies[i].render(g_shader_program);
    
    glm::vec3 lives_text_location = glm::vec3(0.0f);

    if (m_game_state.player->get_position().x > LEVELC_LEFT_EDGE)
        lives_text_location.x = m_game_state.player->get_position().x - 6.0f;
    else lives_text_location.x = LEVELC_LEFT_EDGE - 6.0f;

    if (m_game_state.player->get_position().y > LEVELC_BOTTOM_EDGE)
        lives_text_location.y = m_game_state.player->get_position().y + 4.3f;
    else lives_text_location.y = LEVELC_BOTTOM_EDGE + 4.3f;
    
    Utility::draw_text(g_shader_program, g_font_texture_id_C,
        "Lives: " + std::to_string((m_game_state.player->get_lives())),
        0.5f, 0.0f, lives_text_location);


    if (player_won) {
        Utility::draw_text(g_shader_program, g_font_texture_id_C,
            "You Won!",
            1.0f, 0.0f, glm::vec3(m_game_state.player->get_position().x - 3.5f, m_game_state.player->get_position().y + 2.0f, 0.0f));
    }


    if (this->get_lives() <= 0) {
        glm::vec3 game_over_text_location = glm::vec3(0.0f);

        if (m_game_state.player->get_position().x > LEVELC_LEFT_EDGE)
            game_over_text_location.x = m_game_state.player->get_position().x - 4.3f;
        else game_over_text_location.x = LEVELC_LEFT_EDGE - 4.3f;

        if (m_game_state.player->get_position().y > LEVELC_BOTTOM_EDGE)
            game_over_text_location.y = m_game_state.player->get_position().y + 2.0f;
        else game_over_text_location.y = LEVELC_BOTTOM_EDGE + 2.0f;

        Utility::draw_text(g_shader_program, g_font_texture_id_C,
            "Game Over",
            1.0f, 0.0f, game_over_text_location);
    }

}

void LevelC::move_camera(glm::mat4& g_view_matrix) {
    float x = 0;
    float y = 0;

    if (m_game_state.player->get_position().x < LEVELC_LEFT_EDGE) {
        x = -LEVELC_LEFT_EDGE;
    }
    else if (m_game_state.player->get_position().x > LEVELC_RIGHT_EDGE) {
        x = -LEVELC_RIGHT_EDGE;
    }
    else {
        x = -m_game_state.player->get_position().x;
    }

    if (m_game_state.player->get_position().y > LEVELC_TOP_EDGE) {
        y = -LEVELC_TOP_EDGE;
    }
    else if (m_game_state.player->get_position().y < LEVELC_BOTTOM_EDGE) {
        y = -LEVELC_BOTTOM_EDGE;
    }
    else {
        y = -m_game_state.player->get_position().y;
    }

    g_view_matrix = glm::translate(g_view_matrix, glm::vec3(x, y, 0.0f));

}