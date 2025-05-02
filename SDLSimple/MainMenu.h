#include "Scene.h"

class MainMenu : public Scene {
public:
    // ————— STATIC ATTRIBUTES ————— //
    int ENEMY_COUNT = 0;
    
    // ————— DESTRUCTOR ————— //
    ~MainMenu();
    
    // ————— METHODS ————— //
    void initialise() override;
    void update(float delta_time) override;
    void render(ShaderProgram *program) override;
    void move_camera(glm::mat4& g_view_matrix) override;

};
