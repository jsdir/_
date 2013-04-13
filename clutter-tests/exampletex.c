#include <clutter/clutter.h>
#include <clutter/x11/clutter-x11.h>
#include <stdlib.h>
#include <cogl/cogl.h>

#define OBJECT_COUNT 1

// six empty rectangles and our stage
ClutterActor *stage = NULL;
ClutterActor *rects[OBJECT_COUNT];
CoglHandle   tex;
CoglMaterial *material;

// the create_rect() function needs to create actual rectangles rather than text boxes
ClutterActor *create_rect() {
  ClutterActor *rect = clutter_rectangle_new_with_color(CLUTTER_COLOR_Transparent);
  clutter_actor_set_size(rect, 256, 128);
  clutter_actor_set_position(rect, 256, 256);
  clutter_actor_set_anchor_point(rect, 128, 64);
  //clutter_actor_set_opacity(rect, 0.5);
  clutter_container_add_actor (CLUTTER_CONTAINER (stage), rect);
  //clutter_actor_show (rect);

  return rect;
}

void move_rect(ClutterActor *rect) {
  clutter_actor_animate (rect,
          CLUTTER_EASE_IN_OUT_CUBIC,
          (rand() / (float)RAND_MAX) * 1000 + 1000,
          "x", (float)(rand() % 1200),
          "y", (float)(rand() % 780),
          "width", (float)(rand() % 600),
          "height", (float)(rand() % 600),
          "rotation-angle-z", (float)(rand() % 360),
          NULL);
}


// we'll be filling in this function later
void on_stage_button_press (ClutterStage *stage, ClutterEvent *event, gpointer data) {
  int index;
  for (index = 0; index < OBJECT_COUNT; index++)
  {
    move_rect(rects[index]);
  }
}

static void
on_stage_pre_paint (ClutterActor *actor)
{
  cogl_set_depth_test_enabled (TRUE);
}

static void
on_stage_post_paint (ClutterActor *actor)
{
  cogl_set_depth_test_enabled (FALSE);
}

static void
rect_paint (ClutterActor *rect)
{
  cogl_path_round_rectangle(0.0f, 
                            0.0f, 
                            clutter_actor_get_width(rect), 
                            clutter_actor_get_height(rect), 
                            15.0f, 
                            10.0f);
  // /cogl_path_ellipse(10.0, 10.0f, 500.0f, 500.0f);
  cogl_clip_push_from_path ();

  //cogl_set_source_texture (tex);
  cogl_set_source (material);
  cogl_rectangle_with_texture_coords (
    0, 
    0, 
    clutter_actor_get_width(rect), 
    clutter_actor_get_height(rect),
    0.0, 0.0, clutter_actor_get_width(rect) / 20.0f, 
    clutter_actor_get_height(rect) / 20.0f);
  cogl_clip_pop ();
  //g_signal_stop_emission_by_name (rect, "paint");
}

int main(int argc, char *argv[]) {
  gchar *file;
  int index;

  clutter_x11_set_use_argb_visual (TRUE);
  if (clutter_init (&argc, &argv) != CLUTTER_INIT_SUCCESS)
    return 1;

  //file = g_build_filename ("/home/Sommer_Jason/pr/clutter-tests", "redhand.png", NULL);
  file = g_build_filename ("/home/Sommer_Jason/Pictures", "moulin.png", NULL);
  tex  = cogl_texture_new_from_file (file,
                                          COGL_TEXTURE_NONE,
                                          COGL_PIXEL_FORMAT_ANY,
                                          NULL);
  material = cogl_material_new();
  cogl_material_set_color4ub(material, 255, 255, 255, 230);
  cogl_material_set_layer(material, 0, tex);

  stage = clutter_stage_new();
  clutter_stage_set_user_resizable(CLUTTER_STAGE(stage), TRUE);
  clutter_stage_set_use_alpha(CLUTTER_STAGE(stage), TRUE);
  clutter_actor_set_opacity(stage, 0);
  clutter_actor_set_size(stage, 512, 512);
  g_signal_connect (stage, "destroy", G_CALLBACK (clutter_main_quit), NULL);
  
  for (index = 0; index < OBJECT_COUNT; index++)
  {
    rects[index] = create_rect();
    g_signal_connect (rects[index], "paint", G_CALLBACK (rect_paint), NULL);
  }

  g_signal_connect (stage, "button-press-event", G_CALLBACK (on_stage_button_press), NULL);
  clutter_stage_set_title(CLUTTER_STAGE(stage), "Spinny boxes ahoy!");
  clutter_actor_show_all (stage);
  clutter_main ();

  return 0;
}
