#include <clutter/clutter.h>
#include <clutter/x11/clutter-x11.h>
#include <GL/gl.h>
#include <stdlib.h>

// six empty rectangles and our stage
ClutterActor *stage = NULL;
ClutterActor *rect1 = NULL;
ClutterActor *rect2 = NULL;
ClutterActor *rect3 = NULL;
ClutterActor *rect4 = NULL;
ClutterActor *rect5 = NULL;
ClutterActor *rect6 = NULL;
ClutterActor *rect7 = NULL;
ClutterActor *rect8 = NULL;

// the create_rect() function needs to create actual rectangles rather than text boxes
ClutterActor *create_rect(ClutterColor col) {
  ClutterActor *rect = clutter_rectangle_new_with_color(&col);
  clutter_actor_set_size(rect, 256, 128);
  clutter_actor_set_position(rect, 256, 256);
  clutter_actor_set_anchor_point(rect, 128, 64);
  clutter_container_add_actor (CLUTTER_CONTAINER (stage), rect);
  clutter_actor_show (rect);

  return rect;
}

void move_rect(ClutterActor *rect) {
  clutter_actor_animate (rect,
          CLUTTER_EASE_IN_OUT_CUBIC,
          500,
          "x", (float)(rand() % 1200),
          "y", (float)(rand() % 780),
          "width", (float)(rand() % 600),
          "height", (float)(rand() % 600),
          //"rotation-angle-z", (float)(rand() % 360),
          NULL);
}


// we'll be filling in this function later
void on_stage_button_press (ClutterStage *stage, ClutterEvent *event, gpointer data) {
   move_rect(rect1);
   move_rect(rect2);
   move_rect(rect3);
   move_rect(rect4);
   move_rect(rect5);
   move_rect(rect6);
   move_rect(rect7);
   move_rect(rect8);
}

static void
rect_paint (ClutterActor *rect)
{
  //float radius = clutter_actor_get_width (hand) / 2.0 + 0.5;

  CoglColor fill_color;
  cogl_color_init_from_4ub (&fill_color, 200, 200, 200, 200);

  cogl_set_source_color (&fill_color);

  //cogl_path_move_to (0.0f, 0.0f);
  /*cogl_path_arc (radius, radius,
                 radius, radius,
                 -90.0,
                 -90.0 + end_angle * 180.0 / G_PI);
  cogl_path_arc (radius, radius,
                 radius - HAND_WIDTH, radius - HAND_WIDTH,
                 -90.0 + end_angle * 180.0 / G_PI,
                 -90.0);*/
  //cogl_path_move_to (0.0f, 0.0f);
  cogl_path_round_rectangle(0.0f, 
                            0.0f, 
                            clutter_actor_get_width(rect), 
                            clutter_actor_get_height(rect), 
                            10.0f, 
                            45.0f);
  cogl_path_close ();
  cogl_path_fill ();

  g_signal_stop_emission_by_name (rect, "paint");
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

int main(int argc, char *argv[]) {
  glEnable(GL_MULTISAMPLE);
  glEnable(GL_LINE_SMOOTH);
  clutter_x11_set_use_argb_visual (TRUE);
  int lol = clutter_init (&argc, &argv);

  ClutterColor stage_color = { 0, 0, 0, 255 };

  stage = clutter_stage_get_default();
  clutter_actor_set_size (stage, 512, 512);
  clutter_stage_set_user_resizable (CLUTTER_STAGE (stage), TRUE);
  clutter_stage_set_use_alpha (CLUTTER_STAGE (stage), TRUE);
  clutter_stage_set_color (CLUTTER_STAGE(stage), &stage_color);
  clutter_actor_set_opacity (stage, 0);
  
  ClutterColor red = { 255, 0, 0, 128 };
  ClutterColor green = { 0, 255, 0, 128 };
  ClutterColor blue = { 0, 0, 255, 128 };
  ClutterColor yellow = { 255, 255, 0, 128 };
  ClutterColor cyan = { 0, 255, 255, 128 };
  ClutterColor purple = { 255, 0, 255, 128 };

  rect1 = create_rect(red);
  rect2 = create_rect(red);
  rect3 = create_rect(red);
  rect4 = create_rect(red);
  rect5 = create_rect(red);
  rect6 = create_rect(red);
  rect7 = create_rect(red);
  rect8 = create_rect(red);

  g_signal_connect (rect1, "paint", G_CALLBACK (rect_paint), NULL);
  g_signal_connect (rect2, "paint", G_CALLBACK (rect_paint), NULL);
  g_signal_connect (rect3, "paint", G_CALLBACK (rect_paint), NULL);
  g_signal_connect (rect4, "paint", G_CALLBACK (rect_paint), NULL);
  g_signal_connect (rect5, "paint", G_CALLBACK (rect_paint), NULL);
  g_signal_connect (rect6, "paint", G_CALLBACK (rect_paint), NULL);
  g_signal_connect (rect7, "paint", G_CALLBACK (rect_paint), NULL);
  g_signal_connect (rect8, "paint", G_CALLBACK (rect_paint), NULL);

  g_signal_connect (stage, "paint", G_CALLBACK (on_stage_pre_paint), NULL);
  g_signal_connect_after (stage, "paint", G_CALLBACK (on_stage_post_paint), NULL);
  g_signal_connect (stage, "destroy", G_CALLBACK (clutter_main_quit), NULL);

  g_signal_connect (stage, "button-press-event", G_CALLBACK (on_stage_button_press), NULL);
  clutter_stage_set_title(CLUTTER_STAGE(stage), "Spinny boxes ahoy!");
  clutter_actor_show (stage);

  clutter_main ();

  return EXIT_SUCCESS;
}
