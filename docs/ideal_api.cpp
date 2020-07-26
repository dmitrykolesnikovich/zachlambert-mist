// ----- Ideal api usage -----
// Ideas about what an ideal api would be (in terms of ease of use), to help
// figure out how to design the api.

int main()
{
    Window window; // Sensible defaults
    window.set_size(720, 480); // Can edit attributes afterwards
    window.create(); // May need, dependent on how the window is implemented


    Resources resources;

    resources.create_model_from_file("frog", "animals/frog.obj");

    MaterialConfig matte_red;
    matte_red.set_color(1, 0, 0);
    resources.create_material_from_config("matte red", matte_red);

    // Can also create from texture, etc
    // ie: Anything which may be defined in a .mtl file

    ModelConfig my_sphere_config;
    my_sphere_config.set_type(ModelType::SPHERE);
    my_sphere_config.set_dimension("radius", 10); // Only applicable for certain types
    my_sphere_config.set_material("matte red");
    resources.create_model_from_config("my_sphere", my_sphere_config);

    Entity frog;
    frog.set_model("frog");
    frog.set_orientation(...);

    Entity sphere;
    sphere.set_model("my_sphere");
    sphere.set_position(...);

    Scene scene;
    scene.add_entity("frog", frog);
    scene.add_entity("sphere", sphere);
    // To make further changes to the entities stored
    // within the scene, use scene.get_entity(name)
    // Needs to return a pointer, to allow for returning a null pointer when
    // nothing is found.

    Light light;
    light.set_position(...);
    light.set_color(...);
    light.set_power(...);
    scene.add_light(light);

    Camera &camera = scene.get_camera();
    camera.set_position(0.0f, 0.0f, 5.0f);

    Renderer renderer;

    Clock clock;

    while (window.is_running()) {
        float dt = clock.tick();
        // game logic
        renderer.render(resources, scene);
    }

    return 0;
}
